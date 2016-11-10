#include<cstddef>
#include<vector>
#include<queue>
#include<algorithm>
#include<iostream>
class PartialSolution;


class PartialSolution
{
	public:
		PartialSolution(size_t n, int** matrix);
		PartialSolution(){}
		PartialSolution(const PartialSolution& obj);
		PartialSolution(size_t n, int** matrix, std::vector<int> assignments);

		std::priority_queue<PartialSolution, std::vector<PartialSolution>, std::greater<PartialSolution>> branch();
		int bound();
		bool solution();

		std::vector<int> assignments;
		int lBound;

	
//Operator overloading
		bool operator< (const PartialSolution &s2) const;
		bool operator> (const PartialSolution &s2) const;
		bool operator== (const PartialSolution &s2) const;
		bool operator<= (const PartialSolution &s2) const;
		bool operator>= (const PartialSolution &s2) const;
	

	private:
		size_t depth;
		int** matrix;
		size_t n;
};



size_t minIndexOfColumn(size_t j, int** matrix, size_t n)
{	
	size_t minIndex = 0;
	for(size_t i = 0; i < n; i++)
	{
		if(matrix[i][j] < matrix[minIndex][j])
			minIndex = i;
	}
	return minIndex;
}



class bab
{
	public:
	   	bab(int** matrix, size_t n);
		~bab();
		std::vector<int> solve();

	private:
		int** matrix;
		int n;
		int uBound;
		std::priority_queue<PartialSolution, std::vector<PartialSolution>, std::greater<PartialSolution>> queue;
		PartialSolution bestSol;
};

bab::~bab()
{}

bab::bab(int** matrix, size_t n)
{
	this->matrix = matrix;
	this->n = n;
	std::vector<int> assignments;
	this->uBound = 0;
	for(size_t i = 0; i < n; i++)
	{
		this->uBound += matrix[i][i];
		assignments.push_back(i);	
	}

	bestSol = PartialSolution(n,matrix,assignments);

	PartialSolution initialSol = PartialSolution(n,matrix);
	queue.push(initialSol);
	
}

std::vector<int> bab::solve()
{
	while(!queue.empty())
	{
		PartialSolution sol = queue.top();
		queue.pop();
		if(sol.solution())
		{
			if(sol.lBound < uBound)
			{	
				uBound = sol.lBound;
				bestSol = sol;
#ifdef DEBUG 
				std::cout << std::endl << "New best sol: " << sol.lBound << std::endl;
#endif
			}
		}
		else
		{
			std::priority_queue<PartialSolution, std::vector<PartialSolution>, std::greater<PartialSolution>> pq;
			pq = sol.branch();
			while(!pq.empty())
			{ 
#ifdef DEBUG
				std::cout << "Queue lbound" << pq.top().lBound;
#endif
				if(pq.top().lBound < uBound)
				{
					queue.push(pq.top());
				}
				pq.pop();
			}
		}
	}

	return bestSol.assignments;
}

PartialSolution::PartialSolution(const PartialSolution &obj)
{
	this->depth = obj.depth;
	this->assignments = obj.assignments;
	this->n = obj.n;
	this->matrix = obj.matrix;
	this->lBound = obj.lBound;
	
}

PartialSolution::PartialSolution(size_t n, int** matrix, std::vector<int> assignments)
{
	this->n = n;
	this->depth = n;
	this->assignments = assignments;
	this->matrix = matrix;
	this->lBound = this->bound();
	
}

PartialSolution::PartialSolution(size_t n, int** matrix)
{
	this->matrix = matrix;
	this->n = n;
	this->depth = 0;
	this->lBound = this->bound();
}


int PartialSolution::bound()
{	
	int bound = 0;
	for( size_t i = 0; i < n; i++)
	{
		if(i < depth)
			bound += matrix[assignments[i]][i];
		if(i >= depth)
			bound += matrix[minIndexOfColumn(i,matrix,n)][i];
	}
	return bound;
}

bool PartialSolution::solution()
{
	return depth == n;
}

std::priority_queue<PartialSolution, std::vector<PartialSolution>, std::greater<PartialSolution>> PartialSolution::branch()
{	
#ifdef DEBUG
	std::cout << std::endl << "Branch " << std::endl;
#endif
	std::priority_queue<PartialSolution, std::vector<PartialSolution>, std::greater<PartialSolution>> pq;
	for(size_t i = 0; i < this->n; i++)
	{
		PartialSolution sol(*this);
		sol.depth++;
		
		if(std::find(sol.assignments.begin(),sol.assignments.end(),i)==sol.assignments.end())	
		{
			sol.assignments.push_back(i);
			sol.lBound = sol.bound();
			pq.push(sol);
#ifdef DEBUG
			std::cout << "Lower Bound "<< sol.lBound << std::endl;
#endif
		}
	}
	return pq;
}

bool PartialSolution::operator<(const PartialSolution& s2) const
{
	return this->lBound < s2.lBound;
}

bool PartialSolution::operator>(const PartialSolution& s2) const
{
	return this->lBound > s2.lBound;
}

bool PartialSolution::operator==(const PartialSolution& s2) const
{
	return this->lBound == s2.lBound;
}

bool PartialSolution::operator<=(const PartialSolution& s2) const 
{
	return this->lBound <= s2.lBound;
}

bool PartialSolution::operator>=(const PartialSolution& s2) const
{
	return this->lBound >= s2.lBound;
}


