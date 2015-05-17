#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEBUG
 
const int padding = RSA_PKCS1_PADDING;
const int max_buf = 1024;
const int max_bit = 2048;
const int max_crypted_str = max_bit/8;

void printLastError()
{
  char *err = (char *) malloc(max_buf);
  ERR_load_crypto_strings();
  ERR_error_string(ERR_get_error(), err);
  printf("ERROR: %s\n", err);
  free(err);
}

int pass_cb(char *buf, int size, int rwflag, void *u){
  int len;
  char tmp[max_buf];
  printf("Enter pass phrase:");
  while(fgets(tmp, sizeof(tmp), stdin) == NULL){
    printf("Enter pass phrase:");
  }
  if((len = strlen(tmp)) <= 0) return 0;
  memcpy(buf, tmp, len);
  return len;
}
