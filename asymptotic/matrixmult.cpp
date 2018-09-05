#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main()
{
	
	int n;

	cout << "Enter matrix size: " << endl;
	cin >> n;
	
	int **matrA = new int* [n];
	for (int i = 0; i < n; ++i)
		matrA[i] = new int[n];

	int **matrB = new int* [n];
	for (int i = 0; i < n; ++i)
		matrB[i] = new int[n];

	int **matrC = new int*[n];
	for (int i = 0; i < n; ++i)
		matrC[i] = new int[n];

	srand(time(0));

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			matrA[i][j] = (rand()%100);

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			matrB[i][j] = (rand() % 100);


	for (int l = 0; l < 5; ++l)
	{
		//algorithm
		high_resolution_clock::time_point start = high_resolution_clock::now();
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				matrC[i][j] = 0;
				for (int k = 0; k < n; ++k)
					matrC[i][j] += matrA[i][k] * matrB[k][j];
				//cout << matrC[i][j] << " ";
			}
			//cout << endl;
		}
		high_resolution_clock::time_point stop = high_resolution_clock::now();
		duration<double> sp_time = duration_cast<duration<double>>(stop - start);
		//cout << fixed << setprecision(8);
		cout << "time: " << sp_time.count() << " seconds" << endl;
	}
	//delete arrays

	for (int i = 0; i < n; ++i)
	{
		delete[] matrA[i];
		delete[] matrB[i];
		delete[] matrC[i];
	}

	delete[] matrA;
	delete[] matrB;
	delete[] matrC;
	
	//system("pause");
	
	return 0;
}
