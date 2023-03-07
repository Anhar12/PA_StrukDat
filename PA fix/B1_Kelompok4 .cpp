//HEADER
#include <iostream>
#include <conio.h>
#include <fstream>
#include <sstream>
// #include <unistd.h>
#include <windows.h>
#include <iomanip>

using namespace std;

//PROTOTYPE MENU UTAMA
void menu_utama();
void login_admin();
void login_user();
void exit_program();
void maintenance();

//PROTOTYPE MENU ADMIN
void menu_admin();

//PROTOTYPE MENU USER
void menu_user(string username, string nama);

//PROTOTYPE SORTING DAN SEARCHING
void urutkan_komik();
void cari_komik();

void warna(int x);

// STRUCT KOMIK SEBAGAI TEMPAT DATA KOMIK
struct komik {
	int id;
	string nama;
	string genre;
	string penulis;
	int halaman;
	int stok;
	int harga;
	// UNTUK MENAMBAHKAN POINTER ELEMEN SELANJUTNYA AGAR TERBENTUKNYA LINKED LIST
	komik *next;
	komik *prev;
};

struct akun{
	string nama;
	string username;
	string password;
	akun *next = NULL;
};

struct keranjang{
    string username;
    string nama;
	int id_komik;
	string komik;
    int harga;
    int jumlah;
    int total;
	keranjang *next = NULL;
};

struct checkout{
	string username;
	string nama;
	int id_komik;
	string komik;
    int harga;
    int jumlah;
    int total;
	string status;
	checkout *next = NULL;
};

struct riwayat{
	string username;
	string nama;
	int id_komik;
	string komik;
    int harga;
    int jumlah;
    int total;
	string status;
	riwayat *next = NULL;
};

// VARIABEL GLOBAL
akun *head_akun, *cur_akun;
keranjang *head_keranjang, *cur_keranjang;
checkout *head_check, *cur_check;
riwayat *head_riwayat;
komik *head, *tail, *cur, *Node_Hapus;
//*cur DIGUNAKAN UNTUK MELAKUKAN PROSES TRANVERSAL

// FUNGSI UNTUK MENGEMBALIKAN JUMLAH NODE
int Jumlah_Data() {
	cur = head;
	int jumlah = 0;
	while(cur != NULL){
		jumlah+=1;
		cur = cur->next;
	}
	return jumlah;
}

void warna(int x){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, x);
}

void read_komik(komik **head, komik **tail){
    ifstream file;
    string isi, nama, id, genre, penulis, halaman, harga, stok;
    int id_int, stok_int, harga_int, halaman_int;
    // membuka file untuk membaca file ke program
    file.open("komik.csv", ios::in);
    if (file.is_open()){
        // proses membaca file
        while (getline(file, isi)){
			komik *newNode = new komik;
			stringstream ss(isi);
			
			// mengubah isi data pada file menjadi string semua
			getline(ss, id, ',');
			getline(ss, nama, ',');
			getline(ss, genre, ',');
			getline(ss, penulis, ',');
			getline(ss, halaman, ',');
			getline(ss, stok, ',');
			getline(ss, harga, '\n');

			stringstream id_string(id);
			stringstream halaman_string(halaman);
			stringstream stok_string(stok);
			stringstream harga_string(harga);

			// mengembalikkan nilai yang sebelumnya string menjadi integer kembali
			id_string >> id_int;
			halaman_string >> halaman_int;
			stok_string >> stok_int;
			harga_string >> harga_int;

			// memasukkan data kedalam linked list
			newNode->id = id_int;
			newNode->nama = nama;
			newNode->genre = genre;
			newNode->penulis = penulis;
			newNode->halaman = halaman_int;
			newNode->stok = stok_int;
			newNode->harga = harga_int;

            if (*head == NULL && *tail == NULL){
				newNode->prev = *tail;
				newNode->next = NULL;
				*head = newNode;
				*tail = newNode;
            } else {
                newNode->prev = *tail;
                newNode->next = NULL;
                // mengubah next pada tail menjadi node baru dan node baru menjadi tail
                (*tail)->next = newNode;
                *tail = newNode;
            }
        }
    }
    // menutup file
    file.close();
}

void read_akun(akun **head){
    ifstream file;
    string isi, nama, username, password;
    // membuka file untuk membaca file ke program
    file.open("akun.csv", ios::in);
    if (file.is_open()){
        // proses membaca file
        while (getline(file, isi)){
			akun *newNode = new akun;
			stringstream ss(isi);
			
			// mengubah isi data pada file menjadi string semua
			getline(ss, nama, ',');
			getline(ss, username, ',');
			getline(ss, password, '\n');

			// memasukkan data kedalam linked list
			newNode->nama = nama;
			newNode->username = username;
			newNode->password = password;

            newNode->next = *head;
			*head = newNode;
        }
    }
    // menutup file
    file.close();
}

void read_keranjang(keranjang **head){
	ifstream file;
    string isi, username, id, komik, jumlah, total, status, nama, harga;
    int id_int, jumlah_int, total_int, harga_int;
    // membuka file untuk membaca file ke program
    file.open("keranjang.csv", ios::in);
    if (file.is_open()){
        // proses membaca file
        while (getline(file, isi)){
			cur_keranjang = *head;
			keranjang *newNode = new keranjang;
			stringstream ss(isi);
			
			// mengubah isi data pada file menjadi string semua
			getline(ss, username, ',');
			getline(ss, nama, ',');
			getline(ss, id, ',');
			getline(ss, komik, ',');
			getline(ss, harga, ',');
			getline(ss, jumlah, ',');
			getline(ss, total, '\n');

			stringstream id_string(id);
			stringstream harga_string(harga);
			stringstream jumlah_string(jumlah);
			stringstream total_string(total);

			// mengembalikkan nilai yang sebelumnya string menjadi integer kembali
			id_string >> id_int;
			harga_string >> harga_int;
			jumlah_string >> jumlah_int;
			total_string >> total_int;

			// memasukkan data kedalam linked list
			newNode->username = username;
			newNode->nama = nama;
			newNode->id_komik = id_int;
			newNode->komik = komik;
			newNode->harga = harga_int;
			newNode->jumlah = jumlah_int;
			newNode->total = total_int;
			if (*head == NULL){
				*head = newNode;
			} else {
				while (cur_keranjang->next != NULL){
					cur_keranjang = cur_keranjang->next;
				}
				cur_keranjang->next = newNode;
			}
        }
    }
    // menutup file
    file.close();
}

void read_queue(checkout **head){
	ifstream file;
    string isi, nama, username, id, komik, jumlah, total, status, waktu, harga;
    int id_int, jumlah_int, total_int, harga_int;
    // membuka file untuk membaca file ke program
    file.open("checkout.csv", ios::in);
    if (file.is_open()){
        // proses membaca file
        while (getline(file, isi)){
			cur_check = *head;
			checkout *newNode = new checkout;
			stringstream ss(isi);
			
			// mengubah isi data pada file menjadi string semua
			getline(ss, username, ',');
			getline(ss, nama, ',');
			getline(ss, id, ',');
			getline(ss, komik, ',');
			getline(ss, harga, ',');
			getline(ss, jumlah, ',');
			getline(ss, total, ',');
			getline(ss, status, '\n');

			stringstream id_string(id);
			stringstream harga_string(harga);
			stringstream jumlah_string(jumlah);
			stringstream total_string(total);

			// mengembalikkan nilai yang sebelumnya string menjadi integer kembali
			id_string >> id_int;
			harga_string >> harga_int;
			jumlah_string >> jumlah_int;
			total_string >> total_int;

			// memasukkan data kedalam linked list
			newNode->username = username;
			newNode->nama = nama;
			newNode->id_komik = id_int;
			newNode->komik = komik;
			newNode->harga = harga_int;
			newNode->jumlah = jumlah_int;
			newNode->total = total_int;
			newNode->status = status;

            if (*head == NULL){
				*head = newNode;
            } else {
				while (cur_check->next != NULL){
					cur_check = cur_check->next;
				}
				cur_check->next = newNode;
            }
        }
    }
    // menutup file
    file.close();
}

void read_riwayat(riwayat **head){
	ifstream file;
	riwayat *temp = *head;
    string isi, nama, username, id, komik, jumlah, total, status, waktu, harga;
    int id_int, jumlah_int, total_int, harga_int;
    // membuka file untuk membaca file ke program
    file.open("riwayat.csv", ios::in);
    if (file.is_open()){
        // proses membaca file
        while (getline(file, isi)){
			temp = *head;
			riwayat *newNode = new riwayat;
			stringstream ss(isi);
			
			// mengubah isi data pada file menjadi string semua
			getline(ss, username, ',');
			getline(ss, nama, ',');
			getline(ss, id, ',');
			getline(ss, komik, ',');
			getline(ss, harga, ',');
			getline(ss, jumlah, ',');
			getline(ss, total, ',');
			getline(ss, status, '\n');

			stringstream id_string(id);
			stringstream harga_string(harga);
			stringstream jumlah_string(jumlah);
			stringstream total_string(total);

			// mengembalikkan nilai yang sebelumnya string menjadi integer kembali
			id_string >> id_int;
			harga_string >> harga_int;
			jumlah_string >> jumlah_int;
			total_string >> total_int;

			// memasukkan data kedalam linked list
			newNode->username = username;
			newNode->nama = nama;
			newNode->id_komik = id_int;
			newNode->komik = komik;
			newNode->komik = komik;
			newNode->harga = harga_int;
			newNode->jumlah = jumlah_int;
			newNode->total = total_int;
			newNode->status = status;

            if (*head == NULL){
				*head = newNode;
            } else {
				while (temp->next != NULL){
					temp = temp->next;
				}
				temp->next = newNode;
            }
        }
    }
    // menutup file
    file.close();
}

