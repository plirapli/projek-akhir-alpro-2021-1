#include <iostream>
#include <conio.h>
#include <iomanip>
#include <stdlib.h>
#include <string>

using namespace std;

// 📃 MENU
void ReadMenu(string menu[], int length); // Menampilkan daftar menu

// 🏢 DATA INVENTARIS
void ReadDataInventaris();             // Menampilkan data inventaris
void ReadDataInvCopy(int invStok[]);   // Menampilkan data inv (copy)
void UpdateStokBarang(string search);  // Mengubah stok
void UpdateHargaBarang(string search); // Mengubah harga
int FindInv(string kodeBarang);        // Mencari barang based on kode barang

// 💰 KASIR
// Menampilkan keranjang
void ReadCart(string cartStr[][2], int cartInt[][3], int jml, int &total, bool member = false);
string NoTransaksi(string tgl); // Mengenerate kode transaksi

// 📝 LOG PENJUALAN
void ReadTransaction(int logIndex); // Menampilkan riwayat transaksi

// 🙋🏼‍♂️ CRM
void ReadMembers();                                        // Menampilkan semua member
void ReadMember(int index);                                // Menampilkan member
int FindMember(string uname);                              // Mencari member berdasarkan username
void AddMember();                                          // Menambahkan member baru
void ReadMemberTransaction(int indexMember, int logIndex); // Menampilkan transaksi member

// ⚪ MISC
void Garis(int length); // Generate garis
void PressAnyKey();     // Print "press any key" 😅

// 🌏 GLOBAL VARIABLES
// 👨🏼‍💼 DATA ADMIN
string g_admin[2][3] = {
    {"mrafli", "123210078", "Rafli"},
    {"desyna", "123210083", "Desy"}};

// 🏢 DATA INV
const int g_invSize = 6; // Index Data Inv
string g_invKodeNama[g_invSize][2] = {
    {"00A1", "Printer Canon Ip 700"},
    {"00A2", "Laptop Acer"},
    {"00A3", "Hardisk Maxtor 60GB"},
    {"00A4", "Flashdisk Toshiba 8GB"},
    {"00B1", "Notebook Asus"},
    {"00B2", "Printer Epson Stylus"},
};
int g_invStokHarga[g_invSize][2] = {
    {20, 550000},
    {42, 800000},
    {35, 450000},
    {7, 100000},
    {0, 3000000},
    {1, 2800000},
};

// 👫 DATA MEMBER
string g_member[20][4] = {
    {"rei_simp", "Seva Giantama", "Temanggung", "seva@dummy.com"},
    {"shazi_senpai", "Shazi Awaludin", "Cikarang", "shazi@dummy.com"},
    {"cici_sunbae", "Cici Yuriza", "Bengkulu", "cici@dummy.com"}};
int g_activeMember = 3; // Jumlah member aktif

// 📝 DATA PENJUALAN
string g_logPenjualan[50][2];
int g_logHargaPenjualan[50];

// 📝👫 DATA PENJUALAN MEMBER
string g_logPenjualanMember[20][50][2];
int g_logHargaPenjualanMember[20][50];

