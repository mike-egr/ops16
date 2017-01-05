
#include<string>
#include<fstream>
#include<sstream>
#include<exception>
#include<iostream>

#include"./MatrixFormatException.h"
#include"bab.h"

int* assignement(int n ,int** kosten);
int** loadMatrix(std::string path,size_t * n);


int main(void)
{

	size_t n;
	int** a = loadMatrix("test.txt",&n);

	bab b = bab(a,n);
	std::vector<int> result = b.solve();
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