// fungsi untuk menulis sekaligus memperbarui data ke dalam file
void write_komik(komik *head){
    fstream file;
    cur = head;
    // membuka file untuk menulis data ke file
    file.open("komik.csv", ios::trunc | ios::out | ios::in);
    if (file.is_open()){
        // traversal
        while (cur != NULL){
            file << cur->id << ",";
            file << cur->nama << ",";
            file << cur->genre << ",";
            file << cur->penulis << ",";
            file << cur->halaman << ",";
            file << cur->stok << ",";
            file << cur->harga << endl;
            cur = cur->next;
        }
    }
    // menutup file
    file.close();
}

void write_akun(akun *head){
    fstream file;
    cur_akun = head;
    // membuka file untuk menulis data ke file
    file.open("akun.csv", ios::trunc | ios::out | ios::in);
    if (file.is_open()){
        // traversal
        while (cur_akun != NULL){
            file << cur_akun->nama << ",";
            file << cur_akun->username << ",";
            file << cur_akun->password << endl;
            cur_akun = cur_akun->next;
        }
    }
    // menutup file
    file.close();
}

void write_keranjang(keranjang *head){
	fstream file;
    cur_keranjang = head;
    // membuka file untuk menulis data ke file
    file.open("keranjang.csv", ios::trunc | ios::out | ios::in);
    if (file.is_open()){
        // traversal
        while (cur_keranjang != NULL){
            file << cur_keranjang->username << ",";
            file << cur_keranjang->nama << ",";
            file << cur_keranjang->id_komik << ",";
            file << cur_keranjang->komik << ",";
            file << cur_keranjang->harga << ",";
            file << cur_keranjang->jumlah << ",";
            file << cur_keranjang->total << endl;
            cur_keranjang = cur_keranjang->next;
        }
    }
    // menutup file
    file.close();
}

void write_queue(checkout *head) {
	fstream file;
    cur_check = head;
    // membuka file untuk menulis data ke file
    file.open("checkout.csv", ios::trunc | ios::out | ios::in);
    if (file.is_open()){
        // traversal
        while (cur_check != NULL){
            file << cur_check->username << ",";
            file << cur_check->nama << ",";
            file << cur_check->id_komik << ",";
            file << cur_check->komik << ",";
            file << cur_check->harga << ",";
            file << cur_check->jumlah << ",";
            file << cur_check->total << ",";
            file << cur_check->status << endl;
            cur_check = cur_check->next;
        }
    }
    // menutup file
    file.close();
}

void write_riwayat(riwayat *head){
	fstream file;
    riwayat *temp = head;
    // membuka file untuk menulis data ke file
    file.open("riwayat.csv", ios::trunc | ios::out | ios::in);
    if (file.is_open()){
        // traversal
        while (temp != NULL){
            file << temp->username << ",";
            file << temp->nama << ",";
            file << temp->id_komik << ",";
            file << temp->komik << ",";
            file << temp->harga<< ",";
            file << temp->jumlah << ",";
            file << temp->total << ",";
            file << temp->status << endl;
            temp = temp->next;
        }
    }
    // menutup file
    file.close();
}

// UNTUK MENAMPILKAN DAFTAR KOMIK DARI DEPAN
void display_komik(komik *head) {
	system("cls");
	// UNTUK MENGECEK APAKAH LINKED LIST NYA SUDAH ADA ISINYA ATAU BELUM
	if (head == NULL){
		cout << "-----------------------------------------------" << endl;
		cout << "              DAFTAR KOMIK KOSONG              " << endl;
		cout << "-----------------------------------------------" << endl;
		cout << "\nSilahkan tambahkan komik terlebih dahulu..."; getch();
	} else {
		string baris(117, '=');
		cout << baris << endl;
		cout << "|                                       <<~~~  Daftar Komik Yang Dijual  ~~~>>                                      |" << endl;
		cout << baris << endl;
		cout << "| "<< setiosflags(ios::left) << setw(5) << "No" << "|";
        cout << " " << setiosflags(ios::left) << setw(9) << "ID Komik" << "|";
        cout << " " << setiosflags(ios::left) << setw(20) << "Judul Komik" << "|";
        cout << " " << setiosflags(ios::left) << setw(12) << "Genre Komik" << "|";
        cout << " " << setiosflags(ios::left) << setw(16) << "Penulis" << "|";
		cout << " " << setiosflags(ios::left) << setw(15) << "Jumlah Halaman" << "|";
		cout << " " << setiosflags(ios::left) << setw(12) << "Jumlah Stok" << "|";
		cout << " " << setiosflags(ios::left) << setw(11) << "Harga" << "|" << endl;
		cout << baris << endl;
		// VARIABEL i DIGUNAKAN UNTUK MENAMPILKAN URUTAN INDEKS NYA
		int i = 1;
		while (head != NULL) {
//			cout << "Nomor [" << (i) << "]: " << endl;
//			cout << "ID Komik             : " << head->id << endl;
//			cout << "Judul Buku Komik     : " << head->nama << endl;
//			cout << "Genre Buku komik     : " << head->genre << endl;
//			cout << "Penulis Komik        : " << head->penulis << endl;
//			cout << "Jumlah Halaman Komik : " << head->halaman << endl;
//			cout << "Jumlah Stok Komik    : " << head->stok << endl;
//			cout << "Harga Komik          : Rp" << head->harga << endl;
//			cout << "_______________________________________________" << endl;
			cout << resetiosflags(ios::adjustfield);
	        cout << "| ["<< i << setiosflags(ios::left) << setw(3) << "]" << "|";
	        cout << " " << setiosflags(ios::left) << setw(9) << head->id << "|";
	        cout << " " << setiosflags(ios::left) << setw(20) << head->nama << "|";
	        cout << " " << setiosflags(ios::left) << setw(12) << head->genre << "|";
	        cout << " " << setiosflags(ios::left) << setw(16) << head->penulis << "|";
			cout << " " << setiosflags(ios::left) << setw(15) << head->halaman << "|";
			cout << " " << setiosflags(ios::left) << setw(12) << head->stok << "|";
			cout << " Rp. " << setiosflags(ios::left) << setw(7) << head->harga << "|";
			cout << endl;
			tail = head;
			head = head->next;
			i++;
		}
		cout << resetiosflags(ios::adjustfield);
		cout << baris << endl;
	}
}

int cek_keranjang(string username, keranjang *head){
	cur_keranjang = head;
	while (cur_keranjang != NULL){
		if (cur_keranjang->username == username){
			return 1;
		} else {
			cur_keranjang = cur_keranjang->next;
		}
	}
	return -1;
}

void display_keranjang(string username, keranjang *head){
	cur_keranjang = head;
	system("cls");
	// UNTUK MENGECEK APAKAH LINKED LIST NYA SUDAH ADA ISINYA ATAU BELUM
	if (cek_keranjang(username, head) == -1){\
		cout << "---------------------------------------------------" << endl;
		cout << "              DAFTAR KERANJANG KOSONG              " << endl;
		cout << "---------------------------------------------------" << endl;
	} else {
		string baris(72, '=');
		cout << baris << endl;
		cout << "|              <<~~~  Daftar Keranjang Pesanan Anda  ~~~>>             |" << endl;
		cout << baris << endl;
		cout << "| "<< setiosflags(ios::left) << setw(5) << "No" << "|";
        cout << " " << setiosflags(ios::left) << setw(9) << "ID Komik" << "|";
        cout << " " << setiosflags(ios::left) << setw(20) << "Judul Komik" << "|";
		cout << " " << setiosflags(ios::left) << setw(15) << "Jumlah Pesanan" << "|";
		cout << " " << setiosflags(ios::left) << setw(12) << "Total Harga" << "|" << endl;
		cout << baris << endl;
		// VARIABEL i DIGUNAKAN UNTUK MENAMPILKAN URUTAN INDEKS NYA
		int i = 1;
		while (cur_keranjang != NULL) {
			if (cur_keranjang->username == username){
//				cout << "Nomor [" << i << "]: " << endl;
//				cout << "ID Komik       : " << cur_keranjang->id_komik << endl;
//				cout << "Judul Komik    : " << cur_keranjang->komik << endl;
//				cout << "Jumlah Pesanan : " << cur_keranjang->jumlah << endl;
//				cout << "Total Harga    : Rp" << cur_keranjang->total << endl;
//				cout << "___________________________________________________" << endl;
				cout << resetiosflags(ios::adjustfield);
		        cout << "| ["<< i << setiosflags(ios::left) << setw(3) << "]" << "|";
		        cout << " " << setiosflags(ios::left) << setw(9) << cur_keranjang->id_komik << "|";
		        cout << " " << setiosflags(ios::left) << setw(20) << cur_keranjang->komik << "|";
				cout << " " << setiosflags(ios::left) << setw(15) << cur_keranjang->jumlah << "|";
				cout << " Rp. " << setiosflags(ios::left) << setw(8) << cur_keranjang->total << "|";
				cout << endl;
				i++;
			}
			cur_keranjang = cur_keranjang->next;
		}
		cout << resetiosflags(ios::adjustfield);
		cout << baris << endl;
	}
}

void tambah_riwayat(riwayat **head, checkout *temp, string status){
	riwayat *newNode = new riwayat;
	riwayat *add = *head;
	newNode->username = temp->username;
	newNode->nama = temp->nama;
	newNode->id_komik = temp->id_komik;
	newNode->komik = temp->komik;
	newNode->harga = temp->harga;
	newNode->jumlah = temp->jumlah;
	newNode->total= temp->total;
	newNode->status = status;
	if (*head == NULL){
		*head = newNode;
	} else {
		while (add->next != NULL){
			add = add->next;
		}
		add->next = newNode;
	}
}

