#ifndef ALAY_HEADER
#define ALAY_HEADER

#include <stdio.h>
#include <string.h>

#define MATIKAN_PNG

#define MAX_PENGUBAH (256)
#define MAX_DERET_PERUBAHAN (16)
#define UKURAN_KALIMAT (2048)
#define true (1)
#define false (0)

#define FITUR_SEMUA (0x3)
#define FITUR_KATA (0x2)
#define FITUR_ANGKA (0x1)

#define HURUF_BESAR_P(c) ((c >= 65) && (c <= 90))
#define HURUF_KECIL_P(c) ((c >= 97) && (c <= 122))
#define BATASAN_ALPHA(c) (HURUF_BESAR_P(c) || HURUF_KECIL_P(c))
#define BATASAN_ANGKA(c) ((c >= 48) && (c <= 57))
#define HURUF_KE_KECIL(c) ((HURUF_BESAR_P(c)) ? (char)(c - 65 + 97) : c)
#define HURUF_KE_BESAR(c) ((HURUF_KECIL_P(c)) ? (char)(c + 65 - 97) : c)

typedef struct gp gaul_program;
typedef unsigned char bool;
typedef void (*pengambil_perintah) (gaul_program*);
typedef void (*pengambil_hasil) (char*, void*);

struct deret_asal {
	char titik;
	size_t panjang;
	char *tunjuk;
};

struct rangka_perubahan {
	char jadi[256];
	char asal[128 * MAX_DERET_PERUBAHAN];
	struct deret_asal deret[MAX_DERET_PERUBAHAN];
};

typedef struct gp {
	short fitur;
	char teks[1024];

	pengambil_perintah fungsi;
	pengambil_hasil balik;
	void *balik_benda;

	char tempat[256];
	struct rangka_perubahan evolusi[MAX_PENGUBAH];
	size_t ukuran;
	bool berlanjut;
} gaul_program;

void merubah_kalimat(gaul_program*);

#endif