int main()
{
  // Initialize main var
  bool ulangiMenu, ulangiProgram = 1;
  char menuOption;
  string admin;

  do
  {
    // Login
    do
    {
      int indexUser;
      string username, passwd;

      ulangiMenu = 1;

      cout << "Login \n"
           << "Username: ";
      cin >> username;
      cout << "Password: ";
      cin >> passwd;

      for (int i = 0; i < 2; i++)
      {
        indexUser = ((g_admin[i][0] == username) && (g_admin[i][1] == passwd)) ? i : 2;

        if (indexUser != 2)
        {
          admin = g_admin[indexUser][2];
          ulangiMenu = 0;
          break;
        }
      }

      if (indexUser == 2)
        cout << "Username atau Password anda salah! \n\n";
      else
      {
        system("CLS");
        cout << "Selamat datang, " + admin + "! \n\n";
      }
    } while (ulangiMenu == 1);

    // Main Program
    do
    {
      int logIndex = 0, logIndexMember[20] = {};
      string menuMain[4] = {"INVENTARIS", "KASIR", "LOG PENJUALAN", "CRM"};

      ulangiMenu = 1;

      // Menampilkan Main Menu
      cout << "MAIN MENU \n";
      ReadMenu(menuMain, 4);
      cout << "-------------------- \n"
           << "[9] LOG OUT \n"
           << "[0] KELUAR \n"
           << "Pilih > ";
      cin >> menuOption;
      system("CLS");

      // FITUR INVENTARIS
      if (menuOption == '1')
      {
        char option, ulang, revaluestok;
        string kode;

        do
        {
          cout << "Menu Inventaris \n"
               << "[1] Tampilkan Daftar Inventaris \n"
               << "[2] Ubah Stok \n"
               << "[3] Ubah harga \n"
               << "[0] Kembali \n"
               << "Pilih > ";
          cin >> option;
          cin.ignore();
          system("CLS");

          switch (option)
          {
          case '1':
            ReadDataInventaris();
            cout << endl;
            break;

          case '2':
            ReadDataInventaris();
            cout << "Search kode barang : ";
            getline(cin, kode);
            UpdateStokBarang(kode);
            break;

          case '3':
            ReadDataInventaris();
            cout << "Search kode barang : ";
            getline(cin, kode);
            UpdateHargaBarang(kode);
            break;

          case '0':
            break;

          default:
            cout << "Pilihan tidak valid \n";
            break;
          }
        } while (option != '0');
      }

      // FITUR KASIR
      else if (menuOption == '2')
      {
        // Initialize variable
        bool ulangiKasir = 1, isMember = 0;
        int jmlCart = 0, inputQty, total = 0, paid;
        string inBuyDate, noTrans, inKodeBarang;

        // Copy inv "stok"
        int copy_invStok[g_invSize];
        for (int i = 0; i < g_invSize; i++)
          copy_invStok[i] = g_invStokHarga[i][0];

        // Initialize Cart
        string cartStr[g_invSize][2];
        int cartInt[g_invSize][3];

        cout << "Kasir \n"
             << "Tanggal Transaksi (DD-MM-YYYY): ";
        cin >> inBuyDate;

        noTrans = NoTransaksi(inBuyDate);

        do
        {
          system("CLS");
          cout << "Kasir \n"
               << "Tanggal: " << inBuyDate << "\n\n";
          ReadDataInvCopy(copy_invStok);
          cout << "\n";

          cout << "[1] Tambah Barang \n";
          if (jmlCart > 0)
          {
            cout << "[2] Lihat keranjang \n"
                 << "[3] Hapus Barang dari Keranjang \n"
                 << "[4] Lanjutkan \n";
          }
          cout << "[0] Kembali \n"
               << "Pilih > ";
          cin >> menuOption;

          // Tambah Barang
          if (menuOption == '1')
          {
            bool ulangiCari = 1;
            int indexBarang;

            do
            {
              system("CLS");
              ReadDataInvCopy(copy_invStok);

              cout << "Masukkan kode barang: ";
              cin >> inKodeBarang;

              // Mengecek ketersediaan barang
              indexBarang = FindInv(inKodeBarang);

              if (indexBarang != g_invSize)
              {
                string namaBarang = g_invKodeNama[indexBarang][1];
                int stok = copy_invStok[indexBarang];
                int hargaBarang = g_invStokHarga[indexBarang][1];

                if (stok > 0)
                {
                  system("CLS");
                  cout << "Kode Produk  : " << inKodeBarang << "\n"
                       << "Nama Produk  : " << namaBarang << "\n"
                       << "Stok Produk  : " << stok << "\n"
                       << "Harga Produk : Rp" << hargaBarang << ",- \n\n";

                  cout << "Lanjutkan (y/n)? > ";
                  cin >> menuOption;

                  if (menuOption == 'y' || menuOption == 'Y')
                  {
                    do
                    {
                      cout << "Jumlah : ";
                      cin >> inputQty;

                      if (inputQty > stok)
                        cout << "Stok tidak cukup! \n";

                    } while (inputQty > stok);

                    int totalHarga = hargaBarang * inputQty;

                    cartStr[jmlCart][0] = inKodeBarang;
                    cartStr[jmlCart][1] = namaBarang;
                    cartInt[jmlCart][0] = inputQty;
                    cartInt[jmlCart][1] = hargaBarang;
                    cartInt[jmlCart][2] = totalHarga;

                    copy_invStok[indexBarang] -= inputQty;
                    jmlCart++;

                    cout << "Added to cart! \n";
                    ulangiCari = 0;
                  }
                  else if (menuOption == 'n' || menuOption == 'N')
                  {
                    cout << "Penambahan barang dibatalkan. \n";
                    ulangiCari = 0;
                  }
                  else
                    cout << "Input tidak valid! \n";

                  PressAnyKey();
                }
                else
                  cout << "Stok Habis! \n\n";
              }
              else
                cout << "Barang tidak ditemukan. \n\n";
            } while (ulangiCari == 1);
          }

          // Kembali
          else if (menuOption == '0')
          {
            cout << "Yakin ingin kembali? Semua barang di keranjang akan dihapus. (y/n) > ";
            cin >> menuOption;
            system("CLS");
            ulangiKasir = (menuOption == 'y' || menuOption == 'Y') ? 0 : 1;
          }

          else if (jmlCart > 0)
          {
            // Lihat keranjang
            if (menuOption == '2')
            {
              system("CLS");
              cout << "Cart : \n";
              ReadCart(cartStr, cartInt, jmlCart, total);
              PressAnyKey();
            }

            // Hapus keranjang
            else if (menuOption == '3')
            {
              bool ulangiHapus = 1;
              int inNomor, indexBarang;

              system("CLS");
              ReadCart(cartStr, cartInt, jmlCart, total);
              do
              {
                cout << "\n"
                     << "Masukkan nomor > ";
                cin >> inNomor;

                if (!(inNomor > jmlCart || inNomor <= 0))
                {
                  string kodeBarang = cartStr[inNomor - 1][0];
                  string namaBarang = cartStr[inNomor - 1][1];
                  int hargaBarang = cartInt[inNomor - 1][1];

                  cout << "Nama Produk  : " << namaBarang + " [" + kodeBarang + "] \n"
                       << "Harga Produk : Rp" << hargaBarang << ",- \n\n";

                  cout << "Lanjutkan (y/n)? > ";
                  cin >> menuOption;

                  if (menuOption == 'y' || menuOption == 'Y')
                  {
                    // Menambah stok barang yang telah dihapus
                    indexBarang = FindInv(cartStr[inNomor - 1][0]);
                    copy_invStok[indexBarang] += cartInt[inNomor - 1][0];

                    // Menaikkan baris
                    for (int i = inNomor - 1; i < jmlCart; i++)
                    {
                      cartStr[i][0] = cartStr[i + 1][0];
                      cartStr[i][1] = cartStr[i + 1][1];
                      cartInt[i][0] = cartInt[i + 1][0];
                      cartInt[i][1] = cartInt[i + 1][1];
                      cartInt[i][2] = cartInt[i + 1][2];
                    }
                    jmlCart--;

                    cout << "Barang telah dihapus! \n";
                    ulangiHapus = 0;
                  }
                  else if (menuOption == 'n' || menuOption == 'N')
                  {
                    cout << "Dibatalkan. \n";
                    ulangiHapus = 0;
                  }
                  else
                    cout << "Input tidak valid! \n";

                  PressAnyKey();
                }
                else
                  cout << "Barang tidak ditemukan \n";
              } while (ulangiHapus == 1);
            }

            // Next
            else if (menuOption == '4')
            {
              system("CLS");
              cout << "Cart : \n";
              ReadCart(cartStr, cartInt, jmlCart, total);

              cout << "\n"
                   << "Lanjutkan (y/n)? > ";
              cin >> menuOption;

              if (menuOption == 'y')
              {
                int indexMember;
                string username, name;

                cout << "Punya member (y/n)? > ";
                cin >> menuOption;
                system("CLS");

                if (menuOption == 'y')
                {
                  string inUname;

                  do
                  {
                    cout << "Masukkan username: ";
                    cin >> inUname;

                    indexMember = FindMember(inUname);

                    if (indexMember == g_activeMember)
                      cout << "Member tidak ditemukan. \n\n";

                  } while (indexMember == g_activeMember);

                  cout << "\n";
                  ReadMember(indexMember);

                  cout << "\n"
                       << "Lanjutkan (y/n)? > ";
                  cin >> menuOption;

                  isMember = (menuOption == 'y' || 'Y') ? 1 : 0;
                  system("CLS");
                }

                ReadCart(cartStr, cartInt, jmlCart, total, isMember);

                // Bayar
                do
                {
                  cout << "Bayar : Rp";
                  cin >> paid;

                  if (paid < total)
                    cout << "Uang anda tidak mencukupi. \n";
                } while (paid < total);
                system("CLS");

                int change = paid - total;

                // Ubah stok di inventaris
                for (int i = 0; i < g_invSize; i++)
                  g_invStokHarga[i][0] = copy_invStok[i];

                // Masukkan pembelian ke db log penjualan (khusus member)
                if (isMember == 1)
                {
                  int index = indexMember;

                  g_logPenjualanMember[index][logIndexMember[index]][0] = noTrans;
                  g_logPenjualanMember[index][logIndexMember[index]][1] = inBuyDate;
                  g_logHargaPenjualanMember[index][logIndexMember[index]] = total;
                  logIndexMember[index]++;
                }

                // Masukkan pembelian ke db log penjualan
                g_logPenjualan[logIndex][0] = noTrans;
                g_logPenjualan[logIndex][1] = inBuyDate;
                g_logHargaPenjualan[logIndex] = total;
                logIndex++;

                // Nota Pembelian
                cout << "No.     : " + noTrans + "\n"
                     << "Kasir   : " + admin + "\n";
                ReadCart(cartStr, cartInt, jmlCart, total, isMember);
                cout << "Bayar   : Rp" << paid << "\n"
                     << "Kembali : Rp" << change << "\n\n";

                cout << "Terima kasih! \n";
                PressAnyKey();

                ulangiKasir = 0;
              }
            }
          }

          else
          {
            cout << "Pilihan tidak valid! \n\n";
            PressAnyKey();
          }
        } while (ulangiKasir == 1);
      }

      // FITUR LAPORAN PENJUALAN
      else if (menuOption == '3')
        ReadTransaction(logIndex);

      // FITUR CRM
      else if (menuOption == '4')
      {
        bool ulangiCRM = 1;
        string menuCRM[4] = {
            "Daftar Member",
            "Tambah Member",
            "Pengeluaran Member",
            "Hapus Member",
        };

        do
        {
          // Menampilkan Menu CRM
          cout << "Customer Releationship Management (CRM) \n";
          ReadMenu(menuCRM, 4);
          cout << "[0] Kembali \n"
               << "Pilih > ";
          cin >> menuOption;
          system("CLS");

          switch (menuOption)
          {
          case '1':
            ReadMembers();
            break;

          case '2':
            ReadMembers();
            AddMember();
            break;

          // Detail pengeluaran member
          case '3':
          {
            int indexMember;
            string username;

            ReadMembers();
            cout << "Detail pengeluaran member \n";

            do
            {
              cout << "Masukkan username: ";
              cin >> username;

              indexMember = FindMember(username);

              if (indexMember == g_activeMember)
                cout << "Member tidak ditemukan. \n\n";

            } while (indexMember == g_activeMember);
            system("CLS");

            ReadMember(indexMember);
            ReadMemberTransaction(indexMember, logIndexMember[indexMember]);
            break;
          }

          // Hapus member
          case '4':
          {
            bool ulangiHapus = 1;
            int indexMember;
            string username;

            ReadMembers();

            do
            {
              do
              {
                cout << "Masukkan username > ";
                cin >> username;

                indexMember = FindMember(username);

                if (indexMember == g_activeMember)
                  cout << "Member tidak ditemukan. \n\n";
              } while (indexMember == g_activeMember);

              system("CLS");
              ReadMember(indexMember);

              cout << "Lanjutkan (y/n)? > ";
              cin >> menuOption;

              if (menuOption == 'y' || menuOption == 'Y')
              {
                // Menaikkan baris
                for (int i = indexMember; i < g_activeMember; i++)
                {
                  for (int j = 0; j < 4; j++)
                    g_member[i][j] = g_member[i + 1][j];

                  logIndexMember[i] = logIndexMember[i + 1];
                }
                g_activeMember--;

                cout << "Member telah dihapus! \n";
                ulangiHapus = 0;
              }
              else if (menuOption == 'n' || menuOption == 'N')
              {
                cout << "Dibatalkan. \n";
                ulangiHapus = 0;
              }
              else
                cout << "Input tidak valid! \n";

              PressAnyKey();
            } while (ulangiHapus == 1);
            break;
          }

          case '0':
            ulangiCRM = 0;
            break;

          default:
            cout << "Pilihan invalid! \n\n";
            break;
          }
        } while (ulangiCRM == 1);
      }

      // LOGOUT
      else if (menuOption == '9')
      {
        cout << "Sampai jumpa, " + admin + "! \n\n";
        ulangiMenu = 0;
      }

      // KELUAR
      else if (menuOption == '0')
      {
        ulangiMenu = 0;
        ulangiProgram = 0;
      }

      else
        cout << "Pilihan invalid! \n";

    } while (ulangiMenu == 1);
  } while (ulangiProgram == 1);

  cout << "Terima Kasih. \n";
  PressAnyKey();

  return 0;
}

