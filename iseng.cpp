#include <iostream>
#include <iomanip>

using namespace std;

// DATA INVENTARIS
// 1. Kode dan Nama
string invKodeNama[6][2] = {
    {"00A1", "Printer Canon Ip 700"},
    {"00A2", "Laptop Acer"},
    {"00A3", "Hardisk Maxtor 60GB"},
    {"00A4", "Flashdisk Toshiba 8GB"},
    {"00B1", "Notebook Asus"},
    {"00B2", "Printer Epson Stylus"},
};

// 2. Stok dan Harga
int invStokHarga[6][2] = {
    {20, 550000},
    {42, 800000},
    {35, 450000},
    {7, 100000},
    {0, 3000000},
    {1, 2800000},
};
// END DATA INVENTARIS

int invSize = 6;

int main()
{
  // DATA INVENTARIS
  // 1. Kode dan Nama
  string copy_invKodeNama[invSize][2];
  int copy_invStokHarga[invSize][2];

  for (int i = 0; i < invSize; i++)
    for (int j = 0; j < 2; j++)
      copy_invKodeNama[i][j] = invKodeNama[i][j];

  for (int i = 0; i < invSize; i++)
    for (int j = 0; j < 2; j++)
      copy_invStokHarga[i][j] = invStokHarga[i][j];

  for (int i = 0; i < invSize; i++)
  {
    for (int j = 0; j < 2; j++)
      cout << copy_invKodeNama[i][j] << " ";

    for (int j = 0; j < 2; j++)
      cout << copy_invStokHarga[i][j] << " ";

    cout << "\n";
  }

  return 0;
}