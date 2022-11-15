#include "queue.h"

#include <unistd.h>
#include <stddef.h> 
#include <time.h>

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

  // IF WE REACHED THE END QUEUE MANAGED TO PUSH AN ELEMENT INSTEAD OF HANGING INDEFINETLY 
  queue_t *q = queue_new(0); // ZERO CAPACITY 
  if (q == NULL) {
    return 1;
  }
  
  queue_push(q, (void *)1);
  
  // expect to pop a 1
  void *r;
  queue_pop(q, &r);
  printf("r is : %td\n", (ptrdiff_t)r);
  if ((ptrdiff_t)r != 1) {
    // if not, then we failed
    return 1;
  }

  queue_delete(&q);
  return 1;
}
