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

const char *daftar_file = \
	"0: o, O\n" \
	"1: i, I\n" \
	"2: z, Z\n" \
	"4: a, A\n" \
	"5: s, S\n" \
	"6: G\n" \
	"7: t, d, T, D\n" \
	"9: g";