void display_queue(checkout *head){
	cur_check = head;
	system("cls");
	// UNTUK MENGECEK APAKAH LINKED LIST NYA SUDAH ADA ISINYA ATAU BELUM
	if (head == NULL){
			cout << "---------------------------------------------------" << endl;
			cout << "               DAFTAR ANTRIAN KOSONG               " << endl;
			cout << "---------------------------------------------------"; getch();
	} else {
		string baris(121, '=');
		cout << baris << endl;
		cout << "|                                         <<~~~  Daftar Antrian Pesanan  ~~~>>                                          |" << endl;
		cout << baris << endl;
		cout << "| "<< setiosflags(ios::left) << setw(5) << "No" << "|";
        cout << " " << setiosflags(ios::left) << setw(20) << "Pesanan Atas Nama" << "|";
        cout << " " << setiosflags(ios::left) << setw(9) << "ID Komik" << "|";
        cout << " " << setiosflags(ios::left) << setw(20) << "Judul Komik" << "|";
		cout << " " << setiosflags(ios::left) << setw(11) << "Harga" << "|";
		cout << " " << setiosflags(ios::left) << setw(15) << "Jumlah Pesanan" << "|";
		cout << " " << setiosflags(ios::left) << setw(12) << "Total Harga" << "|";
		cout << " " << setiosflags(ios::left) << setw(12) << "Status" << "|" << endl;
		cout << baris << endl;
		// VARIABEL i DIGUNAKAN UNTUK MENAMPILKAN URUTAN INDEKS NYA
		int i = 1;
		// cout << "\n===================================================" << endl;
		// cout << "     ~~~>>>  Daftar Antrian Pesanan  <<<~~~      " << endl;
		// cout << "===================================================" << endl;
		while (cur_check != NULL) {
			// cout << "Nomor [" << (i) << "]: " << endl;
			// cout << "Pesanan Atas Nama : " << cur_check->nama << endl;
			// cout << "ID Buku Komik     : " << cur_check->id_komik << endl;
			// cout << "Judul Buku Komik  : " << cur_check->komik << endl;
			// cout << "Harga Buku Komik  : Rp" << cur_check->harga<< endl;
			// cout << "Jumlah Pesanan    : " << cur_check->jumlah << endl;
			// cout << "Total Harga       : Rp." << cur_check->total << endl;
			// cout << "Status            : " << cur_check->status << endl;
			// cout << "___________________________________________________\n" << endl;
			cout << resetiosflags(ios::adjustfield);
	        cout << "| ["<< i << setiosflags(ios::left) << setw(3) << "]" << "|";
	        cout << " " << setiosflags(ios::left) << setw(20) << cur_check->nama << "|";
	        cout << " " << setiosflags(ios::left) << setw(9) << cur_check->id_komik << "|";
	        cout << " " << setiosflags(ios::left) << setw(20) << cur_check->komik << "|";
			cout << " Rp. " << setiosflags(ios::left) << setw(7) << cur_check->harga << "|";
	        cout << " " << setiosflags(ios::left) << setw(15) << cur_check->jumlah << "|";
			cout << " Rp. " << setiosflags(ios::left) << setw(8) << cur_check->total << "|";
			cout << " " << setiosflags(ios::left) << setw(12) << cur_check->status << "|";
			cout << endl;
			cur_check = cur_check->next;
			i++;
		}
		cout << resetiosflags(ios::adjustfield);
		cout << baris << endl;
		cout << "\nTekan ENTER Untuk Melanjutkan..."; getch();
	}
}

void konfirmasi_queue(checkout **head, riwayat **HEAD, komik *kmk){
	komik *temp = kmk;
	char confirm;
	system("cls");
	// UNTUK MENGECEK APAKAH LINKED LIST NYA SUDAH ADA ISINYA ATAU BELUM
	if (*head == NULL){
		cout << "---------------------------------------------------" << endl;
		cout << "               DAFTAR ANTRIAN KOSONG               " << endl;
		cout << "---------------------------------------------------"; getch();
	} else {
		// VARIABEL i DIGUNAKAN UNTUK MENAMPILKAN URUTAN INDEKS NYA
		int i = 1;
		cur_check = *head;
		while (cur_check != NULL) {
			while (true){
				system("cls");
				cout << "\n===================================================" << endl;
				cout << "     ~~~>>>    Konfirmasi Pesananan    <<<~~~      " << endl;
				cout << "===================================================" << endl;
				cout << "Nomor [" << (i) << "]: " << endl;
				cout << "Pesanan Atas Nama : " << cur_check->nama << endl;
				cout << "ID Buku Komik     : " << cur_check->id_komik << endl;
				cout << "Judul Buku Komik  : " << cur_check->komik << endl;
				cout << "Harga Buku Komik  : Rp" << cur_check->harga<< endl;
				cout << "Jumlah Pesanan    : " << cur_check->jumlah << endl;
				cout << "Total Harga       : Rp." << cur_check->total << endl;
				cout << "Status Pesanan    : " << cur_check->status << endl;
				cout << "___________________________________________________\n" << endl;
				cout << "\nTekan B Jika Ingin Kembali Ke Menu Utama" << endl;
				cout << "\nKonfirmasi Pesanan Berhasil (y/n) : "; confirm = getch();
				checkout *hapus = cur_check;
				if (confirm == 'y' || confirm == 'Y'){
					*head = (*head)->next;
					while (temp != NULL){
						if (temp->id == cur_check->id_komik){
							if (temp->stok >= cur_check->jumlah){
								temp->stok = temp->stok - cur_check->jumlah;
								tambah_riwayat(HEAD, cur_check, "Berhasil");
							} else {
								tambah_riwayat(HEAD, cur_check, "Stok Tidak Mencukupi");
							}
							break;
						}
						temp = temp->next;
					}
					delete hapus;
					break;
				} else if (confirm == 'n' || confirm == 'N'){
					*head = (*head)->next;
					tambah_riwayat(HEAD, cur_check, "Gagal");
					delete hapus;
					break;
				} else if (confirm == 'b' || confirm == 'B'){
					break;
				} else {
					cout << "\n\nInput Yang Anda Masukkan Tidak Sesuai!"; getch();
				}
			}
			if (confirm == 'b' || confirm == 'B'){
				break;
			} 
			cur_check = cur_check->next;
			i++;
		}
		write_komik(kmk);
		write_queue(*head);
		write_riwayat(*HEAD);
	}
}

int cek_checkout(string username, checkout *head){
	cur_check = head;
	while (cur_check != NULL){
		if (cur_check->username == username){
			return 1;
		} else {
			cur_check = cur_check->next;
		}
	}
	return -1;
}

void display_checkout(string username, checkout *head){
	cur_check = head;
	system("cls");
	if (cek_checkout(username, head) == -1){\
		cout << "--------------------------------------------------" << endl;
		cout << " >> Daftar Komik Yang Telah Di Checkout Kosong << " << endl;
		cout << "--------------------------------------------------" << endl;
		cout << "\nSilahkan checkout pesanan terlebih dahulu..."; getch();
	} else {
		string baris(110, '=');
		cout << baris << endl;
		cout << "|                              <<~~~  Daftar Komik Yang Telah Di Checkout  ~~~>>                             |" << endl;
		cout << baris << endl;
		cout << "| "<< setiosflags(ios::left) << setw(5) << "No" << "|";
        cout << " " << setiosflags(ios::left) << setw(20) << "Pesanan Atas Nama" << "|";
        cout << " " << setiosflags(ios::left) << setw(20) << "Judul Komik" << "|";
		cout << " " << setiosflags(ios::left) << setw(11) << "Harga" << "|";
		cout << " " << setiosflags(ios::left) << setw(15) << "Jumlah Pesanan" << "|";
		cout << " " << setiosflags(ios::left) << setw(12) << "Total Harga" << "|";
		cout << " " << setiosflags(ios::left) << setw(12) << "Status" << "|" << endl;
		cout << baris << endl;
		// cout << "===================================================" << endl;
		// cout << " ~~~>>  Daftar Komik Yang Telah Di Checkout  <<~~~ " << endl;
		// cout << "===================================================" << endl;
		int i = 1;
		while (cur_check != NULL) {
			if (cur_check->username == username){
				// cout << "Nomor [" << i << "]: " << endl;
				// cout << "Pesanan Atas Nama : " << cur_check->nama << endl;
				// cout << "Judul Buku Komik  : " << cur_check->komik << endl;
				// cout << "Harga Buku Komik  : Rp" << cur_check->harga << endl;
				// cout << "Jumlah Pesanan    : " << cur_check->jumlah << endl;
				// cout << "Total Harga       : Rp" << cur_check->total << endl;
				// cout << "Status Pesanan    : " << cur_check->status << endl;
				// cout << "___________________________________________________" << endl;
				cout << resetiosflags(ios::adjustfield);
				cout << "| ["<< i << setiosflags(ios::left) << setw(3) << "]" << "|";
				cout << " " << setiosflags(ios::left) << setw(20) << cur_check->nama << "|";
				cout << " " << setiosflags(ios::left) << setw(20) << cur_check->komik << "|";
				cout << " Rp. " << setiosflags(ios::left) << setw(7) << cur_check->harga << "|";
				cout << " " << setiosflags(ios::left) << setw(15) << cur_check->jumlah << "|";
				cout << " Rp. " << setiosflags(ios::left) << setw(8) << cur_check->total << "|";
				cout << " " << setiosflags(ios::left) << setw(12) << cur_check->status << "|";
				cout << endl;
				i++;
			}
			cur_check = cur_check->next;
		}
		cout << resetiosflags(ios::adjustfield);
		cout << baris << endl;
		cout << "\nTekan ENTER Untuk Melanjutkan..."; getch();
	}
}

