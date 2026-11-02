#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// Definisi entitas Unit
struct Unit {
    string name;
    int hp;
    int maxHp;
    int attackPower;
    Unit* target;
};

// Fungsi untuk mengunci target
void setTarget(Unit* attacker, Unit* defender) {
    if (attacker == nullptr || defender == nullptr) {
        return;
    }

    if (attacker->hp <= 0) {
        cout << "[BATTLE] " << attacker->name
             << " sudah kalah dan tidak dapat menyerang.\n";
        attacker->target = nullptr;
        return;
    }

    if (defender->hp <= 0) {
        cout << "[TARGET LOCK] Target sudah kalah!\n";
        attacker->target = nullptr;
        return;
    }

    attacker->target = defender;

    cout << "[TARGET LOCK] " << attacker->name
         << " mengunci target: " << defender->name << endl;
}

// Fungsi untuk mengeksekusi serangan
void executeAttack(Unit* attacker) {
    if (attacker == nullptr || attacker->hp <= 0) {
        return;
    }

    if (attacker->target == nullptr) {
        cout << "[BATTLE] Tidak ada target yang dikunci.\n";
        return;
    }

    Unit* defender = attacker->target;

    if (defender->hp <= 0) {
        cout << "[BATTLE] Target sudah kalah.\n";
        attacker->target = nullptr;
        return;
    }

    // Mengurangi HP target melalui pointer
    defender->hp -= attacker->attackPower;

    if (defender->hp < 0) {
        defender->hp = 0;
    }

    cout << "[ATTACK] " << attacker->name
         << " menyerang " << defender->name
         << " sebesar " << attacker->attackPower
         << " damage!\n";

    cout << "[STATUS] HP " << defender->name
         << ": " << defender->hp
         << "/" << defender->maxHp << endl;

    // Memeriksa apakah target kalah
    if (defender->hp <= 0) {
        cout << "[BATTLE] " << defender->name
             << " telah dikalahkan!\n";

        // Mengosongkan target penyerang
        attacker->target = nullptr;
    }
}

// Fungsi menampilkan status unit
void showStatus(Unit* units[], int jumlah) {
    for (int i = 0; i < jumlah; i++) {
        cout << i + 1 << ". " << units[i]->name
             << " | HP: " << units[i]->hp
             << "/" << units[i]->maxHp
             << " | ATK: " << units[i]->attackPower
             << endl;
    }
}

// Memeriksa apakah masih ada anggota tim yang hidup
bool partyAlive(Unit* party[], int jumlah) {
    for (int i = 0; i < jumlah; i++) {
        if (party[i]->hp > 0) {
            return true;
        }
    }

    return false;
}

