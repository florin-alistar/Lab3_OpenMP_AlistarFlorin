// OpenMPStart.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<omp.h>
#include <time.h>

const int n = 1500;
int a[n][n] =
{
	{1, 2, 3}, {1, 2, 3}, {1, 2, 3}
};

int b[n][n] =
{
	{1, 2, 3}, {1, 2, 3}, {1, 2, 3}
};

int c[n][n] = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };

int main()
{
	omp_set_num_threads(8);
	/*int i = 0;

// for asigneaza o iteratie pentru un thread anume
	// => doar un thread executa o iteratie

#pragma omp parallel for lastprivate(i)
	for (i = 0; i < 10; i++) {
		printf("thread %d -> i = %d\n", omp_get_thread_num(), i);
	}*/
	
	int i, j, k;

	clock_t start, end;
	double cpu_time_used;

	start = clock();

#pragma omp parallel for private(i, j)
	for (k = 0; k < n; k++)
	{
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}

	end = clock();

#pragma omp critical
	{
		for (i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				//std::cout << c[i][j] << " ";
			}
			//std::cout << std::endl;
		}
	}

	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

	std::cout << "Timp scurs: " << cpu_time_used << "\n";

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
