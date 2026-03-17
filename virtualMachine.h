#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#define MAX_STACK_SIZE 256

typedef enum { OBJ_INT, OBJ_PAIR } ObjectType;

typedef struct stackObject {
  struct stackObject *next;
  unsigned char marked;
  ObjectType objType;

  union {
    int intVal;

    struct {
      struct stackObject *head;
      struct stackObject *tail;
    };
  };
} Object;

// Let's start by building a Virtual Machine to model out GC

typedef struct {
  Object *firstObject;
  Object *stack[MAX_STACK_SIZE];
  int currentStackSize;
} VirtualMachine;

VirtualMachine *createVM();
void push(VirtualMachine *vm, Object *value);
Object *pop(VirtualMachine *vm);
Object *createObject(VirtualMachine *vm, ObjectType type);
void pushInt(VirtualMachine *vm, int intValue);
Object *pushPair(VirtualMachine *vm);
void mark(Object *object);
void markAll(VirtualMachine *vm);
void sweep(VirtualMachine *vm);
#endif
