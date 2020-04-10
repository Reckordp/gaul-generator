#include <stdlib.h>
#include <alay.h>
#include <alay/pecah.h>

bool kata_sama_p(char *kanan, char *kiri, size_t panjang) {
	while (panjang--) {
		if (*kanan++ != *kiri++) return false;
	}
	return true;
}

bool cocokkan(bagian_kalimat *bk, struct rangka_perubahan *rp, char **k, char **r, size_t *pj) {
	size_t urutan, jumlah, panjang;
	struct deret_asal *deret;
	char **ketemu;
	bool cocok;

	urutan = MAX_DERET_PERUBAHAN;
	deret = rp->deret;

	while(urutan--) {
		panjang = deret->panjang;
		if (!panjang) break;

		jumlah = cari_pada_kalimat(deret->titik, bk, (void**)(&ketemu));
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

	char jaga[lebar + lebih + 1];
	memcpy(jaga + lebih, asal, lebar + lebih + 1);
	memcpy(jaga + panjang - timpa + lebih, jadi, timpa);
	if (perbesar) memcpy(asal, jaga, lebar + lebih + 1);
	else memcpy(asal, jaga + panjang - timpa, lebar + timpa - panjang + 1);
}

void merubah_kalimat(gaul_program *gaul) {
	size_t urutan, panjang;
	char *asal, *jadi;
	bagian_kalimat bk;

	memset(&bk, 0, sizeof(bagian_kalimat));
	pecah_kalimat(&bk, gaul->teks);
	urutan = 0;

	while(gaul->ukuran - urutan) {
		if (cocokkan(&bk, gaul->evolusi + urutan, &asal,  &jadi, &panjang)) {
			ubah_teks(asal, jadi, panjang);
			pecah_kalimat(&bk, gaul->teks);
		} else urutan++;
	}
}

