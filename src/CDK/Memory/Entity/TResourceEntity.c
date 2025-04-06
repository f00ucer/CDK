#include "CDK/Memory/Entity/TResourceEntity.h"

#include "CDK/Memory/Utility/AllocatorUtility.h"

struct _TResourceEntity
{
  IAllocator *allocator;

  struct _TResourceEntity *prv;
  struct _TResourceEntity *nxt;

  USize size;

  void *resource;
};

typedef struct _TResourceEntity _TResourceEntity;

TResourceEntity *
Instantiate_TResourceEntity(
  IAllocator *allocator,
  USize size
)
{
  _TResourceEntity *_entity = AllocatorUtility_Allocate(allocator, sizeof(_TResourceEntity));

  if (!_entity)
    goto exception;

  _entity->allocator = allocator;

  _entity->prv = NULL;
  _entity->nxt = NULL;

  _entity->size = size;

  _entity->resource = AllocatorUtility_Allocate(allocator, size);

  if (!_entity->resource)
    goto exception;

  return (TResourceEntity *) _entity;

exception:
  Dispose_TResourceEntity((TResourceEntity *) _entity);

  _entity = NULL;

  return NULL;
}

void
Dispose_TResourceEntity(
  TResourceEntity *entity
)
{
  _TResourceEntity *_entity = (_TResourceEntity *) entity;

  if (!_entity)
    return;

  IAllocator *allocator = _entity->allocator;

  _entity->allocator = NULL;

  _entity->prv = NULL;
  _entity->nxt = NULL;

  _entity->size = 0;

  if (_entity->resource) {
    AllocatorUtility_Deallocate(allocator, _entity->resource);
    _entity->resource = NULL;
  }

  AllocatorUtility_Deallocate(allocator, _entity);
  _entity = NULL;
}

TResourceEntity *
TResourceEntity_GetPrv(
  TResourceEntity *entity
)
{
  return (TResourceEntity *) ((_TResourceEntity *) entity)->prv;
}

TResourceEntity *
TResourceEntity_GetNxt(
  TResourceEntity *entity
)
{
  return (TResourceEntity *) ((_TResourceEntity *) entity)->nxt;
}

void
TResourceEntity_SetPrv(
  TResourceEntity *entity,
  TResourceEntity *prv
)
{
  _TResourceEntity *_entity = (_TResourceEntity *) entity;

  _entity->prv = (_TResourceEntity *) prv;
}

void
TResourceEntity_SetNxt(
  TResourceEntity *entity,
  TResourceEntity *nxt
)
{
  _TResourceEntity *_entity = (_TResourceEntity *) entity;

  _entity->nxt = (_TResourceEntity *) nxt;
}

void *
TResourceEntity_GetResource(
  TResourceEntity *entity
)
{
  _TResourceEntity *_entity = (_TResourceEntity *) entity;

  return _entity->resource;
}

Boolean
TResourceEntity_Contains(
  TResourceEntity *entity,
  void *pointer
)
{
  _TResourceEntity *_entity = (_TResourceEntity *) entity;

  UPointer x = (UPointer) pointer;
  UPointer a = (UPointer) _entity->resource;
  UPointer b = a + _entity->size;

  return x >= a && x < b;
}
