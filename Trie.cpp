#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "conio.h"

using namespace std;

// Node dalam Trie
struct TrieNode {
    unordered_map<char, TrieNode*> children; // Anak-anak dari node akan diimpelementasikan dengan map
    bool isEndOfWord; // Penanda akhir sebuah kata
    TrieNode() : isEndOfWord(false) {} // Konstruktor default
};

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
void kataDasar() {
    TrieNode* root = new TrieNode();

    insertCompactTrieFromFile(root, "D:/POLBAN/Semester 2/Struktur Data dan Algoritma/Big Project/AutoComplete_Tubes_SDA_2024/kata-dasar.txt");
    string prefix;
    cout << "Masukkan beberapa huruf, dan kamu akan menemukan keajaiban ('<') !\n";
    cout << "Ketik di sini : \n";
    cin >> prefix;
    // mengubah semua char menjadi lowercase.
    transform(prefix.begin(), prefix.end(), prefix.begin(), [](unsigned char c){ return tolower(c); });
    vector<string> results = autocomplete(root, prefix);

    cout << "Berikut ini kata-kata yang berawalan '" << prefix << "': " << endl;
    for (string word : results) {
        cout << word << endl;
    }
}

// Fungsi untuk menampilkan hasil autocomplete nama daerah di Indonesia
void kota() {
    TrieNode* root = new TrieNode();

    insertCompactTrieFromFile(root, "D:/POLBAN/Semester 2/Struktur Data dan Algoritma/Big Project/AutoComplete_Tubes_SDA_2024/kota.txt");
    string prefix;
    cout << "Masukkan beberapa huruf, dan kamu akan menemukan keajaiban ('<') !\n";
    cout << "Ketik di sini : \n";
    cin >> prefix;
    // Mengubah char pertama menjadi uppercase.
    prefix[0] = static_cast<char>(prefix[0]);
    vector<string> results = autocomplete(root, prefix);

    cout << "Berikut ini nama kota yang berawalan '" << prefix << "': " << endl;
    for (string word : results) {
        cout << word << endl;
    }
}

// Fungsi untuk menampilkan hasil autocomplete nama-nama orang
void namaOrang() {
    TrieNode* root = new TrieNode();

    insertCompactTrieFromFile(root, "D:/POLBAN/Semester 2/Struktur Data dan Algoritma/Big Project/AutoComplete_Tubes_SDA_2024/namaOrang.txt");
    string prefix;
    cout << "Masukkan beberapa huruf, dan kamu akan menemukan keajaiban ('<') !\n";
    cout << "Ketik di sini : \n";
    cin >> prefix;
    // mengubah semua char menjadi lowercase.
    transform(prefix.begin(), prefix.end(), prefix.begin(), [](unsigned char c){ return tolower(c); });
    vector<string> results = autocomplete(root, prefix);

    cout << "Berikut ini nama-nama orang yang berawalan '" << prefix << "': " << endl;
    for (string word : results) {
        cout << word << endl;
        cin.get();
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

        switch (choice) {
            case 1:
                kataDasar();
                break;
            case 2:
                namaOrang();
                break;
            case 3:
                kota();
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