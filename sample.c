#include <stdio.h>
void main() {
	int x, y, z, k;
	x = 10;
	y = -x;
	z = x++;
	k = ++x;
    printf("%d",x,y,z,k);
}