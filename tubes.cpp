#include "tubes.h"

// Menu
void tampilkanMenu() {
    cout << "\n========== MENU ==========\n";
    cout << "1. Tambah Pengguna (Dari Belakang)\n";
    cout << "2. Tambah Pengguna (Dari Depan)\n";
    cout << "3. Tampilkan Semua Pengguna\n";
    cout << "4. Hapus Pengguna\n";
    cout << "5. Tambah Makanan\n";
    cout << "6. Tampilkan Semua Makanan\n";
    cout << "7. Hubungkan Pengguna dengan Makanan\n";
    cout << "8. Riwayat pengguna dan ulasan\n";
    cout << "9. Tampilkan Semua Data\n";
    cout << "10. Keluar\n";
    cout << "==========================\n";
    cout << "Pilih menu: ";
}

// Inisialisasi list
void buatListPengguna(ListPengguna &L) {
    L.first = NULL;
    L.last = NULL;
}

void buatListMakanan(ListMakanan &L) {
    L.first = NULL;
}

void buatListRelasi(ListRelasi&L) {
    L.first = NULL;
}

void masukkanContohData(ListPengguna &penggunaList, ListMakanan &makananList, ListRelasi &relasiList) {
    // Menambahkan data pengguna
    tambahPengguna(penggunaList, buatPengguna("U001", "Alice", "alice@gmail.com"));
    tambahPengguna(penggunaList, buatPengguna("U002", "Bob", "bob@gmail.com"));
    tambahPengguna(penggunaList, buatPengguna("U003", "Charlie", "charlie@gmail.com"));

    // Menambahkan data makanan
    tambahMakanan(makananList, buatMakanan("M001", "Pizza", "Fast Food"));
    tambahMakanan(makananList, buatMakanan("M002", "Sushi", "Japanese"));
    tambahMakanan(makananList, buatMakanan("M003", "Ice Cream", "Dessert"));

    // Membuat relasi antara pengguna dan makanan
    adrP pengguna1 = cariPengguna(penggunaList, "U001");
    adrP pengguna2 = cariPengguna(penggunaList, "U002");
    adrM makanan1 = cariMakanan(makananList, "M001");
    adrM makanan2 = cariMakanan(makananList, "M002");

    if (pengguna1 && makanan1) {
        hubungkanPenggunaMakanan(relasiList, pengguna1, makanan1, "Lezat dan memuaskan", 5);
    }
    if (pengguna2 && makanan2) {
        hubungkanPenggunaMakanan(relasiList, pengguna2, makanan2, "Rasanya autentik", 4);
    }

    cout << "Contoh data berhasil dimasukkan.\n";
}



// Fungsi untuk membuat elemen baru
adrP buatPengguna(string id, string nama, string email) {
    adrP baru = new Pengguna{id, nama, email, NULL, NULL};
    return baru;
}

adrM buatMakanan(string id, string nama, string kategori) {
    adrM baru = new Makanan{id, nama, kategori, NULL};
    return baru;
}

adrR buatRelasi(adrP pengguna, adrM makanan, string ulasan, int rating) {
    adrR baru = new Relasi{pengguna, makanan, ulasan, rating, NULL};
    return baru;
}

// Operasi pada list pengguna
void tambahPenggunaDepan(ListPengguna &L, adrP pengguna) {
    if (!L.first) { // Jika list kosong
        L.first = pengguna;
        L.last = pengguna;
    } else { // Jika list sudah ada elemen
        pengguna->next = L.first;
        L.first->prev = pengguna;
        L.first = pengguna;
    }
}

void tambahPengguna(ListPengguna &L, adrP pengguna) {
    if (!L.first) { // Jika list kosong
        L.first = pengguna;
        L.last = pengguna;
    } else { // Jika list sudah ada elemen
        L.last->next = pengguna;
        pengguna->prev = L.last;
        L.last = pengguna;
    }
}


void tampilkanPengguna(ListPengguna &L) {
    adrP temp = L.first;
    while (temp) {
        cout << "ID: " << temp->id_pengguna << ", Nama: " << temp->nama_pengguna
             << ", Email: " << temp->email << endl;
        temp = temp->next;
    }
}

void hapusPengguna(ListPengguna &L, ListRelasi &relasiList, string id) {
    adrP pengguna = L.first;

    while (pengguna && pengguna->id_pengguna != id) pengguna = pengguna->next; // Cari pengguna
    if (!pengguna) {
        cout << "Pengguna dengan ID " << id << " tidak ditemukan.\n";
        return;
    }

    // Hapus dari list relasi terlebih dahulu
    adrR relasi = relasiList.first;
    while (relasi) {
        if (relasi->pengguna == pengguna) {
            adrR hapusRelasi = relasi;
            if (relasi == relasiList.first) {
                relasiList.first = relasi->next;
            } else {
                adrR prevRelasi = relasiList.first;
                while (prevRelasi->next != relasi) prevRelasi = prevRelasi->next;
                prevRelasi->next = relasi->next;
            }
            relasi = relasi->next;
            delete hapusRelasi;
        } else {
            relasi = relasi->next;
        }
    }

    // Hapus elemen pengguna dari list pengguna
    if (pengguna == L.first) { // Jika elemen pertama
        L.first = pengguna->next;
        if (L.first) L.first->prev = NULL; // Update prev elemen berikutnya
        if (pengguna == L.last) L.last = NULL; // Jika elemen terakhir juga
    } else if (pengguna == L.last) { // Jika elemen terakhir
        L.last = pengguna->prev;
        L.last->next = NULL;
    } else { // Elemen di tengah
        pengguna->prev->next = pengguna->next;
        pengguna->next->prev = pengguna->prev;
    }

    delete pengguna;
    cout << "Pengguna dengan ID " << id << " berhasil dihapus.\n";
}



