#ifndef HEADER_H
#define HEADER_H

#include <iostream>
using namespace std;

// Typedef untuk pointer
typedef struct Pengguna *adrP;
typedef struct Makanan *adrM;
typedef struct Relasi *adrR;

// Struktur data untuk parent (Pengguna)
struct Pengguna {
    string id_pengguna;
    string nama_pengguna;
    string email;
    adrP next;
    adrP prev;
};

// Struktur data untuk child (Makanan)
struct Makanan {
    string id_makanan;
    string nama_makanan;
    string kategori;
    adrM next;
};

// Struktur data untuk relasi
struct Relasi {
    adrP pengguna;
    adrM makanan;
    string ulasan;
    int rating;
    adrR next;
};

// Struktur List
struct ListPengguna {
    adrP first;
    adrP last;
};

struct ListMakanan {
    adrM first;
};

struct ListRelasi {
    adrR first;
};
//menu
void tampilkanMenu();
// Fungsi untuk inisialisasi list (Juan)
void buatListPengguna(ListPengguna &L);
void buatListMakanan(ListMakanan &L);
void buatListRelasi(ListRelasi &L);

//dylan
void masukkanContohData(ListPengguna &penggunaList, ListMakanan &makananList, ListRelasi &relasiList);

// Pembuatan elemen (Juan)
adrP buatPengguna(string id, string nama, string email);
adrM buatMakanan(string id, string nama, string kategori);
adrR buatRelasi(adrP pengguna, adrM makanan, string ulasan, int rating);

// Operasi pada list (juan)
void tambahPenggunaDepan(ListPengguna &L, adrP pengguna);
void tambahPengguna(ListPengguna &L, adrP pengguna); //dari belakang

//dylan
void tampilkanPengguna(ListPengguna &L);
//juan
void hapusPengguna(ListPengguna &L, ListRelasi& relasiList, string id);//eror hapus waktu masih ada relasi
//dylan
void tambahMakanan(ListMakanan &L, adrM makanan); //dari belakang
//dylan
void tampilkanMakanan(ListMakanan &L);
//juan
void hapusMakanan(ListMakanan &M, ListRelasi &relasiList, string id);
//dylan
void hubungkanPenggunaMakanan(ListRelasi &L, adrP pengguna, adrM makanan, string ulasan, int rating);
//juan
void tampilkanRelasi(ListPengguna &penggunaList,ListRelasi &relasiList);
//
int hitungRelasi(ListRelasi relasiList,adrP pengguna);

// Fungsi pencarian
//dylan
adrP cariPengguna(ListPengguna &L, string id);
adrM cariMakanan(ListMakanan &L, string id);
//
adrR cariRelasi(ListRelasi L, string idP, string idM) ;

// Fungsi validasi (dylan)
int validasiRating();

#endif
