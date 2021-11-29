#include <iostream>
#include <iomanip>

using namespace std;

// Fungsi untuk menampilkan data inventaris
void readDataInventaris();

void readCopyInv(int invStok[]);

// Fungsi untuk menampilkan keranjang
void readCart(string cartStr[][2], int cartInt[][3], int jml, int &total, bool member);

void ReadMember();

// Fungsi u/ mengubah stok
void UpdateStokBarang(string search);

// Fungsi u/ mengubah harga
void UpdateHargaBarang(string search);

// Fungsi untuk mengenerate kode transaksi
string noTransaksi(string tgl);

// Global Variables

// DATA ADMIN
string g_admin[2][3] = {
    {"mrafli", "123210078", "Rafli"},
    {"desyna", "123210083", "Desy"}};

// DATA INVENTARIS
// 1. Kode dan Nama
string g_invKodeNama[6][2] = {
    {"00A1", "Printer Canon Ip 700"},
    {"00A2", "Laptop Acer"},
    {"00A3", "Hardisk Maxtor 60GB"},
    {"00A4", "Flashdisk Toshiba 8GB"},
    {"00B1", "Notebook Asus"},
    {"00B2", "Printer Epson Stylus"},
};

// 2. Stok dan Harga
int g_invStokHarga[6][2] = {
    {20, 550000},
    {42, 800000},
    {35, 450000},
    {7, 100000},
    {0, 3000000},
    {1, 2800000},
};
// END DATA INVENTARIS

// DATA MEMBER
string member[20][2] = {
    {"yoojung_simp", "Seva Giantama"},
    {"shazi_senpai", "Shazi Awaludin"},
    {"cici_sunbae", "Cici Yuriza"},
    {"nurlight", "Heri Nur Cahyana"},
};

// DATA PENJUALAN
string logPenjualan[50][2];
int logHargaPenjualan[50];

int invSize = 6, activeMember = 4;

