// Mohsen AliMohammadi 96440296

#include <iostream>
using namespace std;
int nand(float * w, float * x, float t)
{
	float sum = (w[0] * x[0]) + (w[1] * x[1]);
	if (sum < t)
		return 1;
	return 0;
}
int main()
{
	float w[2] = { 1,1 }, x[4][2] = { {0,0}, {0,1}, {1,0}, {1,1} }, t = 1.5;
	for (int i = 0; i < 4; i++)
	{
		cout << x[i][0] << " " << x[i][1] << " " << nand(w, x[i], t) << "\n";
	}
	return 0;
}