void ReadMenu(string menu[], int length)
{
  for (int i = 0; i < length; i++)
    cout << "[" << i + 1 << "] " + menu[i] << "\n";
}

void ReadDataInventaris()
{
  int jmlGaris = 59;

  cout << "Daftar Barang : \n";
  Garis(jmlGaris);
  cout << left
       << "| " << setw(12) << "Kode Barang"
       << "| " << setw(25) << "Nama Barang"
       << "| " << setw(5) << "Stok"
       << "| " << setw(10) << "Harga"
       << "| \n";
  Garis(jmlGaris);

  for (int i = 0; i < g_invSize; i++)
  {
    string kode = g_invKodeNama[i][0];
    string nama = g_invKodeNama[i][1];
    int stok = g_invStokHarga[i][0];
    int harga = g_invStokHarga[i][1];

    cout << left
         << "| " << setw(12) << kode
         << "| " << setw(25) << nama
         << "| " << setw(5) << stok
         << "| " << right << setw(10) << harga;
    cout << "| \n";
  }
  Garis(jmlGaris);
}

void ReadDataInvCopy(int invStok[])
{
  int jmlGaris = 60;

  cout << "Daftar Barang : \n";
  Garis(jmlGaris);
  cout << left
       << "| " << setw(12) << "Kode Barang"
       << "| " << setw(25) << "Nama Barang"
       << "| " << setw(5) << "Stok"
       << "| " << setw(11) << "Harga (Rp)"
       << "| \n";
  Garis(jmlGaris);

  for (int i = 0; i < g_invSize; i++)
  {
    string kode = g_invKodeNama[i][0];
    string nama = g_invKodeNama[i][1];
    int stok = invStok[i];
    int harga = g_invStokHarga[i][1];

    cout << left
         << "| " << setw(12) << kode
         << "| " << setw(25) << nama
         << "| " << setw(5) << stok
         << "| " << right << setw(11) << harga;
    cout << "| \n";
  }
  Garis(jmlGaris);
}

