/* Author: Zach Muller
   NID: za303315 
   COP 3502 */
#include "Fibonacci.h"
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int getLength(unsigned int n);

/* PRECONDITION: p and q are pointing to arrays(HugeInts) 
to be added together

   POSTCONDITION: p and q have been added and put into a new array
   called sum

   NOTES: If a NULL pointer is passed to the function (p or q),
   simply return NULL. If and DMA function within this function,
   also return a NULL. 

   **CAUTION** Avoid memory leaks when doing so 

   RETURNS: A POINTER to a newly allocated HugeInteger struct, or NULL*/	
HugeInteger *hugeAdd(HugeInteger *p, HugeInteger *q) {

   //Create space for struct
   HugeInteger *sum = (HugeInteger *)malloc(sizeof(HugeInteger));

    //If p or q is NULL, return NULL
   if(p == NULL || q == NULL) {
      return NULL;
   }

   //If p is bigger 
   if(p->length > q->length) {
      
      //malloc space for size of struct * p's length
      sum->digits = (int *)malloc(sizeof(int) * (p->length + 1));
      sum->length = 0;

      //Create a buffer to hold array of smaller number with padded 0s
      int *buffer = (int *)malloc(sizeof(int) * p->length);
      int i;
      for(i = 0; i < q->length; i++) {
         buffer[i] = q->digits[i];
      }

      //Loop through smaller array and pad 0's until it's the same
      //length as the bigger array
      for(i = (q->length); i < (p->length); i++) {
         buffer[i] = 0;
      }

      //Loop through the two arrays and add them
      //Store them in sum->digits
      int j;
      int carry = 0;
      for(j = 0; j < p->length; j++) {

         sum->digits[j] = p->digits[j] + buffer[j] + carry;

         //If there's a carry
         if(sum->digits[j] > 9) {

            carry = sum->digits[j] / 10;
     
            sum->digits[j] %= 10;
         }

         else {
            carry = 0;
         }
      }
      
      if(carry == 1) {
         sum->digits[p->length] = carry;
         sum->length++;
      }

      //store length of sum
      sum->length += p->length;  
   }
   
   //If q is bigger 
   if(q->length > p->length) {

      //malloc space for size of struct * q's length
      sum->digits = (int *)malloc(sizeof(int) * (q->length + 1));
      sum->length = 0;

      //Create a buffer to hold array of smaller number with padded 0s
      int *buffer = (int *)malloc(sizeof(int) * q->length);
      int i;
      for(i = 0; i < p->length; i++) {
         buffer[i] = p->digits[i];
      }

      //Loop through smaller array and pad 0's until it's the same
      //length as the bigger array
      for(i = (p->length); i < (q->length); i++) {
         buffer[i] = 0;
      }

      //Loop through both arrays and add them
      //store their sum in sum->digits
      int j;
      int carry = 0;
      for(j = 0; j < q->length; j++) {

         sum->digits[j] = q->digits[j] + buffer[j] + carry;

         //If there's a carry
         if(sum->digits[j] > 9) {
            
            carry = sum->digits[j] / 10;
          
            sum->digits[j] %= 10;
         }

         else {
            carry = 0;
         }
      }

      if(carry == 1) {
         sum->digits[q->length] = carry;
         sum->length++;
      }

      //Store length of sum
      sum->length += q->length;
   }

   //If they're the same length
   if(p->length == q->length) {

      //malloc space for size of struct * p's length
      sum->digits = (int *)malloc(sizeof(int) * (p->length + 1));
      sum->length = 0;

      //Loop through the two arrays and add them
      //Store them in sum->digits
      int j;
      int carry = 0;
      for(j = 0; j < p->length; j++) {
         
         sum->digits[j] = p->digits[j] + q->digits[j] + carry;

         //If there's a carry
         if(sum->digits[j] > 9) {
            
            carry = sum->digits[j] / 10;
            
            sum->digits[j] %= 10;
         }

         else {
            carry = 0;
         }
      }

      if(carry == 1) {
         sum->digits[p->length] = 1;
         sum->length++;
      }

      //store length of sum
      sum->length += p->length;
   }


   //If malloc fails, return NULL
   if(sum == NULL) {
      return NULL;
   }

  	return sum;
}


/* PRECONDITION: p has a populated array 

   POSTCONDITION: reurns an empty array

   RETURNS: NULL */	
HugeInteger *hugeDestroyer(HugeInteger *p) {

	if(p == NULL) {
      return NULL;
   }
   
   free(p->digits);
   free(p);

   return p;
}


/* PRECONDITION: Object passed to function is a string

   NOTES: If empty string "" is passed in, treat it as a "0". 
   If any DMA functions within this function fail, or if str is NULL,
   return NULL
   **CAUTION** Be careful CJ! memory leaks!
   Assume: the string will only contain ASCII digits 0-9 and there will
   be no leading 0s in the string

   POSTCONDITION: string is parsed and put in struct

   RETURNS: A POINTER to a newly allocated HugeInteger struct,
   or NULL if the DMA fails, or if string is NULL */	
HugeInteger *parseString(char *str) {

   //Allocate memory for temp struct
   HugeInteger *parseString = (HugeInteger *)malloc(sizeof(HugeInteger));

   //The best defense is a good offense
      //Nothing in the string
   if(str == NULL) {
      return NULL;
   }

      //Malloc failed
   else if(parseString == NULL) {

      printf("ERROR: parseString failed to allocate memory.\n");
      return NULL;

   }

   //Length of string in question
   int stringLength;
   stringLength = strlen(str);

   parseString->length = stringLength;

   //Malloc space for digits size of string length.
   //If string length = 0, then return 1
   parseString->digits = (int *)malloc(sizeof(int) * (stringLength == 0 ? 1 : stringLength));

   int i, j = 0;
   //Go through whole string
   for(i = stringLength - 1; i >= 0; i--) {

      //token = strtok(str, int); 
      // ^^^ couldn't use this because string has no delimiters

      //Put the pointer to the int in the array
      parseString->digits[j++] = str[i] - '0';
   }

   return parseString;

}


