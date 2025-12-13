#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib> // Random
#include <ctime>   // Time
#include <windows.h> // PENTING: Untuk Warna

using namespace std;

// --- DEFINISI WARNA (Agar kode mudah dibaca) ---
#define RESET   7
#define BLUE    9
#define GREEN   10
#define CYAN    11
#define RED     12
#define PINK    13
#define YELLOW  14

// --- STRUCT DATA ---
struct Player {
    string name;
    int hp;
    int maxHp;
    int gold;
    int potions;
    int currentLevel;
};

struct Monster {
    string name;
    string question;
    int correctAnswer;
    int minDmg;
    int maxDmg;
    int goldReward;
};

// Global Variable
Monster levels[5];

// --- FUNGSI VISUAL (TAMPILAN) ---
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void clearScreen() {
    system("cls");
}

void drawLine(int length, int color) {
    setColor(color);
    for (int i = 0; i < length; i++) cout << "=";
    cout << endl;
    setColor(RESET);
}

// Fitur Keren: Health Bar Visual
void drawHealthBar(int current, int max) {
    cout << "HP: [";
    int totalBars = 20; // Panjang bar
    int filledBars = (current * totalBars) / max;
    
    setColor(current > (max/2) ? GREEN : RED); // Hijau jika sehat, Merah jika kritis
    
    for (int i = 0; i < totalBars; i++) {
        if (i < filledBars) cout << "|";
        else cout << " ";
    }
    setColor(RESET);
    cout << "] " << current << "/" << max << endl;
}

// --- LOGIKA GAME ---
void initGame() {
    // Setup Data Soal & Monster
    levels[0] = {"Slime Logika", "5 + 5 * 2 = ?", 15, 5, 10, 50};
    levels[1] = {"Goblin Aritmatika", "(20 / 2) + (3 * 4) = ?", 22, 10, 20, 75};
    levels[2] = {"Orc Aljabar", "Jika 3x = 27, x = ?", 9, 15, 25, 100};
    levels[3] = {"Golem Modulo", "Sisa bagi dari 10 % 3 adalah?", 1, 20, 35, 150};
    levels[4] = {"Dragon Calculus", "Turunan 5x^2 saat x=2 (Hint: 2*5*x)?", 20, 30, 50, 500};
}

void saveGame(Player *p) {
    ofstream file("savegame.txt");
    if (file.is_open()) {
        file << p->name << endl << p->hp << endl << p->maxHp << endl 
             << p->gold << endl << p->potions << endl << p->currentLevel;
        file.close();
        setColor(YELLOW); cout << "\n>> Progress berhasil disimpan!\n"; setColor(RESET);
    }
}

void loadGame(Player *p) {
    ifstream file("savegame.txt");
    if (file.is_open()) {
        file >> p->name >> p->hp >> p->maxHp >> p->gold >> p->potions >> p->currentLevel;
        file.close();
        setColor(GREEN); cout << "\n>> Save data ditemukan! Selamat datang kembali, " << p->name << ".\n"; setColor(RESET);
    } else {
        setColor(RED); cout << "\n>> Tidak ada save data.\n"; setColor(RESET);
        p->currentLevel = -1; // Indikator gagal load
    }
}

void shopMenu(Player *p) {
    char choice;
    int price = 50;
    
    cout << endl;
    drawLine(40, YELLOW);
    cout << "       MERCHANT (TOKO ITEM)       \n";
    drawLine(40, YELLOW);
    cout << "Pedagang: 'Mau beli Potion? Harganya " << price << " Gold'\n";
    cout << "Gold Kamu: " << p->gold << " G\n";
    cout << "[B] Beli  |  [K] Keluar Toko\n";
    cout << "Pilihan >> "; cin >> choice;

    if (choice == 'b' || choice == 'B') {
        if (p->gold >= price) {
            p->gold -= price;
            p->potions++;
            setColor(GREEN); cout << ">> Pembelian Berhasil! (+1 Potion)\n"; setColor(RESET);
        } else {
            setColor(RED); cout << ">> Gold tidak cukup!\n"; setColor(RESET);
        }
    }
}

