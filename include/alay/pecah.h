struct kait_titik {
	char titik;
	char *tunjuk[64];
	size_t ukuran;
};

typedef struct {
	char titik_tersedia[128];
	struct kait_titik badan[128];
	char *asli;
} bagian_kalimat;

void pecah_kalimat(bagian_kalimat*, char*);
size_t cari_pada_kalimat(char, bagian_kalimat*, void**);