void display_riwayat(riwayat *head){
	riwayat *temp = head;
	system("cls");
	if (head == NULL){
		cout << "==================================================" << endl;
		cout << "  >>  Daftar Riwayat Pemesanan Komik Kosong  <<   " << endl;
		cout << "=================================================="; getch();
	} else {
		string baris(110, '=');
		cout << baris << endl;
		cout << "|                               <<~~~  Daftar Riwayat Pemesanan Komik  ~~~>>                                 |" << endl;
		cout << baris << endl;
		cout << "| "<< setiosflags(ios::left) << setw(5) << "No" << "|";
        cout << " " << setiosflags(ios::left) << setw(20) << "Pesanan Atas Nama" << "|";
        cout << " " << setiosflags(ios::left) << setw(20) << "Judul Komik" << "|";
		cout << " " << setiosflags(ios::left) << setw(11) << "Harga" << "|";
		cout << " " << setiosflags(ios::left) << setw(15) << "Jumlah Pesanan" << "|";
		cout << " " << setiosflags(ios::left) << setw(12) << "Total Harga" << "|";
		cout << " " << setiosflags(ios::left) << setw(12) << "Status" << "|" << endl;
		cout << baris << endl;
		// cout << "===================================================" << endl;
		// cout << "   <<~~~  Daftar Riwayat Pemesanan Komik  ~~~>>    " << endl;
		// cout << "===================================================" << endl;
		int i = 1;
		while (temp != NULL) {
			// cout << "Nomor [" << i << "]: " << endl;
			// cout << "Pesanan Atas Nama : " << temp->nama << endl;
			// cout << "Judul Buku Komik  : " << temp->komik << endl;
			// cout << "Harga Buku Komik  : Rp" << temp->harga << endl;
			// cout << "Jumlah Pesanan    : " << temp->jumlah << endl;
			// cout << "Total Harga       : Rp" << temp->total << endl;
			// cout << "Status Pesanan    : " << temp->status << endl;
			// cout << "___________________________________________________" << endl;
			cout << resetiosflags(ios::adjustfield);
	        cout << "| ["<< i << setiosflags(ios::left) << setw(3) << "]" << "|";
	        cout << " " << setiosflags(ios::left) << setw(20) << temp->nama << "|";
	        cout << " " << setiosflags(ios::left) << setw(20) << temp->komik << "|";
			cout << " Rp. " << setiosflags(ios::left) << setw(7) << temp->harga << "|";
	        cout << " " << setiosflags(ios::left) << setw(15) << temp->jumlah << "|";
			cout << " Rp. " << setiosflags(ios::left) << setw(8) << temp->total << "|";
			cout << " " << setiosflags(ios::left) << setw(12) << temp->status << "|";
			cout << endl;
			i++;
			temp = temp->next;
		}
		cout << resetiosflags(ios::adjustfield);
		cout << baris << endl;
		cout << "\nTekan ENTER Untuk Melanjutkan..."; getch();
	}
}

void clear_riwayat(riwayat *head){
	riwayat *temp = head, *hapus;
	while (temp != NULL){
		hapus = temp;
		if (temp->next == NULL){
			head = NULL;
		} else {
			head = head->next;
		}
		delete hapus;
		temp = temp->next;
	}
}

// FUNGSI UNTUK MENGINPUT DATA
komik *tambahKomik(komik **head) {
	bool loop;
	komik *nodeBaru = new komik;
	komik *temp = *head;
	cout << "\n=============== Tambah komik ================" << endl;
	while (loop){
		cout << "Masukkan ID Komik             : "; cin >> nodeBaru->id;
		if (nodeBaru->id > 0){
			while (temp != NULL){
				if (temp->id == nodeBaru->id){
					cout << "\nID Komik Telah Digunakan, Silahkan Gunakan ID Lain\n" << endl;
					break;
				} else {
					temp = temp->next;
				}
				if (temp == NULL){
					loop = false;
				}
			}
		} else {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\nInputan Anda Salah, Silahkan Coba Lagi!\n" << endl;
		}
	}
	while (true){
		cout << "Masukkan Judul Komik          : "; fflush(stdin); getline(cin, nodeBaru->nama);
		if (nodeBaru->nama == ""){
			cout << "\nNama komik tidak boleh kosong!\n" << endl;
		} else {
			break;
		}
	}
	while (true){
		cout << "Masukkan Genre Komik          : "; getline(cin, nodeBaru->genre);
		if (nodeBaru->genre == ""){
			cout << "\nGenre komik tidak boleh kosong!\n" << endl;
		} else {
			break;
		}
	}
	while (true){
		cout << "Masukkan Penulis Komik        : "; getline(cin, nodeBaru->penulis);
		if (nodeBaru->penulis == ""){
			cout << "\nPenulis komik tidak boleh kosong!\n" << endl;
		} else {
			break;
		}
	}
	while (true){
		cout << "Masukkan Jumlah Halaman Komik : "; cin >> nodeBaru->halaman;
		if (nodeBaru->halaman > 0){
			break;
		} else {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\nInputan Anda Salah, Silahkan Coba Lagi!\n" << endl;
		}
	}
	while (true){
		cout << "Masukkan Jumlah Stok Komik    : "; cin >> nodeBaru->stok;
		if (nodeBaru->stok > 0){
			break;
		} else {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\nInputan Anda Salah, Silahkan Coba Lagi!\n" << endl;
		}
	}
	while (true){
		cout << "Masukkan Harga Komik          : Rp"; cin >> nodeBaru->harga;
		if (nodeBaru->harga > 0){
			break;
		} else {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\nInputan Anda Salah, Silahkan Coba Lagi!\n" << endl;
		}
	}
	cout << endl;
	return nodeBaru;
}

akun *tambahAkun(akun **head) {
	akun *nodeBaru = new akun;
	string password;
	bool loop = true;
	cur_akun = *head;
	while (loop){
		system("cls");
		cout << "\n=============== Registrasi Akun ================" << endl;
		while (true){
			cout << "Masukkan Nama Lengkap   : "; fflush(stdin) ; getline(cin, nodeBaru->nama);
			if (nodeBaru->nama == ""){
				cout << "\nNama Tidak Boleh Kosong!\n" << endl;
			} else {
				break;
			}
		}
		cout << "Masukkan Username       : "; cin >> nodeBaru->username;
		cout << "Masukkan Password       : "; cin >> password;
		cout << "Konfirmasi Password     : "; cin >> nodeBaru->password;
		if (*head == NULL){
			break;
		} else if (password != nodeBaru->password){
			cout << "\nPassword Yang Anda Masukkan Berbeda, Silahkan Input Kembali"; getch();
		} else {
			while (cur_akun != NULL){
				if (cur_akun->username == nodeBaru->username){
					cout << "\nUsername Telah Digunakan, Silahkan Gunakan Username Yang Lain"; getch();
					break;
				} else {
					cur_akun = cur_akun->next;
				}
				if (cur_akun == NULL){
					loop = false;
					break;
				}
			}
		}
	}
	return nodeBaru;
}

void registrasi(akun **head){
	akun *node_baru = tambahAkun(head);
	node_baru->next = *head;
	*head = node_baru;
	write_akun(*head);
	cout << "===========================================" << endl;
	cout << "         Berhasil Registrasi Akun!         " << endl;
	cout << "===========================================" << endl;
}

void tambah_keranjang(string username, string nama, komik *HEAD, keranjang **head, checkout **head_check){
	string beli;
	int pilih, jumlah, total;
	display_komik(HEAD);
	komik *temp = HEAD;
	cur_check = *head_check;
	cout << "\n===============================================" << endl;
	cout << "    <<~~~  Form Tambah Pesanan Komik  ~~~>>    " << endl;
	cout << "===============================================" << endl;
	cout << "\nMasukkan Nomor Komik Yang Ingin Dipesan : "; cin >> pilih;
	if (pilih > 0 && pilih <= Jumlah_Data()){
		for (int i = 1 ; i < pilih ; i++){
			temp = temp->next;
		}
		if (temp->stok < 1){
			cout << "\nStok Buku Komik Masih Kosong..."; getch();
		} else {
			system("cls");
			cout << "\n===============================================" << endl;
			cout << "    <<~~~  Form Tambah Pesanan Komik  ~~~>>    " << endl;
			cout << "===============================================" << endl;
			cout << "ID Buku Komik        : " << temp->id << endl;
			cout << "Judul Buku Komik     : " << temp->nama << endl;
			cout << "Genre Buku Komik     : " << temp->genre << endl;
			cout << "Penulis Buku Komik   : " << temp->penulis << endl;
			cout << "Jumlah Halaman Komik : " << temp->halaman << endl;
			cout << "Harga Buku Komik     : Rp" << temp->harga << endl;
			cout << "Jumlah Stok          : " << temp->stok << endl;
			cout << "-----------------------------------------------" << endl;
			while (true){
				cout << "\nIngin Pesan Berapa Banyak Komik : "; cin >> jumlah;
				if (jumlah > 0 && jumlah <= temp->stok){
					break;
				} else if (jumlah > temp->stok) {
					cout << "\nStok Buku Komik Tidak Mencukupi" << endl;
				} else if (jumlah < 1 && jumlah > 0) {
					cout << "\nMinimal Pesan Satu Buku Komik" << endl;
				} else {
					cin.clear();
					cin.ignore(100, '\n');
					cout << "\nInputan Anda Salah, Silahkan Coba Lagi!" << endl;
				}
			}
			total = temp->harga * jumlah;
			keranjang *nodeBaru = new keranjang;
			nodeBaru->username = username;
			nodeBaru->nama = nama;
			nodeBaru->id_komik = temp->id;
			nodeBaru->komik = temp->nama;
			nodeBaru->harga = temp->harga;
			nodeBaru->jumlah = jumlah;
			nodeBaru->total = total;
			while (true){
				system("cls");
				cout << "===============================================" << endl;
				cout << "  <<~~~ Berhasil Menambah Ke Keranjang! ~~~>>  " << endl;
				cout << "===============================================" << endl;
				cout << "Judul Buku Komik  : " << nodeBaru->komik << endl;
				cout << "Harga Buku Komik  : Rp" << nodeBaru->harga << endl;
				cout << "Jumlah Pesanan    : " << nodeBaru->jumlah << endl;
				cout << "Total Harga       : Rp" << nodeBaru->total << endl;
				cout << "----------------------------------------------" << endl;
				cout << "\n  [1] Langsung Checkout " << endl; 
				cout << "  [2] Kembali " << endl; 
				cout << "----------------------------------------------" << endl;
				cout << "Masukkan Pilihan : " ; cin >> beli;
				if (beli == "1"){
					checkout *newNode = new checkout;
					newNode->username = username;
					newNode->nama = nama;
					newNode->id_komik = nodeBaru->id_komik;
					newNode->komik = nodeBaru->komik;
					newNode->harga = nodeBaru->harga;
					newNode->jumlah = nodeBaru->jumlah;
					newNode->total = nodeBaru->total;
					newNode->status = "Menunggu";
					if (*head_check == NULL){
						*head_check = newNode;
					} else {
						while (cur_check->next != NULL){
							cur_check = cur_check->next;
						}
						cur_check->next = newNode;
					}
					write_queue(*head_check);
					system("cls");
					cout << "\n===============================================" << endl;
					cout << "    <<~~~  Berhasil Checkout Pesanan!  ~~~>>   " << endl;
					cout << "===============================================" << endl;
					cout << "Pesanan Atas Nama : " << newNode->nama << endl;
					cout << "Judul Buku Komik  : " << newNode->komik << endl;
					cout << "Harga Buku Komik  : Rp" << newNode->harga << endl;
					cout << "Jumlah Pesanan    : " << newNode->jumlah << endl;
					cout << "Total Harga       : Rp" << newNode->total << endl;
					cout << "Status Pesanan    : " << newNode->status << endl;
					cout << "----------------------------------------------" << endl;
					cout << "\nTekan ENTER Untuk Melanjutkan..."; getch();
					break;
				} else if (beli == "2"){
					nodeBaru->next = *head;
					*head = nodeBaru;
					write_keranjang(*head);
					break;
				} else {
					cout << "\nPilihan Menu Tidak Ditemukan" << endl;
				}
			}
		}
	} else if (pilih < 0 || pilih > Jumlah_Data()){
		cout << "\nNomor Yang Anda Masukkan Diluar Range Data Komik!" << endl;
		cout << "\nTekan ENTER Untuk Melanjutkan..."; getch();
	} else {
		cin.clear();
		cin.ignore(100, '\n');
		cout << "\nInputan Anda Salah!"; getch();
	}
}

