#include "tubes.h"



int main() {
    ListPengguna penggunaList;
    ListMakanan makananList;
    ListRelasi relasiList;

    buatListPengguna(penggunaList);
    buatListMakanan(makananList);
    buatListRelasi(relasiList);

    masukkanContohData(penggunaList, makananList, relasiList);

    int pilihan;

    do {
        tampilkanMenu();
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                string id, nama, email;
                cout << "Masukkan ID Pengguna: ";
                cin >> id;
                cout << "Masukkan Nama Pengguna: ";
                cin.ignore();
                getline(cin, nama);
                cout << "Masukkan Email Pengguna: ";
                cin >> email;
                if (cariPengguna(penggunaList,id) == NULL) {
                    tambahPengguna(penggunaList, buatPengguna(id, nama, email));
                    cout << "Pengguna berhasil ditambahkan di belakang!\n";
                }else{
                    cout << "data id double gagal masuk!!";
                }
                break;
            }
            case 2: {
                string id, nama, email;
                cout << "Masukkan ID Pengguna: ";
                cin >> id;
                cout << "Masukkan Nama Pengguna: ";
                cin.ignore();
                getline(cin, nama);
                cout << "Masukkan Email Pengguna: ";
                cin >> email;
                if (cariPengguna(penggunaList,id) == NULL) {
                    tambahPenggunaDepan(penggunaList, buatPengguna(id, nama, email));
                    cout << "Pengguna berhasil ditambahkan di depan!\n";
                }else{
                    cout << "data id double gagal masuk!!";
                }
                break;
            }
            case 3:
                cout << "\nDaftar Pengguna:\n";
                tampilkanPengguna(penggunaList);
                break;
            case 4: {
                string id;
                cout << "Masukkan ID Pengguna yang akan dihapus: ";
                cin >> id;
                hapusPengguna(penggunaList, relasiList, id);
                cout << "Pengguna berhasil dihapus (jika ada)!\n";
                break;
            }
            case 5: {
                string id, nama, kategori;
                cout << "Masukkan ID Makanan: ";
                cin >> id;
                cout << "Masukkan Nama Makanan: ";
                cin.ignore();
                getline(cin, nama);
                cout << "Masukkan Kategori Makanan: ";
                getline(cin, kategori);
                if (cariMakanan(makananList,id) == NULL) {
                    tambahMakanan(makananList, buatMakanan(id, nama, kategori));
                    cout << "Makanan berhasil ditambahkan!\n";
                }else{
                    cout << "data id double gagal masuk!!";
                }
                break;
            }
            case 6:
                cout << "\nDaftar Makanan:\n";
                tampilkanMakanan(makananList);
                break;
            case 7: {
                string idPengguna, idMakanan, ulasan;

                cout << "Masukkan ID Pengguna: ";
                cin >> idPengguna;
                adrP pengguna = cariPengguna(penggunaList, idPengguna);
                if (!pengguna) {
                    cout << "Pengguna dengan ID " << idPengguna << " tidak ditemukan.\n";
                    break;
                }

                cout << "Masukkan ID Makanan: ";
                cin >> idMakanan;
                adrM makanan = cariMakanan(makananList, idMakanan);
                if (!makanan) {
                    cout << "Makanan dengan ID " << idMakanan << " tidak ditemukan.\n";
                    break;
                }

                cout << "Masukkan Ulasan: ";
                cin.ignore();
                getline(cin, ulasan);

                int rating = validasiRating();

                hubungkanPenggunaMakanan(relasiList, pengguna, makanan, ulasan, rating);
                cout << "Relasi berhasil ditambahkan!\n";
                break;
            }
            case 8:{
                string idPengguna, idMakanan;
                cout << "Masukkan ID Pengguna: ";
                cin >> idPengguna;
                cout << "Masukkan ID Makanan: ";
                cin >> idMakanan;
                adrR relasi = cariRelasi(relasiList, idPengguna, idMakanan);
                if (relasi) {
                    cout << "\nPengguna: " << relasi->pengguna->nama_pengguna
                         << " (ID: " << relasi->pengguna->id_pengguna << ", Email: " << relasi->pengguna->email << ")\n";
                    cout << "Pengguna sudah pernah mengulas makanan ini dengan ulasan: \n";
                    cout << "- Nama Makanan: " << relasi->makanan->nama_makanan
                         << " (ID: " << relasi->makanan->id_makanan
                         << ", Kategori: " << relasi->makanan->kategori << ")\n";
                    cout << "  Ulasan: " << relasi->ulasan
                         << ", Rating: " << relasi->rating << "\n";

                    char pilihan;
                    cout << "Apakah Anda ingin menghapus makanan dari ulasan ini? (Y/y(untuk ya dan lainnya untuk tidak)): ";
                    cin >> pilihan;

                    if (pilihan == 'Y' || pilihan == 'y') {
                        // Menghapus relasi
                        hapusMakanan(makananList, relasiList,relasi->makanan->id_makanan);
                        cout << "Ulasan berhasil dihapus.\n";
                    } else {
                        cout << "Ulasan tidak dihapus.\n";
                    }
                }else{
                    cout << "data tidak ditemukann!!!!";
                }
                break;
            }
            case 9:
                cout << "\nDaftar Relasi:\n";
                tampilkanRelasi(penggunaList, relasiList);
                break;
            case 10:
                cout << "Keluar dari program. Terima kasih!\n";
                break;
            default:
                cout << "Pilihan tidak valid! Silakan coba lagi.\n";
        }
    } while (pilihan != 9);

    return 0;
}
