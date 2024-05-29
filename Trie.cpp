#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>
#include "conio.h"

using namespace std;
void menu();

// Node dalam Trie
struct TrieNode {
    unordered_map<char, TrieNode*> children; // Anak-anak dari node akan diimpelementasikan dengan map
    bool isEndOfWord; // Penanda akhir sebuah kata
    TrieNode() : isEndOfWord(false) {} // Konstruktor default
};
// vector<string> words;

// Node dalam Double Linked List
struct ListNode {
    string data;
    ListNode* prev;
    ListNode* next;

    ListNode(const string& value) : data(value), prev(nullptr), next(nullptr) {}
};

ListNode* head = nullptr;
ListNode* tail = nullptr;

// Fungsi untuk menambahkan kata ke dalam Double Linked List
void addWord(const string& word) {
    ListNode* newNode = new ListNode(word);

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

// Fungsi untuk menampilkan kata-kata dalam Double Linked List
void displayWords() {
    ListNode* current = head;
    while (current != nullptr) {
        cout << current->data;
        if (current->next != nullptr) {
            cout << " ";
        }
        current = current->next;
    }
}

// Fungsi untuk memasukkan kata ke dalam Trie
void insertWord(TrieNode*& root, string word) {
    TrieNode* node = root; // Inisialisasi node dengan root Trie.
    // Loop melalui setiap karakter yang terdapat dalam kata
    for (char c : word) {
        // Pengecekan keberadaan karakter dalam node anak.
        if (!node->children.count(c)) {
            node->children[c] = new TrieNode(); // Jika tidak ada, buat node baru
        }
        node = node->children[c]; // Jika ada, maka pindahkan ke node anak
    }
    node->isEndOfWord = true; // Menandai node terakhir sebagai akhir dari kata
}

// Fungsi untuk membaca kata-kata dari file dan memasukkannya ke dalam Trie
void insertCompactTrieFromFile(TrieNode* root, const string& filename) {
    ifstream file(filename); // Membuka file kata-kata atau nama daerah atau nama orang
    string word; // menyimpan kata dari file

    // Pengecekan file, apakah sudah dibuka?
    if (file.is_open()) {
        // Loop melalui setiap baris yang ada di dalam file
        while (getline(file, word)) {
            insertWord(root, word); // Masukkan kata ke dalam Trie
        }
        file.close(); // Menutup file apabila telah selesai membaca
    } else {
        cerr << "Failed to open file: " << filename << endl; // Menampilkan pesan apabila file tidak berhasil dibuka
    }
}


// Fungsi untuk menemukan node terakhir dari suatu prefix
TrieNode* findNode(TrieNode* root, string prefix) {
    TrieNode* node = root; // Inisialisasi node dengar root Trie
    // Loop melalui setiap karakter dalam prefix
    for (char c : prefix) {
        if (!node->children.count(c)) return nullptr; // Jika karakter tidak tersedia dalam node anak, maka kembalikan null
        node = node->children[c]; // Jika tersedia, pindahkan node ke node anak
    }
    return node; // Mengembalikan node terakhir dari prefix
}

// Fungsi rekursif untuk membangun semua kata yang memiliki prefix tertentu
void buildWords(TrieNode* node, vector<string>& results, string prefix) {
    // Jika node saat ini adalah akhir dari kata
    if (node->isEndOfWord) {
        results.push_back(prefix); // Tambahkan kata ke dalam results
    }
    // Jika belum, maka loop melalui setiap pasangan karakter dan node anak
    for (const auto& pair : node->children) {
        char c = pair.first; // Ambil karakter dari pasangan
        TrieNode* child = pair.second; // Ambil node anak dari pasangan
        buildWords(child, results, prefix + c); // Panggil rekursif buildWords untuk membangun kata-kata
    }
}

// Fungsi untuk mencari semua kata yang memiliki prefix tertentu
vector<string> autocomplete(TrieNode* root, string prefix) {
    vector<string> results; // Vektor untuk menyimpan hasil autocomplete
    TrieNode* node = findNode(root, prefix); // Temukan node terakhir dari prefix untuk kemudian disimpan ke dalam 'node'
    // Jika node telah ditemukan
    if (node) {
        buildWords(node, results, prefix); // Panggil fungsi rekursif untuk membangun kata-kata
    }
    return results; // Kembalikan vektor results
}

// Fungsi untuk menampilkan hasil autocomplete kata-kata dalam bahasa Indonesia
void kataDasar(string prefix) {
    TrieNode* root = new TrieNode();

    insertCompactTrieFromFile(root, "kata-dasar.txt");
    
    // mengubah semua char menjadi lowercase.
    transform(prefix.begin(), prefix.end(), prefix.begin(), [](unsigned char c){ return tolower(c); });

    while (true) {
        vector<string> results = autocomplete(root, prefix);

        sort(results.begin(), results.end());
        bool shouldExit = false;
        for (string word : results) {
            if (shouldExit){
                break;
            }    
            system("cls");
            cout << "Berikut ini kata-kata yang berawalan '" << prefix << "': " << endl;
            displayWords(); 
            cout << " " << word;
            while (true) {
                char ch = ((char)_getch()); // Menggunakan getch() untuk menangkap input tanpa enter
                if (ch == 9) { // 'Tab' (kode ASCII 9)
                    break; 
                } else if (ch == 32) { // 'Spasi' (kode ASCII 32)
                    addWord(word);
                    shouldExit = true; 
                    break;  
                } else if (ch == 13) { // 'Enter' (kode ASCII 13)
                    shouldExit = true;
                    break;
                }
            }
        }

        if (shouldExit) {
            break;
        }

        cout << "Tekan Enter untuk melanjutkan atau character lain untuk keluar: ";
        char ch = ((char)_getch());
        if (ch!= 13) {
            menu();
        }
    }
}

// Fungsi untuk menampilkan hasil autocomplete nama daerah di Indonesia
void kota(string prefix) {
    TrieNode* root = new TrieNode();

    insertCompactTrieFromFile(root, "kota.txt");

    // Mengubah char pertama menjadi uppercase.
    prefix[0] = static_cast<char>(toupper(prefix[0]));
    vector<string> results = autocomplete(root, prefix);

    sort(results.begin(), results.end());
    bool shouldExit = false;
    for (string word : results) {
        if (shouldExit){
            break;
        }    
        system("cls");
        cout << "Berikut ini kata-kata yang berawalan '" << prefix << "': " << endl;
        displayWords(); 
        cout << " " << word;
        while (true) {
            char ch = ((char)_getch()); // Menggunakan getch() untuk menangkap input tanpa enter
            if (ch == 9) { // 'Tab' (kode ASCII 9)
                break; 
            } else if (ch == 32) { // 'Enter' (kode ASCII 13)
                addWord(word);
                shouldExit = true; 
                break;  
            }
        }
    }
}

// Fungsi untuk menampilkan hasil autocomplete nama-nama orang
void namaOrang(string prefix) {
    TrieNode* root = new TrieNode();

    insertCompactTrieFromFile(root, "namaOrang.txt");

    // mengubah semua char menjadi lowercase.
    transform(prefix.begin(), prefix.end(), prefix.begin(), [](unsigned char c){ return tolower(c); });
    vector<string> results = autocomplete(root, prefix);

    sort(results.begin(), results.end());
    bool shouldExit = false;
    for (string word : results) {
        if (shouldExit){
            break;
        }    
        system("cls");
        cout << "Berikut ini kata-kata yang berawalan '" << prefix << "': " << endl;
        displayWords(); 
        cout << " " << word;
        while (true) {
            char ch = ((char)_getch()); // Menggunakan getch() untuk menangkap input tanpa enter
            if (ch == 9) { // 'Tab' (kode ASCII 9)
                break; 
            } else if (ch == 32) { // 'Enter' (kode ASCII 13)
                addWord(word);
                shouldExit = true; 
                break;  
            }
        }
    }   
}

void menu() {
    int choice = 0;

    while (true) {
        system("cls"); // Bersihkan layar (Windows)
        cout << " ================================================ " << endl;
        cout << "|                   BANK KATA                    |" << endl;
        cout << "|                   ---------                    |" << endl;
        cout << "|            Halo, mau nyari apa nih?            |" << endl;
        cout << "|         (1) Kosakata Bahasa Indonesia          |" << endl;
        cout << "|         (2) Nama Orang                         |" << endl;
        cout << "|         (3) Nama Daerah di Indonesia           |" << endl;
        cout << "|         (0) Keluar                             |" << endl;
        cout << "|            Masukkan beberapa huruf             |" << endl;
        cout << "|            Temukan keajaiban! ('<')            |" << endl;
        cout << " ================================================ " << endl;
        cout << "Pilih menu: ";
        cin >> choice;
        string prefix;
        switch (choice) {
            case 1:
                cout << "Masukkan beberapa huruf, dan kamu akan menemukan keajaiban ('<') !" << endl;
                cout << "Ketik di sini : ";
                while (true){
                    cout << " ";
                    cin >> prefix;
                    kataDasar(prefix);
                }
                break;
            case 2:
                cout << "Masukkan beberapa huruf, dan kamu akan menemukan keajaiban ('<') !" << endl;
                cout << "Ketik di sini : ";
                while (true){
                    cout << " ";
                    cin >> prefix;
                    namaOrang(prefix);
                }
                break;
            case 3:
                while (true){
                    cout << " ";
                    cin >> prefix;
                    kota(prefix);
                }
                break;
            case 0:
                exit(0);
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }

        // Tunggu input dari pengguna
        cout << "Tekan tombol apa saja untuk melanjutkan...";
        getch();
        getchar();
    }
}

int main() {
    menu();

    cin.get(); // Menunggu input dari pengguna sebelum keluar
    return 0;
}