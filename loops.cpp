#include <bits/stdc++.h>
using namespace std::chrono;

const int MAX = 10000;
double A[MAX][MAX], x[MAX], y[MAX];

int main()
{
	auto beg = high_resolution_clock::now();
	
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			y[i] += A[i][j] * x[j];
	
	auto end = high_resolution_clock::now();
	
	auto duration1 = duration_cast<microseconds>(end - beg);
	
	beg = high_resolution_clock::now();
	
	for (int j = 0; j < MAX; j++)
		for (int i = 0; i < MAX; i++)
			y[i] += A[i][j] * x[j];
	
	end = high_resolution_clock::now();
	
	auto duration2 = duration_cast<microseconds>(end - beg);
	
	std::cout << "Duration 1: " << duration1.count() << "\nDuration 2: " << duration2.count() << '\n';
	
	// El primer bucle es más rápido debido a la localidad: se acceden a espacios de memoria consecutivos uno tras de otro, mientras
	// que en el segundo se acceden a espacios de memoria separados por el espacio que ocupan MAX doubles.
	
	return 0;
}
