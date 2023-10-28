#include "Target.h"

Target::Target(int x, int y, int radius) : Circle(x, y, radius) {  }

Target::Target(POINT center, int radius) : Circle(center, radius) {  }
