// Mohsen AliMohammadi 96440296
// Fateme ZahraParsaei 95440193
// Shayan Rostamzadeh  95440176
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <time.h>
#include <cmath>
#define arr2d vector<vector<float>>
#define hiddenLayerSels 10
using namespace std;
float createRandomVal()
{
	float value = rand() % 11;
	value -= 5;
	return value / 10;
}
float findMax(const arr2d & a)
{
	float mx = a[1][1];
	for (int i = 0; i < a.size(); i++)
		for (int j = 0; j < a[i].size(); j++)
			if (mx < a[i][j])
				mx = a[i][j];
	return mx;
}
float findMin(const arr2d & a)
{
	float mn = a[1][1];
	for (int i = 0; i < a.size(); i++)
		for (int j = 0; j < a[i].size(); j++)
			if (mn > a[i][j])
				mn = a[i][j];
	return mn;
}
float sigmoid(const float & a)
{
	return (1 - exp(-1 * a)) / (1 + exp(-1 * a));
}
float derivativeSigmoid(const float & a)
{
	return 0.5 * (1 + sigmoid(a)) * (1 - sigmoid(a));
}
int main()
{
	arr2d sample
	{
		{ -1 , -1 , +1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , +1 , -1 , -1 , -1 , -1 , -1 , +1 , -1 , +1 , -1 , -1 , -1 , -1 , +1 , -1 , +1 , -1 , -1 , -1 , +1 , +1 , +1 , +1 , +1 , -1 , -1 , +1 , -1 , -1 , -1 , +1 , -1 , +1 , +1 , +1 , -1 , +1 , +1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 } ,
		{ +1 , +1 , +1 , +1 , +1 , -1 , -1 , -1 , +1 , -1 , -1 , -1 , +1 , -1 , -1 , +1 , -1 , -1 , -1 , +1 , -1 , -1 , +1 , +1 , +1 , +1 , -1 , -1 , -1 , +1 , -1 , -1 , -1 , +1 , -1 , -1 , +1 , -1 , -1 , -1 , +1 , -1 , -1 , +1 , -1 , -1 , -1 , +1 , -1 , +1 , +1 , +1 , +1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 } ,
		{ -1 , -1 , +1 , +1 , +1 , +1 , -1 , -1 , +1 , -1 , -1 , -1 , +1 , -1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , +1 , -1 , -1 , -1 , +1 , -1 , -1 , -1 , +1 , +1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 } ,
		{ +1 , +1 , +1 , +1 , -1 , -1 , -1 , -1 , +1 , -1 , -1 , +1 , -1 , -1 , -1 , +1 , -1 , -1 , -1 , +1 , -1 , -1 , +1 , -1 , -1 , -1 , +1 , -1 , -1 , +1 , -1 , -1 , -1 , +1 , -1 , -1 , +1 , -1 , -1 , -1 , +1 , -1 , -1 , +1 , -1 , -1 , +1 , -1 , -1 , +1 , +1 , +1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 } ,
		{ +1 , +1 , +1 , +1 , +1 , +1 , -1 , -1 , +1 , -1 , -1 , -1 , +1 , -1 , -1 , +1 , -1 , +1 , -1 , -1 , -1 , -1 , +1 , +1 , +1 , -1 , -1 , -1 , -1 , +1 , -1 , +1 , -1 , -1 , -1 , -1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , +1 , -1 , -1 , -1 , +1 , -1 , +1 , +1 , +1 , +1 , +1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 } ,
		{ +1 , +1 , +1 , +1 , +1 , +1 , -1 , -1 , +1 , -1 , -1 , -1 , +1 , -1 , -1 , +1 , -1 , +1 , -1 , -1 , -1 , -1 , +1 , +1 , +1 , -1 , -1 , -1 , -1 , +1 , -1 , +1 , -1 , -1 , -1 , -1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , +1 , -1 , -1 , -1 , -1 , -1 , +1 , +1 , +1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 } ,
		{ -1 , -1 , +1 , +1 , +1 , +1 , -1 , -1 , +1 , -1 , -1 , -1 , +1 , -1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , +1 , -1 , -1 , -1 , +1 , +1 , +1 , +1 , -1 , -1 , -1 , -1 , +1 , -1 , -1 , +1 , -1 , -1 , -1 , +1 , -1 , -1 , -1 , +1 , +1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 } ,
		{ +1 , +1 , +1 , -1 , +1 , +1 , +1 , -1 , +1 , -1 , -1 , -1 , +1 , -1 , -1 , +1 , -1 , -1 , -1 , +1 , -1 , -1 , +1 , +1 , +1 , +1 , +1 , -1 , -1 , +1 , -1 , -1 , -1 , +1 , -1 , -1 , +1 , -1 , -1 , -1 , +1 , -1 , -1 , +1 , -1 , -1 , -1 , +1 , -1 , +1 , +1 , +1 , -1 , +1 , +1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 } ,
		{ -1 , +1 , +1 , +1 , +1 , +1 , -1 , -1 , -1 , -1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , +1 , -1 , -1 , -1 , -1 , +1 , +1 , +1 , +1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 } ,
		{ -1 , -1 , +1 , +1 , +1 , +1 , -1 , -1 , -1 , -1 , -1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , +1 , -1 , -1 , +1 , -1 , -1 , -1 , +1 , -1 , -1 , +1 , -1 , -1 , -1 , +1 , -1 , -1 , -1 , +1 , +1 , +1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 }
	};
	arr2d target = sample;

	srand(time(NULL));
	arr2d w(hiddenLayerSels + 1, vector <float>(target[0].size()));
	for (int i = 0; i < w.size(); i++)
		for (int j = 0; j < w[i].size(); j++)
			w[i][j] = createRandomVal();

	arr2d v(sample[0].size() + 1, vector <float>(hiddenLayerSels));
	for (int i = 0; i < v.size(); i++)
		for (int j = 0; j < v[i].size(); j++)
			v[i][j] = createRandomVal();

	float alpha = 0.05, epsilon = 0.01;
	int cnt = 0;
	bool sw = true;

	// step 1.
	while (sw)
	{
		// step 2.
		for (int s = 0; s < sample.size(); s++)
		{
			vector <float> z_in, z;
			vector <float> y_in, y;
			vector <float> delta_k, delta_in, delta_j;
			arr2d delta_w(hiddenLayerSels + 1, vector <float>(target[0].size(), 0));
			arr2d delta_v(sample[0].size() + 1, vector <float>(hiddenLayerSels, 0));

			// step 3.
			vector <float> x;
			for (int i = 0; i < sample[s].size(); i++)
				x.push_back(sample[s][i]);

			vector <float> t;
			for (int i = 0; i < target[s].size(); i++)
				t.push_back(target[s][i]);

			// step 4.
			for (int j = 0; j < hiddenLayerSels; j++)
			{
				float sum = 0;
				for (int i = 0; i < x.size(); i++)
					sum += x[i] * v[i + 1][j];

				z_in.push_back(v[0][j] + sum);
				z.push_back(sigmoid(z_in[j]));
			}

			// step 5.
			for (int k = 0; k < t.size(); k++)
			{
				float sum = 0;
				for (int j = 0; j < hiddenLayerSels; j++)
					sum += z[j] * w[j + 1][k];

				y_in.push_back(w[0][k] + sum);
				y.push_back(sigmoid(y_in[k]));
			}

			// step 6.
			for (int k = 0; k < t.size(); k++)
			{
				delta_k.push_back((t[k] - y[k]) * derivativeSigmoid(y_in[k]));
				for (int j = 0; j < hiddenLayerSels; j++)
					delta_w[j + 1][k] = alpha * delta_k[k] * z[j];
				delta_w[0][k] = alpha * delta_k[k];
			}

			// step 7.
			for (int j = 0; j < hiddenLayerSels; j++)
			{
				float sum = 0;
				for (int k = 0; k < t.size(); k++)
				{
					sum += delta_k[k] * w[j + 1][k];
				}
				delta_in.push_back(sum);
				delta_j.push_back(delta_in[j] * derivativeSigmoid(z_in[j]));
				for (int i = 0; i < x.size(); i++)
				{
					delta_v[i + 1][j] = alpha * delta_j[j] * x[i];
				}
				delta_v[0][j] = alpha * delta_j[j];
			}

			// step 8.
			for (int k = 0; k < t.size(); k++)
				for (int j = 0; j < hiddenLayerSels + 1; j++)
					w[j][k] = w[j][k] + delta_w[j][k];

			for (int j = 0; j < hiddenLayerSels; j++)
				for (int i = 0; i < x.size() + 1; i++)
					v[i][j] = v[i][j] + delta_v[i][j];

			// step 9.
			float max_delta_w = findMax(delta_w);
			float min_delta_w = findMin(delta_w);
			float max_delta_v = findMax(delta_v);
			float min_delta_v = findMin(delta_v);

			if (epsilon < max(max_delta_w, -1 * min_delta_w) || epsilon < max(max_delta_v, -1 * min_delta_v))
				sw = true;
			else
				sw = false;
		}
		cnt++;

		//test use ----------------------------------------------------------------------------------
		/* */
		arr2d output;
		cout << "epoch " << cnt << ": \n";
		for (int s = 0; s < sample.size(); s++)
		{
			vector <float> z_in, z;
			vector <float> y_in, y;
			// step 2.
			vector <float> x;
			for (int i = 0; i < sample[s].size(); i++)
				x.push_back(sample[s][i]);
			vector <float> t;
			for (int i = 0; i < target[s].size(); i++)
				t.push_back(target[s][i]);
			// step 3.
			for (int j = 0; j < hiddenLayerSels; j++)
			{
				float sum = 0;
				for (int i = 0; i < x.size(); i++)
					sum += x[i] * v[i + 1][j];
				z_in.push_back(v[0][j] + sum);
				z.push_back(sigmoid(z_in[j]));
			}
			// step 4.
			for (int k = 0; k < t.size(); k++)
			{
				float sum = 0;
				for (int j = 0; j < hiddenLayerSels; j++)
					sum += z[j] * w[j + 1][k];
				y_in.push_back(w[0][k] + sum);
				y.push_back(sigmoid(y_in[k]));
			}
			float sum = 0;
			for (int k = 0; k < t.size(); k++)
				sum += abs(t[k] - y[k]);
			cout << sum << " ";

			//
			if (sw == false)
				output.push_back(y);
			//
		}
		cout << "\n------------------------------------\n\n";
		if (sw == false)
		{
			for (int i = 0; i < output.size(); i++)
			{
				for (int j = 0; j < output[i].size(); j++)
					cout << output[i][j] << " ";
				cout << "\n";
			}
		}
		/* */
		//-------------------------------------------------------------------------------------------
	}
	cout << "\n\nNumber of epochs: " << cnt << "\n";

	// section use
	// step 1.
	/*
	for (int s = 0; s < sample.size(); s++)
	{
		vector <float> z_in, z;
		vector <float> y_in, y;

		// step 2.
		vector <float> x;
		for (int i = 0; i < sample[s].size(); i++)
			x.push_back(sample[s][i]);

		vector <float> t;
		for (int i = 0; i < target[s].size(); i++)
			t.push_back(target[s][i]);

		// step 3.
		for (int j = 0; j < hiddenLayerSels; j++)
		{
			float sum = 0;
			for (int i = 0; i < x.size(); i++)
				sum += x[i] * v[i + 1][j];

			z_in.push_back(v[0][j] + sum);
			z.push_back(sigmoid(z_in[j]));
		}

		// step 4.
		for (int k = 0; k < t.size(); k++)
		{
			float sum = 0;
			for (int j = 0; j < hiddenLayerSels; j++)
				sum += z[j] * w[j + 1][k];

			y_in.push_back(w[0][k] + sum);
			y.push_back(sigmoid(y_in[k]));
		}

		for (int i = 0; i < y.size(); i++)
			cout << y[i] << " ";
		cout << "\n";
	}
	*/
	system("pause>A");
	return 0;
}