#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

// Node dalam Trie
struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;
    TrieNode() : isEndOfWord(false) {}
};

// Fungsi untuk memasukkan kata ke dalam Trie
void insertWord(TrieNode*& root, string word) {
    TrieNode* node = root;
    for (char c : word) {
        if (!node->children.count(c)) {
            node->children[c] = new TrieNode();
        }
        node = node->children[c];
    }
    node->isEndOfWord = true;
}

void insertCompactTrieFromFile(TrieNode* root, const string& filename) {
    ifstream file(filename);
    string word;

    if (file.is_open()) {
        while (getline(file, word)) {
            insertWord(root, word);
        }
        file.close();
    } else {
        cerr << "Failed to open file: " << filename << endl;
    }
}


// Fungsi untuk menemukan node terakhir dari suatu prefix
TrieNode* findNode(TrieNode* root, string prefix) {
    TrieNode* node = root;
    for (char c : prefix) {
        if (!node->children.count(c)) return nullptr;
        node = node->children[c];
    }
    return node;
}

// Fungsi rekursif untuk membangun semua kata yang memiliki prefix tertentu
void buildWords(TrieNode* node, vector<string>& results, string prefix) {
    if (node->isEndOfWord) {
        results.push_back(prefix);
    }
    for (const auto& pair : node->children) {
        char c = pair.first;
        TrieNode* child = pair.second;
        buildWords(child, results, prefix + c);
    }
}

// Fungsi untuk mencari semua kata yang memiliki prefix tertentu
vector<string> autocomplete(TrieNode* root, string prefix) {
    vector<string> results;
    TrieNode* node = findNode(root, prefix);
    if (node) {
        buildWords(node, results, prefix);
    }
    return results;
}

int main() {
    TrieNode* root = new TrieNode();

    insertCompactTrieFromFile(root, "C:/POLITEKNIK NEGERI BANDUNG/SEMESTER 2/SDA/Praktik/Tugas Besar/SOURCE CODE/kata-dasar.txt");
    string prefix = "a";
    vector<string> results = autocomplete(root, prefix);
    sort(results.begin(), results.end());

    cout << "Autocomplete suggestions for '" << prefix << "': " << endl;
    for (string word : results) {
        cout << word << endl;
    }

    cin.get(); // Menunggu input dari pengguna sebelum keluar
    return 0;
}