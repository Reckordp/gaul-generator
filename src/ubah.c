#include <alay/ubah.h>

void merubah_kalimat(char *kalimat, size_t ukuran, rangka_perubahan *ev, size_t u_ev) {
	size_t uk_ev;
	char *asal;
	bool diganti;

	while (ukuran > 0) {
		uk_ev = u_ev;
		diganti = false;

		while(uk_ev > 0) {
			asal = ev[u_ev - uk_ev].asal;

			while(*asal != '\0') {
				if (*asal == *kalimat) {
					diganti = true;
					*kalimat = ev[u_ev - uk_ev].jadi;
					break;
				}
				asal++;
			}

			if (diganti) break;
			uk_ev--;
		}

		kalimat++;
		ukuran--;
	}
}