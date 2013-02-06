#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <aes.h>

#pragma comment(lib, "aes.lib")

void encrypt(const char *fileIn, const char *fileOut, const unsigned char *key);
void decrypt(const char *fileIn, const char *fileOut, const unsigned char *key);

//int main() {
//	const unsigned char key[] = "my key";
//
//	srand(time(NULL));
//
//	aes_init();
//	encrypt("main.c", "main.c.encrypted", key);
//	decrypt("main.c.encrypted", "main.c.decrypted", key);
//
//	return 0;
//}

void encrypt(const char *fileIn, const char *fileOut, const unsigned char *key) {
	int i;
	aes_encrypt_ctx ctx[1];
	unsigned char iv[16]; /* initialization vector */
	unsigned char inBuffer[200], outBuffer[200];
	FILE *inFile = fopen(fileIn, "rb");
	FILE *outFile = fopen(fileOut, "wb");

	/* pick a random initialization vector */
	for(i = 0; i < 16; ++i)
		iv[i] = rand() & 0xFF;
	fwrite(iv, 1, 16, outFile);

	aes_encrypt_key256(key, ctx);
	while(( i = fread(inBuffer, 1, sizeof(inBuffer), inFile) ) > 0) {
		aes_ofb_crypt(inBuffer, outBuffer, i, iv, ctx);
		fwrite(outBuffer, 1, i, outFile);
	}
	aes_ofb_crypt(inBuffer, outBuffer, i, iv, ctx);
	fwrite(outBuffer, 1, i, outFile);

	fclose(inFile);
	fclose(outFile);
}

void decrypt(const char *fileIn, const char *fileOut, const unsigned char *key) {
	int i;
	aes_encrypt_ctx ctx[1];
	unsigned char iv[16]; /* initialisation vector */
	unsigned char inBuffer[200], outBuffer[200];
	FILE *inFile = fopen(fileIn, "rb");
	FILE *outFile = fopen(fileOut, "wb");

	/* read initialization vector from file */
	if (fread(iv, 1, 16, inFile) < 16)
		return; /* error: file doesn't even contain an initialization vector */

	aes_encrypt_key256(key, ctx);
	while((i = fread(inBuffer, 1, sizeof(inBuffer), inFile)) > 0) {
		aes_ofb_crypt(inBuffer, outBuffer, i, iv, ctx);
		fwrite(outBuffer, 1, i, outFile);
	}

	fclose(inFile);
	fclose(outFile);
}