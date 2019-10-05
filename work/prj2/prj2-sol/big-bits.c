#include "big-bits.h"
#include "hex-util.h"

#include <stdio.h>

#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

/** Provide concrete definition for struct BigBits to flesh out
 *  abstract BigBits data type.
 */
struct BigBits {
  //@TODO
  char *arr;
  int *size;
};



/** Return a pointer to a representation of a big integer with value
 *  corresponding to the non-empty hexadecimal string hex.  Note that
 *  hex will only contain hexadecimal characters '0' - '9', 'a' - 'f'
 *  and 'A' - 'F' terminated by a NUL '\0' char.
 *
 *  The string hex may not remain valid after this function returns.
 *
 *  Returns NULL on error with errno set "appropriately".
 */
const BigBits *
newBigBits(const char *hex)
{
  assert(CHAR_BIT == 8);
  //@TODO
  struct BigBits *num;
  num = (struct BigBits*) malloc(sizeof(num));
  num->arr = (char*) malloc(strlen(hex));
  num->size = (int *) malloc(sizeof(int));

  num->size[0] = 0;
  
  while(isHexChar(hex[num->size[0]])){

    num->arr[num->size[0]] = charToHexet(hex[num->size[0]]);
    num->size[0]++;
  }

  printf("size: %d \n", num->size[0]);

  
  return num;
}

/** Frees all resources used by currently valid bigBits.  bigBits
 *  is not valid after this function returns.
 */
void
freeBigBits(BigBits *bigBits)
{
  //@TODO
  free(bigBits->arr);
  free(bigBits->size);
  free(bigBits);
}


/** Return a lower-case hex string representing bigBits. Returned
 *  string should not contain any non-significant leading zeros.
 *  Returns NULL on error with errno set "appropriately".  (Note that
 *  there is no call to free the corresponding string).
 */
const char *
stringBigBits(const BigBits *bigBits)
{ 
  //@TODO
  
  printf("size: %d \n", bigBits->size[0]);
  
  char str[bigBits->size[0]];

  int counter = bigBits->size[0];

  while(counter > 0){

    if(bigBits->arr[counter-1] != '0'){

      str[bigBits->size[0] - counter] = bigBits->arr[counter - 1] + '0';
    }

    counter--;
  }

   
  return str;
}


/** Return a new BigBits which is the bitwise-& of bigBits1 and bigBits2.
 *  Returns NULL on error with errno set "appropriately".
 */
const BigBits *
andBigBits(const BigBits *bigBits1, const BigBits *bigBits2)
{
  //@TODO
  return NULL;
}

/** Return a new BigBits which is the bitwise-| of bigBits1 and bigBits2.
 *  Returns NULL on error with errno set "appropriately".
 */
const BigBits *
orBigBits(const BigBits *bigBits1, const BigBits *bigBits2)
{
  //@TODO
  return NULL;
}

/** Return a new BigBits which is the bitwise-^ of bigBits1 and bigBits2.
 *  Returns NULL on error with errno set "appropriately".
 */
const BigBits *
xorBigBits(const BigBits *bigBits1, const BigBits *bigBits2)
{
  //@TODO
  return NULL;
}
