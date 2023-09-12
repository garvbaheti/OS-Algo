using namespace std;

#include <iostream>

//FIFO
int fifo(int a[], int n, int k)
{
    //inisilisasi cetak
    for (int i = 0; i < k; i++)
        cout << a[i] << " ";

    cout << endl;

    //proses
    for (int i = k; i < n; i++)
    {
        int j;

        //loop sampai akhir
        for (j = 0; j < k; j++)

            //cek apakah sudah ada di cache
            if (a[i] == a[j])
                break;

        if (j == k)
        {
            //ganti elemen pertama dengan elemen baru
            for (j = 1; j < k; j++)
                a[j - 1] = a[j];

            a[k - 1] = a[i];
        }

        //cetak
        for (int j = 0; j < k; j++)
            cout << a[j] << " ";

        cout << endl;
    }

    return 0;
}

//normalisasi
int normal(int a[], int n)
{
    int b[100];

    for (int i = 0; i < n; i++)
        b[a[i]] = 1;

    for (int i = 0, j = 0; i < 100; i++)
        if (b[i] == 1)
            a[j++] = i;

    return 0;
}

//LRU
int lru(int a[], int n, int k)
{
    //inisilisasi
    int b[k];
    for (int i = 0; i < k; i++)
        b[i] = -1;

    //cetak
    for (int i = 0; i < k; i++)
        cout << a[i] << " ";

    cout << endl;

    //proses
    for (int i = k; i < n; i++)
    {
        int j;

        //loop sampai akhir
        for (j = 0; j < k; j++)

            //cek elemen regular
            if (a[i] == b[j])
            {
                int temp = b[j];

                //shift ke atas kecuali elemen terakhir
                for (; j < k - 1; j++)
                    b[j] = b[j + 1];

                b[k - 1] = temp;
                break;
            }

        if (j == k)
        {
            //shift up semua
            for (j = 1; j < k; j++)
                b[j - 1] = b[j];

            b[k - 1] = a[i];
        }

        //cetak
        for (int i = 0; i < k; i++)
            cout << b[i] << " ";

        cout << endl;
    }

    return 0;
}

//driver
int main()
{
    int a[] = {1, 2, 8, 3, 4, 1, 5, 6, 2, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7};
    int n = 19;

    //FIFO
    fifo(a, n, 3);
    cout << "LRU\n";
    //LRU
    int b[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    n = 20;

    //normalisasi
    normal(b, n);

    //fungsi LRU
    lru(b, n, 5);

    return 0;
}