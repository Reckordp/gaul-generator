#include <muat/load.h>

#define L(badan) (laporan->badan)
#define LT(badan) (L(tempat)->badan)
#define SEL_JA \
	do { \
		L(situasi) = SELESAI; \
		return true; \
	} while(0)

#define GANTI_GARIS \
	do { \
		L(situasi) = BARU; \
		return true; \
	} while(0)

#define AMBIL_BARANG if (fread(&bacaan, sizeof(char), 1, L(gudang)) == 0) SEL_JA
#define APA_GANTI_GARIS if (((int)bacaan) == 10) GANTI_GARIS
#define BATASAN_ALPHA(c) (((c >= 97) && (c <= 122)) || ((c >= 65) && (c <= 90)))
#define BATASAN_ANGKA(c) ((c >= 48) && (c <= 57))
#define BATASAN (BATASAN_ALPHA((int)bacaan) || BATASAN_ANGKA((int)bacaan))

bool olah_informasi(penyerapan_informasi *laporan) {
	char bacaan;
	switch(laporan->situasi) {
		case BARU:
		LT(tanda) = true;
		L(penunjuk) = 0;
		L(situasi) = TITIK;
		break;
	
		case TITIK:
		AMBIL_BARANG;
		if (!BATASAN) SEL_JA;
		LT(jadi) = bacaan;
		L(situasi) = PEMISAH;
		break;
	
		case PEMISAH:
		AMBIL_BARANG;
		if (BATASAN) SEL_JA;
		L(situasi) = TUJUAN;
		break;

		case TUJUAN:
		AMBIL_BARANG;
		APA_GANTI_GARIS;
		if (bacaan == 32) AMBIL_BARANG;
		if (!BATASAN) SEL_JA;
		LT(asal)[L(penunjuk)] = bacaan;
		L(penunjuk)++;
		AMBIL_BARANG;
		APA_GANTI_GARIS;
		if (bacaan != 44) SEL_JA;
		break;
	}

	return false;
}

#undef BATASAN
#undef BATASAN_ANGKA
#undef BATASAN_ALPHA
#undef APA_GANTI_GARIS
#undef AMBIL_BARANG
#undef GANTI_GARIS
#undef SEL_JA
#undef LT
#undef L

size_t dapatkan_pengubah(rangka_perubahan *tempat, size_t ukuran) {
	penyerapan_informasi laporan;
	size_t uk_t;

	if (access("daftar", F_OK) < 0) {
		printf("File gak ada buat satu\n");
		FILE *df = fopen("daftar", "w");
		fwrite(daftar_file, sizeof(char), strlen(daftar_file), df);
		fclose(df);
	}

	laporan.tempat = tempat;
	laporan.penunjuk = 0;
	laporan.gudang = fopen("daftar", "r");
	laporan.situasi = BARU;
	uk_t = ukuran;

	while(uk_t > 0) {
		if (olah_informasi(&laporan)) {
			if (laporan.situasi == SELESAI) break;
			laporan.tempat++;
			uk_t--;
		}
	}

	fclose(laporan.gudang);
	return ukuran - uk_t;
}