// LoginStateMachine + LoginController 完整可编译示例
// 设计要点（对应历史讨论）：
// 1. LoginStateMachine 是纯引擎：只认状态+事件+合法转移关系，Action 用 std::function<void()>，
//    不 #include 任何业务头文件，彻底通用可复用。
// 2. LoginController 在构造阶段（装配期）一次性把业务 lambda 挂到各转移 / entry action 上。
// 3. 运行阶段外部只调用语义化接口（submitCredentials/onAuthSuccess/...），
//    内部转成 fsm_.fire(event)，不需要外部再 switch/if 复查状态。
//
// 编译：g++ -std=c++17 login_state_machine_demo.cpp -o demo && ./demo

#include <cstdio>
#include <functional>
#include <map>
#include <stdexcept>
#include <string>

// =====================================================================
// 第一层：纯引擎状态机（不感知任何业务语义）
// =====================================================================

enum class LoginState {
    Idle,
    Authenticating,
    LoggedIn,
    Failed,
    Locked
};

enum class LoginEvent {
    SubmitCredentials,
    AuthSuccess,
    AuthFailure,
    Retry,
    Logout,
    TooManyFailures
};

inline const char* toString(LoginState s) {
    switch (s) {
        case LoginState::Idle:           return "Idle";
        case LoginState::Authenticating: return "Authenticating";
        case LoginState::LoggedIn:       return "LoggedIn";
        case LoginState::Failed:         return "Failed";
        case LoginState::Locked:         return "Locked";
    }
    return "Unknown";
}

inline const char* toString(LoginEvent e) {
    switch (e) {
        case LoginEvent::SubmitCredentials: return "SubmitCredentials";
        case LoginEvent::AuthSuccess:       return "AuthSuccess";
        case LoginEvent::AuthFailure:       return "AuthFailure";
        case LoginEvent::Retry:             return "Retry";
        case LoginEvent::Logout:            return "Logout";
        case LoginEvent::TooManyFailures:   return "TooManyFailures";
    }
    return "Unknown";
}

class LoginStateMachine {
public:
    using Action = std::function<void()>;

    explicit LoginStateMachine(LoginState initial = LoginState::Idle)
        : state_(initial) {}

    // 装配期：注册一条合法转移及其伴随动作（可为空 action）
    void addTransition(LoginState from, LoginEvent event, LoginState to,
                        Action action = nullptr) {
        transitions_[{from, event}] = {to, std::move(action)};
    }

    // 装配期：注册进入某状态时统一触发的动作（每个状态只需写一次）
    void addEntryAction(LoginState state, Action action) {
        entryActions_[state] = std::move(action);
    }

    LoginState state() const { return state_; }

    // 运行期：唯一驱动入口。查表转移成功后自动执行 transition action 和 entry action。
    // 非法转移返回 false，不改变状态（可按需改为抛异常）。
    bool fire(LoginEvent event) {
        auto it = transitions_.find({state_, event});
        if (it == transitions_.end()) {
            std::printf("[FSM] 拒绝非法转移: state=%s, event=%s\n",
                        toString(state_), toString(event));
            return false;
        }

        const LoginState from = state_;
        const LoginState to = it->second.first;
        const Action& transitionAction = it->second.second;

        std::printf("[FSM] 转移: %s --(%s)--> %s\n",
                    toString(from), toString(event), toString(to));

        state_ = to;

        if (transitionAction) {
            transitionAction();
        }
        auto entryIt = entryActions_.find(to);
        if (entryIt != entryActions_.end() && entryIt->second) {
            entryIt->second();
        }
        return true;
    }

private:
    LoginState state_;
    std::map<std::pair<LoginState, LoginEvent>, std::pair<LoginState, Action>> transitions_;
    std::map<LoginState, Action> entryActions_;
};

// =====================================================================
// 假设的业务依赖（网络请求、UI、日志），仅用于演示注入点
// =====================================================================

struct Credentials {
    std::string username;
    std::string password;
};

class NetworkClient {
public:
    // 模拟异步发送登录请求；真实场景中回调会在网络线程/事件循环里调用
    // onSuccess / onFailure
    void sendLoginRequest(const Credentials& cred,
                           std::function<void()> onSuccess,
                           std::function<void()> onFailure) {
        std::printf("[Network] 发送登录请求: user=%s\n", cred.username.c_str());
        // demo 里用简单规则模拟服务端返回，替换成真实异步调用即可
        if (cred.password == "correct") {
            onSuccess();
        } else {
            onFailure();
        }
    }
};

class UiNotifier {
public:
    void showAuthenticating() { std::printf("[UI] 显示登录中...\n"); }
    void showLoginSuccess()   { std::printf("[UI] 登录成功，跳转首页\n"); }
    void showLoginFailed(int failCount) {
        std::printf("[UI] 登录失败，第 %d 次\n", failCount);
    }
    void showAccountLocked()  { std::printf("[UI] 账号已锁定，请稍后重试\n"); }
    void showIdle()           { std::printf("[UI] 返回登录首页\n"); }
};

// =====================================================================
// 第二层：装配期绑定业务动作的 Controller
// =====================================================================

