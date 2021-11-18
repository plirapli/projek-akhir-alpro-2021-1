#include <iostream>
#include <iomanip>

using namespace std;

int strToI(string str);
void readDataInventaris();

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

int arrSize = 6;

int main()
{
  char menuEnum;

  // FITUR KASIR
  bool ulangi = 1;
  int indexBarang = 6, jmlCart = 0, inputQty;
  string inBuyDate, inKodeBarang;
  string dataField[4] = {"Kode Barang", "Nama Barang", "Stok", "Harga"};

  // CART
  string cartStr[arrSize][2];
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
    case '1':
      cout << "Masukkan kode barang: ";
      cin >> inKodeBarang;

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

    case '2':
    {
      int total = 0;
      cout << "Cart : \n";

      if (jmlCart == 0)
        cout << "Keranjang masih kosong. \n";
      else
      {
        for (int i = 0; i < jmlCart; i++)
        {
          cout << cartInt[i][0] << "x "
               << cartStr[i][1] + " (" + cartStr[i][0] + ") "
               << "Rp" << cartInt[i][1] << " = "
               << "Rp" << cartInt[i][2];
          total += cartInt[i][2];

          cout << "\n";
        }

        cout << "Total : Rp" << total << "\n";
      }

      break;
    }

    case '3':
      ulangi = 0;
      break;

    default:
      cout << "Pilihan tidak valid! \n";
      break;
    }

    cout << "\n";

  } while (ulangi == 1);
  // END FITUR KASIR

  return 0;
}

// int strToI(string str)
// {
//   int num = 0;

//   for (int i = 0; i < str.length(); i++)
//     num = num * 10 + (int(str[i]) - 48);

//   return num;
// }

void readDataInventaris()
{
  // READ DATA
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
  // END READ DATA
}