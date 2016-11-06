
#include<string>
#include<fstream>
#include<sstream>
#include<exception>
#include<iostream>

#include"./MatrixFormatException.h"


int* assignement(int n ,int** kosten);
int** loadMatrix(std::string path);


int main(void)
{

/*DEBUG	
	int** a = loadMatrix("test.txt");

	for(size_t i = 0; i < 3; i++)
	{
		std::cout << std::endl;
		for(size_t j = 0; j < 3; j++)
		{
			std::cout << a[i][j] << " ";
		}
	}
	std::cout << std::endl;
*/
	return 0;
}


int ** loadMatrix(std::string path)
{
	std::ifstream infile(path);
	std::string line;
	size_t n; //Number of lines
	std::getline(infile,line);
	std::istringstream line1(line);
	if(!(line1 >> n)) {throw new MatrixFormatException;}
	
	int ** a = new int*[n];

	for(size_t i = 0; (i < n); i++)
	{	
		a[i] = new int[n];

		std::getline(infile,line);
		std::istringstream iss(line);
		
		for(size_t j = 0; j < n; j++)
		{
			if(!(iss >> a[i][j]))
				throw new MatrixFormatException;
		}
	}
	return a;
}



