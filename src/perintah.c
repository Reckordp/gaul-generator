#include <io.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <alay/pilihan.h>
#include <alay/version.h>

void hasil_mode_normal(char *hasil, void *benda) {
	printf("=> %s\n", hasil);
}

void hasil_mode_file(char *hasil, void *benda) {
	FILE* f;
	f = fopen((char*)benda, "w");
	fwrite(hasil, sizeof(char), strlen(hasil), f);
	fclose(f);
	free(benda);
}

void hasil_mode_png(char *hasil, void *benda) {
	printf("%s\n", hasil);
}

void tampilkan_penggunaan() {
	static const char *const penggunaan[] = {
		"Pastikan tidak menggunakan antivirus. Kalo ada uninstal gih.", 
		"Penggunaan:", 
		"  -b, -bantu 			Menampilkan penggunaan", 
		"  -k, -ke			Mengubah tulisan didalam file", 
		"  -n, -normal			Ngetik di terminal/cmd", 
#ifndef MATIKAN_PNG
		"  -m, -mim 	Langsung terapkan pada .png"
#endif
		"  -v, -version			Menampilkan versi", 
		" ", 
		"Fitur:", 
		"  tidak-<FITUR>			Mematikan fitur", 
		"  ANGKA				Ubah huruf menjadi angka", 
		"  KATA				Ubah beberapa huruf", 
		NULL
	};

	const char *const *teks = penggunaan;
	while(*teks) printf("%s\n", *teks++);
}

void tampilkan_versi() {
	printf("%s\n", GAUL_DESKRIPSI);
}

void penggunaan_normal(gaul_program *g) {
	printf("Kalimat : ");
	gets(g->teks);
	if (!g->teks[0]) return;
	g->balik_benda = NULL;
	g->balik = hasil_mode_normal;
}

void penggunaan_file(gaul_program *g) {
	FILE* fp;
	char pegang[256], nama_file[256], *benda;
	long ukuran;
	struct stat st;

	*nama_file = 0;
	while (!strlen(nama_file)) {
		printf("Ukuran Maksimal 1KB\n");
		printf("Nama File : ");
		gets(nama_file);
		if (!*nama_file) printf("Masukin lagi\n\n");
	}

	if (stat(nama_file, &st) < 0) {
		memcpy(pegang, nama_file, strlen(nama_file) + 1);
		memcpy(nama_file, g->tempat, strlen(g->tempat));
		memcpy(nama_file + strlen(g->tempat), pegang, strlen(pegang));
		if (stat(nama_file, &st) < 0) {
			printf("\n	%s tidak ditemukan!\n", pegang);
			return;
		}
	}
	if ((((st.st_mode) & S_IFMT) == S_IFDIR)) {
		printf("\n	%s itu folder, yang dibutuhkan file!\n", nama_file);
		return;
	}

	printf("Menghitung ukuran... ");

	fp = fopen(nama_file, "r");
	fseek(fp, 0, SEEK_END);
	ukuran = ftell(fp);

	if (ukuran > 1024) {
		printf("%dKB\nUkuran terlalu besar", ukuran / 1024);
		return;
	}
	printf("%dBytes\n", ukuran);
	fseek(fp, 0, SEEK_SET);
	
	fread(g->teks, 1, ukuran, fp);
	g->teks[ukuran] = 0;
	fclose(fp);

	benda = malloc(strlen(nama_file) + 1);
	memcpy(benda, nama_file, strlen(nama_file) + 1);
	g->balik_benda = (void*)benda;
	g->balik = hasil_mode_file;
	printf("Mengubah...\n");
}

void penggunaan_png(gaul_program *g) {
	char tampung[1024], *teks;
	size_t panjang, tersisa;

	printf("Kalimat Atas : ");
	gets(tampung);

	teks = g->teks;
	panjang = strlen(tampung);
	tersisa = 1024 - panjang - 2;
	if (panjang > 1024) {
		printf("Ruang sudah penuh, akhiri batalkan agenda\n");
		return;
	}
	else if (panjang > 512) {
		printf("Tersisa %d ruang, kelebihan akan dihapus\n\n", tersisa);
	}

	tampung[panjang] = (char)(128);
	memcpy(teks, tampung, panjang + 1);
	teks = teks + panjang + 1;

	printf("Kalimat Bawah : ");
	gets(tampung);
	panjang = strlen(tampung);
	memcpy(teks, tampung, tersisa > panjang ? panjang : tersisa);

	g->balik_benda = NULL;
	g->balik = hasil_mode_png;
}