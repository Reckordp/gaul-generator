#include <alay.h>
#include <alay/pecah.h>

bool kaitkan_char(bagian_kalimat *dt, char huruf, char *tunjuk) {
	struct kait_titik *tempat;
	char *tersedia;

	if (!huruf) return false;
	tempat = dt->badan;
	tersedia = dt->titik_tersedia;
	while(*tersedia != huruf && *tersedia++) tempat++;
	if (!(*tersedia)) {
		*tersedia = huruf;
		tempat->titik = huruf;
	}

	tempat->tunjuk[tempat->ukuran] = tunjuk;
	tempat->ukuran++;
	return true;
}

void pecah_kalimat(bagian_kalimat *dt, char *teks) {
	size_t urutan;
	urutan = 0;
	while (kaitkan_char(dt, teks[urutan], (teks + urutan))) urutan++;
	dt->asli = teks;
}

size_t cari_pada_kalimat(char dicari, bagian_kalimat *tempat, char*** pencari) {
	size_t urutan;
	while(tempat->titik_tersedia[urutan] && tempat->titik_tersedia[urutan] != dicari) urutan++;
	if (!(tempat->titik_tersedia[urutan])) return 0;
	*pencari = tempat->badan[urutan].tunjuk;
	return tempat->badan[urutan].ukuran;
}