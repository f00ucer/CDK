#include "CDK/Memory/Utility/AllocatorUtility.h"

#include <stdlib.h>

void *
AllocatorUtility_Allocate(
  IAllocator *allocator,
  USize size
)
{
  if (allocator) {
    return IAllocator_Allocate(allocator, size);
  } else {
    return malloc(size);
  }
}

void
AllocatorUtility_Deallocate(
  IAllocator *allocator,
  void *pointer
)
{
  if (allocator) {
    IAllocator_Deallocate(allocator, pointer);
  } else {
    free(pointer);
  }

  pointer = NULL;
}
