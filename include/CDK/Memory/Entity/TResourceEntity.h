#ifndef CDK_Memory_Entity_TResourceEntity
#define CDK_Memory_Entity_TResourceEntity

#include "CDK/CDK.h"
#include "CDK/Memory/IAllocator.h"

typedef struct { } TResourceEntity;

TResourceEntity *
Instantiate_TResourceEntity(
  IAllocator *allocator,
  USize size
);

void
Dispose_TResourceEntity(
  TResourceEntity *entity
);

TResourceEntity *
TResourceEntity_GetPrv(
  TResourceEntity *entity
);

TResourceEntity *
TResourceEntity_GetNxt(
  TResourceEntity *entity
);

void
TResourceEntity_SetPrv(
  TResourceEntity *entity,
  TResourceEntity *prv
);

void
TResourceEntity_SetNxt(
  TResourceEntity *entity,
  TResourceEntity *nxt
);

void *
TResourceEntity_GetResource(
  TResourceEntity *entity
);

Boolean
TResourceEntity_Contains(
  TResourceEntity *entity,
  void *pointer
);

#endif
