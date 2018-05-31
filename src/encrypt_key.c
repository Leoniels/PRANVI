#include <stdio.h>
#include <sys/resource.h> // setpriority()

#include "math.h"

/*
--------------------------------------------------------------------
  Main
--------------------------------------------------------------------
*/
int main (int argc, char *argv[]) {
  long int secondsEncrypted;
  FILE *fp;

  mpz_t n, fiN, exp, two, base, powMod, time, key, encryptedKey;
  mpz_init(n);
  mpz_init(fiN);
  mpz_init(exp);
  mpz_init(two);
  mpz_init(base);
  mpz_init(powMod);
  mpz_init(time);
  mpz_init(key);
  mpz_init(encryptedKey);

  // Capture from argument the time the key will need to be
  // decrypted.
  if (argc != 2) {
    printf ("Introduce encrypt time (seconds)\n");
    return 1;
  }
  secondsEncrypted = atol(argv[1]);

  // Read the ratio square per seconds stored in file.
  fp = fopen("average_square_per_seconds.txt", "r");
  if (!fp) {
    printf("average_square_per_seconds.txt not found");
    return 1;
  }
  mpz_inp_str(time, fp, 10);
  fclose(fp);

  // Calculate T parameter (T = time(seconds) * ratio(square per
  // per seconds).
  mpz_mul_si(time, time, secondsEncrypted);

  // Obtain modulus
  getModulus(n, fiN);

  // Obtaining random base.
  getRandomBase(base, n);

  // exp = 2 ^ time mod fi(n)
  mpz_set_ui (two, 2L);
  mpz_powm(exp, two, time, fiN);

  // powMod = 2 ^ exp mod n
  mpz_powm(powMod, base, exp, n);

  // Get key value and load it into a mpz_int
  fp = fopen("key.txt", "r");
  if (!fp) {
    printf("key.txt not found");
    return 1;
  }
  mpz_inp_str(key, fp, 10);
  fclose(fp);
  // Obtain encrypted key
  mpz_add(encryptedKey, key, powMod);

  // Store data to next decrypt
  fp = fopen("key_encrypted.txt", "w");
  if (!fp) {
    printf("key_encrypted.txt not found");
    return 1;
  }
  mpz_out_str(fp, 16, encryptedKey);
  fputc('\n', fp);
  mpz_out_str(fp, 16, n);
  fputc('\n', fp);
  mpz_out_str(fp, 16, base);
  fputc('\n', fp);
  mpz_out_str(fp, 16, time);
  fclose(fp);

  // Free memory
  mpz_clear(n);
  mpz_clear(fiN);
  mpz_clear(exp);
  mpz_clear(two);
  mpz_clear(base);
  mpz_clear(powMod);
  mpz_clear(time);
  mpz_clear(key);
  mpz_clear(encryptedKey);
  return 0;
}
