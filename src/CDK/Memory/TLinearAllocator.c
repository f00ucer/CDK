#include "CDK/Memory/TLinearAllocator.h"

#include "CDK/Memory/Manager/TResourceManager.h"
#include "CDK/Memory/Utility/AllocatorUtility.h"

struct _TLinearAllocator
{
  UInt implementation;

  IAllocator *allocator;

  TResourceManager *manager;
};

typedef struct _TLinearAllocator _TLinearAllocator;

TLinearAllocator *
Instantiate_TLinearAllocator(
  IAllocator *allocator,
  USize size
)
{
  _TLinearAllocator *_linearAllocator = AllocatorUtility_Allocate(allocator, sizeof(_TLinearAllocator));

  if (!_linearAllocator)
    goto exception;

  _linearAllocator->implementation = 1;

  _linearAllocator->allocator = allocator;

  _linearAllocator->manager = Instantiate_TResourceManager(_linearAllocator->allocator, size);

  if (!_linearAllocator->manager)
    goto exception;

  return (TLinearAllocator *) _linearAllocator;

exception:
  Dispose_TLinearAllocator((TLinearAllocator *) _linearAllocator);

  _linearAllocator = NULL;

  return NULL;
}

void
Dispose_TLinearAllocator(
  TLinearAllocator *linearAllocator
)
{
  _TLinearAllocator *_linearAllocator = (_TLinearAllocator *) linearAllocator;

  if (!_linearAllocator)
    return;

  IAllocator *allocator = _linearAllocator->allocator;

  _linearAllocator->implementation = 0;

  _linearAllocator->allocator = NULL;

  if (_linearAllocator->manager) {
    Dispose_TResourceManager(_linearAllocator->manager);

    _linearAllocator->manager = NULL;
  }

  AllocatorUtility_Deallocate(allocator, _linearAllocator);
  _linearAllocator = NULL;
}

void *
TLinearAllocator_Allocate(
  TLinearAllocator *linearAllocator,
  USize size
)
{
  return NULL;
}

void
TLinearAllocator_Reset(
  TLinearAllocator *linearAllocator
)
{

}