int hitung_keranjang(string username, keranjang **head){
	cur_keranjang = *head;
	int hasil = 0;
	while (cur_keranjang != NULL){
		if (cur_keranjang->username == username){
			hasil+=1;
		}
		cur_keranjang = cur_keranjang->next;
	}
	return hasil;
}

void update_keranjang(string username, keranjang **head, komik **kmk){
	keranjang *temp = *head;
	komik *cek = *kmk;
	int no, harga, jumlah;
	system("cls");
	if (cek_keranjang(username, *head) == -1){
		cout << "-----------------------------------------------" << endl;
		cout << "            DAFTAR KERANJANG KOSONG            " << endl;
		cout << "-----------------------------------------------" << endl;
		cout << "\nSilahkan tambah pesanan terlebih dahulu..."; getch();
	} else {
		display_keranjang(username, *head);
		cout << "\nMasukkan Nomor Data Yang Ingin Diupdate : "; cin >> no;
		if (no < 0 || no > hitung_keranjang(username, head)){
			cout << "\nNomor Yang Anda Masukkan Tidak Sesuai!"; getch();
		} else if (no > 0 && no <= hitung_keranjang(username, head)){
			for (int i = 1; i < no ; i++){
                temp = temp->next;
            }
			while (cek->id != temp->id_komik){
				cek = cek->next;
			}
			while (true){
				system("cls");
				cout << "Nomor [" << no << "]: " << endl;
				cout << "ID Komik       : " << temp->id_komik << endl;
				cout << "Judul Komik    : " << temp->komik << endl;
				cout << "Jumlah Pesanan : " << temp->jumlah << endl;
				cout << "Total Harga    : Rp" << temp->total << endl;
				harga = temp->total / temp->jumlah;
				cout << "_______________________________________________\n" << endl;
				cout << "===============================================" << endl;
				cout << "   ~~~>>  Ubah Data Keranjang Menjadi  <<~~~   " << endl;
				cout << "===============================================" << endl;
				cout << "Jumlah Pesanan : "; cin >> jumlah;
				if (jumlah > 0){
					if (jumlah <= cek->stok){
						temp->jumlah = jumlah;
						temp->total = harga * temp->jumlah;
						write_keranjang(*head);
						system("cls");
						cout << "\n===============================================" << endl;
						cout << "  ~~~>> Berhasil Update Data Keranjang! <<~~~  " << endl;
						cout << "===============================================" << endl;
						cout << "Nomor [" << no << "]: " << endl;
						cout << "ID Komik       : " << temp->id_komik << endl;
						cout << "Judul Komik    : " << temp->komik << endl;
						cout << "Jumlah Pesanan : " << temp->jumlah << endl;
						cout << "Total Harga    : Rp" << temp->total << endl;
						cout << "_______________________________________________" << endl;
						cout << "\nTekan ENTER Untuk Melanjutkan..." ; getch();
					} else {
						cout << "\nJumlah Stok Buku Komik Tidak Mencukupi!"; getch();
					}
					break;
				} else {
					cin.clear();
					cin.ignore(100, '\n');
					cout << "\nInputan Anda Salah, Silahkan Coba Lagi!"; getch();
				}
			}
		} else {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\nInputan Anda Salah!"; getch();
		}
	}
}

void hapus_keranjang(string username, keranjang **head){
	keranjang *temp = *head;
	keranjang *temp_hapus = *head;
	int no, tanda = 0;
	system("cls");
	if (cek_keranjang(username, *head) == -1){
		cout << "-----------------------------------------------" << endl;
		cout << "            DAFTAR KERANJANG KOSONG            " << endl;
		cout << "-----------------------------------------------" << endl;
		cout << "\nSilahkan tambah pesanan terlebih dahulu..."; getch();
	} else {
		display_keranjang(username, *head);
		cout << "\nMasukkan Nomor Data Yang Ingin Dihapus : "; cin >> no;
		if (no < 0 || no > hitung_keranjang(username, head)){
			cout << "\nNomor Yang Anda Masukkan Tidak Sesuai!"; getch();
		} else if (no > 0 && no <= hitung_keranjang(username, head)){
			while (tanda != no){
				if (temp_hapus->username == username){
					tanda += 1;
				} else {
					temp_hapus = temp_hapus->next;
				}
			}
			if (temp_hapus == *head){
				*head = (*head)->next;
			} else {
				tanda = 0;
				while (tanda != no-1){
					if (temp->username == username){
						tanda += 1;
					} else {
						temp = temp->next;
					}
				}
				temp->next = temp_hapus->next;
			}
			delete temp_hapus;
			write_keranjang(*head);
			cout << "\n===============================================" << endl;
			cout << "   ~~~>> Berhasil Hapus Data Keranjang! <<~~~  " << endl;
			cout << "===============================================" << endl;
			cout << "\nTekan ENTER Untuk Melanjutkan..." ; getch();
		} else {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\nInputan Anda Salah!"; getch();
		}
	} 
}

void enqueue_pesanan(string username, string nama, keranjang **head, checkout **HEAD){
	keranjang *temp_hapus = *head;
	cur_check = *HEAD;
	keranjang *temp = *head;
	int no, tanda = 0;
	display_keranjang(username, *head);
	cout << "\nIngin Checkout Data Keranjang Nomor Berapa : "; cin >> no;
	if (no < 0 || no > hitung_keranjang(username, head)){
		cout << "\nNomor Yang Anda Masukkan Tidak Sesuai!"; getch();
	} else if (no > 0 && no <= hitung_keranjang(username, head)) {
		while (tanda != no){
			if (temp_hapus->username == username){
				tanda += 1;
			} else {
				temp_hapus = temp_hapus->next;
			}
		}
		checkout *newNode = new checkout;
		newNode->username = temp_hapus->username;
		newNode->nama = nama;
		newNode->id_komik = temp_hapus->id_komik;
		newNode->komik = temp_hapus->komik;
		newNode->harga = temp_hapus->harga;
		newNode->jumlah = temp_hapus->jumlah;
		newNode->total = temp_hapus->total;
		// newNode->waktu = waktu;
		newNode->status = "Menunggu";
		if (*HEAD == NULL){
			*HEAD = newNode;
		} else {
			while (cur_check->next != NULL){
				cur_check = cur_check->next;
			}
			cur_check->next = newNode;
		}
		write_queue(*HEAD);
		if (temp_hapus == *head){
			*head = (*head)->next;
		} else {
			tanda = 0;
			while (tanda != no-1){
				if (temp->username == username){
					tanda += 1;
				} else {
					temp = temp->next;
				}
			}
			temp->next = temp_hapus->next;
		}
		delete temp_hapus;
		write_keranjang(*head);
		system("cls");
		cout << "\n===================================================" << endl;
		cout << "     <<~~~  Berhasil Checkout Pesanan!  ~~~>>      " << endl;
		cout << "===================================================" << endl;
		cout << "Pesanan Atas Nama : " << newNode->username << endl;
		cout << "Judul Buku Komik  : " << newNode->komik << endl;
		cout << "Harga Buku Komik  : Rp" << newNode->harga << endl;
		cout << "Jumlah Pesanan    : " << newNode->jumlah << endl;
		cout << "Total Harga       : Rp" << newNode->total << endl;
		cout << "Status Pesanan    : " << newNode->status << endl;
		cout << "---------------------------------------------------" << endl;
		cout << "\nTekan ENTER Untuk Melanjutkan..." ; getch();
	} else {
		cin.clear();
		cin.ignore(100, '\n');
		cout << "\nInputan Anda Salah!"; getch();
	}
}

int cek_riwayat_user(string username, riwayat *head){
	riwayat *temp = head;
	while (temp != NULL){
		if (temp->username == username){
			return 1;
			break;
		}
		temp = temp->next;
	}
	return -1;
}