int main()
{
  // Initialize Main Variable
  bool ulangiMenu;
  int jmlCart = 0, logIndex = 0, indexUser = 2;
  char MenuOption;
  string username, passwd;

  // // Login
  // do
  // {
  //   ulangiMenu = 1;

  //   cout << "Login \n"
  //        << "Username: ";
  //   cin >> username;
  //   cout << "Password: ";
  //   cin >> passwd;

  //   for (int i = 0; i < 2; i++)
  //   {
  //     indexUser = ((g_admin[i][0] == username) && (g_admin[i][1] == passwd)) ? i : 2;

  //     if (indexUser != 2)
  //     {
  //       ulangiMenu = 0;
  //       break;
  //     }
  //   }

  //   if (indexUser == 2)
  //     cout << "Username atau Password anda salah! \n\n";
  //   else
  //     cout << "Selamat datang, " + g_admin[indexUser][2] + "! \n\n";

  // } while (ulangiMenu == 1);

  // Main Program
  do
  {
    ulangiMenu = 1;

    cout << "MENU \n"
         << "[1] INVENTARIS \n"
         << "[2] KASIR \n"
         << "[3] LOG PENJUALAN \n"
         << "[4] CRM \n"
         << "[0] KELUAR \n"
         << "Pilih > ";
    cin >> MenuOption;

    // FITUR INVENTARIS
    if (MenuOption == '1')
    {
      char option, ulang, revaluestok;
      string kode;

      do
      {
        cout << "[1] Tampilkan Daftar Inventaris \n"
             << "[2] Ubah Stok \n"
             << "[3] Ubah harga \n"
             << "[4] Exit \n"
             << "Pilih > ";
        cin >> option;
        cin.ignore();

        switch (option)
        {
        case '1':
          cout << "Daftar Barang : \n";
          readDataInventaris();
          cout << endl;
          option = '3';
          break;

        case '2':
          readDataInventaris();
          option = '3';
          cout << "\nSearch kode barang : ";
          getline(cin, kode);
          UpdateStokBarang(kode);
          break;

        case '3':
          readDataInventaris();
          option = '3';
          cout << "\nSearch kode barang : ";
          getline(cin, kode);
          UpdateHargaBarang(kode);
          break;

        case '4':
          option = '0';
          break;

        default:
          option = '3';
          cout << "Pilihan tidak valid \n";
          break;
        }
      } while (option == '3');

      cout << "Terima Kasih \n\n";
    }

    // FITUR KASIR
    else if (MenuOption == '2')
    {
      // Initialize variable
      char menuEnum;
      bool ulangiKasir = 1, isMember = 0;
      int indexBarang = invSize, inputQty, total = 0, paid;
      string kasir = g_admin[indexUser][2], inBuyDate, noTrans, inKodeBarang, inMember;

      // Copy inv "stok"
      int copy_invStok[invSize];

      for (int i = 0; i < invSize; i++)
        copy_invStok[i] = g_invStokHarga[i][0];

      // Initialize Cart
      string cartStr[invSize][2];
      int cartInt[invSize][3];

      cout << "Tanggal Transaksi (DD-MM-YY): ";
      cin >> inBuyDate;

      noTrans = noTransaksi(inBuyDate);

      cout << "\n";

      do
      {
        readCopyInv(copy_invStok);
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
        cin >> menuEnum;

        // Tambah Barang
        if (menuEnum == '1')
        {
          bool ulangiCari = 1;

          do
          {
            cout << "Masukkan kode barang: ";
            cin >> inKodeBarang;

            // Mengecek ketersediaan barang
            for (int i = 0; i < invSize; i++)
            {
              indexBarang = (g_invKodeNama[i][0] == inKodeBarang) ? i : invSize;
              if (indexBarang != invSize)
                break;
            }

            if (indexBarang != invSize)
            {
              string namaBarang = g_invKodeNama[indexBarang][1];
              int stok = copy_invStok[indexBarang];
              int hargaBarang = g_invStokHarga[indexBarang][1];

              if (stok > 0)
              {
                cout << "Nama Produk: " << namaBarang << "\n"
                     << "Harga Produk: "
                     << "Rp" << hargaBarang << ",-"
                     << "\n";
                cout << "Lanjutkan (y/n)? ";
                cin >> menuEnum;

                if (menuEnum == 'y')
                {
                  do
                  {
                    cout << "Jumlah: ";
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
                else
                {
                  cout << "Penambahan barang dibatalkan. \n\n";
                  ulangiCari = 0;
                }
              }
              else
                cout << "Stok Habis! \n\n";
            }
            else
              cout << "Barang tidak ditemukan. \n\n";
          } while (ulangiCari == 1);
        }

        else if (jmlCart > 0)
        {
          // Lihat keranjang
          if (menuEnum == '2')
          {
            cout << "Cart : \n";
            readCart(cartStr, cartInt, jmlCart, total, isMember);
          }

          // Next
          else if (menuEnum == '4')
          {
            cout << "Cart : \n";
            readCart(cartStr, cartInt, jmlCart, total, isMember);

            cout << "Lanjutkan (y/n)? ";
            cin >> menuEnum;

            if (menuEnum == 'y')
            {
              cout << "Punya member (y/n)? ";
              cin >> menuEnum;

              if (menuEnum == 'y')
              {
                do
                {
                  cout << "Masukkan kode member: ";
                  cin >> inMember;

                  for (int i = 0; i < activeMember; i++)
                  {
                    indexBarang = (member[i][0] == inMember) ? i : 20;
                    if (indexBarang != 20)
                      break;
                  }

                  if (indexBarang == 20)
                    cout << "Member tidak ditemukan. \n";

                } while (indexBarang == 20);

                cout << "[" + member[indexBarang][0] + "] " + member[indexBarang][1]
                     << "\n\n";
                isMember = 1;
              }

              readCart(cartStr, cartInt, jmlCart, total, isMember);

              do
              {
                cout << "Bayar : Rp";
                cin >> paid;

                if (paid < total)
                  cout << "Uang anda tidak mencukupi. \n";

              } while (paid < total);

              int change = paid - total;

              // Ubah stok di inventaris
              for (int i = 0; i < invSize; i++)
                g_invStokHarga[i][0] = copy_invStok[i];

              // Masukkan pembelian ke db log penjualan
              logPenjualan[logIndex][0] = noTrans;
              logPenjualan[logIndex][1] = inBuyDate;
              logHargaPenjualan[logIndex] = total;

              logIndex++;

              // Nota Pembelian
              cout << "No. Transaksi : " + noTrans + "\n"
                   << "Kasir : " + kasir + "\n";
              readCart(cartStr, cartInt, jmlCart, total, isMember);
              cout << "Bayar : Rp" << paid << "\n"
                   << "Kembali : Rp" << change << "\n\n";

              cout << "Terima kasih! \n";

              ulangiKasir = 0;
            }
          }
        }

        else if (menuEnum == '0')
        {
          char kembali;
          cout << "Yakin ingin kembali? Semua barang di keranjang akan dihapus. (y/n) > ";
          cin >> kembali;
          if (kembali == 'y' || kembali == 'Y')
          {
            ulangiKasir = 0;
          }
          else
          {
            ulangiKasir = 1;
          }
        }

        else
          cout << "Pilihan tidak valid! \n";

        cout << "\n";

      } while (ulangiKasir == 1);
    }
    // END FITUR KASIR

    // FITUR LAPORAN PENJUALAN
    else if (MenuOption == '3')
    {
      // Initialize var
      int total = 0;

      cout << "Riwayat Penjualan : \n";

      if (logIndex > 0)
      {
        for (int i = 0; i < logIndex; i++)
        {
          cout << "[" + logPenjualan[i][1] + "] "
               << "#" + logPenjualan[i][0] + " "
               << "Rp" << logHargaPenjualan[i] << "\n";
          total += logHargaPenjualan[i];
        }
      }
      else
        cout << "- \n";

      cout << "\n"
           << "Total : Rp" << total
           << "\n\n";
    }

    else if (MenuOption == '4')
    {
      ReadMember();

      cout << "[1] Tambah Member \n"
           << "[2] Detail pengeluaran member \n"
           << "[0] Kembali \n"
           << "Pilih > ";
      cin >> MenuOption;
    }

    else if (MenuOption == '0')
      ulangiMenu = 0;

  } while (ulangiMenu == 1);

  cout << "Terima Kasih. \n";
  return 0;
}

void readDataInventaris()
{
  int jmlGaris = 70;

  cout << "+" << setfill('-') << setw(jmlGaris) << "+ \n";
  cout << setfill(' ') << left
       << "| " << setw(15) << "Kode Barang"
       << "| " << setw(25) << "Nama Barang"
       << "| " << setw(10) << "Stok"
       << "| " << setw(10) << "Harga"
       << "|";
  cout << setfill('-') << setw(jmlGaris) << "\n";

  cout << setfill(' ') << "\n";
  for (int i = 0; i < invSize; i++)
  {
    cout << left
         << "| " << setw(15) << g_invKodeNama[i][0]
         << "| " << setw(25) << g_invKodeNama[i][1]
         << "| " << setw(10) << g_invStokHarga[i][0]
         << "| " << right << setw(10) << g_invStokHarga[i][1];
    cout << "|\n";
  }
  cout << "+" << setfill('-') << setw(jmlGaris) << "+ \n";
  setfill(' ');
}

void readCopyInv(int invStok[])
{
  for (int i = 0; i < invSize; i++)
  {
    for (int j = 0; j < 2; j++)
      cout << g_invKodeNama[i][j] + " - ";

    cout << invStok[i] << " - "
         << g_invStokHarga[i][1];

    cout << "\n";
  }
}

void UpdateStokBarang(string search)
{
  int stok[5];
  string nama[50];

  int counter = 0;
  for (int x = 0; x < invSize; x++)
  {
    if (g_invKodeNama[x][0] == search)
    {
      counter++;

      cout << "Update stok barang : ";
      cin >> stok[x];

      g_invStokHarga[x][0] = stok[x];

      cout << "Update successfull. \n";
      break;
    }
  }
}

void UpdateHargaBarang(string search)
{
  int harga[10];
  string nama[50];

  int counter = 0;
  for (int x = 0; x < invSize; x++)
  {
    if (g_invKodeNama[x][0] == search)
    {
      counter++;

      cout << "Update harga barang : ";
      cin >> harga[x];

      g_invStokHarga[x][1] = harga[x];

      cout << "update successfull. \n";
    }
  }
}

void readCart(string cartStr[][2], int cartInt[][3], int jml, int &total, bool member)
{
  if (jml == 0)
    cout << "Keranjang masih kosong. \n";
  else
  {
    // Mencari jumlah kata terbanyak di field Nama barang
    int totalColLength = 0, colLength[4] = {14, 12, 5, 10};

    for (int i = 0; i < jml; i++)
    {
      int dataLength = cartStr[i][1].length() + 9;
      colLength[0] = (dataLength > colLength[0]) ? dataLength : colLength[0];
    }

    for (int i = 0; i < 4; i++)
      totalColLength += colLength[i];

    // Menampilkan Cart
    total = 0;
    string field[4] = {"Barang", "Harga", "Qty", "Total"};

    for (int i = 0; i < totalColLength; i++)
      cout << "-";
    cout << "\n";

    for (int i = 0; i < 4; i++)
      cout << left << setw(colLength[i]) << field[i];
    cout << "\n";

    for (int i = 0; i < totalColLength; i++)
      cout << "-";
    cout << "\n";

    for (int i = 0; i < jml; i++)
    {
      cout << left << setw(colLength[0]) << cartStr[i][1] + " (" + cartStr[i][0] + ") "
           << "Rp" << setw(colLength[1] - 2) << cartInt[i][1]
           << setw(colLength[2]) << cartInt[i][0]
           << "Rp" << cartInt[i][2];
      total += cartInt[i][2];

      cout << "\n";
    }

    for (int i = 0; i < totalColLength; i++)
      cout << "-";
    cout << "\n";

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

void ReadMember()
{
  int i, j;

  for (i = 0; i < activeMember; i++)
  {
    cout << "| " << i + 1 << " | ";
    for (j = 0; j < 2; j++)
      cout << member[i][j] + " | ";

    cout << "\n";
  }
  cout << "\n";
}

string noTransaksi(string tgl)
{
  char tanggal[] = {tgl[0], tgl[1], tgl[3], tgl[4], tgl[6], tgl[7], '\0'};
  char angka[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

  string kodeTgl = tanggal;
  string res = "";

  for (int i = 0; i < 4; i++)
    res += angka[rand() % 10];

  return kodeTgl + res;
}