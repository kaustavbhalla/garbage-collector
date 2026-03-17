#include "virtualMachine.h"
#include <stdio.h>
#include <stdlib.h>

void garbageCollector(VirtualMachine *vm) {
  markAll(vm);
  sweep(vm);
}

int main() {
  printf("Simple Garbage collector");
  VirtualMachine *vm = createVM();
  garbageCollector(vm);
}
