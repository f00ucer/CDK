CC = gcc
CFLAGS = -std=c99 -Wall -Werror -I./include

SRC = ./src/runner.c

SRC += ./src/CDK/Memory/Utility/AllocatorUtility.c

SRC += ./src/CDK/Memory/Entity/TResourceEntity.c
SRC += ./src/CDK/Memory/Manager/TResourceManager.c
SRC += ./src/CDK/Memory/IAllocator.c
SRC += ./src/CDK/Memory/TLinearAllocator.c
SRC += ./src/CDK/Memory/TStackAllocator.c
SRC += ./src/CDK/Memory/TPoolAllocator.c
SRC += ./src/CDK/Memory/TFreeListAllocator.c

SRC += ./src/CDK/Collection/TArray.c
SRC += ./src/CDK/Collection/TLinkedList.c
SRC += ./src/CDK/Collection/TArrayList.c
SRC += ./src/CDK/Collection/THashSet.c
SRC += ./src/CDK/Collection/THashMap.c
SRC += ./src/CDK/Collection/TQueue.c
SRC += ./src/CDK/Collection/TStack.c
SRC += ./src/CDK/Collection/TRingBuffer.c

OBJ = $(patsubst %.c,%.o,$(SRC))

debug: CFLAGS += -g
debug: all

release: CFLAGS += -O3
release: all

all: clean $(OBJ)
	mkdir ./bin
	$(CC) $(CFLAGS) -o ./bin/CDK $(OBJ)
	rm -f $(OBJ)

clean:
	rm -f $(OBJ)
	rm -rf ./bin

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@
