#ifndef CDK_Memory_TLinearAllocator
#define CDK_Memory_TLinearAllocator

#include "CDK/CDK.h"
#include "CDK/Memory/IAllocator.h"

typedef struct { } TLinearAllocator;

TLinearAllocator *
Instantiate_TLinearAllocator(
  IAllocator *allocator,
  USize size
);

void
Dispose_TLinearAllocator(
  TLinearAllocator *linearAllocator
);

void *
TLinearAllocator_Allocate(
  TLinearAllocator *linearAllocator,
  USize size
);

void
TLinearAllocator_Reset(
  TLinearAllocator *linearAllocator
);

#endif
