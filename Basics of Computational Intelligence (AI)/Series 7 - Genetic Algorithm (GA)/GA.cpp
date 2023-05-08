// Mohsen AliMohammadi 96440296
// Fateme ZahraParsaei 95440193
// Shayan Rostamzadeh  95440176
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <time.h>
#define geneSize 50
#define fitVal 28
#define arr vector <int>
#define genArr vector <Gene>
#define period 100
using namespace std;
struct Gene
{
	arr chromosome{ 1, 2, 3, 4, 5, 6, 7, 8 };
	int fitnessValue = fitVal;
};
int findMax(const genArr & _a, int & _idx)
{
	int _mx = _a[0].fitnessValue;
	_idx = 0;
	for (int i = 1; i < _a.size(); i++)
	{
		if (_mx < _a[i].fitnessValue)
		{
			_mx = _a[i].fitnessValue;
			_idx = i;
		}
	}
	return _mx;
}
bool check(const arr & a, const int & index)
{
	for (int i = 0; i < a.size(); i++)
		if (i != index)
			if (a[i] == a[index] || abs(i - index) == abs(a[i] - a[index]))
				return false;
	return true;
}
void init(genArr & _a)
{
	for (int i = 0; i < geneSize; i++)
		shuffle(_a[i].chromosome.begin(), _a[i].chromosome.end(), default_random_engine(rand()));
}
void fitnessFunction(genArr & _a)
{
	for (int i = 0; i < geneSize; i++)
		for (int j = 0; j < _a[i].chromosome.size(); j++)
			if (check(_a[i].chromosome, j) == true)
				_a[i].fitnessValue--;
}
genArr selectionOperator(const genArr & _a)
{
	genArr _temp, _res;
	for (int i = 0; i < _a.size(); i++)
		for (int j = 0; j < _a[i].fitnessValue; j++)
			_temp.push_back(_a[i]);

	shuffle(_temp.begin(), _temp.end(), default_random_engine(rand()));

	for (int i = 0; i < _a.size(); i++)
		_res.push_back(_temp[i]);

	return _res;
}
genArr crossOver(const genArr & _a)
{
	genArr _res = _a;
	for (int i = 0; i < _res.size() - 1; i++)
	{
		_res[i].fitnessValue = fitVal;
		if (i % 2 == 0)
		{
			int randNum = rand() % 8;
			for (int j = 0; j < randNum; j++)
				swap(_res[i].chromosome[j], _res[i + 1].chromosome[j]);
		}
	}
	return _res;
}
void mutation(genArr & _a)
{
	int n = 0.04 * _a.size();
	for (int i = 0; i < n; i++)
	{
		int index = rand() % _a.size(),
			chromosomeIdx = rand() % _a[index].chromosome.size(),
			val = rand() % _a[index].chromosome.size();
		_a[index].chromosome[chromosomeIdx] = val + 1;
	}
}
genArr replacement(genArr & _pop, genArr & _child)
{
	genArr _res;
	int n = 0.04 * _pop.size(),
		m = _pop.size() - n;
	shuffle(_pop.begin(), _pop.end(), default_random_engine(rand()));
	for (int i = 0; i < m; i++)
	{
		_res.push_back(_pop[i]);
	}
	for (int i = 0; i < n;i++)
	{
		int index;
		findMax(_child, index);
		_res.push_back(_child[index]);
		_child[index].fitnessValue = 0;
	}
	return _res;
}
void output(const genArr & _a)
{
	for (int i = 0; i < geneSize; i++)
	{
		cout << "value of { ";
		for (int j = 0; j < _a[i].chromosome.size(); j++)
			cout << _a[i].chromosome[j] << " ";
		cout << "} is " << _a[i].fitnessValue << "\n\n";
	}
}
int main()
{
	srand(time(NULL));
	genArr population(geneSize);
	init(population);
	fitnessFunction(population);
	int cnt = 0;
	bool sw = true;
	while (sw)
	{
		cnt++;
		genArr newPopulation = selectionOperator(population);
		genArr children = crossOver(newPopulation);
		mutation(children);
		fitnessFunction(children);
		population = replacement(newPopulation, children);
		fitnessFunction(population);
		int index, mx = findMax(population, index);
		if (mx == fitVal)
		{
			sw = false;
			cout << "value of { ";
			for (int j = 0; j < population[index].chromosome.size(); j++)
				cout << population[index].chromosome[j] << " ";
			cout << "} is " << population[index].fitnessValue << "\n\n";
			cout << cnt << "\n";
		}
		if (cnt % period == 0)
		{
			cout << mx << "\t" << cnt << "\n";
		}
	}
	//output(population);
	return 0;
}