#include <stdlib.h>
#include <alay/pilihan.h>

void buat_bungkus(gaul_program** bungkus) {
	*bungkus = malloc(sizeof(gaul_program));
	memset(*bungkus, 0, sizeof(gaul_program));
}

#define SAMA(k, o) ((kata_sama_p(k, o, strlen(o)) && (strlen(o) == strlen(k))) ? o[0] : '\0')

char singkat_tanda(char *tanda) {
	if (strlen(tanda) <= 1) return tanda[0];

	switch(tanda[0]) {
		case 'b':
		return SAMA(tanda, "bantu");
		case 'n':
		return SAMA(tanda, "normal");
		case 'k':
		return SAMA(tanda, "ke");
		case 'm':
		return SAMA(tanda, "mim");
		case 'v':
		return SAMA(tanda, "version");
	}
	return 0;
}

#undef SAMA

void pahami_tanda(char tanda, gaul_program** bb) {
	gaul_program *b;
	buat_bungkus(bb);
	b = *bb;

	switch(tanda) {
		case 'n':
		b->fungsi = penggunaan_normal;
		return;

		case 'k':
		b->fungsi = penggunaan_file;
		return;

		case 'm':
		b->fungsi = penggunaan_png;
		return;

		case 'b':
		tampilkan_penggunaan();
		break;

		case 'v':
		tampilkan_versi();
		break;

		default:
		printf("Tidak mengenali perintah\n");
	}

	free(b);
	*bb = NULL;
}

void tanda_berlanjut(gaul_program *g, char* tanda) {
	if (!kata_sama_p(tanda, "tidak-", 6)) return;
	tanda = tanda + 6;
	if (kata_sama_p(tanda, "ANGKA", 5) && g->fitur & FITUR_ANGKA) g->fitur ^= FITUR_ANGKA;
	else if (kata_sama_p(tanda, "KATA", 4) && g->fitur & FITUR_KATA) g->fitur ^= FITUR_KATA;
	else printf("%s bukan fitur\n", tanda);
}

void urai_berlanjut(int argc, char** argv, gaul_program *bungkus, char *tempat) {
	char *t;

	t = (tempat + strlen(tempat) - 1);
	while(*t != '/' && *t != '\\') *t-- = '\0';

	memcpy(bungkus->tempat, tempat, strlen(tempat));
	bungkus->fitur = FITUR_SEMUA;
	while(argc > 0 && argc--) tanda_berlanjut(bungkus, *argv++);
}

gaul_program *urai_args(int argc, char** argv) {
	char *tanda, *tempat;
	gaul_program *bungkus;

	argc--;
	tempat = *argv++;
	bungkus = NULL;

	if (!argc) tanda = "-normal";
	else tanda = argv[0];

	switch(*tanda) {
		case '-':
		pahami_tanda(singkat_tanda(++tanda), &bungkus);
		break;
	
		case 'b':
		if (singkat_tanda(tanda) == 'b') pahami_tanda('b', &bungkus);
		break;

		default:
		printf("Tidak mengerti perintah anda. Untuk menampilkan penggunaan (-bantu)\n");
	}

	if (bungkus) urai_berlanjut(--argc, ++argv, bungkus, tempat);
	return bungkus;
}