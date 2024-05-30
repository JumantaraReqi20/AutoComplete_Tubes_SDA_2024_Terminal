#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>
#include "conio.h"
#include "Trie.h"

using namespace std;

tempKata* headTemp = nullptr;
tempKata* tailTemp = nullptr;

// Fungsi untuk menambahkan kata-kata sementara ke dalam Linked List
void addWordTemp(const string& word) {
    tempKata* newNode = new tempKata(word);

    if (headTemp == nullptr) {
        headTemp = newNode;
        tailTemp = newNode;
    } else {
        tailTemp->next = newNode;
        tailTemp = newNode;
    }
}

// Fungsi untuk menampilkan kata-kata sementara dalam Double Linked List
void displayWordsTemp() {
    tempKata* current = headTemp;
    while (current != nullptr) {
        cout << current->data;
        if (current->next != nullptr) {
            cout << " ";
        }
        current = current->next;
    }
}

//Fungsi untuk menghapus elemen linked list
void deleteListTemp() {
    tempKata* current = headTemp;
    while (current != nullptr) {
        tempKata* temp = current;
        current = current->next;
        delete temp;
    }
    headTemp = nullptr;
    tailTemp = nullptr;
}

// Fungsi untuk memasukkan kata ke dalam Trie
void insertWord(TrieNode*& root, string word) {
    TrieNode* node = root; 
    // Loop melalui setiap karakter yang terdapat dalam kata
    for (char c : word) {
        // Pengecekan keberadaan karakter dalam node anak.
        if (!node->children.count(c)) {
            node->children[c] = new TrieNode(); 
        }
        node = node->children[c]; 
    }
    node->isEndOfWord = true; // Menandai node terakhir sebagai akhir dari kata
}