void battleArena(Player *p) {
    int answer;
    char action;
    
    while (p->hp > 0 && p->currentLevel < 5) {
        clearScreen();
        Monster m = levels[p->currentLevel];

        // --- VISUAL HEADER ---
        drawLine(50, BLUE);
        cout << "LEVEL " << p->currentLevel + 1 << " - DUNGEON FLOOR\n";
        drawLine(50, BLUE);

        // --- VISUAL STATS ---
        cout << "PLAYER: " << p->name << "\t\tGOLD: " << p->gold << "\tPOTIONS: " << p->potions << endl;
        drawHealthBar(p->hp, p->maxHp);
        
        cout << endl;
        setColor(RED);
        cout << "MONSTER : " << m.name << endl;
        cout << "SOAL    : " << m.question << endl;
        setColor(RESET);
        
        drawLine(50, BLUE);
        cout << "[J] Jawab (Serang)  [H] Heal (30HP)  [S] Save & Quit\n";
        cout << "Aksi kamu >> ";
        cin >> action;

        if (action == 'h' || action == 'H') {
            if (p->potions > 0) {
                p->potions--;
                p->hp += 30;
                if (p->hp > p->maxHp) p->hp = p->maxHp;
                setColor(GREEN); cout << "\n>> Glup.. HP bertambah!\n"; setColor(RESET);
            } else {
                setColor(RED); cout << "\n>> Potion habis! Monster menyerang!\n"; setColor(RESET);
                p->hp -= m.minDmg; // Hukuman
            }
            system("pause");
        } 
        else if (action == 's' || action == 'S') {
            saveGame(p);
            return; // Keluar ke menu
        }
        else if (action == 'j' || action == 'J') {
            cout << "Jawabanmu (Angka): ";
            cin >> answer;

            if (answer == m.correctAnswer) {
                setColor(GREEN);
                cout << "\n>>> BENAR! CRITICAL HIT! <<<\n";
                cout << "Kamu dapat " << m.goldReward << " Gold.\n";
                setColor(RESET);
                
                p->gold += m.goldReward;
                p->currentLevel++;
                
                system("pause");
                if (p->currentLevel < 5) shopMenu(p); // Buka toko tiap naik level
            } else {
                int damage = (rand() % (m.maxDmg - m.minDmg + 1)) + m.minDmg; // RNG
                p->hp -= damage;
                
                setColor(RED);
                cout << "\n>>> SALAH! Kamu terkena " << damage << " damage! <<<\n";
                setColor(RESET);
            }
            system("pause");
        }
    }

    if (p->hp <= 0) {
        setColor(RED);
        cout << "\n=== GAME OVER ===\n";
        cout << "Perjuangan " << p->name << " berakhir disini.\n";
        setColor(RESET);
        remove("savegame.txt"); // Hapus save file (Hardcore mode)
    } else if (p->currentLevel == 5) {
        clearScreen();
        drawLine(50, YELLOW);
        cout << "       SELAMAT! KAMU MENAMATKAN GAME INI       \n";
        cout << "       Sisa Gold: " << p->gold << " | Status: LEGEND\n";
        drawLine(50, YELLOW);
        remove("savegame.txt");
    }
}

// --- MAIN MENU ---
int main() {
    srand(time(0)); // Seed Random
    initGame();
    
    Player hero;
    int choice;

    do {
        clearScreen();
        setColor(CYAN);
        cout << "========================================\n";
        cout << "    THE MATH DUNGEON: VISUAL EDITION    \n";
        cout << "========================================\n";
        setColor(RESET);
        cout << "1. New Game\n";
        cout << "2. Load Game\n";
        cout << "3. Exit\n";
        cout << "Pilihan >> ";
        cin >> choice;

        if (cin.fail()) { // Validasi Input
            cin.clear(); cin.ignore(); choice = 0;
        }

        switch(choice) {
            case 1:
                cout << "\nMasukkan Nama Hero: "; cin >> hero.name;
                hero.hp = 100; hero.maxHp = 100; hero.gold = 0; 
                hero.potions = 1; hero.currentLevel = 0;
                battleArena(&hero);
                break;
            case 2:
                loadGame(&hero);
                if (hero.currentLevel != -1) battleArena(&hero);
                system("pause");
                break;
            case 3:
                cout << "Terima kasih telah bermain.\n";
                break;
        }
    } while (choice != 3);

    return 0;
}