void display_riwayat_user(string username, riwayat *head){
	riwayat *temp = head;
	system("cls");
	if (cek_riwayat_user(username, head) == -1){
		cout << "==================================================" << endl;
		cout << "  >>  Daftar Riwayat Pemesanan Komik Kosong  <<   " << endl;
		cout << "=================================================="; getch();
	} else {
		cout << "===================================================" << endl;
		cout << "   <<~~~  Daftar Riwayat Pemesanan Komik  ~~~>>    " << endl;
		cout << "===================================================" << endl;
		int i = 1;
		while (temp != NULL) {
			if (temp->username == username){
				cout << "Nomor [" << i << "]: " << endl;
				cout << "Pesanan Atas Nama : " << temp->nama << endl;
				cout << "Judul Buku Komik  : " << temp->komik << endl;
				cout << "Harga Buku Komik  : Rp" << temp->harga << endl;
				cout << "Jumlah Pesanan    : " << temp->jumlah << endl;
				cout << "Total Harga       : Rp" << temp->total << endl;
				cout << "Status Pesanan    : " << temp->status << endl;
				cout << "___________________________________________________" << endl;
				i++;
			}
			temp = temp->next;
		}
		cout << "\nTekan ENTER Untuk Melanjutkan..."; getch();
	}
}

// UNTUK MENAMBAH DATA DI AWAL LINKED LIST
void addFirst(komik **head, komik **tail) {
	komik *nodeBaru = tambahKomik(head);
    nodeBaru->prev = NULL;
    nodeBaru->next = NULL;
	if (*head == NULL){
		*head = nodeBaru;
		*tail = nodeBaru;
	}else{
		nodeBaru->prev = NULL;
		nodeBaru->next = *head;
		(*head)->prev = nodeBaru;
		*head = nodeBaru;
	}
	write_komik(*head);
	cout << "==========================================" << endl;
	cout << "Data berhasil ditambahkan ke node pertama!" << endl;
	cout << "==========================================" ; getch();
}

// UNTUK MENAMBAH DATA DI TENGAH LINKED LIST
void addMiddle(komik **head, komik **tail) {
	komik *nodeBaru = tambahKomik(head);
	int nomor;
	int ulang = 0;
	while (ulang == 0) {
		cout << "Masukkan Data Ke Nomor : ";
		cin >> nomor;
		if (nomor > 1 && nomor < Jumlah_Data()+1) {
			cur = *head;
			int Nomor = 1;
			while(Nomor < nomor-1){
				cur = cur->next;
				Nomor++;
			}
			cur->next->prev = nodeBaru;
			nodeBaru->next = cur->next;
			cur->next = nodeBaru;
			nodeBaru->prev = cur;
			cout << endl;
			write_komik(*head);
			cout << "========================================" << endl;
			cout << "Data berhasil ditambahkan diantara node!" << endl;
			cout << "========================================"; getch();
			ulang++;
		} else {
			cout << "Data harus diletakkan diantara node!" << endl;
		}
	}	
}

// UNTUK MENAMBAH DATA DI AKHIR LINKED LIST
void addLast(komik **head, komik **tail) {
	komik *nodeBaru = tambahKomik(head);
	if (Jumlah_Data() >= 1) {
		nodeBaru->next = NULL;
		nodeBaru->prev = *tail;
		if (*head == NULL && *tail == NULL) {
			*head = nodeBaru;
			*tail = nodeBaru;
			return;
		}
		(*tail)->next = nodeBaru;
		*tail = nodeBaru;
	} else {
    	nodeBaru->prev = NULL;
    	nodeBaru->next = NULL;
		*head = nodeBaru;
		*tail = nodeBaru;
	}
	write_komik(*head);
	cout << "===========================================" << endl;
	cout << "Data berhasil ditambahkan ke node terakhir!" << endl;
	cout << "==========================================="; getch();
}

// UNTUK MENGEDIT DATA YANG DI INGINKAN DALAM LINKED LIST
void ubah(komik **head, komik **tail) {
	int no;
	bool loop = true;
	komik *temp = *head;
	if (*head == NULL && *tail == NULL){
		cout << "-----------------------------------------------" << endl;
		cout << "              DAFTAR KOMIK KOSONG              " << endl;
		cout << "-----------------------------------------------" << endl;
		cout << "\nSilahkan tambahkan komik terlebih dahulu..."; getch();
	} else {
		display_komik(*head);
		cout << "\n===============================================" << endl;
		cout << "      <<<~~~   Update Data Komik   ~~~>>>      " << endl;
		cout << "===============================================" << endl;
		cout << "Masukkan Nomor Data Yang Ingin Diupdate : "; cin >> no;
		if (no < 1 || no > Jumlah_Data()){
			cout << "\nNomor Yang Anda Masukkan Tidak Sesuai!"; getch();
		} else if (no > 0 && no <= Jumlah_Data()){
			cur = *head;
			for (int i = 1 ; i < no ; i++){
				cur = cur->next;
			}
			system("cls");
			cout << "ID Komik             : " << cur->id << endl;
			cout << "Judul Buku Komik     : " << cur->nama << endl;
			cout << "Genre Buku komik     : " << cur->genre << endl;
			cout << "Penulis Komik        : " << cur->penulis << endl;
			cout << "Jumlah Halaman Komik : " << cur->halaman << endl;
			cout << "Jumlah Stok Komik    : " << cur->stok << endl;
			cout << "Harga Komik          : Rp" << cur->harga << endl;
			cout << "\n===============================================" << endl;
			cout << "   <<<~~~  Update Data Komik Menjadi  ~~~>>>   " << endl;
			cout << "===============================================" << endl;
			while (loop){
				cout << "Masukkan ID Komik             : "; cin >> cur->id;
				if (cur->id > 0){
					int cek = 1;
					while (temp != NULL){
						if (temp->id == cur->id){
							if (cek == no){
								loop = false;
							} else {
								cout << "\nID Komik Telah Digunakan, Silahkan Gunakan ID Lain\n" << endl;
							}
							break;
						} else {
							temp = temp->next;
							cek += 1;
						}
						if (temp == NULL){
							loop = false;
						}
					}
				} else {
					cin.clear();
					cin.ignore(100, '\n');
					cout << "\nInputan Anda Salah, Silahkan Coba Lagi!\n" << endl;
				}
			}
			while (true){
				cout << "Masukkan Judul Komik          : "; fflush(stdin); getline(cin, cur->nama);
				if (cur->nama == ""){
					cout << "\nJudul Komik Tidak Boleh Kosong!\n" << endl;
				} else {
					break;
				}
			}
			while (true){
				cout << "Masukkan Genre Komik          : "; fflush(stdin); getline(cin, cur->genre);
				if (cur->genre == ""){
					cout << "\nGenre Komik Tidak Boleh Kosong!\n" << endl;
				} else {
					break;
				}
			}
			while (true){
				cout << "Masukkan Penulis Komik        : "; fflush(stdin); getline(cin, cur->penulis);
				if (cur->penulis == ""){
					cout << "\nPenulis Komik Tidak Boleh Kosong!\n" << endl;
				} else {
					break;
				}
			}
			while (true){
				cout << "Masukkan Jumlah Halaman Komik : "; cin >> cur->halaman;
				if (cur->halaman > 0){
					break;
				} else {
					cin.clear();
					cin.ignore(100, '\n');
					cout << "\nInputan Anda Salah, Silahkan Coba Lagi!\n" << endl;
				}
			}
			while (true){
				cout << "Masukkan Jumlah Stok Komik    : "; cin >> cur->stok;
				if (cur->stok > 0){
					break;
				} else {
					cin.clear();
					cin.ignore(100, '\n');
					cout << "\nInputan Anda Salah, Silahkan Coba Lagi!\n" << endl;
				}
			}
			while (true){
				cout << "Masukkan Harga Komik          : Rp"; cin >> cur->harga;
				if (cur->harga > 0){
					break;
				} else {
					cin.clear();
					cin.ignore(100, '\n');
					cout << "\nInputan Anda Salah, Silahkan Coba Lagi!\n" << endl;
				}
			}
			system("cls");
			cout << "\n===============================================" << endl;
			cout << "   ~~~>>  Berhasil Update Data Komik!  <<~~~   " << endl;
			cout << "===============================================" << endl;
			cout << "ID Komik             : " << cur->id << endl;
			cout << "Judul Buku Komik     : " << cur->nama << endl;
			cout << "Genre Buku komik     : " << cur->genre << endl;
			cout << "Penulis Komik        : " << cur->penulis << endl;
			cout << "Jumlah Halaman Komik : " << cur->halaman << endl;
			cout << "Jumlah Stok Komik    : " << cur->stok << endl;
			cout << "Harga Komik          : Rp" << cur->harga << endl;
			cout << "_______________________________________________" << endl;
			write_komik(*head);
			cout << "\nTekan ENTER Untuk Melanjutkan..." ; getch();
		} else {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\nInputan Anda Salah!"; getch();
		}
	}
}

void deleteComic(komik **head, komik **tail){
	int no;
	if (*head == NULL && *tail == NULL){
		cout << "-----------------------------------------------" << endl;
		cout << "              DAFTAR KOMIK KOSONG              " << endl;
		cout << "-----------------------------------------------" << endl;
		cout << "\nSilahkan tambahkan komik terlebih dahulu..."; getch();
	} else {
		display_komik(*head);
		cout << "\n===============================================" << endl;
		cout << "      <<<~~~   Hapus Data Komik   ~~~>>>       " << endl;
		cout << "===============================================" << endl;
		cout << "Masukkan Nomor Data Yang Ingin Dihapus : "; cin >> no;
		if (no < 0 || no > Jumlah_Data()){
			cout << "\nNomor Yang Anda Masukkan Tidak Sesuai!"; getch();
		} else if (no > 0 && no <= Jumlah_Data()){
			if (no == 1 && no == Jumlah_Data()){
				*head = NULL;
				*tail = NULL;
			} else if (no == 1){
				*head = (*head)->next;
				(*head)->prev = NULL;
			} else if (no == Jumlah_Data()){
				*tail = (*tail)->prev;
				(*tail)->next = NULL;
			} else {
				cur = *head;
				for (int i = 1 ; i < no ; i++){
					cur = cur->next;
				}
				cur->prev->next = cur->next;
				cur->next->prev = cur->prev;
			}
			write_komik(*head);
			cout << "\n===============================================" << endl;
			cout << "    ~~~>>  Berhasil Hapus Data Komik!  <<~~~   " << endl;
			cout << "===============================================" << endl;
			cout << "\nTekan ENTER Untuk Melanjutkan..." ; getch();
		} else {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\nInputan Anda Salah!"; getch();
		}
	}
}

