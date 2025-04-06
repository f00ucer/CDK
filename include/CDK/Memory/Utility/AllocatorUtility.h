#ifndef CDK_Memory_Utility_AllocatorUtility
#define CDK_Memory_Utility_AllocatorUtility

#include "CDK/CDK.h"
#include "CDK/Memory/IAllocator.h"

void *
AllocatorUtility_Allocate(
  IAllocator *allocator,
  USize size
);

void
AllocatorUtility_Deallocate(
  IAllocator *allocator,
  void *pointer
);

#endif