class LoginController {
public:
    LoginController(NetworkClient& networkClient, UiNotifier& ui,
                     int maxFailCount = 3)
        : networkClient_(networkClient),
          ui_(ui),
          maxFailCount_(maxFailCount),
          fsm_(LoginState::Idle) {
        wireTransitions();
        wireEntryActions();
    }

    // ---- 对外暴露的语义化接口（外部不感知 fire/state，也无需 switch 复查）----

    void submitCredentials(const Credentials& cred) {
        pendingCredentials_ = cred;
        fsm_.fire(LoginEvent::SubmitCredentials);
    }

    void retry() {
        fsm_.fire(LoginEvent::Retry);
    }

    void logout() {
        fsm_.fire(LoginEvent::Logout);
    }

    LoginState currentState() const { return fsm_.state(); }

private:
    // 装配期：把状态转移与真实业务逻辑绑定
    void wireTransitions() {
        // Idle --SubmitCredentials--> Authenticating：发起网络请求
        fsm_.addTransition(
            LoginState::Idle, LoginEvent::SubmitCredentials, LoginState::Authenticating,
            [this] {
                networkClient_.sendLoginRequest(
                    pendingCredentials_,
                    [this] { fsm_.fire(LoginEvent::AuthSuccess); },
                    [this] { fsm_.fire(LoginEvent::AuthFailure); });
            });

        // Authenticating --AuthSuccess--> LoggedIn
        fsm_.addTransition(LoginState::Authenticating, LoginEvent::AuthSuccess,
                            LoginState::LoggedIn);

        // Authenticating --AuthFailure--> Failed：转移动作只做计数，
        // 不在此处递归触发下一个事件（否则会在 Failed 的 entry action 执行前
        // 就跳到 Locked，导致日志时序错乱、Failed 状态被"闪过"）。
        // 是否连锁触发 TooManyFailures 的判断放到 Failed 的 entry action 里，
        // 此时 Failed 状态已经完整稳定建立。
        fsm_.addTransition(
            LoginState::Authenticating, LoginEvent::AuthFailure, LoginState::Failed,
            [this] { ++failCount_; });

        // Failed --Retry--> Authenticating：重新发起请求
        fsm_.addTransition(
            LoginState::Failed, LoginEvent::Retry, LoginState::Authenticating,
            [this] {
                networkClient_.sendLoginRequest(
                    pendingCredentials_,
                    [this] { fsm_.fire(LoginEvent::AuthSuccess); },
                    [this] { fsm_.fire(LoginEvent::AuthFailure); });
            });

        // Failed --TooManyFailures--> Locked
        fsm_.addTransition(LoginState::Failed, LoginEvent::TooManyFailures,
                            LoginState::Locked);

        // LoggedIn --Logout--> Idle：重置失败计数
        fsm_.addTransition(
            LoginState::LoggedIn, LoginEvent::Logout, LoginState::Idle,
            [this] { failCount_ = 0; });
    }

    // 装配期：进入某状态时统一触发的 UI 动作，只需写一次
    void wireEntryActions() {
        fsm_.addEntryAction(LoginState::Authenticating,
                             [this] { ui_.showAuthenticating(); });
        fsm_.addEntryAction(LoginState::LoggedIn,
                             [this] { ui_.showLoginSuccess(); });
        fsm_.addEntryAction(LoginState::Failed,
                             [this] {
                                 ui_.showLoginFailed(failCount_);
                                 // Failed 状态已稳定建立后再判断是否连锁触发锁定，
                                 // 保证 Failed 的 UI 提示一定先于 Locked 出现。
                                 if (failCount_ >= maxFailCount_) {
                                     fsm_.fire(LoginEvent::TooManyFailures);
                                 }
                             });
        fsm_.addEntryAction(LoginState::Locked,
                             [this] { ui_.showAccountLocked(); });
        fsm_.addEntryAction(LoginState::Idle,
                             [this] { ui_.showIdle(); });
    }

    NetworkClient& networkClient_;
    UiNotifier& ui_;
    int maxFailCount_;
    int failCount_ = 0;
    Credentials pendingCredentials_;
    LoginStateMachine fsm_;
};

// =====================================================================
// 演示运行
// =====================================================================

int main() {
    NetworkClient network;
    UiNotifier ui;
    LoginController controller(network, ui, /*maxFailCount=*/3);

    std::printf("\n=== 场景1：密码错误连续3次 -> 锁定 ===\n");
    controller.submitCredentials({"alice", "wrong"});
    controller.retry();
    controller.retry();
    std::printf("最终状态: %s\n", toString(controller.currentState()));

    std::printf("\n=== 场景2：新建一个controller，密码正确 -> 登录成功 -> 登出 ===\n");
    LoginController controller2(network, ui, 3);
    controller2.submitCredentials({"bob", "correct"});
    std::printf("最终状态: %s\n", toString(controller2.currentState()));
    controller2.logout();
    std::printf("登出后状态: %s\n", toString(controller2.currentState()));

    std::printf("\n=== 场景3：非法操作被状态机拒绝（Idle状态下直接logout）===\n");
    LoginController controller3(network, ui, 3);
    controller3.logout(); // Idle 状态下没有 Logout 转移，fire() 内部会打印拒绝日志并返回 false
    std::printf("状态未变化: %s\n", toString(controller3.currentState()));

    return 0;
}
