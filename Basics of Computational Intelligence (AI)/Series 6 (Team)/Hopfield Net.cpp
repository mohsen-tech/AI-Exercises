// Mohsen AliMohammadi 96440296
// Fateme ZahraParsaei 95440193
// Shayan Rostamzadeh  95440176
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <time.h>
#include <cmath>
#include <string>
#define arr2d vector<vector<float>>
#define theta 0
#define noiseLevel 10
#define numberOfTests 10
using namespace std;
int calConflict(const vector <float> & target, const vector <float> & y)
{
	int cnt = 0;
	if (target.size() == y.size())
		for (int i = 0; i < target.size(); i++)
			if (target[i] != y[i])
				cnt++;
	return cnt;
}
void binaryReshape(const vector <float> & src, arr2d & des)
{
	int i = 0, j = 0;
	for (int k = 0; k < src.size(); k++)
	{
		if (src[k] == -1)
			des[i][j++] = 0;
		else
			des[i][j++] = src[k];
		if ((k + 1) % 10 == 0)
		{
			i++;
			j = 0;
		}
	}
}
void print(const arr2d & temp)
{
	for (int i = 0; i < temp.size(); i++)
	{
		cout << "\t\t";
		for (int j = 0; j < temp[i].size(); j++)
			cout << temp[i][j] << " ";
		cout << "\n";
	}
}
void useHebbRule(const arr2d & sample, const arr2d & target, arr2d & w)
{
	// step 1.
	for (int s = 0; s < sample.size(); s++)
	{
		vector <float> x, y;
		// step 2.
		for (int i = 0; i < sample[s].size(); i++)
			x.push_back(sample[s][i]);

		// step 3.
		for (int j = 0; j < target[s].size(); j++)
			y.push_back(target[s][j]);

		// step 4.
		for (int i = 0; i < x.size(); i++)
			for (int j = 0; j < y.size(); j++)
				if (i == j)
					w[i][j] = 0;
				else
					w[i][j] = w[i][j] + x[i] * y[j];
	}
}
void hopfieldNet(const arr2d & sample, const arr2d & target, arr2d & w)
{
	// step 0.
	useHebbRule(sample, target, w);

	for (int n = 0; n < numberOfTests; n++)
	{
		arr2d damagedSamples = sample;

		// create Damaged Samples
		for (int s = 0; s < damagedSamples.size(); s++)
		{
			vector <bool> randomIndex(damagedSamples[s].size(), false);
			for (int i = 0; i < noiseLevel; i++)
			{
				int j;
				while (true)
				{
					j = rand() % damagedSamples[s].size();
					if (randomIndex[j] == false)
					{
						randomIndex[j] = true;
						break;
					}
				}
				if (damagedSamples[s][j] == -1)
					damagedSamples[s][j] = 1;
				else
					damagedSamples[s][j] = -1;
			}
		}

		// step 1.
		for (int s = 0; s < damagedSamples.size(); s++)
		{
			vector <float> y;
			// step 2.
			for (int i = 0; i < damagedSamples[s].size(); i++)
				y.push_back(damagedSamples[s][i]); // y[i] = x[i];

			bool sw = true;
			while (sw)
			{
				int cnt = 0;
				vector <float> y_in(y.size(), 0);
				vector <bool> randomIndex(y.size(), false);

				// step 3.			
				for (int k = 0; k < y.size(); k++)
				{
					int i;
					while (true)
					{
						i = rand() % y.size();
						if (randomIndex[i] == false)
						{
							randomIndex[i] = true;
							break;
						}
					}

					// step 4.
					float sum = 0;
					for (int j = 0; j < y.size(); j++)
						sum += y[j] * w[j][i];
					y_in[i] = y[i] + sum; // y[i] = x[i];

					// step 5, 6.
					if (y_in[i] > theta)
					{
						if (y[i] != 1)
							cnt++;
						y[i] = 1;
					}
					else if (y_in[i] == theta)
					{
						y[i] = y[i];
					}
					else if (y_in[i] < theta)
					{
						if (y[i] != -1)
							cnt++;
						y[i] = -1;
					}
				}
				// step 7.
				if (cnt == 0)
					sw = false;
			}
			arr2d sample10x10(10, vector <float>(10));
			arr2d Y10x10(10, vector <float>(10));

			binaryReshape(damagedSamples[s], sample10x10);
			binaryReshape(y, Y10x10);

			int targetConflictWithY = calConflict(target[s], y);

			cout << "Test " << n + 1 << ":\n";
			cout << "\t" << "Sample " << s + 1 << ":\n\n";
			cout << "\t\t" << "Data Of Damaged Sample:\n";
			print(sample10x10);
			cout << "\n\t\t" << "Data Of Y:\n";
			print(Y10x10);
			cout << "\n\t" << "Number Of Target Conflict With Y = " << targetConflictWithY << "\n";
			cout << "-----------------------------------------------------\n";
		}
	}
}
int main()
{
	arr2d sample
	{
		{ -1 , -1 , -1 , -1 , +1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , +1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , +1 , +1 , +1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , +1 , -1 , -1 , +1 , -1 , -1 , -1 , -1 , -1 , +1 , +1 , -1 , -1 , +1 , +1 , -1 , -1 , -1 , -1 , +1 , -1 , -1 , -1 , -1 , +1 , -1 , -1 , -1 , +1 , +1 , +1 , +1 , +1 , +1 , +1 , +1 , -1 , -1 , +1 , +1 , +1 , +1 , +1 , +1 , +1 , +1 , -1 , +1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , +1 , +1 , +1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , +1 , +1 },
		{ +1 , +1 , +1 , +1 , +1 , +1 , -1 , -1 , -1 , -1 , +1 , +1 , +1 , +1 , +1 , +1 , +1 , -1 , -1 , -1 , +1 , +1 , -1 , -1 , -1 , +1 , +1 , -1 , -1 , -1 , +1 , +1 , +1 , +1 , +1 , +1 , +1 , -1 , -1 , -1 , +1 , +1 , +1 , +1 , +1 , +1 , +1 , -1 , -1 , -1 , +1 , +1 , -1 , -1 , -1 , +1 , +1 , +1 , -1 , -1 , +1 , +1 , -1 , -1 , -1 , -1 , +1 , +1 , -1 , -1 , +1 , +1 , -1 , -1 , -1 , +1 , +1 , +1 , -1 , -1 , +1 , +1 , +1 , +1 , +1 , +1 , +1 , -1 , -1 , -1 , +1 , +1 , +1 , +1 , +1 , +1 , -1 , -1 , -1 , -1 },
		{ -1 , +1 , +1 , +1 , +1 , +1 , +1 , +1 , +1 , -1 , +1 , +1 , +1 , +1 , +1 , +1 , +1 , +1 , +1 , +1 , +1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , +1 , +1 , +1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , +1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , +1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , +1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , +1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , +1 , +1 , +1 , +1 , +1 , +1 , +1 , +1 , +1 , +1 , +1 , +1 , -1 , +1 , +1 , +1 , +1 , +1 , +1 , +1 , +1 , -1 },
		{ +1 , +1 , +1 , +1 , +1 , +1 , +1 , -1 , -1 , -1 , +1 , +1 , +1 , +1 , +1 , +1 , +1 , +1 , -1 , -1 , +1 , +1 , -1 , -1 , -1 , -1 , +1 , +1 , +1 , -1 , +1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , +1 , +1 , +1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , +1 , +1 , +1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , +1 , +1 , +1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , +1 , +1 , +1 , +1 , -1 , -1 , -1 , -1 , +1 , +1 , +1 , -1 , +1 , +1 , +1 , +1 , +1 , +1 , +1 , +1 , -1 , -1 , +1 , +1 , +1 , +1 , +1 , +1 , +1 , -1 , -1 , -1 }
	};
	arr2d target = sample;
	arr2d w(sample[0].size(), vector <float>(target[0].size(), 0));

	srand(time(NULL));
	hopfieldNet(sample, target, w);

	system("pause>A");
	return 0;
}