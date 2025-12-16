#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <cmath>
#include <limits>

using namespace std;

struct Char {
    string nick;
    string job;
    int hp, mhp;
    int mp, mmp;
    int duit;
    int pot;
    int xp, mxp;
    int lvl;
    int stage;
    int atk;
    int def;
};

struct Musuh {
    string nama;
    int hp, mhp;
    int atk;
    int xp;
    int duit;
    string art;
};

Musuh listMusuh[10];

void warna(int w) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), w);
}

void cls() { system("cls"); }

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void box(string s, int w) {
    warna(w);
    cout << "==================================================" << endl;
    cout << "| " << s;
    for(int i=0; i < 47 - s.length(); i++) cout << " ";
    cout << "|" << endl;
    cout << "==================================================" << endl;
    warna(15);
}

void loadData() {
    listMusuh[0] = {"Slime Lendir", 30, 30, 5, 20, 10, "(o_o)"};
    listMusuh[1] = {"Goblin Angka", 50, 50, 8, 30, 15, "<(-_-)>"};
    listMusuh[2] = {"Serigala Biner", 80, 80, 12, 45, 25, "/^._.^\\"};
    listMusuh[3] = {"Orc Aljabar", 120, 120, 18, 60, 40, "( O_O )"};
    listMusuh[4] = {"Hantu Geometri", 150, 150, 25, 80, 55, "{ X_X }"};
    listMusuh[5] = {"Golem Fisika", 200, 200, 35, 100, 70, "[ ._. ]"};
    listMusuh[6] = {"Naga Kalkulus", 350, 350, 50, 200, 150, "<( @ )>"};
    listMusuh[7] = {"DEMON KING ERROR", 999, 999, 99, 500, 500, "\\(!!)/"};
}

void cekLvl(Char &p) {
    if (p.xp >= p.mxp) {
        p.xp -= p.mxp;
        p.lvl++;
        p.mxp = p.lvl * 50;
        p.mhp += 20; p.hp = p.mhp;
        p.mmp += 10; p.mp = p.mmp;
        p.atk += 3;
        p.def += 2;

        warna(14);
        cout << "\n\t>>> LEVEL UP! HERO NAIK KE LEVEL " << p.lvl << "! <<<" << endl;
        cout << "\tHP, Mana, Attack, dan Defense meningkat tajam!\n";
        warna(15);
        system("pause");
    }
}

void genSoal(int s, string &tanya, int &jawab) {
    int a = rand() % 10 + 2;
    int b = rand() % 10 + 2;
    int c = rand() % 5 + 1;

    if (s == 0) {
        tanya = to_string(a) + " + " + to_string(b) + " * " + to_string(c) + " = ?";
        jawab = a + (b * c);
    } 
    else if (s == 1) {
        int beda = rand() % 5 + 2;
        int u1 = rand() % 5 + 1;
        tanya = to_string(u1) + ", " + to_string(u1+beda) + ", " + to_string(u1+beda*2) + ", ... (Suku ke-4?)";
        jawab = u1 + beda*3;
    }
    else if (s == 2) {
        jawab = rand() % 15 + 1;
        string bin = "";
        int n = jawab;
        for(int i=0; n>0; i++){    
            bin = to_string(n%2) + bin;    
            n = n/2;    
        }    
        tanya = "Ubah biner " + bin + " ke desimal!";
    }
    else if (s == 3) {
        jawab = rand() % 10 + 1;
        int res = (a * jawab) + b;
        tanya = "Jika " + to_string(a) + "x + " + to_string(b) + " = " + to_string(res) + ", nilai x?";
    }
    else if (s == 4) {
        int m = rand() % 3 + 1;
        int sa = 3 * m;
        int sb = 4 * m;
        jawab = 5 * m;
        tanya = "Segitiga siku alas=" + to_string(sa) + ", tinggi=" + to_string(sb) + ". Sisi miring?";
    }
    else if (s == 5) {
        int m = rand() % 10 + 5;
        int ac = rand() % 5 + 2;
        jawab = m * ac;
        tanya = "Massa benda " + to_string(m) + "kg didorong a=" + to_string(ac) + "m/s2. Gaya (N)?";
    }
    else {
        int k = rand() % 5 + 2;
        int x = 2;
        jawab = 2 * k * x; 
        tanya = "f(x) = " + to_string(k) + "x^2. Hitung f'(2) (Turunan saat x=2)";
    }
}

