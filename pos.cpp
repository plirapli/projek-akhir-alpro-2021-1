#include <iostream>
#include <iomanip>

using namespace std;

// Fungsi untuk menampilkan data inventaris
void readDataInventaris();

// Fungsi untuk menampilkan keranjang
void readCart(string cartStr[][2], int cartInt[][3], int jml, int &total, bool member);

// Fungsi untuk mengenerate kode transaksi
string noTransaksi(string tgl);

// Fungsi u/ mengubah stok
void UpdateStokBarang(string search);

// Fungsi u/ mengubah harga
void UpdateHargaBarang(string search);

// Global Variables
// DATA INVENTARIS
// Kode dan Nama
string invKodeNama[6][2] = {
    {"00A1", "Printer Canon Ip 700"},
    {"00A2", "Laptop Acer"},
    {"00A3", "Hardisk Maxtor 60GB"},
    {"00A4", "Flashdisk Toshiba 8GB"},
    {"00B1", "Notebook Asus"},
    {"00B2", "Printer Epson Stylus"},
};

// Stok dan Harga
int invStokHarga[6][2] = {
    {20, 550000},
    {42, 800000},
    {35, 450000},
    {7, 100000},
    {0, 3000000},
    {1, 2800000},
};
// END DATA INVENTARIS

// DATA MEMBER
string member[10][2] = {
    {"001", "Muhammad Rafli"},
    {"002", "Desy Nur Azizah"},
    {"003", "Seva Giantama"},
    {"004", "Shazi Awaludin"},
    {"005", "Heri Nur Cahyana"},
};

// DATA PENJUALAN
string logPenjualan[50][2] = {{"1510211234", "15-10-21"}};
int logHargaPenjualan[50] = {43000};

int arrSize = 6;