// Operasi pada list makanan
void tambahMakanan(ListMakanan &L, adrM makanan) {
    if (!L.first) {
        L.first = makanan;
    } else {
        adrM temp = L.first;
        while (temp->next) temp = temp->next;
        temp->next = makanan;
    }
}

void tampilkanMakanan(ListMakanan &L) {
    adrM temp = L.first;
    while (temp) {
        cout << "ID: " << temp->id_makanan << ", Nama: " << temp->nama_makanan
             << ", Kategori: " << temp->kategori << endl;
        temp = temp->next;
    }
}
void hapusMakanan(ListMakanan &L, ListRelasi &relasiList, string id) {
    adrM makanan = L.first;

    // Cari makanan berdasarkan ID
    while (makanan && makanan->id_makanan != id) {
        makanan = makanan->next; // Cari makanan
    }
    if (!makanan) {
        cout << "Makanan dengan ID " << id << " tidak ditemukan.\n";
        return;
    }

    // Hapus dari list relasi terlebih dahulu
    adrR relasi = relasiList.first;
    while (relasi) {
        if (relasi->makanan == makanan) {
            adrR hapusRelasi = relasi;
            if (relasi == relasiList.first) {
                relasiList.first = relasi->next;
            } else {
                adrR prevRelasi = relasiList.first;
                while (prevRelasi->next != relasi) prevRelasi = prevRelasi->next;
                prevRelasi->next = relasi->next;
            }
            relasi = relasi->next;  // Lanjutkan iterasi
            delete hapusRelasi;     // Hapus relasi
        } else {
            relasi = relasi->next;  // Lanjutkan iterasi
        }
    }

    // Hapus elemen makanan dari list makanan
    if (makanan == L.first) { // Jika elemen pertama
        L.first = makanan->next;
    } else { // Elemen di tengah atau terakhir
        adrM prev = L.first;
        while (prev->next != makanan) {
            prev = prev->next; // Cari elemen sebelumnya
        }
        prev->next = makanan->next; // Update pointer next
    }

    delete makanan; // Hapus makanan dari memori

    cout << "Makanan dengan ID " << id << " berhasil dihapus.\n";
}


// Operasi pada list relasi
void hubungkanPenggunaMakanan(ListRelasi &L, adrP pengguna, adrM makanan, string ulasan, int rating) {
    adrR baru = buatRelasi(pengguna, makanan, ulasan, rating);
    if (!L.first) {
        L.first = baru;
    } else {
        adrR temp = L.first;
        while (temp->next) temp = temp->next;
        temp->next = baru;
    }
}

void tampilkanRelasi(ListPengguna &penggunaList,ListRelasi &relasiList) {
    adrP pengguna = penggunaList.first;
    if (!pengguna) {
        cout << "Tidak ada data pengguna.\n";
        return;
    }

    while (pengguna) {
        cout << "\nPengguna: " << pengguna->nama_pengguna
             << " (ID: " << pengguna->id_pengguna << ", Email: " << pengguna->email << ")\n";

        // Hitung jumlah relasi
        int jumlahRelasi = hitungRelasi(relasiList,pengguna);
        cout << "Jumlah Relasi: " << jumlahRelasi << "\n";

        if (jumlahRelasi > 0) {
            cout << "Relasi (Makanan):\n";
            adrR relasi;
            relasi = relasiList.first;
            while (relasi) {
                if (relasi->pengguna == pengguna) {
                    cout << "- Nama Makanan: " << relasi->makanan->nama_makanan
                         << " (ID: " << relasi->makanan->id_makanan
                         << ", Kategori: " << relasi->makanan->kategori << ")\n";
                    cout << "  Ulasan: " << relasi->ulasan
                         << ", Rating: " << relasi->rating << "\n";
                }
                relasi = relasi->next;
            }
        } else {
            cout << "Tidak memiliki relasi.\n";
        }

        pengguna = pengguna->next;
    }
}

int hitungRelasi(ListRelasi relasiList,adrP pengguna){
    int jumlahRelasi = 0;
    adrR relasi = relasiList.first;
        while (relasi) {
            if (relasi->pengguna == pengguna) {
                jumlahRelasi++;
            }
            relasi = relasi->next;
        }
    return jumlahRelasi;
}

// Fungsi pencarian
adrP cariPengguna(ListPengguna &L, string id) {
    adrP temp = L.first;
    while (temp) {
        if (temp->id_pengguna == id) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

adrM cariMakanan(ListMakanan &L, string id) {
    adrM temp = L.first;
    while (temp) {
        if (temp->id_makanan == id) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
adrR cariRelasi(ListRelasi L, string idP, string idM) {
    adrR current = L.first;
    while (current) {
        if (current->pengguna->id_pengguna == idP && current->makanan->id_makanan == idM) {
            return current; // Relasi ditemukan
        }
        current = current->next;
    }
    return nullptr; // Relasi tidak ditemukan
}


// Fungsi validasi rating
int validasiRating() {
    int rating;
    do {
        cout << "Masukkan Rating (1-5): ";
        cin >> rating;
        if (rating < 1 || rating > 5) {
            cout << "Rating tidak valid! Harap masukkan angka antara 1 dan 5.\n";
        }
    } while (rating < 1 || rating > 5);
    return rating;
}