string getFileName(int slot) {
    return "savegame_" + to_string(slot) + ".txt";
}

string intipSlot(int slot) {
    ifstream f(getFileName(slot));
    string nama;
    if(f.is_open()) {
        getline(f, nama); 
        return nama;
    }
    return "<KOSONG>";
}

void save(Char p) {
    cls();
    box("PILIH SLOT PENYIMPANAN", 11);
    cout << "Slot 1: " << intipSlot(1) << endl;
    cout << "Slot 2: " << intipSlot(2) << endl;
    cout << "Slot 3: " << intipSlot(3) << endl;
    cout << "--------------------------------\n";
    cout << "Pilih Slot (1-3) >> ";
    
    int slot;
    while(!(cin >> slot) || slot < 1 || slot > 3) {
        clearInput();
        cout << "Slot tidak valid! Masukkan angka 1, 2, atau 3 >> ";
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    ofstream f(getFileName(slot));
    if(f.is_open()) {
        f << p.nick << endl << p.job << endl << p.lvl << endl << p.xp << endl << p.mxp << endl;
        f << p.hp << endl << p.mhp << endl << p.mp << endl << p.mmp << endl;
        f << p.atk << endl << p.def << endl << p.duit << endl << p.pot << endl << p.stage;
        f.close();
        warna(10); cout << ">> Game Saved to Slot " << slot << " Successfully!\n"; warna(15);
    } else {
        cout << "Gagal membuka file!\n";
    }

}

bool load(Char &p) {
    cls();
    box("LOAD GAME", 11);
    cout << "Slot 1: " << intipSlot(1) << endl;
    cout << "Slot 2: " << intipSlot(2) << endl;
    cout << "Slot 3: " << intipSlot(3) << endl;
    cout << "--------------------------------\n";
    cout << "Pilih Slot (1-3) >> ";

    int slot;
    while(!(cin >> slot) || slot < 1 || slot > 3) {
        clearInput();
        cout << "Slot tidak valid! Masukkan angka 1, 2, atau 3 >> ";
    }

    ifstream f(getFileName(slot));
    if(f.is_open()) {
        getline(f, p.nick); getline(f, p.job); 
        f >> p.lvl >> p.xp >> p.mxp;
        f >> p.hp >> p.mhp >> p.mp >> p.mmp;
        f >> p.atk >> p.def >> p.duit >> p.pot >> p.stage;
        f.close();
        cout << "Berhasil memuat data " << p.nick << "!\n";
        Sleep(1000);
        return true;
    }
    
    cout << "Slot kosong atau file rusak!\n";
    Sleep(1000);
    return false;
}

void info(Char p) {
    cls();
    box("STATUS CHARACTER", 11);
    cout << "Nama   : " << p.nick << " (" << p.job << ")\n";
    cout << "Level  : " << p.lvl << " (EXP: " << p.xp << "/" << p.mxp << ")\n";
    cout << "Stage  : " << p.stage + 1 << "\n";
    cout << "--------------------------------------------------\n";
    warna(10); cout << "HP     : " << p.hp << "/" << p.mhp << endl;
    warna(9);  cout << "Mana   : " << p.mp << "/" << p.mmp << endl;
    warna(12); cout << "Attack : " << p.atk << endl;
    warna(8);  cout << "Defense: " << p.def << endl;
    warna(14); cout << "Gold   : " << p.duit << " G" << endl;
    warna(15);
    cout << "==================================================" << endl;
    system("pause");
}

void camp(Char &p) {
    while(true) {
        cls();
        box("SAFE ZONE (TOKO & ISTIRAHAT)", 14);
        cout << "[1] Beli Potion (HP+50)    - 50 G\n";
        cout << "[2] Beli Ether (Mana+50)   - 50 G\n";
        cout << "[3] Upgrade Senjata (Atk+5)- 200 G\n";
        cout << "[4] Upgrade Armor (Def+5)  - 200 G\n";
        cout << "[5] Cek Status Hero\n";
        cout << "[6] Save Game\n";
        cout << "[7] Save & Exit (Simpan & Keluar)\n";
        cout << "[0] Kembali Bertualang\n";
        cout << "Gold kamu: " << p.duit << "\n";
        cout << ">> ";
        
        char pil; cin >> pil;

        if (pil != '1' && pil != '2' && pil != '3' && pil != '4' && pil != '5' && pil != '6' && pil != '7' && pil != '0') {
            cout << "Menu tidak tersedia! Pilih 0-7.\n";
            Sleep(1000);
            continue;
        }

        if(pil == '1') {
            if(p.duit >= 50) { p.duit-=50; p.pot++; cout << "Beli Potion sukses!\n"; }
            else cout << "Gold kurang!\n";
        }
        else if(pil == '2') {
            if(p.duit >= 50) { 
                p.duit-=50; p.mp+=50; 
                if(p.mp>p.mmp) p.mp=p.mmp; 
                cout << "Mana dipulihkan!\n"; 
            }
            else cout << "Gold kurang!\n";
        }
        else if(pil == '3') {
            if(p.duit >= 200) { p.duit-=200; p.atk+=5; cout << "Senjata makin tajam!\n"; }
            else cout << "Gold kurang!\n";
        }
        else if(pil == '4') {
            if(p.duit >= 200) { p.duit-=200; p.def+=5; cout << "Armor makin keras!\n"; }
            else cout << "Gold kurang!\n";
        }
        else if(pil == '5') info(p);
        else if(pil == '6') {
            save(p);
            system("pause");
        }
        else if(pil == '7') {
            save(p);
            cout << "Keluar dari game...\n";
            Sleep(1000);
            exit(0);
        }
        else if(pil == '0') break;
        Sleep(800);
    }
}

void mainGame(Char &p) {
    if(p.stage > 7) {
        cls();
        warna(14);
        cout << "\n\n\tSELAMAT! KAMU TELAH MENAMATKAN DUNGEON INI!\n";
        cout << "\tKamu adalah Math Wizard sejati.\n\n";
        system("pause");
        return;
    }

    Musuh m = listMusuh[p.stage];
    int mhp = m.hp;
    string textSoal; 
    int key, ans;

    while(p.hp > 0 && mhp > 0) {
        cls();
        warna(12);
        cout << "Lantai " << p.stage+1 << " - VS " << m.nama << " [" << m.art << "]\n";
        cout << "Monster HP: " << mhp << "/" << m.mhp << "\n";
        warna(15); box("BATTLE AREA", 15);
        
        warna(10); cout << "HP : " << p.hp << "/" << p.mhp << "   ";
        warna(9);  cout << "MP : " << p.mp << "/" << p.mmp << "   ";
        warna(14); cout << "POT: " << p.pot << "\n";
        warna(15);
        cout << "----------------------------------------\n";
        
        genSoal(p.stage, textSoal, key);
        
        cout << "Monster bersiap menyerang! Jawab soal untuk Counter Attack!\n";
        warna(11); cout << "SOAL: " << textSoal << endl; warna(15);
        
        cout << "\nMENU AKSI:\n";
        cout << "[1] Serang (Jawab Soal) - Dmg: " << p.atk << "\n";
        cout << "[2] Skill Spesial (25 MP)\n";
        cout << "[3] Gunakan Potion (HP+50)\n";
        cout << "Pilihan >> "; 
        
        char op; cin >> op;

        if (op != '1' && op != '2' && op != '3') {
            warna(12);
            cout << "Input tidak sesuai! Pilih [1], [2], atau [3].\n";
            warna(15);
            Sleep(1000); 
            continue;
        }

        if (op == '3') {
            if(p.pot > 0) {
                p.pot--;
                p.hp += 50; if(p.hp > p.mhp) p.hp = p.mhp;
                cout << "Glup glup.. HP bertambah.\n";
            } else cout << "Potion habis!\n";
            
            int inDmg = m.atk - (p.def/2);
            if(inDmg < 0) inDmg = 0;
            p.hp -= inDmg;
            cout << "Monster menyerangmu sebesar " << inDmg << " dmg!\n";
        }
        else if (op == '2') {
            if(p.mp >= 25) {
                p.mp -= 25;
                cout << "Jawab untuk Skill >> ";
                cin >> ans;
                if(ans == key) {
                    int skill = p.atk * 3;
                    mhp -= skill;
                    warna(11); cout << "SKILL ACTIVATED! BOOM! " << skill << " Damage!\n";
                } else {
                    warna(12); cout << "Gagal casting spell! Jawaban salah.\n";
                }
            } else {
                cout << "Mana tidak cukup!\n";
                Sleep(1000); continue;
            }
        }
        else if (op == '1') {
            cout << "Jawab >> "; cin >> ans;
            if(ans == key) {
                mhp -= p.atk;
                warna(10); cout << "TEPAT! Kamu menyerang " << p.atk << " damage!\n";
            } else {
                warna(12); cout << "SALAH! Jawabannya " << key << ".\n";
                int inDmg = m.atk;
                p.hp -= inDmg;
                cout << "Kamu terbuka lebar! Kena " << inDmg << " damage!\n";
                Sleep(1500); continue;
            }
        }

        if(mhp > 0 && op != '3') { 
            int inDmg = m.atk - (p.def/2);
            if(inDmg < 1) inDmg = 1;
            p.hp -= inDmg;
            warna(12); cout << m.nama << " membalas serangan! -" << inDmg << " HP\n";
        }
        
        warna(15);
        Sleep(1500);
    }

    if(p.hp <= 0) {
        cls();
        warna(12); cout << "GAME OVER...\n"; warna(15);
        system("pause");
    } else {
        cout << "\nMonster Kalah!\n";
        p.duit += m.duit;
        p.xp += m.xp;
        p.stage++;
        cekLvl(p);
        camp(p);
    }
}

int main() {
    srand(time(0));
    loadData();
    Char p;
    
    cls();
    box("THE MATH RPG: LEGENDARY EDITION", 14);
    cout << "1. New Game\n2. Load Game\n3. Exit\nPilih >> ";
    char menu; cin >> menu;
    while(menu != '1' && menu != '2' && menu != '3') {
        clearInput();
        cout << "Menu tidak valid! Pilih 1, 2, atau 3 >> ";
        cin >> menu;
    }

    if(menu == '2') {
        if(!load(p)) {
            cout << "Save data tidak ada! Mulai baru.\n";
            menu = '1';
        }
    }
    
    if(menu == '1') {
        cout << "Masukkan Nama Hero: "; cin >> p.nick;
        cout << "Pilih Job Class:\n[K] Knight (HP Tinggi, Def Tinggi)\n[M] Mage (Mana Tinggi, Skill Sakit)\nPilih (K/M): ";
        char j; cin >> j;
        
        while(tolower(j) != 'k' && tolower(j) != 'm') {
            clearInput();
            cout << "Pilihan tidak valid! Pilih K atau M >> ";
            cin >> j;
        }

        p.lvl = 1; p.xp = 0; p.mxp = 50;
        p.duit = 50; p.pot = 2; p.stage = 0;

        if(tolower(j) == 'm') {
            p.job = "Mage";
            p.mhp = 80; p.mmp = 100;
            p.atk = 25; p.def = 5;
        } else {
            p.job = "Knight";
            p.mhp = 120; p.mmp = 40;
            p.atk = 15; p.def = 15;
        }
        p.hp = p.mhp; p.mp = p.mmp;
    } else if (menu == '3') return 0;

    while(p.hp > 0) {
        mainGame(p);
    }

    return 0;
}