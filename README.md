# FixedPoint
A fixed point c++ library

Designed for use with the TI84 calculator
  * can be used with other platforms without issue

Usage
 
 - Import header file
 - Typedef the layout you want for ease of use
   - first template parameter should be the total number of bits used to store the value
   - second template parameter should be the number of bits (out of the total) used to store the point
   - (optional) third parameter should be the expand type (ideally at least twice as large as the number of bits)
   - (optional) fourth parameter should be the integer type used for Integer <-> Fixed -> Fixed operations
 - Should generally work like a floating point value operation-wise
   - as of version 1.0 every normal operation is covered (report any operations not included that should be)

```
// prints 'Value: 0.953125'

#include "fixed.h"
#include <stdio.h>

typedef GenericFixedPoint<24, 6> fixed;
 
int main() {
    fixed x = 3.141592f;
    x *= 2;
    printf("Value: %f\n", (float)(6 / x));
    return 0;
}
```

TI84 Calculator Specific Instructions
 - meant for use with 3d game engine rendering (for performance boost compared to using floats)
 - recommeneded template is <24, 6, long, short> to give reasonable percision and to match register size
   - though of course try out different layouts to perfectly match your application