int FindInv(string kodeBarang)
{
  int index;
  for (int i = 0; i < g_invSize; i++)
  {
    index = (kodeBarang == g_invKodeNama[i][0]) ? i : g_invSize;
    if (index != g_invSize)
      break;
  }
  return index;
}

void UpdateStokBarang(string search)
{
  int stok[5];
  string nama[50];

  int counter = 0;
  for (int x = 0; x < g_invSize; x++)
  {
    if (g_invKodeNama[x][0] == search)
    {
      counter++;

      cout << "Update stok barang : ";
      cin >> stok[x];

      g_invStokHarga[x][0] = stok[x];

      cout << "Update berhasil. \n";
      PressAnyKey();
    }
  }
}

void UpdateHargaBarang(string search)
{
  int harga[10];
  string nama[50];

  int counter = 0;
  for (int x = 0; x < g_invSize; x++)
  {
    if (g_invKodeNama[x][0] == search)
    {
      counter++;

      cout << "Update harga barang : ";
      cin >> harga[x];

      g_invStokHarga[x][1] = harga[x];

      cout << "Update berhasil. \n";
      PressAnyKey();
    }
  }
}

void ReadCart(string cartStr[][2], int cartInt[][3], int jml, int &total, bool member)
{
  if (jml == 0)
    cout << "Keranjang masih kosong. \n";
  else
  {
    string field[5] = {"No", "Barang", "Harga", "Qty", "Total"};
    int totalColLength = 0, colLength[5] = {4, 14, 12, 5, 16};
    total = 0;

    // Mencari jumlah kata terbanyak di field Nama barang
    for (int i = 0; i < jml; i++)
    {
      int dataLength = cartStr[i][1].length() + 9;
      colLength[1] = (dataLength > colLength[1]) ? dataLength : colLength[1];
    }

    // Menjumlahkkan baris
    for (int i = 0; i < 5; i++)
      totalColLength += colLength[i];

    // Menampilkan Cart
    // Kolom
    Garis(totalColLength);
    cout << "  ";
    for (int i = 0; i < 5; i++)
      cout << left << setw(colLength[i]) << field[i];
    cout << "\n";
    Garis(totalColLength);

    // Isi Keranjang
    for (int i = 0; i < jml; i++)
    {
      cout << "  ";
      cout << left << setw(colLength[0]) << i + 1
           << setw(colLength[1]) << cartStr[i][1] + " (" + cartStr[i][0] + ") "
           << "Rp" << setw(colLength[2] - 2) << cartInt[i][1]
           << setw(colLength[3]) << cartInt[i][0]
           << "Rp" << cartInt[i][2];
      total += cartInt[i][2];

      cout << "\n";
    }
    Garis(totalColLength);

    if (member == 1)
    {
      int diskon;
      diskon = total * 0.1;

      cout << "Total : Rp" << total << "\n";
      cout << "Diskon member (10%) : Rp" << diskon << "\n";

      total -= diskon;
    }

    cout << "Total : Rp" << total << "\n";
  }
}

