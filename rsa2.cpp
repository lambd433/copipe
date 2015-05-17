#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#define DEBUG
 
int padding = RSA_PKCS1_PADDING;

int public_encrypt(char *data, RSA *rsa, unsigned char *encrypted)
{
  int data_len = strlen(data);
  int result = RSA_public_encrypt(data_len, (unsigned char *)data, encrypted, rsa, padding);
  return result;
}
int public_decrypt(unsigned char *enc_data, RSA *rsa, unsigned char *decrypted)
{
  int data_len = strlen((char *)enc_data);
  int result = RSA_public_decrypt(data_len,enc_data,decrypted,rsa,padding);
  return result;
}
int private_decrypt(unsigned char *enc_data, RSA *rsa, unsigned char *decrypted)
{
  int data_len = strlen((char *)enc_data);
  int result = RSA_private_decrypt(data_len, enc_data, decrypted, rsa, padding);
  return result;
}
int private_encrypt(char *data, RSA *rsa, unsigned char *encrypted)
{
  int data_len = strlen(data);
  int result = RSA_private_encrypt(data_len, (unsigned char *)data, encrypted, rsa, padding);
  return result;
}
 
void printLastError(char *msg)
{
  char *err = (char *) malloc(130);
  ERR_load_crypto_strings();
  ERR_error_string(ERR_get_error(), err);
  printf("%s ERROR: %s\n",msg, err);
  free(err);
}
 
int main(){
  char pri_path[] = "pri-key.pem";
  char pub_path[] = "pub-key.pem";
  FILE *fp;
  RSA *pri_key, *pub_key;

  //reading private-key 
  if((fp = fopen(pri_path, "r")) == NULL){
    fprintf(stderr, "Failed to open %s\n", pri_path);
    exit(1);
  }
  if((pri_key = PEM_read_RSAPrivateKey(fp, NULL, NULL, NULL)) == NULL){
    fprintf(stderr, "Failed to open %s as RSA Private Key\n", pri_path);
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
  // if((pub_key = PEM_read_RSAPublicKey(fp, NULL, NULL, NULL)) == NULL){
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

  char plainText[] = "Hello OpenSSL cryptographic library";
 
  unsigned char encrypted[128]={};
  unsigned char decrypted[128]={};

  printf("plainText=%s\n", plainText);

  // public-enc -> pricate-dec
  int encrypted_len= public_encrypt(plainText, pub_key, encrypted);
  if(encrypted_len == -1)
    {
      printLastError("Public Encrypt failed ");
      exit(0);
    }
  printf("Encrypted length=%d\n", encrypted_len);
  // printf("(Public) Encrypted Text =%s\n", encrypted); non-regular char *
  for (int i=0; i< encrypted_len; i++ ){
    printf("%X", encrypted[i]);
  }
  printf("\n");

  int decrypted_len = private_decrypt(encrypted, pri_key, decrypted);
  if(decrypted_len == -1)
    {
      printLastError("Private Decrypt failed ");
      exit(0);
    }
  printf("Decrypted Length=%d\n", decrypted_len);
  printf("(Private) Decrypted Text=%s\n", decrypted);

  //private-enc -> public_dec
  strcpy((char*) encrypted, "");
  encrypted_len = private_encrypt(plainText, pri_key, encrypted);
  if(encrypted_len == -1)
    {
      printLastError("Private Encrypt failed");
      exit(0);
    }
  printf("Encrypted length=%d\n", encrypted_len);
  // printf("(Private) Encrypted text =%s\n", encrypted); non-regular char *
  for (int i=0; i<encrypted_len; i++ ){
    printf("%X", encrypted[i]);
  }
  printf("\n");

  strcpy((char*)decrypted, "");
  decrypted_len = public_decrypt(encrypted, pub_key, decrypted);
  if(decrypted_len == -1)
    {
      printLastError("Public Decrypt failed");
      exit(0);
    }
  printf("(Public) Decrypted Text=%s\n",decrypted);
  printf("Decrypted Length=%d\n",decrypted_len);
}