// VOID MENU TAMBAH UNTUK MEMILIH OPSI TAMBAH YANG DI INGINKAN
void menuTambah() {
	system("cls");
	cout << "\n===============================================" << endl;
	cout << "    <<~~~   Form Tambah Data Komik   ~~~>>     " << endl;
	cout << "===============================================" << endl;
	cout << "|  [1] Tambah komik di posisi pertama         |" << endl;
	cout << "|  [2] Tambah komik di tengah                 |" << endl;
	cout << "|  [3] Tambah komik di posisi terakhir        |" << endl;
	cout << "|  [0] Kembali                                |" << endl;
	cout << "|_____________________________________________|" << endl;
}

//---------------------------------------------------------------------------------
// FUNSI SORTING
komik *SortedMerge(komik *a, komik *b, string kategori, string urutan){
	komik *result = NULL;
    bool ASC_OR_DSC = urutan == "1";
    bool condition = false;

    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    if(kategori == "1") {
        condition = ASC_OR_DSC ? a->nama <= b->nama : a->nama >= b->nama;
    } 
	else if(kategori == "2") {
        condition = ASC_OR_DSC ? a->id <= b->id : a->id >= b->id;
    }
    
    if (condition) {
        result = a;
        result->next = SortedMerge(a->next, b, kategori, urutan);
        result->next->prev = result;
        result->prev = NULL;
    } else {
        result = b; 
        result->next = SortedMerge(a, b->next, kategori, urutan);
        result->next->prev = result;
        result->prev = NULL;
    }
    return (result);
}

void FrontBackSplit(komik *source,komik **frontRef, komik **backRef){
	komik *fast;
	komik *slow;
	slow = source;
	fast = source->next;
	/* Advance 'fast' two nodes, and advance 'slow' one node */
	while (fast != NULL){
		fast = fast->next;
		if (fast != NULL){
			slow = slow->next;
			fast = fast->next;
		}
	}
//	/* 'slow' is before the midpoint in the list, so split it in two
//	at that point. */
	*frontRef = source;
	*backRef = slow->next;
	slow->next = NULL;
}

// sorts the linked list by changing next pointers (not data)
void MergeSort(komik **headder, string kategori, string urutan){
	komik *head = *headder;
	komik *a;
	komik *b;
	/* Base case -- length 0 or 1 */
	if ((head == NULL) || (head->next == NULL)){
		return;
	}
	
	FrontBackSplit(head, &a, &b);
	MergeSort(&a, kategori, urutan);
    MergeSort(&b, kategori, urutan);
    *headder = SortedMerge(a, b, kategori, urutan);
	}
	
// FUNSI SORTING
//---------------------------------------------------------------------------------

// VOID UNTUK MEMILIH JENIS SORTING YANG DIINGINKAN
void pilih_sort_komik(string kategori){
	string urutan; 
	while (true){
		system ("cls"); 
		cout << "===============================================" << endl;
		cout << "     ~~~>>  Lihat Data Komik Secara  <<~~~     " << endl;
		cout << "===============================================" << endl;
		cout << "|  [1] Ascending                              |" << endl;
		cout << "|  [2] Descending                             |" << endl;
		cout << "|  [0] Kembali                                |" << endl;
		cout << "|_____________________________________________|" << endl;
		cout << "Pilihan Menu : "; cin >> urutan;
		if (urutan == "1" || urutan == "2") {
			MergeSort(&head, kategori, urutan);
			display_komik(head);
			break; 
		} else if (urutan == "0"){
			break;
		} else {
			cout << "Pilihan Tidak Tersedia!"; getch();
		}
	}
}

// PROSEDUR MENU KE-5 URUTKAN KOMIK
void urutkan_komik() {
	string kategori;
	if (head != NULL) { 
		while (true){
			system ("cls"); 
			cout << "===============================================" << endl;
			cout << "  ~~~>>  Lihat Data Komik Berdasarkan  <<~~~   " << endl;
			cout << "===============================================" << endl;
			cout << "|  [1] Berdasarkan Judul Komik                |" << endl;
			cout << "|  [2] Berdasarkan ID Komik                   |" << endl;
			cout << "|  [0] Kembali                                |" << endl;
			cout << "|_____________________________________________|" << endl;
			cout << "\nPilih kategori mana yang ingin disorting: "; cin >> kategori;
			if (kategori == "1" || kategori == "2") { 
				pilih_sort_komik(kategori);
				break;
			} else if (kategori == "0") { 
				break;
			} else {
				cout << "Pilihan Tidak Tersedia!"; getch();
			}
		}
	} else {
		system("cls");
		cout << "-----------------------------------" << endl;
		cout << "        DAFTAR KOMIK KOSONG        " << endl;
		cout << "-----------------------------------" << endl;
		cout << "Silahkan tambahkan komik terlebih dahulu..."; getch();
	}
}

// FUNSI SEARCHING
//-----------------------------------------------------------------------------------------------------------------
//ALGORITMA FIBONACCI SEARCH
int Fibonacci_Search(string x, int y, int Panjang_Data, string pilih) {
	int F0 = 0;
	int F1 = 1;
	int F = F0 + F1;
	
	while (F < Panjang_Data) {
		F0 = F1;
		F1 = F;
		F = F0 + F1;
	}
	
	int offset = -1;
	while(F > 1){
		komik *Cari = head;
		int indeks = min(offset + F0, Panjang_Data-1);
		for (int k = 0; Cari->next != NULL && k < indeks; k++) {
			Cari = Cari->next;
		}
		if (pilih == "1"){
			if (Cari->id < y) {
				F = F1;
				F1 = F0;
				F0 = F - F1;
				offset = indeks;
			}else if(Cari->id > y) {
				F = F0;
				F1 = F1 - F0;
				F0 = F - F1;
			}else{
				return indeks;
			}
		} else if (pilih == "2"){
			if (Cari->nama < x) {
				F = F1;
				F1 = F0;
				F0 = F - F1;
				offset = indeks;
			}else if(Cari->nama > x) {
				F = F0;
				F1 = F1 - F0;
				F0 = F - F1;
			}else{
				return indeks;
			}
		}
	}
	
	komik *Cari2 = head;
	for (int k = 0; Cari2->next != NULL && k < offset; k++) {
		Cari2 = Cari2->next;
	}
	if (F1 && Cari2->nama == x) return offset + 1;
	return -1;
}
// FUNSI SEARCHING
//-----------------------------------------------------------------------------------------------------------------

// PROSEDUR MENU KE-6 CARI DATA KOMIK
void cari_komik() {
	bool loop = true;
	if (head != NULL) { 
		while (loop){
			string cari_nama = "", pilih;
			int cari = 0;
			system ("cls"); 
			cout << "================================================" << endl;
			cout << "       ~~~>>    Cari Data Komik    <<~~~        " << endl;
			cout << "================================================" << endl;
			cout << "|  [1] Cari Data Komik Berdasarkan ID          |" << endl; 
			cout << "|  [2] Cari Data Komik Berdasarkan Judul Komik |" << endl; 
			cout << "|  [0] Kembali                                 |" << endl; 
			cout << "================================================" << endl;
			cout << "Masukkan Pilihan Menu : " ; cin >> pilih;
			if (pilih == "1"){
				cout << "\nMasukkan ID Komik Yang Ingin Dicari : "; cin >> cari;
				MergeSort(&head, "2", "1");
				loop = false;
			} else if (pilih == "2"){
				cout << "\n[Note: Perhatikan Huruf kapital pada judul komik yang dicari, inputan harus sesuai pada judul komik yang ada!]\n" << endl;
				cout << "Masukkan Nama Komik Yang Ingin Dicari: "; fflush(stdin); getline(cin, cari_nama);
				MergeSort(&head, "1", "1");
				loop = false;
			} else if (pilih == "0") {
				break;
			} else {
				cout << "\nMenu Tidak Ditemukan!"; getch();
			}
			if (pilih == "1" || pilih == "2"){
				int Data_Cari = Fibonacci_Search(cari_nama, cari, Jumlah_Data(), pilih);
				//MEMANGGIL FUNGSI FIBONACCI
				int nomor = 0;
				cur = head;
				if(Data_Cari == -1) {
					cout << "\n================================================"<<endl;
					cout << "              DATA TIDAK DITEMUKAN              "<<endl;
					cout << "================================================"; getch();
					return;
				}
				while (cur != NULL) {
					if(nomor == Data_Cari) {	
						system ("cls"); 	
						cout << "================================================" << endl;
						cout << "       ~~~>>    Hasil Pencarian    <<~~~        " << endl;
						cout << "================================================" << endl;
						cout << "ID Komik             : " << cur->id << endl;
						cout << "Judul Buku Komik     : " << cur->nama << endl;
						cout << "Genre Buku komik     : " << cur->genre << endl;
						cout << "Penulis Komik        : " << cur->penulis << endl;
						cout << "Jumlah Halaman Komik : " << cur->halaman << endl;
						cout << "Jumlah Stok Komik    : " << cur->stok << endl;
						cout << "Harga Komik          : Rp" << cur->harga << endl;
						cout << "___________________________________________________" << endl;
						cout << "\nTekan ENTER Untuk Melanjutkan..."; getch();
						break;
					}
					cur = cur->next;
					nomor++;
				}
			}
		}
	} else {
		system("cls");
		cout << "-----------------------------------------------" << endl;
		cout << "              DAFTAR KOMIK KOSONG              " << endl;
		cout << "-----------------------------------------------" << endl;
		cout << "\nSilahkan tambahkan komik terlebih dahulu..."; getch();
	}
}

