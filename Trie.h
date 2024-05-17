#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// Node dalam Trie
struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;
    TrieNode() : isEndOfWord(false) {}
};

/*  Prosedur untuk memasukkan setiap huruf dari kata ke tree    */
void insertWord(TrieNode*& root, string word);

/*  Prosedur untuk memasukkan setiap kata dari sebuah file ke tree  */
void insertCompactTrieFromFile(TrieNode* root, const string& filename);

/*  Fungsi untuk mencari node berdasarkan prefix yang diinputkan oleh user  */
TrieNode* findNode(TrieNode* root, string prefix);

/*  Prosedur untuk membentuk kata yang mungkin terbentuk berdasarkan prefiks yang diinputkan oleh user   */
void buildWords(TrieNode* node, vector<string>& results, string prefix);

/*  Fungsi untuk mengumpulkan dan mengembalikan kata yang mungkin terbentuk dari prefiks yang sudah diinputkan oleh user  */
vector<string> autocomplete(TrieNode* root, string prefix);

#endif