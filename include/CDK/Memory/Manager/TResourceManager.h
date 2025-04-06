#ifndef CDK_Memory_Manager_TResourceManager
#define CDK_Memory_Manager_TResourceManager

#include "CDK/CDK.h"
#include "CDK/Memory/IAllocator.h"

typedef struct { } TResourceManager;

TResourceManager *
Instantiate_TResourceManager(
  IAllocator *allocator,
  USize size
);

void
Dispose_TResourceManager(
  TResourceManager *manager
);

USize
TResourceManager_GetSize(
  TResourceManager *manager
);

void
TResourceManager_Reset(
  TResourceManager *manager
);

Boolean
TResourceManager_Next(
  TResourceManager *manager
);

Boolean
TResourceManager_Back(
  TResourceManager *manager
);

void *
TResourceManager_GetResource(
  TResourceManager *manager
);

void *
TResourceManager_GetResourceByPointer(
  TResourceManager *manager,
  void *pointer
);

Boolean
TResourceManager_Append(
  TResourceManager *manager
);

#endif