/* PRECONDITION: unsigned int is passed to function

   NOTE: if DMA fails at any time in function, return NULL
   **BE CAREFUL CJ!** Memory leaks!

   POSTCONDITION: unsigned int is parsed and put in struct

   RETURNS: A POINTER to a newly allocated HugeInteger struct, or
   NULL if DMA fails at any point */	
HugeInteger *parseInt(unsigned int n) {

   //Allocate memory for local struct
	HugeInteger *parseInt = (HugeInteger *)malloc(sizeof(HugeInteger));
   
   int intLength;
   intLength = getLength(n);

   //Put it in struct
   parseInt -> length = intLength;
   
   //Allocate space for array of digits
   parseInt->digits = (int*)malloc(sizeof(int) * (intLength == 0 ? 1 : intLength));

   //Defense if malloc fails...
   if(parseInt == NULL) {
      printf("ERROR: parseInt failed to allocate memory.\n");
      return NULL;
   }

   //Pointer to each element in the unsigned int
   int *current = (int *)malloc(sizeof(int));
   //Assign it to struct element digits
   current = parseInt->digits;

   //If given a '0' put it in array inside struct
   //change length of array from 0 to 1
   if(n == 0) {
      *current = n;
      parseInt->length = 1;
   }

   //Get each digit of the integer and put it into array buffer
   while(n != 0) {

      //This is where decimal point is currently on the integer
      *current++ = n % 10;
      //n is whatever is to the right of the decimal
      n /= 10;
      //Move decimal point up re-entry to loop

   }

	return parseInt;
}


/* PRECONDITION: newly instantiated struct p passed to the function

   NOTE: The only reason that this function returns a POINTER
   insted of an UNSIGNED INT is so that we can return a NULL
   to signify failure in cases where 'p' cannot be represented
   by an unsigned int

   POSTCONDITION: Pointer returned

   RETURNS: A POINTER to a newly allocated unsigned integer, or
   NULL if value cannot be represented as an unsigned int
   (including the case where 'p' is NULL) */	
unsigned int *toUnsignedInt(HugeInteger *p) {

   //Allocate memory for unsigned int
	unsigned int *Uint = (unsigned int *)malloc(sizeof(unsigned int));
   
   //If passed HugeInteger is NULL, return NULL
   if(p == NULL) {
      return NULL;
   }

   //Put the backwards digit array back together in the right order
   //to be compared to UINT_MAX
   int i, k = 0;
   for(i = (p->length - 1); i >= 0; i--) {
      k = 10 * k + p->digits[i];
   }
   
   //If the number is greater than or equal to the max number that can be stored as an
   //unsigned int, add one so that it will be displayed as an
   //unsigned int
   if(k > UINT_MAX) {
      return NULL;
   }

   //If integer is too large to be displayed as an unsigned int
   //Display error and return NULL
   if(k <= UINT_MAX) {

      //Convert all digits in int array to unsigned ints
      int j;
      for(j = (p->length - 1); j >= 0; j--) {
         *Uint = 10 * (*Uint) + p->digits[j];
      }
   }

	return Uint;
}


/* PRECONDITION: n is the number of times we will run the Fib function

   NOTE: When computing F(n) for large n, it's important to 
   KEEP AS FEW NUMBERS IN MEMORY AS NECESSARY AT ANY GIVEN TIME
   Assume: n is not negative. If DMA functions fail with this function,
   return NULL
   **BE CAREFUL CJ!**

   POSTCONDITION: unsigned int is parsed and put in struct

   RETURNS: A POINTER to a newly allocated HugeInteger struct, or
   NULL if DMA fails at any point */	
HugeInteger *fib(int n) {

   HugeInteger *fibNum1 = (HugeInteger *)malloc(sizeof(HugeInteger));
   HugeInteger *fibNum2 = (HugeInteger *)malloc(sizeof(HugeInteger));
   HugeInteger *nFibNum = (HugeInteger *)malloc(sizeof(HugeInteger));
   fibNum1 = parseInt(0);
   fibNum2 = parseInt(1);

   //If malloc fails, return NULL
   if(fibNum1 == NULL || fibNum2 == NULL || nFibNum == NULL) {
      return NULL;
   }

   if(n == 0) {

      nFibNum = parseInt(n);
   }

   if(n == 1) {

      nFibNum = parseInt(n);
   }

   if(n > 1) {

      int i;
      for(i = 2; i <= n; i++) {

         nFibNum = hugeAdd(fibNum1, fibNum2);
         
         hugeDestroyer(fibNum1);
         fibNum1 = fibNum2;

         fibNum2 = nFibNum;

      }
   }  
   return nFibNum;
}

int getLength(unsigned int n) {
   
   //Get number of digits in int
   int intLength = 0;
   unsigned int i = n;

   if(n == 0) {
      intLength = 1;
   }
   while(i != 0) {
      i /= 10;
      intLength++;
   }

   return intLength;
}

/* PRECONDITION: The program is finished and it was tough

   POSTCONDITION: The professor will know how tough it was for me */	
double difficultyRating(void) {

	double difficulty;

   difficulty = 5.0;

	return difficulty;
}


/* PRECONDITION: I have worked long and hard on this chunk of software
   POSTCONDITION: The professor will know how long it took me */	
double hoursSpent(void) {

	double hourseOfLabor;

   hourseOfLabor = 42.0;

	return hourseOfLabor;
}