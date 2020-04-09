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
		panjang = deret->panjang;
		if (!panjang) break;

		jumlah = cari_pada_kalimat(deret->titik, bk, &ketemu);
		while (jumlah--) {
			if (strlen(ketemu[jumlah]) < panjang) continue;
			if (kata_sama_p(deret->tunjuk, ketemu[jumlah], panjang)) {
				*pj = panjang;
				*k = ketemu[jumlah];
				*r = rp->jadi;
				return true;
			}
		}
		deret++;
	}

	*pj = -1;
	return false;
}

void ubah_teks(char *asal, char *jadi, size_t panjang) {
	bool perbesar;
	size_t lebar = strlen(asal), timpa = strlen(jadi), lebih;
	perbesar = panjang < timpa;
	lebih = (perbesar ? timpa - panjang : 0);

	char jaga[lebar + lebih];
	memcpy(jaga + lebih, asal, lebar + lebih);
	memcpy(jaga + panjang - timpa + lebih, jadi, timpa);
	if (panjang > timpa) memcpy(asal, jaga + panjang - timpa, lebar + timpa - panjang + 1);
	else memcpy(asal, jaga, lebar);
}

void merubah_kalimat(char *kalimat, size_t ukuran, rangka_perubahan *ev, size_t u_ev) {
	size_t urutan, panjang;
	char *asal, *jadi;
	bagian_kalimat *bk;

	urutan = 0;
	bk = malloc(sizeof(bagian_kalimat));
	memset(bk, 0, sizeof(bagian_kalimat));
	pecah_kalimat(bk, kalimat);

	while (u_ev - urutan) {
		if (cocokkan_perubahan(bk, ev + urutan, &asal, &jadi, &panjang)) {
			ubah_teks(asal, jadi, panjang);
			pecah_kalimat(bk, kalimat);
		} else {
			urutan++;
		}
	}

	free(bk);
}