
#include<string>
#include<fstream>
#include<sstream>
#include<exception>
#include<iostream>

#include<cstdlib>

#include"./MatrixFormatException.h"
#include"bab.h"

#include <boost/program_options.hpp>

#include <random>
#include <chrono>

int* assignement(int n ,int** kosten);
int** loadMatrix(std::string path,size_t * n);

int** randomMatrix(size_t n, int minval, int maxval);

namespace po = boost::program_options;

int main(int argc, char** argv)
{
	size_t n=7;
	int** matrix;
	int min = 1, max = 9;
	po::options_description desc("Allowed options");
	desc.add_options() 
		("help", "print help message")
		("file", po::value<std::string>(), "input file")
		("random",po::value<size_t>(),"use random generated Matrix")
		("min",po::value<int>(),"min Value used in randomly generated Matrix [default = 1]")
		("max",po::value<int>(),"max Value used in randomly generated Matrix [default = 9]")	;
	
	po::variables_map vm;
	po::store(po::parse_command_line(argc,argv,desc),vm);
	po::notify(vm);

	if(vm.count("help"))
	{
		std::cout << desc << std::endl;
		return 1;
	}
	
	if(vm.count("min"))
		min = vm["min"].as<int>();

	if(vm.count("max"))
		max = vm["max"].as<int>();


	//Datei laden
	if(vm.count("file"))
	{   std::string filepath = vm["file"].as<std::string>();
		matrix = loadMatrix(filepath,&n);	
	}
	else if(vm.count("random"))
	{
		n = vm["random"].as<size_t>();
		matrix = randomMatrix(n,min,max);
	}
	else
	{
		matrix = randomMatrix(n,min,max);
	}

	
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	 
	bab b = bab(matrix,n);
	std::vector<int> result = b.solve();

	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
	
	for(size_t i = 0; i < n; i++)
	{
		std::cout << std::endl;
		for(size_t j = 0; j < n; j++)
		{
			std::cout << matrix[i][j] << " ";
		}
	}
	std::cout << std::endl;
	std::cout << std::endl;
	int minimum = 0;
	for(size_t i = 0; i < n; i++)
	{
		std::cout << result[i] << " ";
		minimum += matrix[result[i]][i];
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
	std::default_random_engine generator(time(0));
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





