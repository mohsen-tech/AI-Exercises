// Mohsen AliMohammadi 96440296
	
#include <iostream>
using namespace std;
void nand(float * x, float y, float * w)
{
	for (int j = 0; j < 2; j++)
		w[j] += (x[j] * y);
}
int main()
{
	float w[2] = { 0,0 }, x[4][2] = { { -1,-1 },{ -1,1 },{ 1,-1 },{ 1,1 } }, y[4] = { 1,1,1,-1 }, b = 0;
	for (int i = 0; i < 4; i++)
	{
		nand(x[i], y[i], w);
		b += y[i];
	}
	cout << w[0] << " " << w[1] << " " << b << endl;
	return 0;
}