// Fungsi untuk membaca kata-kata dari file dan memasukkannya ke dalam Trie
void insertCompactTrieFromFile(TrieNode* root, const string& filename) {
    ifstream file(filename); // Membuka file kata-kata atau nama daerah atau nama orang
    string word; 

   
    if (file.is_open()) {
        // Loop melalui setiap baris yang ada di dalam file
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
    // Loop melalui setiap karakter dalam prefix
    for (char c : prefix) {
        if (!node->children.count(c)) return nullptr; // Jika karakter tidak tersedia dalam node anak, maka kembalikan null
        node = node->children[c]; 
    }
    return node; 
}

// Fungsi rekursif untuk membangun semua kata yang memiliki prefix tertentu
void buildWords(TrieNode* node, vector<string>& results, string prefix) {
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
    vector<string> results; 
    TrieNode* node = findNode(root, prefix); // Temukan node terakhir dari prefix untuk kemudian disimpan ke dalam 'node'

    if (node) {
        buildWords(node, results, prefix); // Panggil fungsi rekursif untuk membangun kata-kata
    } 
    return results; 
}

// Fungsi untuk menampilkan hasil autocomplete kata-kata dalam bahasa Indonesia
void kataDasar(string prefix) {
    TrieNode* root = new TrieNode();
    insertCompactTrieFromFile(root, "./source/kata-dasar.txt");

    // mengubah semua char menjadi lowercase
    transform(prefix.begin(), prefix.end(), prefix.begin(), [](unsigned char c) {
        return tolower(c);
    });

    vector<string> results = autocomplete(root, prefix);
    sort(results.begin(), results.end());
    bool shouldExit = false;
    int keluar = 0;

    size_t index = 0;
    size_t panjang = results.size();
    if (panjang > 0){
        while (!shouldExit){  
            system("cls");
            cout << "Berikut ini kata-kata yang berawalan '" << prefix << "': " << endl;
            if (headTemp == nullptr){
                cout << ">>";
            } else {
                displayWordsTemp();
            }

            cout << " " << results[index];
            while (true) {
                char ch = ((char)_getch()); // Menggunakan getch() untuk menangkap input tanpa enter
                if (ch == 9) { // 'Tab' (kode ASCII 9)
                    index = (index + 1) % panjang;
                    break; 
                } else if (ch == 32) { // 'Spasi' (kode ASCII 13)
                    addWordTemp(results[index]);
                    shouldExit = true; 
                    break;
                } else if (ch == 13){ // 'Enter' (kode ASCII 13)
                    keluar = 1;
                    shouldExit = true;
                    break;
                }
            }
        }
        if (keluar == 1){
            deleteListTemp();
            menu();
        }
    } else {
        cout << "Kata tidak terdaftar dalam KBBI!" << endl;
        cout << "Masukkan kata yang benar >> ";
    }
}

// Fungsi untuk menampilkan hasil autocomplete nama daerah di Indonesia
void kota(string prefix) {
    TrieNode* root = new TrieNode();

    insertCompactTrieFromFile(root, "./source/kota.txt");

    // Mengubah char pertama menjadi uppercase.
    prefix[0] = static_cast<char>(toupper(prefix[0]));
    vector<string> results = autocomplete(root, prefix);
    sort(results.begin(), results.end());

    bool shouldExit = false;
    int keluar = 0;

    size_t index = 0;
    size_t panjang = results.size();
    if (panjang > 0){
        while (!shouldExit){  
            system("cls");

            cout << "Berikut ini kota-kota yang berawalan '" << prefix << "': " << endl;
            displayWordsTemp();
            
            cout << " " << results[index];
            while (true) {
                char ch = ((char)_getch()); // Menggunakan getch() untuk menangkap input tanpa enter
                if (ch == 9) { // 'Tab' (kode ASCII 9)
                    index = (index + 1) % panjang;
                    break; 
                } else if (ch == 32) { // 'Spasi' (kode ASCII 13)
                    addWordTemp(results[index]);
                    shouldExit = true; 
                    break;
                } else if (ch == 13){ // 'Enter' (kode ASCII 13)
                    keluar = 1;
                    shouldExit = true;
                    break;
                }
            }
        
        }
        if (keluar == 1){
            deleteListTemp();
            menu();
        }
    } else {
        cout << "Kata tidak terdaftar dalam KBBI!" << endl;
        cout << "Masukkan kata yang benar >> ";
    }
}

// Fungsi untuk menampilkan hasil autocomplete nama-nama orang
void namaOrang(string prefix) {
    TrieNode* root = new TrieNode();

    insertCompactTrieFromFile(root, "./source/namaOrang.txt");

    // mengubah semua char menjadi lowercase.
    transform(prefix.begin(), prefix.end(), prefix.begin(), [](unsigned char c){ return tolower(c); });
    vector<string> results = autocomplete(root, prefix);
    sort(results.begin(), results.end());

    bool shouldExit = false;
    int keluar = 0;

    size_t index = 0;
    size_t panjang = results.size();
    if (panjang > 0){
        while (!shouldExit){  
            system("cls");

        cout << "Berikut ini nama-nama yang berawalan '" << prefix << "': " << endl;
        displayWordsTemp();
        
            cout << " " << results[index];
            while (true) {
                char ch = ((char)_getch()); // Menggunakan getch() untuk menangkap input tanpa enter
                if (ch == 9) { // 'Tab' (kode ASCII 9)
                    index = (index + 1) % panjang;
                    break; 
                } else if (ch == 32) { // 'Spasi' (kode ASCII 13)
                    addWordTemp(results[index]);
                    shouldExit = true; 
                    break;
                } else if (ch == 13){ // 'Enter' (kode ASCII 13)
                    keluar = 1;
                    shouldExit = true;
                    break;
                }
            }
        
        }
        if (keluar == 1){
            deleteListTemp();
            menu();
        }   
    } else {
        cout << "Kata tidak terdaftar dalam KBBI!" << endl;
        cout << "Masukkan kata yang benar >> ";
    }
}

void saveWordsToFile(const string& filename) {
    ofstream outFile(filename); // Membuka file untuk output

    if (!outFile) {
        cerr << "Error: File could not be opened." << endl;
        return;
    }

    Node* current = headTemp;
    while (current != nullptr) {
        outFile << current->data << " "; // Menulis setiap kata ke file
        current = current->next;
    }

    outFile.close(); // Menutup file
    cout << "Words have been saved to " << filename << endl;
    getch();
}

void notePad(string prefix) {
    TrieNode* root = new TrieNode();
    insertCompactTrieFromFile(root, "./source/kata-dasar.txt");
    insertCompactTrieFromFile(root, "./source/kota.txt");
    insertCompactTrieFromFile(root, "./source/namaOrang.txt");

    vector<string> results = autocomplete(root, prefix);
    sort(results.begin(), results.end());
    
    bool shouldExit = false;
    int keluar = 0;

    size_t index = 0;
    size_t panjang = results.size();
    if (panjang > 0){
        while (!shouldExit){  
            system("cls");

            cout << "Tekan tombol Esc untuk menyimpan tulisan!" << endl;
            displayWordsTemp();
                cout << " " << results[index];
                while (true) {
                    char ch = ((char)_getch()); // Menggunakan getch() untuk menangkap input tanpa enter
                    if (ch == 9) { // 'Tab' (kode ASCII 9)
                        index = (index + 1) % panjang;
                        break; 
                    } else if (ch == 32) { // 'Spasi' (kode ASCII 13)
                        addWordTemp(results[index]);
                        shouldExit = true; 
                        break;
                    } else if(ch == 13){ // 'Enter' (kode ASCII 13)
                        addWordTemp("\n");
                        shouldExit = true;
                        break;
                    } else if (ch == 27){ // 'Esc' (kode ASCII 27)
                        keluar = 1;
                        addWordTemp(results[index]);
                        string namaFile;
                        cout << "\nMasukkan nama file >> "; cin >> namaFile;
                        saveWordsToFile(namaFile + ".txt");
                        shouldExit = true;
                        break;
                    }
                } 
        }
        if (keluar == 1){
            deleteListTemp();
            menu();
        } 
    } else {
        cout << "Kata tidak terdaftar dalam KBBI!" << endl;
        cout << "Masukkan kata yang benar >> ";
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
        cout << "|         (4) Magic Notepad (sekali ngedip)      |" << endl;
        cout << "|         (0) Keluar                             |" << endl;
        cout << "|            Masukkan beberapa huruf             |" << endl;
        cout << "|            Temukan keajaiban! ('<')            |" << endl;
        cout << " ================================================ " << endl;
        cout << "Pilih menu: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Masukkan beberapa huruf, dan kamu akan menemukan keajaiban ('<') !" << endl;
                cout << "Ketik di sini : ";
                while (true){
                    string prefix;
                    // cout << " ";
                    cin >> prefix;
                    kataDasar(prefix);
                }
                break;
            case 2:
                cout << "Masukkan beberapa huruf, dan kamu akan menemukan keajaiban ('<') !" << endl;
                cout << "Ketik di sini : ";
                while (true){
                    string prefix;
                    cout << " ";
                    cin >> prefix;
                    namaOrang(prefix);
                }
                break;
            case 3:
                cout << "Masukkan beberapa huruf, dan kamu akan menemukan keajaiban ('<') !" << endl;
                cout << "Ketik di sini : ";
                while (true){
                    string prefix;
                    cout << " ";
                    cin >> prefix;
                    kota(prefix);
                }
                break;
            case 4:
                cout << "Selamat datang di magic Notepad !" << endl;
                cout << ">> ";
                while (true){
                    string prefix;
                    // cout << " ";
                    cin >> prefix;
                    notePad(prefix);
                }
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