// Memilih Hero yang masih hidup secara acak
Unit* randomHeroTarget(Unit* heroes[], int jumlah) {
    int jumlahHidup = 0;

    for (int i = 0; i < jumlah; i++) {
        if (heroes[i]->hp > 0) {
            jumlahHidup++;
        }
    }

    if (jumlahHidup == 0) {
        return nullptr;
    }

    // Memilih nomor urut dari Hero yang masih hidup
    int pilihan = rand() % jumlahHidup;

    for (int i = 0; i < jumlah; i++) {
        if (heroes[i]->hp > 0) {
            if (pilihan == 0) {
                return heroes[i];
            }

            pilihan--;
        }
    }

    return nullptr;
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    // Dynamic spawn: membuat 2 Hero dan 2 Monster
    Unit* hero1 = new Unit{"Arka", 120, 120, 35, nullptr};
    Unit* hero2 = new Unit{"Luna", 100, 100, 25, nullptr};

    Unit* monster1 = new Unit{"Goblin", 60, 60, 15, nullptr};
    Unit* monster2 = new Unit{"Orc", 90, 90, 20, nullptr};

    Unit* heroes[] = {hero1, hero2};
    Unit* monsters[] = {monster1, monster2};

    int jumlahHero = 2;
    int jumlahMonster = 2;

    cout << "====================================\n";
    cout << " TURN-BASED BATTLE PARTY & TARGET LOCK ENGINE\n";
    cout << "====================================\n";

    cout << "\n--- TIM HERO ---\n";
    showStatus(heroes, jumlahHero);

    cout << "\n--- TIM MONSTER ---\n";
    showStatus(monsters, jumlahMonster);

    int jumlahGiliran;

    cout << "\nMasukkan jumlah giliran maksimum: ";
    cin >> jumlahGiliran;

    if (cin.fail() || jumlahGiliran <= 0) {
        cout << "Input tidak valid. Jumlah giliran harus lebih dari 0.\n";
    } else {

        // Perulangan setiap giliran tim
        for (int giliran = 1;
             giliran <= jumlahGiliran;
             giliran++) {

            // Memeriksa kondisi kedua tim
            if (!partyAlive(heroes, jumlahHero) ||
                !partyAlive(monsters, jumlahMonster)) {
                break;
            }

            cout << "\n====================================\n";
            cout << "GILIRAN KE-" << giliran << endl;
            cout << "====================================\n";

            // =================================
            // FASE HERO
            // =================================
            cout << "\n--- GILIRAN HERO ---\n";

            for (int i = 0; i < jumlahHero; i++) {

                // Hero yang kalah tidak dapat bertindak
                if (heroes[i]->hp <= 0) {
                    continue;
                }

                // Pertempuran berhenti jika semua Monster kalah
                if (!partyAlive(monsters, jumlahMonster)) {
                    break;
                }

                cout << "\nPilih target Monster untuk "
                     << heroes[i]->name << ":\n";

                showStatus(monsters, jumlahMonster);

                int pilihanTarget;

                cout << "Masukkan nomor target (1-2): ";
                cin >> pilihanTarget;

                // Validasi pilihan target
                if (cin.fail()) {
                    cout << "Input harus berupa angka.\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                    i--;
                    continue;
                }

                if (pilihanTarget < 1 ||
                    pilihanTarget > jumlahMonster) {
                    cout << "Pilihan target tidak valid.\n";
                    i--;
                    continue;
                }

                Unit* targetMonster =
                    monsters[pilihanTarget - 1];

                if (targetMonster->hp <= 0) {
                    cout << "Monster tersebut sudah kalah. "
                         << "Pilih target lain.\n";
                    i--;
                    continue;
                }

                setTarget(heroes[i], targetMonster);
                executeAttack(heroes[i]);

                // Berhenti jika semua Monster kalah
                if (!partyAlive(monsters, jumlahMonster)) {
                    break;
                }
            }

            // =================================
            // FASE MONSTER
            // =================================
            if (partyAlive(heroes, jumlahHero) &&
                partyAlive(monsters, jumlahMonster)) {

                cout << "\n--- GILIRAN MONSTER ---\n";

                for (int i = 0; i < jumlahMonster; i++) {

                    // Monster yang kalah tidak dapat bertindak
                    if (monsters[i]->hp <= 0) {
                        continue;
                    }

                    // Memilih Hero yang masih hidup secara acak
                    Unit* targetHero =
                        randomHeroTarget(heroes, jumlahHero);

                    if (targetHero == nullptr) {
                        break;
                    }

                    setTarget(monsters[i], targetHero);
                    executeAttack(monsters[i]);
                }
            }

            // Menampilkan kondisi setelah satu giliran
            cout << "\n--- STATUS AKHIR GILIRAN ---\n";

            cout << "\nTim Hero:\n";
            showStatus(heroes, jumlahHero);

            cout << "\nTim Monster:\n";
            showStatus(monsters, jumlahMonster);
        }
    }

    // =================================
    // HASIL PERTEMPURAN
    // =================================
    cout << "\n====================================\n";
    cout << "HASIL PERTEMPURAN\n";
    cout << "====================================\n";

    if (!partyAlive(heroes, jumlahHero) &&
        !partyAlive(monsters, jumlahMonster)) {
        cout << "Pertempuran berakhir seri!\n";
    } else if (!partyAlive(monsters, jumlahMonster)) {
        cout << "Kemenangan! Semua Monster berhasil dikalahkan.\n";
    } else if (!partyAlive(heroes, jumlahHero)) {
        cout << "Kekalahan! Semua Hero telah dikalahkan.\n";
    } else {
        cout << "Pertempuran berakhir karena batas giliran tercapai.\n";
    }

    // =================================
    // CLEANUP MEMORI
    // =================================
    delete hero1;
    hero1 = nullptr;

    delete hero2;
    hero2 = nullptr;

    delete monster1;
    monster1 = nullptr;

    delete monster2;
    monster2 = nullptr;

    cout << "\n[CLEANUP] Seluruh memori unit telah dibersihkan.\n";

    return 0;
}
