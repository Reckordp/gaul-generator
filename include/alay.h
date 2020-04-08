#ifndef ALAY_HEADER
#define ALAY_HEADER

#include <stdio.h>
#include <string.h>

#define MAX_PENGUBAH (256)
#define UKURAN_KALIMAT (2048)
#define true (1)
#define false (0)

typedef unsigned char bool;

typedef struct {
	bool tanda;
	char asal[16];
	char jadi;
} rangka_perubahan;

void merubah_kalimat(char*, size_t, rangka_perubahan*, size_t);

#endif