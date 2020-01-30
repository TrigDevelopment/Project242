#include "program.h"

int main() {
  for (int i = 0; i < 20; ++i) {
    output(grow(3));
  }
  system("pause");
  return 0;
}