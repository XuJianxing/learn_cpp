/*
 * @lc app=leetcode.cn id=208 lang=cpp
 *
 * [208] 实现 Trie (前缀树)
 *
 * https://leetcode.cn/problems/implement-trie-prefix-tree/description/
 *
 * algorithms
 * Medium (72.52%)
 * Likes:    1993
 * Dislikes: 0
 * Total Accepted:    625.2K
 * Total Submissions: 862.9K
 * Testcase Example:  '["Trie","insert","search","search","startsWith","insert","search"]\n' +
  '[[],["apple"],["apple"],["app"],["app"],["app"],["app"]]'
 *
 * Trie（发音类似 "try"）或者说 前缀树
 * 是一种树形数据结构，用于高效地存储和检索字符串数据集中的键。这一数据结构有相当多的应用情景，例如自动补全和拼写检查。
 * 
 * 请你实现 Trie 类：
 * 
 * 
 * Trie() 初始化前缀树对象。
 * void insert(String word) 向前缀树中插入字符串 word 。
 * boolean search(String word) 如果字符串 word 在前缀树中，返回 true（即，在检索之前已经插入）；否则，返回
 * false 。
 * boolean startsWith(String prefix) 如果之前已经插入的字符串 word 的前缀之一为 prefix ，返回 true
 * ；否则，返回 false 。
 * 
 * 
 * 
 * 
 * 示例：
 * 
 * 
 * 输入
 * ["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
 * [[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
 * 输出
 * [null, null, true, false, true, null, true]
 * 
 * 解释
 * Trie trie = new Trie();
 * trie.insert("apple");
 * trie.search("apple");   // 返回 True
 * trie.search("app");     // 返回 False
 * trie.startsWith("app"); // 返回 True
 * trie.insert("app");
 * trie.search("app");     // 返回 True
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 1 <= word.length, prefix.length <= 2000
 * word 和 prefix 仅由小写英文字母组成
 * insert、search 和 startsWith 调用次数 总计 不超过 3 * 10^4 次
 * 
 * 
 */

#include <string>
#include <vector>

using namespace std;

// @lc code=start
// 每个节点：26 个字母各对应一个子节点指针 + 是否为某个单词的结尾
struct TrieNode {
    TrieNode* next[26];
    bool isEnd;

    TrieNode() : isEnd(false) {
        for (int i = 0; i < 26; ++i) {
            next[i] = nullptr;
        }
    }
};

class Trie {
private:
    TrieNode* root;

    // 从根出发沿字符走，走不通返回 nullptr
    TrieNode* find(const string& s) {
        TrieNode* cur = root;
        for (char c : s) {
            int idx = c - 'a';
            if (cur->next[idx] == nullptr) {
                return nullptr;
            }
            cur = cur->next[idx];
        }
        return cur;
    }

    // OUTER: 与本题无关，但是其他用到前缀树结构的地方需要的接口
    // 先序遍历 node 子树，按字典序收集至多 limit 个单词（a->z 天然有序）
    void collect(TrieNode* node, string& path, vector<string>& out, int limit) {
        if ((int)out.size() >= limit) {
            return;
        }
        if (node->isEnd) {
            out.push_back(path);
        }
        for (int i = 0; i < 26; ++i) {
            if (node->next[i] == nullptr) {
                continue;
            }
            path.push_back('a' + i);
            collect(node->next[i], path, out, limit);
            path.pop_back();
            if ((int)out.size() >= limit) {
                return;
            }
        }
    }

    void destroy(TrieNode* node) {
        if (node == nullptr) {
            return;
        }
        for (int i = 0; i < 26; ++i) {
            destroy(node->next[i]);
        }
        delete node;
    }

public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        destroy(root);
    }

    void insert(string word) {
        TrieNode* cur = root;
        for (char c : word) {
            int idx = c - 'a';
            if (cur->next[idx] == nullptr) {
                cur->next[idx] = new TrieNode();
            }
            cur = cur->next[idx];
        }
        cur->isEnd = true;  // 最后一个节点打上"单词结尾"标记
    }

    bool search(string word) {
        TrieNode* node = find(word);
        return node != nullptr && node->isEnd;
    }

    bool startsWith(string prefix) {
        return find(prefix) != nullptr;
    }

    // OUTER: 与本题无关，但是其他用到前缀树结构的地方需要的接口
    // 返回以 prefix 为前缀、字典序最小的至多 limit 个单词（用于搜索推荐）
    vector<string> suggest(const string& prefix, int limit) {
        vector<string> out;
        TrieNode* node = find(prefix);
        if (node == nullptr) {
            return out;
        }
        string path = prefix;
        collect(node, path, out, limit);
        return out;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
// @lc code=end

