#include <assert.h>
#include "maxi.h"

int main(){
  int c;
  c = max(5,7);
  assert(c == 7);

  c = max(0,2);
  assert(c == 2);

  c = max(0,-2);
  assert(c == 0);

  c = max(2,2);
  assert(c == 2);


}
