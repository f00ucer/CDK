#ifndef CDK_Memory_IAllocator
#define CDK_Memory_IAllocator

#include "CDK/CDK.h"

typedef struct { } IAllocator;

void *
IAllocator_Allocate(
  IAllocator *allocator,
  USize size
);

void
IAllocator_Deallocate(
  IAllocator *allocator,
  void *pointer
);

void
IAllocator_Reset(
  IAllocator *allocator
);

#endif
