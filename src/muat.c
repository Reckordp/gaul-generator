#include <alay/muat.h>
#include <daftar.h>

#define L(badan) (laporan->badan)
#define LT(badan, dalam) (L(tempat_ ## badan)->dalam)
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

#define KE_PEMISAH \
	do { \
		L(situasi) = PEMISAH; \
		return false; \
	} while(0)

#define AMBIL_BARANG if (fread(&L(bacaan), sizeof(char), 1, L(gudang)) == 0) SEL_JA
#define BATASAN (BATASAN_ALPHA((int)L(bacaan)) || BATASAN_ANGKA((int)L(bacaan)))

bool olah_informasi(penyerapan_informasi *laporan) {
	switch(laporan->situasi) {
		case BARU:
		L(tempat_jadi) = L(tempat)->jadi;
		L(tempat_asal) = L(tempat)->asal;
		L(tempat_deret) = L(tempat)->deret;
		L(situasi) = TITIK;
		AMBIL_BARANG;
		break;
	
		case TITIK:
		if (!BATASAN) KE_PEMISAH;
		*L(tempat_jadi) = L(bacaan);
		L(tempat_jadi)++;
		AMBIL_BARANG;
		break;
	
		case PEMISAH:
		switch((int)(L(bacaan))) {
			case 10:
			LT(deret, panjang) = (int)(L(tempat_asal) - LT(deret, tunjuk));
			L(tempat_deret)++;
			GANTI_GARIS;
			case 44:
			LT(deret, panjang) = (int)(L(tempat_asal) - LT(deret, tunjuk));
			L(tempat_deret)++;
			case 32:
			case 58:
			AMBIL_BARANG;
			if (BATASAN) {
				L(situasi) = TUJUAN;
				LT(deret, titik) = L(bacaan);
				LT(deret, tunjuk) = L(tempat_asal);
			} 
			else if (L(bacaan) != 32) SEL_JA;
			break;

			default:
			SEL_JA;
			break;
		}
		break;

		case TUJUAN:
		if (!BATASAN) KE_PEMISAH;
		*L(tempat_asal) = L(bacaan);
		L(tempat_asal)++;
		AMBIL_BARANG;
		break;
	}

	return false;
}

#undef BATASAN
#undef AMBIL_BARANG
#undef KE_PEMISAH
#undef GANTI_GARIS
#undef SEL_JA
#undef LT
#undef L

#ifdef _WIN32
#	include <libloaderapi.h>
#endif


size_t dapatkan_pengubah(struct rangka_perubahan *tempat, size_t ukuran) {
	penyerapan_informasi laporan;
	size_t uk_t;
	char jalur[256], *filename = "daftar";
	size_t urutan;

#ifdef _WIN32
	GetModuleFileName(0, jalur, 256);
#else
	readlink("/proc/self/exe", jalur, 256);
#endif

	urutan = strlen(jalur);
	while(*(jalur + urutan - 1) != '/' && *(jalur + urutan - 1) != '\\') urutan--;
	while(*(filename++) != '\0') *(jalur + urutan++) = *(filename - 1);
	*(jalur + urutan) = '\0';

	if (access(jalur, F_OK) < 0) {
		printf("File gak ada, buat satu\n");
		FILE *df = fopen(jalur, "w");
		fwrite(daftar_file, sizeof(char), strlen(daftar_file), df);
		fclose(df);
	}

	laporan.gudang = fopen(jalur, "r");
	laporan.situasi = BARU;
	laporan.bacaan = 0;
	laporan.tempat = tempat;
	uk_t = ukuran;

	while(uk_t > 0) {
		if (olah_informasi(&laporan)) {
			uk_t--;
			laporan.tempat++;
			if (laporan.situasi == SELESAI) break;
		}
	}

	fclose(laporan.gudang);
	return ukuran - uk_t;
}