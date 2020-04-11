#include <alay.h>
#include <alay/muat.h>
#include <alay/pilihan.h>
#include <stdlib.h>

int jalankan_perintah(gaul_program *gaul) {
	gaul->fungsi(gaul);
	if (!gaul->balik) return 1;
	merubah_kalimat(gaul);
	gaul->balik(gaul->teks, gaul->balik_benda);
	gaul->balik_benda = NULL;
}

int main(int argc, char **argv) {
	gaul_program *gaul;
	bool sekali;

	sekali = true;
	gaul = urai_args(argc, argv);
	if (!gaul) return 1;
	dapatkan_pengubah(gaul);

	printf("\n");
	printf("================================");
	printf("================================\n");
	printf("			");
	printf("Gaul Generator\n");
	printf("\n\n");

	while (gaul->berlanjut || sekali) {
		if (jalankan_perintah(gaul)) break;
		sekali = 0;
	}

	printf("\n");
	printf("================================");
	printf("================================\n");
	if (gaul->balik_benda) free(gaul->balik_benda);
	free(gaul);
    return 0;
}