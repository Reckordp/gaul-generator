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
	FILE *gudang;
	jenis_penangkapan situasi;
	char bacaan;
	
	rangka_perubahan *tempat;
	char *tempat_jadi;
	char *tempat_asal;
	struct deret_asal *tempat_deret;
} penyerapan_informasi;

size_t dapatkan_pengubah(rangka_perubahan*, size_t);