void ReadTransaction(int logIndex)
{
  int total = 0;

  cout << "Riwayat Penjualan : \n";

  if (logIndex > 0)
  {
    for (int i = 0; i < logIndex; i++)
    {
      cout << "[" + g_logPenjualan[i][1] + "] "
           << "#" + g_logPenjualan[i][0] + " "
           << "Rp" << g_logHargaPenjualan[i] << "\n";
      total += g_logHargaPenjualan[i];
    }
    cout << "\n";
  }
  else
    cout << "- \n\n";

  cout << "Total : Rp" << total << "\n";
  PressAnyKey();
}

void ReadMembers()
{
  string field[3] = {"No", "Username", "Nama Member"};
  int totalColLength = 5, i, j, colLength[3] = {3, 7, 14};

  // Mencari jumlah kata terbanyak di field Nama
  for (i = 0; i < g_activeMember; i++)
  {
    for (j = 0; j < 2; j++)
    {
      int dataLength = g_member[i][j].length() + 1;
      colLength[j + 1] = (dataLength > colLength[j + 1]) ? dataLength : colLength[j + 1];
    }
  }

  for (i = 0; i < 3; i++)
    totalColLength += colLength[i];

  cout << "Daftar Member : \n";

  Garis(totalColLength);
  for (int i = 0; i < 3; i++)
    cout << left << "| " << setw(colLength[i]) << field[i];
  cout << "| \n";
  Garis(totalColLength);

  for (int i = 0; i < g_activeMember; i++)
  {
    cout << "| " << left << setw(colLength[0]) << i + 1;

    for (j = 0; j < 2; j++)
      cout << left << "| " << setw(colLength[j + 1]) << g_member[i][j];

    cout << "| \n";
  }
  Garis(totalColLength);
  cout << "\n";
}

