#include "bits-to-ints.h"
#include "errors.h"

#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>


//@TODO: auxiliary definitions

/** This function should be called with inFile set to an input FILE
 *  stream corresponding to a file named inName.  This FILE should
 *  contain a stream of '0' or '1' bit-value characters optionally
 *  separated by whitespace (as determined by isspace()) characters.
 *  The function should return the next unsigned integer value given
 *  by the next next nBits bit characters read from in.
 *
 *  The nBits argument (which should be > 0) will specify the number
 *  of bits from FILE stream inFile which are to be grouped to form an
 *  unsigned integer value.
 *
 *  The bytes within the bit-stream are assumed to be in big-endian
 *  order (with the most significant byte first), and the bits within
 *  each byte are ordered little-endian with the least-significant bit
 *  first.
 *
 *  For example, assume that nBits is 16 and the least significant bit
 *  in the result is at index 0, and most significant bit in the
 *  result at index 15; i.e., the bits in the BitsValue result are
 *  indexed 15-14-...-1-0.  The order of the corresponding bits in the
 *  input stream will be 8-9-10-11-12-13-14-15 - 0-1-2-3-4-5-6-7.  So
 *  the bit-stream "1101 0101 1011 0011" will result in the BitsValue
 *  0xabcd (which has binary representation 1010_1011_1100_1101).
 *
 *  When the function returns, *isEof should be set to true if
 *  end-of-file is encountered on inFile.  If EOF is encountered
 *  within a partial value, then a suitable error message should be
 *  printed before returning with *isEof true.
 *
 *  If any character other than '0', '1' or whitespace is encountered
 *  in inFile, then a suitable error message should be printed and the
 *  function should return with *isEof set to true.
 */

int bitsToNum(char n0, char n1, char n2, char n3){

  int returnVal = 0;  
  
  int v0 = n0 - '0';
  int v1 = n1 - '0';
  int v2 = n2 - '0';
  int v3 = n3 - '0';
  
  returnVal += v0;
  returnVal += v1 * 2;
  returnVal += v2 * 4;
  returnVal += v3 * 8;
 
  return returnVal;
}


long long power(int a, int b){
  long long x = 1;
  for(int i = 0; i < b; i++){
    x *= a;
  }
  return x;
}


BitsValue
bits_to_ints(FILE *inFile, const char *inName, int nBits, bool *isEof)
{
  //nBits value should make sense
  assert(0 < nBits && nBits <= CHAR_BIT*sizeof(BitsValue));
  BitsValue value = 0;
  //@TODO

  long  long valueHolder[nBits/4];
  char bitHolder[nBits];
  int valueHolderIndex = 0;

  
  
    for(int i = 0; i < nBits; i++){

     char c = fgetc(inFile);

     

     if(c == EOF && i%8 != 0){
       printf("Unexpected EOF within byte in data file \n" );
       *isEof = true;
       break;
     }
     
     if(c == EOF && i != 0){
      *isEof = true;
      printf("Unexpected EOF within value in data file \n");
      break;
     }

     if(c == EOF){
       *isEof = true;
       break;
     }
     
     if(c != '1' && c != '0' &&  !isspace(c)){
       printf("Unexpected character '%c' in file \n", c);
       *isEof = true;
       break;
     }     
     
      if(isspace(c)){
	i--;
      }
      else{
	bitHolder[i] = c;
      }
    }  
     
      for(int i = 0; i < nBits/4; i++){

	  valueHolder[valueHolderIndex] = bitsToNum(bitHolder[0+(i*4)],bitHolder[1+(i*4)],bitHolder[2+(i*4)],bitHolder[3+(i*4)]);
	  valueHolderIndex++;

	  // printf("%lld \n ", valueHolder[valueHolderIndex -1]);
      }      
      //valueHolder[valueHolderIndex] = bitsToNum(bitHolder[0],bitHolder[1], bitHolder[2], bitHolder[3]);
      //valueHolderIndex++;
	
     
    
    // printf("%d \n" , valueHolder[0]);
    //printf("%d \n" , valueHolder[1]);

     
      for(int i = 0; i < nBits/4; i++){
	if(i%2 == 0){
	  //printf("Value : %lld , Exp value:  %d \n", valueHolder[i], (nBits/4)-(i+2));
	  value += valueHolder[i]*power(16,(nBits/4)-(i+2));
	}
	else{
	  //	  printf("Value : %lld , Exp Value:  %d \n", valueHolder[i], (nBits/4)-i);
	  value += valueHolder[i]*power(16,(nBits/4)-i);
	}
      }
      

      /*
    for(int i = valueHolderIndex; i > 0; i = i--){

     
      value += valueHolder[i-1];
    }
      */
	

  
      return value;
}