int main()
{
  // Initialize Main Variable
  bool ulangiMenu = true;
  int jmlCart = 0, logIndex = 1, activeMember = 5;
  char MenuOption;

  do
  {
    cout << "MENU \n"
         << "[1] INVENTARIS \n"
         << "[2] KASIR \n"
         << "[3] Log Penjualan \n"
         << "[4] Exit \n"
         << "Pilih > ";
    cin >> MenuOption;

    // FITUR INVENTARIS
    if (MenuOption == '1')
    {
      char option, ulang, revaluestok;
      string kode;

      // FITUR INVENTARIS
      do
      {
        cout << "[1] Tampilkan Daftar Inventaris \n"
             << "[2] Ubah Stok \n"
             << "[3] Ubah harga \n"
             << "[4] Exit \n"
             << "Pilih > ";
        cin >> option;

        switch (option)
        {
        case '1':
          readDataInventaris();
          cout << endl;
          option = '3';
          break;
        case '2':
          readDataInventaris();
          cin.ignore();
          option = '3';
          cout << "\nSearch kode barang = ";
          getline(cin, kode);
          UpdateStokBarang(kode);
          break;
        case '3':
          readDataInventaris();
          cin.ignore();
          option = '3';
          cout << "\nSearch kode barang = ";
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
      cout << "Thank You \n";
      // END FITUR INVENTARIS
    }

    // FITUR KASIR
    else if (MenuOption == '2')
    {
      // Initialize variable
      char menuEnum;
      bool ulangi = 1, isMember = 0;
      int indexBarang = 6, inputQty, total = 0, paid;
      string inBuyDate, noTrans, inKodeBarang, inMember;

      // Initialize Cart
      string cartStr[arrSize][2] = {};
      int cartInt[arrSize][3];

      cout << "Tanggal Transaksi (DD-MM-YY): ";
      cin >> inBuyDate;

      noTrans = noTransaksi(inBuyDate);

      cout << "\n";

      do
      {
        readDataInventaris();
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
            for (int i = 0; i < 6; i++)
            {
              indexBarang = (invKodeNama[i][0] == inKodeBarang) ? i : 6;
              if (indexBarang != 6)
                break;
            }

            if (indexBarang != 6)
            {
              string namaBarang = invKodeNama[indexBarang][1];
              int stok = invStokHarga[indexBarang][0];
              int hargaBarang = invStokHarga[indexBarang][1];

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

                  invStokHarga[indexBarang][0] -= inputQty;
                  jmlCart++;

                  cout << "Added to cart! \n";
                  ulangiCari = 0;
                }
                else
                  cout << "Penambahan barang dibatalkan. \n\n";
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
                    indexBarang = (member[i][0] == inMember) ? i : 11;
                    if (indexBarang != 11)
                      break;
                  }

                  if (indexBarang == 11)
                    cout << "Member tidak ditemukan. \n";

                } while (indexBarang == 11);

                cout << "[" + member[indexBarang][0] + "] " + member[indexBarang][1]
                     << "\n\n";
                isMember = 1;

                readCart(cartStr, cartInt, jmlCart, total, isMember);
              }

              do
              {
                cout << "Bayar: ";
                cin >> paid;

                if (paid < total)
                  cout << "Uang anda tidak mencukupi. \n";

              } while (paid < total);

              int change = paid - total;

              logPenjualan[logIndex][0] = noTrans;
              logPenjualan[logIndex][1] = inBuyDate;
              logHargaPenjualan[logIndex] = total;

              logIndex++;

              // Nota Pembelian
              cout << "No. Transaksi: " << noTrans << "\n";
              readCart(cartStr, cartInt, jmlCart, total, isMember);
              cout << "Bayar : Rp" << paid << "\n"
                   << "Kembali : Rp" << change << "\n\n";

              cout << "Terima kasih! \n";

              ulangi = 0;
            }
          }
        }

        else if (menuEnum == '0')
          ulangi = 0;

        else
          cout << "Pilihan tidak valid! \n";

        cout << "\n";

      } while (ulangi == 1);
    }
    // END FITUR KASIR

    // FITUR LAPORAN PENJUALAN
    else if (MenuOption == '3')
    {
      // Initialize var
      int total = 0;

      cout << "Riwayat Penjualan : \n";

      for (int i = 0; i < logIndex; i++)
      {
        cout << "[" + logPenjualan[i][1] + "] "
             << "#" + logPenjualan[i][0] + " "
             << "Rp" << logHargaPenjualan[i] << "\n";
        total += logHargaPenjualan[i];
      }

      cout << "\n"
           << "Total : Rp" << total
           << "\n\n";
    }

    else if (MenuOption == '4')
      ulangiMenu = 0;

  } while (ulangiMenu == 1);

  cout << "Terima Kasih. \n";
  return 0;
}

void readDataInventaris()
{
  for (int i = 0; i < arrSize; i++)
  {
    for (int j = 0; j < 2; j++)
      cout << invKodeNama[i][j] + " - ";

    for (int j = 0; j < 2; j++)
    {
      string separator = (j >= 1) ? "" : " - ";
      cout << invStokHarga[i][j] << separator;
    }
    cout << "\n";
  }
}

void UpdateStokBarang(string search)
{
  int stok[5];
  string nama[50];

  int counter = 0;
  for (int x = 0; x < 6; x++)
  {
    if (invKodeNama[x][0] == search)
    {
      counter++;

      cout << "Update stok barang = ";
      cin >> stok[x];

      invStokHarga[x][0] = stok[x];

      cout << "update seccessfull\n";
      break;
    }
  }
}

void UpdateHargaBarang(string search)
{
  int harga[10];
  string nama[50];

  int counter = 0;
  for (int x = 0; x < 6; x++)
  {
    if (invKodeNama[x][0] == search)
    {
      counter++;

      cout << "Update harga barang = ";
      cin >> harga[x];

      invStokHarga[x][1] = harga[x];

      cout << "update seccessfull\n";
      break;
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