void AddMember()
{
  bool isExist, ulangiPrompt;
  char menuOption;
  int indexMember;
  string newMember[4], field[4] = {"Username", "Nama", "Alamat", "Email"};

  if (g_activeMember < 20)
  {
    // Input dan mengecek ketersediaan username
    do
    {
      cout << "Menambahkan member baru \n";
      cout << field[0] + ": ";
      cin >> newMember[0];
      cin.ignore();

      indexMember = FindMember(newMember[0]);

      if (indexMember != g_activeMember)
      {
        cout << "Username telah terpakai. \n\n";
        isExist = 1;
        PressAnyKey();
      }
      else
        isExist = 0;
    } while (isExist == 1);

    // Mengisi field nama, alamat, dan email
    for (int i = 1; i < 4; i++)
    {
      cout << field[i] + ": ";
      getline(cin, newMember[i]);
    }

    do
    {
      cout << "Tambahkan " + newMember[1] + "sebagai member baru (Y/N)? > ";
      cin >> menuOption;

      if (menuOption == 'y' || menuOption == 'Y')
      {
        // Menyimpan input ke data member
        for (int i = 0; i < 4; i++)
          g_member[g_activeMember][i] = newMember[i];

        g_activeMember++;
        cout << "Berhasil mendaftarkan member baru! \n";
        ulangiPrompt = 0;
      }
      else if (menuOption == 'n' || menuOption == 'N')
      {
        cout << "Pendaftaran member dibatalkan. \n";
        ulangiPrompt = 0;
      }
      else
        cout << "Input tidak valid! \n";
    } while (ulangiPrompt == 1);
  }
  else
    cout << "Jumlah member telah melebihi batas! \n";

  PressAnyKey();
}

