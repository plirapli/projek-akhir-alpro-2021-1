#include <iostream>
#include <iomanip>

using namespace std;

// Fungsi untuk menampilkan data inventaris
void readDataInventaris();

// Fungsi untuk menampilkan keranjang
void readCart(string cartStr[][2], int cartInt[][3], int jml, int &total, bool member);

// Fungsi u/ mengubah stok
void UpdateStokBarang(string search);

// Fungsi u/ mengubah harga
void UpdateHargaBarang(string search);

// DATA INVENTARIS
string invKodeNama[6][2] =
    {
        {"00A1", "Jeruk"},
        {"00A2", "Apel"},
        {"00A3", "Mangga"},
        {"00A4", "Pir"},
        {"00B1", "Semangka"},
        {"00B2", "Melon"},
};

int invStokHarga[6][2] = {
    {20, 8000},
    {42, 6500},
    {35, 4000},
    {7, 3200},
    {0, 25000},
    {1, 18000},
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

int arrSize = 6;

int main()
{
  char MenuOption;

 cout<<"MENU\n"
     <<"[1] INVENTARIS\n"
     <<"[2] KASIR\n"
     <<"Pilih > ";
 cin >> MenuOption;

 if (MenuOption == '1')
 {
  char option, ulang, revaluestok;
  string kode;

  // FITUR INVENTARIS
  do
  {
    cout<<"[1] Tampilkan Daftar Inventaris\n"
        <<"[2] Ubah Stok\n"
        <<"[3] Ubah harga\n"
        <<"[4] Exit\n"
        <<"Pilih > ";
    cin >> option;

    switch (option)
    {
     case '1':
      readDataInventaris();
      cout << endl;
      option = '3';
      break;
     case '2': readDataInventaris();
      cin.ignore();
      option = '3';
      cout << "\nSearch kode barang = ";
      getline(cin, kode);
      UpdateStokBarang(kode);
      break;
     case '3': readDataInventaris();
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
      cout << "Pilihan tidak valid\n";
      break;
    }
  } while (option == '3');
  cout << "Thank You\n";
 // END FITUR INVENTARIS
 } else if (MenuOption == '2')
 {

  char menuEnum;

  // FITUR KASIR
  // Initialize variable
  bool ulangi = 1, isMember = 0;
  int indexBarang = 6, jmlCart = 0, inputQty, total = 0, paid, activeMember = 5;
  string inBuyDate, inKodeBarang, inMember;
  string dataField[4] = {"Kode Barang", "Nama Barang", "Stok", "Harga"};

  // Initialize Cart
  string cartStr[arrSize][2] = {};
  int cartInt[arrSize][3];

  cout << "Tanggal Transaksi (DD-MM-YY): ";
  cin >> inBuyDate;

  cout << "\n";

  do
  {
    readDataInventaris();
    cout << "\n";

    cout << "[1] Tambah Barang \n"
         << "[2] Lihat keranjang \n"
         << "[3] Lanjutkan \n"
         << "Pilih > ";
    cin >> menuEnum;

    switch (menuEnum)
    {
    // Tambah Barang
    case '1':
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

            cout << "\n"
                 << "Added to cart! \n";

            jmlCart++;
          }
          else
            cout << "Penambahan barang dibatalkan. \n";
        }
        else
          cout << "Stok Habis! \n";
      }
      else
        cout << "Barang tidak ditemukan. \n";

      break;

    // Lihat keranjang
    case '2':
    {
      cout << "Cart : \n";
      readCart(cartStr, cartInt, jmlCart, total, isMember);
      break;
    }

    // Next
    case '3':
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

        // Nota Pembelian
        readCart(cartStr, cartInt, jmlCart, total, isMember);
        cout << "Bayar : Rp" << paid << "\n"
             << "Kembali : Rp" << change << "\n";

        cout << "Terima kasih! \n";

        ulangi = 0;
      }

      break;
    }

    default:
      cout << "Pilihan tidak valid! \n";
      break;
    }

    cout << "\n";

  } while (ulangi == 1);
  // END FITUR KASIR
 }
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
  
  int counter=0;
  for (int x=0; x<6; x++)
  {
    if (invKodeNama[x][0] == search)
    {
      counter++;

      cout << "Update stok barang : ";
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
  
  int counter=0;
  for (int x=0; x<6; x++)
  {
    if (invKodeNama[x][0] == search)
    {
      counter++;

      cout << "Update harga barang : ";
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
    int totalColLength = 0, colLength[4] = {14, 8, 5, 10};

    for (int i = 0; i < jml; i++)
    {
      int dataLength = cartStr[i][1].length() + 7;
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