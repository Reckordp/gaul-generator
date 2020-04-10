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


size_t dapatkan_pengubah(gaul_program *gaul) {
	penyerapan_informasi laporan;
	struct deret_asal *da;
	size_t uk_t, urutan;
	char jalur[256], *filename = "daftar";
	short fitur;
	bool izin;

	memcpy(jalur, gaul->tempat, strlen(gaul->tempat) + 1);
	memcpy(jalur + strlen(jalur), filename, strlen(filename) + 1);

	if (access(jalur, F_OK) < 0) {
		printf("File gak ada, buat satu\n");
		FILE *df = fopen(jalur, "w");
		fwrite(daftar_file, sizeof(char), strlen(daftar_file), df);
		fclose(df);
	}

	laporan.gudang = fopen(jalur, "r");
	laporan.situasi = BARU;
	laporan.bacaan = 0;
	laporan.tempat = gaul->evolusi;
	gaul->ukuran = 0;
	uk_t = MAX_DERET_PERUBAHAN;
	fitur = gaul->fitur;

	while(uk_t > 0) {
		if (olah_informasi(&laporan)) {
			izin = true;
			if (!(fitur & FITUR_ANGKA)) {
				izin = !BATASAN_ANGKA(laporan.tempat->jadi[0]);
				da = laporan.tempat_deret;
				while((da - laporan.tempat->deret) && izin) {
					izin = (!BATASAN_ANGKA(da->titik));
					da--;
				}
			}
			if (!(fitur & FITUR_KATA) && izin) {
				izin = (strlen(laporan.tempat->jadi) < 2);
				da = laporan.tempat_deret;
				while((da - laporan.tempat->deret) && izin) {
					izin = (da->panjang < 2);
					da--;
				}
			}

			if (izin) {
				uk_t--;
				laporan.tempat++;
				gaul->ukuran++;
			}

			if (laporan.situasi == SELESAI) break;
		}
	}

	fclose(laporan.gudang);
}

