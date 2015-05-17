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
 
int main(){
  const char pri_path[] = "pri-key.pem";
  const char pub_path[] = "pub-key.pem";
  const char plain[max_crypted_str] = "Hello OpenSSL cryptographic library";
  unsigned char encrypted[max_crypted_str]={};
  unsigned char decrypted[max_crypted_str]={};
  int encrypted_len, decrypted_len;
  FILE *fp;
  RSA *pri_key, *pub_key;

  int plain_len = strlen(plain);

  //reading private-key 
  if((fp = fopen(pri_path, "r")) == NULL){
    fprintf(stderr, "Failed to open %s\n", pri_path);
    exit(1);
  }
  if((pri_key = PEM_read_RSAPrivateKey(fp, NULL, NULL, NULL)) == NULL){
    fprintf(stderr, "Failed to read %s as RSA Private Key\n", pri_path);
    exit(1);
  }
  fclose(fp);
  
#ifdef DEBUG
  fp = fopen("rsa.log", "a");
  RSA_print_fp(fp, pri_key, 0);
  fclose(fp);
#endif

  //reading public-key
  if((fp = fopen(pub_path, "r")) == NULL){
    fprintf(stderr, "Failed to open %s\n", pub_path);
    exit(1);
  }
  if((pub_key = PEM_read_RSA_PUBKEY(fp, NULL, NULL, NULL)) == NULL){
    fprintf(stderr, "Failed to read %s as RSA Public Key\n", pub_path);
    exit(1);
  }
  fclose(fp);

#ifdef DEBUG
  fp = fopen("rsa.log", "a");
  RSA_print_fp(fp, pub_key, 0);
  fclose(fp);
#endif

  printf("Plain Text Length = %d\nPlain Text=%s\n", plain_len, plain);

  // plain -> public_encryped
  if((encrypted_len = RSA_public_encrypt(plain_len, (unsigned char *)plain, encrypted, pub_key, padding)) == -1){
    printf("Failed to Public Encrypt");
    printLastError();
    exit(0);
  }
  printf("Encrypted Length=%d\n", encrypted_len);
  for (int i=0; i< encrypted_len; i++ ){
    printf("%X", encrypted[i]);
  }
  printf("\n");
  // public_encrypted -> private_decryped = plain
  if((decrypted_len = RSA_private_decrypt(encrypted_len, encrypted, decrypted, pri_key, padding)) == -1){
    printf("Failed to Private Decrypt");
    printLastError();
    exit(0);
  }
  printf("(Private) Decrypted Length=%d\nDecryptedText=%s\n", decrypted_len, decrypted);

  memset(encrypted, '\0' , max_crypted_str);
  memset(decrypted, '\0' , max_crypted_str);
  
  // plain -> private_encrypted
  if((encrypted_len = RSA_private_encrypt(plain_len, (unsigned char *)plain, encrypted, pri_key, padding)) == -1){
    printf("Failed to Private Encrypt");
    printLastError();
    exit(0);
  }
  printf("Encrypted Length=%d\n", encrypted_len);
  for (int i=0; i<encrypted_len; i++ ){
    printf("%X", encrypted[i]);
  }
  printf("\n");
  // private_encrypted -> public_decrypted = plain
  if((decrypted_len = RSA_public_decrypt(encrypted_len, encrypted, decrypted, pub_key, padding)) == -1){
    printf("Failed to Public Decrypt");
    printLastError();
    exit(0);
  }
  printf("(Public) Decrypted Length=%d\nDecryptedText=%s\n", decrypted_len, decrypted);
}
