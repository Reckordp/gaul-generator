#ifndef ALAY_HEADER
#define ALAY_HEADER

#include <stdio.h>
#include <string.h>

#define MAX_PENGUBAH (256)
#define UKURAN_KALIMAT (2048)
#define true (1)
#define false (0)

#define HURUF_BESAR_P(c) ((c >= 65) && (c <= 90))
#define HURUF_KECIL_P(c) ((c >= 97) && (c <= 122))
#define BATASAN_ALPHA(c) (HURUF_BESAR_P(c) || HURUF_KECIL_P(c))
#define BATASAN_ANGKA(c) ((c >= 48) && (c <= 57))
#define HURUF_KE_KECIL(c) ((HURUF_BESAR_P(c)) ? (char)(c - 65 + 97) : c)
#define HURUF_KE_BESAR(c) ((HURUF_KECIL_P(c)) ? (char)(c + 65 - 97) : c)

typedef unsigned char bool;

struct deret_asal {
	char titik;
	size_t panjang;
	char *tunjuk;
};

typedef struct {
	char jadi[256];
	char asal[2048];
	struct deret_asal deret[16];
} rangka_perubahan;

void merubah_kalimat(char*, size_t, rangka_perubahan*, size_t);

#endif