// AWAL MULA PROGRAM BERJALAN
int main() {
	read_komik(&head, &tail);
	read_akun(&head_akun);
	read_keranjang(&head_keranjang);
	read_queue(&head_check);
	read_riwayat(&head_riwayat);
	menu_utama();
	return 0;
}

void menu_utama() {
	bool loop = true;
	while (loop){
		system("cls");
		system("color 7");
		// time_t now = time(0);
		// char* waktu = ctime(&now);
		// cout << "Date: " << endl;
		// cout << waktu;
		// UNTUK MENAMPILKAN KETERANGAN WAKTU
		cout << "=====================================" << endl;
		cout << " >>     Destroyer Comic Store     << " << endl;
		cout << "=====================================" << endl;
		cout << "|1. Login Sebagai Admin             |" << endl;
		cout << "|2. Login Sebagai User              |" << endl;
		cout << "|3. Registrasi User                 |" << endl;
		cout << "|4. Exit Program                    |" << endl;
		cout << "|___________________________________| \n" << endl;
		int pilih;
		cout << "Pilih Opsi   : " ;
		cin >> pilih;
		switch(pilih) {
		case 1:
			system("cls");
			login_admin();
			break;
		case 2:
			system("cls");
			login_user();
			break;		
		case 3:
			system("cls");
			registrasi(&head_akun);
			system("PAUSE");
			break;
		case 4:
			cout << "\n____________________________________________" << endl;
			cout << "|                                          |" << endl;
			cout << "|              SELAMAT TINGGAL             |" << endl;
			cout << "|__________________________________________|" << endl;
			loop = false;
			break;
		default:
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\nHarap masukkan angka sesuai pilihan" << endl; 
			system("PAUSE");
		}
	}
}

void login_admin(){
	while (true){
		system("cls");
		cout << "------------------------------------------------------------------" << endl;
		cout << "                           Login Admin                            " << endl;
		cout << "------------------------------------------------------------------" << endl;
		cout << "\n[NOTE: Masukkan angka 00 di username untuk kembali ke menu awal]\n" << endl;
		string username, password;
		cout << "Masukkan Username : "; cin >> username;
		if (username == "00") {
			break;
		} else {
			cout << "Masukkan Password : " ; cin >> password;
			if (username == "admin" && password == "admin"){
				cout << "\n------------------------------------------------------------------" << endl;
				cout << "                         Login Berhasil                           " << endl;
				cout << "------------------------------------------------------------------" << endl;
				menu_admin();
				break;
			} else {
				cout << "\nUsername / Password yang anda masukkan salah, silahkan coba lagi."; getch();
			}
		}
	}
}

void login_user(){
	bool loop = true;
	while (loop){
		cur_akun = head_akun;
		system("cls");
		cout << "------------------------------------------------------------------" << endl;
		cout << "                           Login User                             " << endl;
		cout << "------------------------------------------------------------------" << endl;
		cout << "\n[NOTE: Masukkan angka 00 di username untuk kembali ke menu awal]\n" << endl;
		string username, password;
		cout << "Masukkan Username : "; cin >> username;
		if (username == "00") {
			break;
		} else {
			cout << "Masukkan Password : " ; cin >> password;
			while (cur_akun != NULL){
				if (cur_akun->username == username && cur_akun->password == password){
					cout << "\n------------------------------------------------------------------" << endl;
					cout << "                         Login Berhasil                           " << endl;
					cout << "------------------------------------------------------------------" << endl;
					menu_user(username, cur_akun->nama);
					loop = false;
					break;
				} else {
					cur_akun = cur_akun->next;
				}
				if (cur_akun == NULL){
					cout << "\n------------------------------------------------------------------" << endl;
					cout << "         Username Atau Password Yang Anda Masukkan Salah!         " << endl;
					cout << "------------------------------------------------------------------"; getch();
					break;
				}
			}
		}
	}
}

void menu_admin() {
	bool loop = true;
	string pilih_menu;
	string tambah;
	while (loop){
		// UNTUK MEMBERSIHKAN LAYAR PROGRAM
		system("cls");
		system("color f0");
   		warna(242);
		cout << "===================================================" << endl;
		cout << "    ~~~>>  Destroyer Comic Store (Admin)  <<~~~    " << endl;
		cout << "===================================================" << endl;
		cout << "|  [1] Lihat Data Komik                           |" << endl;
		cout << "|  [2] Tambah Data Komik                          |" << endl;
		cout << "|  [3] Update Data Komik                          |" << endl;
		cout << "|  [4] Hapus Data komik                           |" << endl;
		cout << "|  [5] Cari Data Komik                            |" << endl;
		cout << "|  [6] Lihat Antrian Pesanan                      |" << endl;
		cout << "|  [7] Konfirmasi Antrian Pesanan                 |" << endl;
		cout << "|  [8] Lihat Riwayat Pembelian                    |" << endl;
		cout << "|  [0] Log Out                                    |" << endl;
		cout << "|_________________________________________________| \n" << endl;
		cout << "Pilih Program yang ingin digunakan : "; fflush(stdin); getline(cin, pilih_menu);
		if (pilih_menu == "1") {
			urutkan_komik();
			if (head != NULL) {
				cout << "\nTekan ENTER Untuk Melanjutkan..."; getch();
			}
		} else if (pilih_menu == "2") {
			while (true){
				menuTambah();
				cout << "Masukkan Pilihan : "; cin >> tambah;
				if (tambah == "0"){
					break;
				} else if (tambah == "1"){
					addFirst(&head, &tail);
					break;
				} else if (tambah == "2"){
					if (Jumlah_Data() >= 2) {
						addMiddle(&head, &tail);
					} else {
						cout << "Data harus lebih dari 1" << endl;
					}
					break;
				} else if (tambah == "3"){
					addLast(&head, &tail);
					break;
				} else {
					cout << "\nPilihan Tidak Tersedia!"; getch();
				}
			}
		} else if (pilih_menu == "3") {
			ubah(&head, &tail);
		} else if (pilih_menu == "4") {
			deleteComic(&head, &tail);
		} else if (pilih_menu == "5") {
			cari_komik();	
		} else if (pilih_menu == "6") {
			display_queue(head_check);
		} else if (pilih_menu == "7") {
			konfirmasi_queue(&head_check, &head_riwayat, head);		
		} else if (pilih_menu == "8") {
			display_riwayat(head_riwayat);
		} else if (pilih_menu == "0") {
			cout << "\n=================================================" << endl;
			cout << "                Anda Telah Logout                " << endl; 
			cout << "================================================="; 
			loop = false;
		} else {
			system("color 4");
			cout << "\nHarap masukkan angka sesuai pilihan!"; getch();	
		}
	}
}

void menu_user(string username, string nama) {
	bool loop = true;
	int pilih, tambah, hapus;
	while (loop){
		// UNTUK MEMBERSIHKAN LAYAR PROGRAM
		system("cls");
		system("color f0");
   		warna(242);
		cout << "====================================================" << endl;
		cout << "  >>        Destroyer Comic Store (User)        <<  " << endl;
		cout << "====================================================" << endl;
		cout << "|  [1] Lihat Buku Komik Yang Dijual                |" << endl;
		cout << "|  [2] Cari Buku Komik                             |" << endl;
		cout << "|  [3] Pesan Buku Komik                            |" << endl;
		cout << "|  [4] Lihat Keranjang Pesanan                     |" << endl;
		cout << "|  [5] Update Keranjang Pesanan                    |" << endl;
		cout << "|  [6] Hapus Keranjang Pesanan                     |" << endl;
		cout << "|  [7] Checkout Pesanan                            |" << endl;
		cout << "|  [8] Lihat Data Checkout                         |" << endl;
		cout << "|  [9] Lihat Riwayat Transaksi                     |" << endl;
		cout << "|  [0] Logout                                      |" << endl;
		cout << "|__________________________________________________| \n" << endl;
		string pilih_menu;
		cout << "Pilih Program yang ingin digunakan : "; fflush(stdin); getline(cin, pilih_menu);
		if (pilih_menu == "1") {
			urutkan_komik();
			cout << "\nTekan ENTER Untuk Melanjutkan..."; getch();
		} else if (pilih_menu == "2") {
			cari_komik();
		} else if (pilih_menu == "3") {
			tambah_keranjang(username, nama, head, &head_keranjang, &head_check);
		} else if (pilih_menu == "4") {
			if (cek_keranjang(username, head_keranjang) == -1){
				system("cls");
				cout << "-----------------------------------------------" << endl;
				cout << "            DAFTAR KERANJANG KOSONG            " << endl;
				cout << "-----------------------------------------------" << endl;
				cout << "\nSilahkan tambah pesanan terlebih dahulu..."; getch();
			} else {
				display_keranjang(username, head_keranjang);
				cout << "\nTekan ENTER Untuk Melanjutkan..."; getch();
			}
		} else if (pilih_menu == "5") {
			update_keranjang(username, &head_keranjang, &head);	
		} else if (pilih_menu == "6") {
			hapus_keranjang(username, &head_keranjang);
		} else if (pilih_menu == "7") {
			if (cek_keranjang(username, head_keranjang) == -1){
				system("cls");
				cout << "-----------------------------------------------" << endl;
				cout << "            DAFTAR CHECKOUT KOSONG             " << endl;
				cout << "-----------------------------------------------" << endl;
				cout << "\nSilahkan checkout pesanan terlebih dahulu..."; getch();
			} else {
				enqueue_pesanan(username, nama, &head_keranjang, &head_check);
			}		
		} else if (pilih_menu == "8") {
			display_checkout(username, head_check);
		} else if (pilih_menu == "9") {
			display_riwayat_user(username, head_riwayat);	
		} else if (pilih_menu == "0") {
			cout << "\n=================================================" << endl;
			cout << "                Anda Telah Logout                " << endl; 
			cout << "================================================="; 
			loop = false;
		} else {
			system("color 4");
			cout << "\nHarap masukkan angka sesuai pilihan!"; getch();
		}
	}
}
