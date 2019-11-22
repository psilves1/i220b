#include "fn-trace.h"
#include "x86-64_lde.h"

#include "memalloc.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum {
  CALL_OP = 0xE8,
  RET_FAR_OP = 0xCB,
  RET_FAR_WITH_POP_OP = 0xCA,
  RET_NEAR_OP = 0xC3,
  RET_NEAR_WITH_POP_OP = 0xC2
};

static inline bool is_call(unsigned op) { return op == CALL_OP; }
static inline bool is_ret(unsigned op) {
  return
    op == RET_NEAR_OP || op == RET_NEAR_WITH_POP_OP ||
    op == RET_FAR_OP || op == RET_FAR_WITH_POP_OP;
}


int compare(const void *a, const void *b){

  FnInfo **infoA = (FnInfo **) a;
  FnInfo **infoB = (FnInfo **) b;

  //  printf("Gets to the compare statement \n");
  
  return (*infoA)->address-(*infoB)->address;
}

const FnsData* fnTrace(void* addr, FnsData *fnsdata){ //try making it void

  int funcIndex = fnsdata->nIndex; //next index
  fnsdata->nIndex += 1;
  
  if(fnsdata->len <= funcIndex){
    if(fnsdata->len == 0){
      fnsdata->len = 1;
      //      printf("Set fnsdata->len = 2 \n ");
    }
    else{
      fnsdata->len *= 2;
      //printf("Doubled the size of fnsdata->len \n");
    }
    //    printf("Size of fnsdata->len: %d \n", fnsdata->len);
    //printf("Size of fnsdata->nIndex: %d \n", fnsdata->nIndex);
    fnsdata->arr = reallocChk(fnsdata->arr, fnsdata->len*sizeof(FnInfo *));
  }
  
  fnsdata->arr[funcIndex] = mallocChk(sizeof(FnInfo));
  fnsdata->arr[funcIndex]->nInCalls = 1;
  fnsdata->arr[funcIndex]->nOutCalls = 0;
  fnsdata->arr[funcIndex]->length = 0; 
  
  unsigned char *ptr = addr;

  fnsdata->arr[funcIndex]->address = ptr;
  
  //  printf("get_op_length value: %d \n", get_op_length(ptr));
  
  //  int opLength = get_op_length(ptr);

  bool wasFound = false;
  
  while(!is_ret(*ptr)){

    int opLength = get_op_length(ptr);
        
    if(is_call(*ptr)){

      //printf("Got into the is_call statement \n");
      
      fnsdata->arr[funcIndex]->nOutCalls += 1;
      
      int *offset =  (int *) (ptr + 1); //gets the offset for call
      
      //printf("Size of Offset: %ls \n" , offset);
      
      void* other_address = ptr + *offset + opLength; //could be where things are going wrong 

      //      bool wasFound = false; //bool var for if new func was already in our array 
    
      for(int i = 0; i < fnsdata->nIndex; i++){

	//printf("Got to the for loop \n");
	
	if(fnsdata->arr[i]->address == other_address){

	  //printf("inside of if-statement \n");
	  
	  fnsdata->arr[i]->nInCalls++;
	  wasFound = true; //see if you can change it to 1
	  break;
	}
      }
      if(!wasFound){ //might have an issue here
	//printf("Got to recurssive call \n");
	//printf("sizeof fnsdata->nIndex: %d \n", fnsdata->nIndex);
	fnTrace(other_address, fnsdata);
	//printf("sizeof fnsdata->nIndex: %d \n", fnsdata->nIndex);
      }    
    }

    // printf("Got to past the while loop \n");

    fnsdata->arr[funcIndex]->length += opLength;

    //    printf("opLength = %d \n", opLength);
    
    ptr += opLength; //goes to the next instruction
    
  }

  fnsdata->arr[funcIndex]->length += get_op_length(ptr);

  //printf("returned the data \n");
  
  return fnsdata;
}

/** Return pointer to opaque data structure containing collection of
 *  FnInfo's for functions which are callable directly or indirectly
 *  from the function whose address is rootFn.
 */
const FnsData *
new_fns_data(void *rootFn)
{
  //verify assumption used when decoding call address
  assert(sizeof(int) == 4);

  //@TODO
  FnsData *tracker = mallocChk(sizeof(FnsData));
  tracker->arr = NULL;
  tracker->len = 0;
  tracker->nIndex = 0;

  fnTrace(rootFn, tracker);

  //add q-sort here

  qsort(tracker->arr, tracker->nIndex, sizeof(FnInfo *), compare);
  
  
  return tracker;
}

/** Free all resources occupied by fnsData. fnsData must have been
 *  returned by new_fns_data().  It is not ok to use to fnsData after
 *  this call.
 */
void
free_fns_data(FnsData *fnsData)
{
  //@TODO
  for(int i = 0; i < fnsData->nIndex; i++){
    free(fnsData->arr[i]);
  }
  free(fnsData->arr);
  free(fnsData);  
}

/** Iterate over all FnInfo's in fnsData.  Make initial call with NULL
 *  lastFnInfo.  Keep calling with return value as lastFnInfo, until
 *  next_fn_info() returns NULL.  Values must be returned sorted in
 *  increasing order by fnInfoP->address.
 *
 *  Sample iteration:
 *
 *  for (FnInfo *fnInfoP = next_fn_info(fnsData, NULL); fnInfoP != NULL;
 *       fnInfoP = next_fn_info(fnsData, fnInfoP)) {
 *    //body of iteration
 *  }
 *
 */
const FnInfo *
next_fn_info(const FnsData *fnsData, const FnInfo *lastFnInfo)
{
  //@TODO

  if(lastFnInfo == NULL){
    return fnsData->arr[0];
  }

  int i;

  for(i = 0; lastFnInfo->address != fnsData->arr[i]->address; i++){} //finding the proper i value 
  
  return fnsData->arr[i+1];
}
