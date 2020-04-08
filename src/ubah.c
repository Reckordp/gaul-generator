#include <stdlib.h>
#include <alay.h>
#include <alay/pecah.h>

void ubah_teks(bagian_kalimat *bk, rangka_perubahan *rp) {
	size_t jumlah_ketemu, urutan;
	char **ketemu, saat_ini;

	urutan = strlen(rp->asal);
	while(urutan) {
		saat_ini = rp->asal[urutan - 1];
		jumlah_ketemu = cari_pada_kalimat(saat_ini, bk, &ketemu);

		while(jumlah_ketemu) {
			if (*ketemu[jumlah_ketemu] == saat_ini) {
				*ketemu[jumlah_ketemu] = rp->jadi;
			}
			jumlah_ketemu--;
		}

		urutan--;
	}
}

void merubah_kalimat(char *kalimat, size_t ukuran, rangka_perubahan *ev, size_t u_ev) {
	size_t urutan;
	bagian_kalimat *bk;

	urutan = 0;
	bk = malloc(sizeof(bagian_kalimat));
	memset(bk, 0, sizeof(bagian_kalimat));
	pecah_kalimat(bk, kalimat);

	while (u_ev - urutan) {
		ubah_teks(bk, ev + urutan);
		urutan++;
	}
}