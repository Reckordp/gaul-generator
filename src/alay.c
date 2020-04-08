#include <alay.h>

int main() {
	char asal[UKURAN_KALIMAT];
	rangka_perubahan evolusi[MAX_PENGUBAH];
	size_t ukuran;

	memset(evolusi, 0, MAX_PENGUBAH * sizeof(rangka_perubahan));
	ukuran = dapatkan_pengubah(evolusi, MAX_PENGUBAH);

	printf("================================\n");
	printf("	Gaul Generator ");
	printf("\n\n");

	while(true) {
		printf("Kalimat : ");
		gets(asal);
		if (*asal == '\0') break;
		merubah_kalimat(asal, strlen(asal), evolusi, ukuran);
		printf("=> %s\n\n", asal);
	}

	printf("================================\n");
    return 0;
}