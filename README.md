Program mengubah kalimat formal menjadi kalimat gaul.
Mengubah huruf a/A menjadi 4, i/I menjadi 1, g menjadi 9, G menjadi 6 dst...

![Cuplikan](Cuplikan.png)

## TODO
* ~Pengecekan per kata~
* Auto-mim
* Tulis jadi file
* Matikan angka
* Analisa kapital

## Build
* Terminal
```batch
gcc -c src/alay.c -Iinclude -o build/alay.o
gcc -c src/muat.c -Iinclude -o build/muat.o
gcc -c src/pecah.c -Iinclude -o build/pecah.o
gcc -c src/ubah.c -Iinclude -o build/ubah.o
gcc build/alay.o build/muat.o build/pecah.o build/ubah.o -o gaul.exe
"build/gaul.exe"
```

* Otomatis Rake(Ruby)
```batch
rake
```

## Change Log
* v0.1	Mengganti huruf dengan nomer yang sesuai
* v0.2	Kerangka perubahan dari file
* v0.3	Efisiensi pembacaan kalimat
* v1.0	Perubahan kata
* v1.1	Tambah cara untuk merubah
* v1.2	Perubahan mecah kalimat