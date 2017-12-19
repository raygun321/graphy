#include <Utility.h>
#include <cmath>

int Utility::randomInt(int min, int max) {
   return (min + (rand() % (int)(max - min + 1)));
}