int FindMember(string uname)
{
  int index;
  for (int i = 0; i < g_activeMember; i++)
  {
    index = ((uname == g_member[i][0])) ? i : g_activeMember;
    if (index != g_activeMember)
      break;
  }
  return index;
}

void ReadMember(int index)
{
  string member[4];

  for (int i = 0; i < 4; i++)
    member[i] = g_member[index][i];

  cout << "[PROFILE] \n"
       << "Nama     : " + member[1] + "\n"
       << "Username : " + member[0] + "\n"
       << "Alamat   : " + member[2] + "\n"
       << "Email    : " + member[3] + "\n\n";
}

void ReadMemberTransaction(int indexMember, int logIndex)
{
  int total = 0;
  string nama = g_member[indexMember][1];

  cout << "Riwayat Pengeluaran " + nama + " : \n";
  if (logIndex > 0)
  {
    for (int i = 0; i < logIndex; i++)
    {
      string kodeTransaksi = g_logPenjualanMember[indexMember][i][0];
      string tglTransaksi = g_logPenjualanMember[indexMember][i][1];
      int hargaTransaksi = g_logHargaPenjualanMember[indexMember][i];

      cout << "[" + tglTransaksi + "] "
           << "#" + kodeTransaksi + " "
           << "Rp" << hargaTransaksi << "\n";
      total += hargaTransaksi;
    }
    cout << "\n";
  }
  else
    cout << "- \n";

  cout << "Total : Rp" << total << "\n";
  PressAnyKey();
}

string NoTransaksi(string tgl)
{
  char tanggal[] = {tgl[0], tgl[1], tgl[3], tgl[4], tgl[6], tgl[7], '\0'};
  char angka[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

  string kodeTgl = tanggal;
  string res = "";

  for (int i = 0; i < 4; i++)
    res += angka[rand() % 10];

  return kodeTgl + res;
}

void Garis(int length)
{
  cout << "+";
  for (int i = 0; i < length; i++)
    cout << "-";
  cout << "+ \n";
}

void PressAnyKey()
{
  cout << "\n"
       << "[Press any key to continue.]";
  getch();
  system("CLS");
}