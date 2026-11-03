# Studi Kasus: "Turn-Based Battle Party & Target Lock Engine"

## Latar Belakang

Dalam proyek game JRPG taktis, terdapat tim pemain (*Party*) yang terdiri dari 3 karakter Hero dan sekelompok musuh (*Enemies*). Selama fase pertempuran, setiap unit memilih aksinya, mengunci sasaran lawan melalui pointer `target`, dan memberikan efek (*damage/heal*) langsung ke alamat memori unit tujuan.

## Spesifikasi Tugas

### 1. Definisi Entitas
Buat `struct Unit` yang memiliki variabel:
- `std::string name`
- `int hp`
- `int maxHp`
- `int attackPower`
- `Unit* target` (pointer yang menunjuk lawan yang sedang dibidik).

### 2. Mekanisme Dynamic Spawn
- Gunakan *dynamic allocation* (`new`) untuk membuat minimal 2 objek Hero dan 2 objek Monster.

### 3. Mekanisme Targeting & Serangan
- Buat fungsi `void setTarget(Unit* attacker, Unit* defender)` untuk mengisi pointer `target` pada unit penyerang.
- Buat fungsi `void executeAttack(Unit* attacker)` yang mengeksekusi serangan:
  - Mengurangi HP target yang ditunjuk secara *pass-by-pointer*.
  - Menampilkan log nama dan sisa HP target.
  - Memeriksa apakah target mati (`hp <= 0`).

### 4. Safety & Cleanup
- Jika HP suatu unit mencapai nol, set `target` penyerang kembali menjadi `nullptr`.
- Sebelum program ditutup, hapus seluruh alokasi memori *heap* menggunakan `delete` dan assign pointer tersebut ke `nullptr`.
- Pastikan tidak terjadi *memory leak*.

## Contoh Output

<img width="720" height="290" alt="Screenshot 2026-11-03 064822" src="https://github.com/user-attachments/assets/12449286-127e-48ca-ba1d-715b7abc59d7" />


```text
==============================================
 TURN-BASED BATTLE PARTY & TARGET LOCK ENGINE
==============================================

--- TIM HERO ---
1. Arka | HP: 120/120 | ATK: 35
2. Luna | HP: 100/100 | ATK: 25

--- TIM MONSTER ---
1. Goblin | HP: 60/60 | ATK: 15
2. Orc | HP: 90/90 | ATK: 20

Masukkan jumlah giliran maksimum: 2

====================================
GILIRAN KE-1
====================================

--- GILIRAN HERO ---

Pilih target Monster untuk Arka:
1. Goblin | HP: 60/60 | ATK: 15
2. Orc | HP: 90/90 | ATK: 20
Masukkan nomor target (1-2): 1
[TARGET LOCK] Arka mengunci target: Goblin
[ATTACK] Arka menyerang Goblin sebesar 35 damage!
[STATUS] HP Goblin: 25/60

Pilih target Monster untuk Luna:
1. Goblin | HP: 25/60 | ATK: 15
2. Orc | HP: 90/90 | ATK: 20
Masukkan nomor target (1-2): 1
[TARGET LOCK] Luna mengunci target: Goblin
[ATTACK] Luna menyerang Goblin sebesar 25 damage!
[STATUS] HP Goblin: 0/60
[BATTLE] Goblin telah dikalahkan!

--- GILIRAN MONSTER ---
[TARGET LOCK] Orc mengunci target: Arka
[ATTACK] Orc menyerang Arka sebesar 20 damage!
[STATUS] HP Arka: 100/120

--- STATUS AKHIR GILIRAN ---

Tim Hero:
1. Arka | HP: 100/120 | ATK: 35
2. Luna | HP: 100/100 | ATK: 25

Tim Monster:
1. Goblin | HP: 0/60 | ATK: 15
2. Orc | HP: 90/90 | ATK: 20

====================================
GILIRAN KE-2
====================================

--- GILIRAN HERO ---

Pilih target Monster untuk Arka:
1. Goblin | HP: 0/60 | ATK: 15
2. Orc | HP: 90/90 | ATK: 20
Masukkan nomor target (1-2): 2
[TARGET LOCK] Arka mengunci target: Orc
[ATTACK] Arka menyerang Orc sebesar 35 damage!
[STATUS] HP Orc: 55/90

Pilih target Monster untuk Luna:
1. Goblin | HP: 0/60 | ATK: 15
2. Orc | HP: 55/90 | ATK: 20
Masukkan nomor target (1-2): 2
[TARGET LOCK] Luna mengunci target: Orc
[ATTACK] Luna menyerang Orc sebesar 25 damage!
[STATUS] HP Orc: 30/90

--- GILIRAN MONSTER ---
[TARGET LOCK] Orc mengunci target: Arka
[ATTACK] Orc menyerang Arka sebesar 20 damage!
[STATUS] HP Arka: 80/120

--- STATUS AKHIR GILIRAN ---

Tim Hero:
1. Arka | HP: 80/120 | ATK: 35
2. Luna | HP: 100/100 | ATK: 25

Tim Monster:
1. Goblin | HP: 0/60 | ATK: 15
2. Orc | HP: 30/90 | ATK: 20

====================================
HASIL PERTEMPURAN
====================================
Pertempuran berakhir karena batas giliran tercapai.

[CLEANUP] Seluruh memori unit telah dibersihkan.
```
