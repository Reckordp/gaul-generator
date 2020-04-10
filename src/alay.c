#include <alay.h>
#include <alay/muat.h>
#include <alay/pilihan.h>

int jalankan_perintah(gaul_program *gaul, size_t ukuran) {
	gaul->fungsi(gaul);
	if (!gaul->balik) return 1;
	merubah_kalimat(gaul->teks, strlen(gaul->teks), gaul->evolusi, ukuran);
	gaul->balik(gaul->teks, gaul->balik_benda);
}

int main(int argc, char **argv) {
	gaul_program *gaul;
	size_t ukuran;
	int keluar;

	gaul = urai_args(argc, argv);
	if (!gaul) return 1;
	ukuran = dapatkan_pengubah(gaul->evolusi, MAX_PENGUBAH);
	keluar = 0;

	printf("\n");
	printf("================================");
	printf("================================\n");
	printf("			");
	printf("Gaul Generator\n");
	printf("\n\n");

	keluar = jalankan_perintah(gaul, ukuran);

	printf("\n");
	printf("================================");
	printf("================================\n");
    return keluar;
}