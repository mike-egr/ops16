
#include<string>
#include<fstream>
#include<sstream>
#include<exception>
#include<iostream>

#include<cstdlib>

#include"./MatrixFormatException.h"
#include"bab.h"

#include <random>
#include <chrono>

int* assignement(int n ,int** kosten);
int** loadMatrix(std::string path,size_t * n);

int** randomMatrix(size_t n, int minval, int maxval);


int main(int argc, char** argv)
{

	size_t n=7;
	
	if(argc == 2)
		n= atoi(argv[1]);


	//	int** a = loadMatrix("test.txt",&n);
	int ** a = randomMatrix(n,1,9);
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	 
	bab b = bab(a,n);
	std::vector<int> result = b.solve();

	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
	
	for(size_t i = 0; i < n; i++)
	{
		std::cout << std::endl;
		for(size_t j = 0; j < n; j++)
		{
			std::cout << a[i][j] << " ";
		}
	}
	std::cout << std::endl;
	std::cout << std::endl;
	int minimum = 0;
	for(size_t i = 0; i < n; i++)
	{
		std::cout << result[i] << " ";
		minimum += a[result[i]][i];
	}
	std::cout << std::endl << "Result: " << minimum << std::endl;
	std::cout <<  "Duration: " << duration/ (float)1000 << "s"<< std::endl;
	return 0;
}


int ** loadMatrix(std::string path, size_t* n)
{
	std::ifstream infile(path);
	std::string line;
	std::getline(infile,line);
	std::istringstream line1(line);
	if(!(line1 >> *n)) {throw new MatrixFormatException;}
	
	int ** a = new int*[*n];

	for(size_t i = 0; (i < *n); i++)
	{	
		a[i] = new int[*n];

		std::getline(infile,line);
		std::istringstream iss(line);
		
		for(size_t j = 0; j < *n; j++)
		{
			if(!(iss >> a[i][j]))
				throw new MatrixFormatException;
		}
	}
	return a;
}

int** randomMatrix(size_t n, int minval, int maxval)
{
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(minval,maxval);

	auto randgen = std::bind ( distribution, generator );

	int** m = new int*[n];
	for (size_t i = 0; i < n; i++) 
	{
		m[i] = new int[n];
		for (size_t j = 0; j < n; j++) 
		{
				m[i][j] = randgen();
		}
	}
	
	return m;
}





