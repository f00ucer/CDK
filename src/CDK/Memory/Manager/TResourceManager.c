#include "CDK/Memory/Manager/TResourceManager.h"

#include "CDK/Memory/Entity/TResourceEntity.h"
#include "CDK/Memory/Utility/AllocatorUtility.h"

struct _TResourceManager
{
  IAllocator *allocator;

  TResourceEntity *head;
  TResourceEntity *tail;
  TResourceEntity *current;

  USize size;
};

typedef struct _TResourceManager _TResourceManager;

TResourceManager *
Instantiate_TResourceManager(
  IAllocator *allocator,
  USize size
)
{
  _TResourceManager *_manager = AllocatorUtility_Allocate(allocator, sizeof(_TResourceManager));

  if (!_manager)
    goto exception;

  _manager->allocator = allocator;

  _manager->head    = NULL;
  _manager->tail    = NULL;
  _manager->current = NULL;

  _manager->size = size;

  return (TResourceManager *) _manager;

exception:
  Dispose_TResourceManager((TResourceManager *) _manager);

  _manager = NULL;

  return NULL;
}

void
Dispose_TResourceManager(
  TResourceManager *manager
)
{
  _TResourceManager *_manager = (_TResourceManager *) manager;

  if (!_manager)
    return;

  IAllocator *allocator = _manager->allocator;

  _manager->allocator = NULL;

  while (_manager->head != NULL) {
    TResourceEntity *entity = _manager->head;

    if (_manager->head == _manager->tail) {
      _manager->head = NULL;
      _manager->tail = NULL;
    } else {
      TResourceEntity_SetPrv(
        TResourceEntity_GetNxt(
          _manager->head
        ),
        NULL
      );
      _manager->head = TResourceEntity_GetNxt(_manager->head);
    }

    Dispose_TResourceEntity(entity);
    entity = NULL;
  }

  _manager->current = NULL;

  _manager->size = 0;

  AllocatorUtility_Deallocate(allocator, _manager);
  _manager = NULL;
}

USize
TResourceManager_GetSize(
  TResourceManager *manager
)
{
  _TResourceManager *_manager = (_TResourceManager *) manager;

  return _manager->size;
}

void
TResourceManager_Reset(
  TResourceManager *manager
)
{
  _TResourceManager *_manager = (_TResourceManager *) manager;

  _manager->current = NULL;
}

Boolean
TResourceManager_Next(
  TResourceManager *manager
)
{
  _TResourceManager *_manager = (_TResourceManager *) manager;

  if (!_manager->head)
    return False;

  if (!_manager->current) {
    _manager->current = _manager->head;
    return True;
  }

  if (!TResourceEntity_GetNxt(_manager->current))
    return False;

  _manager->current = TResourceEntity_GetNxt(_manager->current);

  return True;
}

Boolean
TResourceManager_Back(
  TResourceManager *manager
)
{
  _TResourceManager *_manager = (_TResourceManager *) manager;

  if (!_manager->tail)
    return False;

  if (!_manager->current) {
    _manager->current = _manager->tail;
    return True;
  }

  if (!TResourceEntity_GetPrv(_manager->current))
    return False;

  _manager->current = TResourceEntity_GetPrv(_manager->current);

  return True;
}

void *
TResourceManager_GetResource(
  TResourceManager *manager
)
{
  _TResourceManager *_manager = (_TResourceManager *) manager;

  if (!_manager->current)
    return NULL;

  return TResourceEntity_GetResource(_manager->current);
}

void *
TResourceManager_GetResourceByPointer(
  TResourceManager *manager,
  void *pointer
)
{
  _TResourceManager *_manager = (_TResourceManager *) manager;

  TResourceEntity *entity = _manager->head;

  while (entity) {
    if (TResourceEntity_Contains(entity, pointer))
      return TResourceEntity_GetResource(entity);

    entity = TResourceEntity_GetNxt(entity);
  }

  return NULL;
}

Boolean
TResourceManager_Append(
  TResourceManager *manager
)
{
  _TResourceManager *_manager = (_TResourceManager *) manager;

  TResourceEntity *entity = Instantiate_TResourceEntity(_manager->allocator, _manager->size);
  if (!entity)
    return False;

  if (!_manager->tail) {
    _manager->tail = entity;
    _manager->head = _manager->tail;
  } else {
    TResourceEntity_SetNxt(_manager->tail, entity);
    TResourceEntity_SetPrv(entity, _manager->tail);
    _manager->tail = entity;
  }

  _manager->current = _manager->tail;

  return True;
}
