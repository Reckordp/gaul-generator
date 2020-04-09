#include <stdlib.h>
#include <alay.h>
#include <alay/pecah.h>

bool kata_sama_p(char *kanan, char *kiri, size_t panjang) {
	while (panjang--) {
		if (*kanan++ != *kiri++) return false;
	}
	return true;
}

bool cocokkan_perubahan(bagian_kalimat *bk, rangka_perubahan *rp, char **k, char **r, size_t *pj) {
	size_t urutan, jumlah, panjang;
	struct deret_asal *deret;
	char **ketemu;
	bool cocok;

	urutan = MAX_DERET_PERUBAHAN;
	deret = rp->deret;

	while(urutan--) {
		jumlah = cari_pada_kalimat(deret->titik, bk, &ketemu);
		while (jumlah--) {
			panjang = deret->panjang;

			if (strlen(ketemu[jumlah]) < panjang) continue;
			if (kata_sama_p(deret->tunjuk, ketemu[jumlah], panjang)) {
				*pj = panjang;
				*k = deret->tunjuk;
				*r = ketemu[jumlah];
				return true;
			}
		}
		deret++;
	}

	*pj = -1;
	return false;
}

void ubah_teks(bagian_kalimat *bk, rangka_perubahan *rp) {
	size_t panjang;
	char *tempat, *tujuan;
	if (cocokkan_perubahan(bk, rp, &tempat, &tujuan, &panjang)) {
		memcpy(tempat, tujuan, panjang);
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

	free(bk);
}