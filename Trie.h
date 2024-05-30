#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

//////////////////////////////////////////////
/*
    *** Start Struktur Data ***
*/
struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;
    TrieNode() : isEndOfWord(false) {}
};

typedef struct Node
{
    string data;
    Node* next;
    Node(const string& kata) : data(kata),  next(nullptr){}
}tempKata;

extern tempKata* headTemp;
extern tempKata* tailTemp;
/*
    *** End Struktur Data ***
*/
////////////////////////////////////////////////

////////////////////////////////////////////////
/*
    *** Metode untuk Linked list ***
*/
// Fungsi untuk menambahkan kata-kata sementara ke dalam Linked List
void addWordTemp(const string& word);

// Fungsi untuk menampilkan kata-kata sementara dalam Double Linked List
void displayWordsTemp();

//Fungsi untuk menghapus elemen linked list
void deleteListTemp();


/*
    *** Metode untuk Trie ***
*/
// Fungsi untuk memasukkan kata ke dalam Trie
void insertWord(TrieNode*& root, string word);

// Fungsi untuk membaca kata-kata dari file dan memasukkannya ke dalam Trie
void insertCompactTrieFromFile(TrieNode* root, const string& filename);

// Fungsi untuk menemukan node terakhir dari suatu prefix
TrieNode* findNode(TrieNode* root, string prefix);

// Fungsi rekursif untuk membangun semua kata yang memiliki prefix tertentu
void buildWords(TrieNode* node, vector<string>& results, string prefix);

// Fungsi untuk mencari semua kata yang memiliki prefix tertentu
vector<string> autocomplete(TrieNode* root, string prefix);


/*
    *** Metode untuk aplikasi program ***
*/
// Fungsi untuk menampilkan hasil autocomplete kata-kata dalam bahasa Indonesia
void kataDasar(string prefix);

// Fungsi untuk menampilkan hasil autocomplete nama daerah di Indonesia
void kota(string prefix);

// Fungsi untuk menampilkan hasil autocomplete nama-nama orang
void namaOrang(string prefix);

// Fungsi Notepad
void notePad(string prefix);

// Fungsi untuk menyimpan text ke file
void saveWordsToFile(const string& filename);

// Fungsi untuk mengelola menu
void menu();
////////////////////////////////////////////////

#endif