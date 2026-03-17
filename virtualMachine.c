#include "virtualMachine.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 256

VirtualMachine *createVM() {
  VirtualMachine *vm = malloc(sizeof(VirtualMachine));
  vm->currentStackSize = 0;
  vm->firstObject = NULL;
  return vm;
}

void push(VirtualMachine *vm, Object *value) {
  if (vm->currentStackSize >= MAX_STACK_SIZE) {
    printf("Stack Overflow");
    exit(1);
  }
  vm->stack[vm->currentStackSize++] = value;
}

Object *pop(VirtualMachine *vm) {
  if (vm->currentStackSize <= 0) {
    printf("Stack underflow");
    exit(1);
  }

  return vm->stack[--vm->currentStackSize];
}

Object *createObject(VirtualMachine *vm, ObjectType type) {
  Object *object = malloc(sizeof(Object));
  object->objType = type;
  object->marked = 0;

  object->next = vm->firstObject;
  vm->firstObject = object;
  return object;
}

void pushInt(VirtualMachine *vm, int intValue) {
  Object *object = createObject(vm, OBJ_INT);
  object->intVal = intValue;
  push(vm, object);
}

Object *pushPair(VirtualMachine *vm) {
  Object *object = createObject(vm, OBJ_PAIR);
  object->tail = pop(vm);
  object->head = pop(vm);

  push(vm, object);
  return object;
}

// Marking functions

void mark(Object *object) {
  if (object->marked)
    return;

  object->marked = 1;

  if (object->objType == OBJ_PAIR) {
    mark(object->head);
    mark(object->tail);
  }
}

void markAll(VirtualMachine *vm) {
  for (int i = 0; i < vm->currentStackSize; i++) {
    mark(vm->stack[i]);
  }
}

// Sweep Algo

void sweep(VirtualMachine *vm) {
  Object **object = &vm->firstObject;

  while (*object != NULL) {
    if (!(*object)->marked) {
      Object *unreached = *object;
      *object = unreached->next;
      free(unreached);
    } else {
      (*object)->marked = 0;
      object = &(*object)->next;
    }
  }
}
