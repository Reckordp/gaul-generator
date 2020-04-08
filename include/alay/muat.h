#include <io.h>
#include <alay.h>

typedef enum {
	BARU, 
	TITIK, 
	PEMISAH, 
	TUJUAN, 
	SELESAI
} jenis_penangkapan;

typedef struct {
	rangka_perubahan *tempat;
	int penunjuk;
	FILE *gudang;
	jenis_penangkapan situasi;
} penyerapan_informasi;

size_t dapatkan_pengubah(rangka_perubahan*, size_t);