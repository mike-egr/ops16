#include<cstddef>
#include<vector>
#include<queue>
#include<algorithm>
#include<iostream>
#include<list>
class PartialSolution;

//Repräsentiert einen Lösungskandidaten
class PartialSolution
{
	public:
		PartialSolution(size_t n, int** matrix);
		PartialSolution(){}
		PartialSolution(const PartialSolution& obj);
		PartialSolution(size_t n, int** matrix, std::vector<int> assignments);

		std::list<PartialSolution> branch();
		bool bound(); //lbound hier drinnen setzen!!!
		bool solution();

		std::vector<int> assignments;
		int lBound;

	
//Operator overloading zum sortieren
		bool operator< (const PartialSolution &s2) const;
		bool operator> (const PartialSolution &s2) const;
		bool operator== (const PartialSolution &s2) const;
		bool operator<= (const PartialSolution &s2) const;
		bool operator>= (const PartialSolution &s2) const;
	

	private:
		size_t depth; //Anzahl der gültig besetzten Variablen
		int** matrix; 
		size_t n; 
};


//Gibt Index zurück in an dem sich der Minimalwert der jeweiligen Spalte befindet
// size_t j ... Spalte
// int** matrix ... Problemmatrix
// size_t n ... Größe der Problemmatrix
size_t minIndexOfColumn(size_t j, int** matrix, size_t n,std::vector<int> exclude)
{	
	size_t minIndex = 0;
	for(size_t i = 0; i < n; i++)
	{
		if(matrix[i][j] < matrix[minIndex][j] && find(exclude.begin(),exclude.end(),i) == exclude.end() )
			minIndex = i;
	}
	return minIndex;
}



//Konstruktoren

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



//Berechnet eine untere Schranke für den Lösungskandidaten
//TODO:überprüfen ob es eine Lösung ist
//Returns true if valid soulution is found while calculatiing lower bound, else false
bool PartialSolution::bound()
{	
	int bound = 0;
	std::vector<int> ass(assignments); //Used for calculation lbound and checking if it is as solution
	std::list<int> range(n);

	std::iota(range.begin(),range.end(),0);
	
	for( size_t i = 0; i < n; i++)
	{
		if(i < depth)
			bound += matrix[assignments[i]][i];
		if(i >= depth)
		{
			ass.push_back(minIndexOfColumn(i,matrix,n,assignments));
			bound += matrix[ass[i]][i];
		}
	}

	this->lBound = bound;

	if(std::is_permutation(ass.begin(),ass.begin()+n,range.begin()))
	{

		//Set assignments and depth; we should also set upper bound for problem
				
		this->assignments = ass;
		this->depth = n;


#ifdef DEBUG
		std::cout << std::endl << "Solution found while calculating lower bound:" << bound ;
#endif
		return true;
	}

	return false;	
}

//Übeprüft ob es sich bei dem Lösungskandidaten um eine gültige Lösung handelt
bool PartialSolution::solution()
{
	return depth == n;
}

//Branch methode: Gibt die Unterlösungen eines Lösungskandidaten in einer PQ zurück
// hier wird gebrancht und gebounded
std::list<PartialSolution> PartialSolution::branch()
{	
#ifdef DEBUG
	std::cout << std::endl << std::endl << "BEGIN Branch:";
#endif
	std::list<PartialSolution> list;
	for(size_t i = 0; i < this->n; i++)
	{
		PartialSolution sol(*this);
		sol.depth++;
		
		if(std::find(sol.assignments.begin(),sol.assignments.end(),i)==sol.assignments.end())	
		{
			sol.assignments.push_back(i);
			//valid solutions in at the begining of the list, so they are processed first
			if(sol.bound())
			{	
				list.insert(list.begin(),sol);//return std::list<PartialSolution>(1,sol);
			}
			else
				list.insert(list.end(),sol);
#ifdef DEBUG
			std::cout << std::endl << "Branch Lower Bound "<< sol.lBound << std::endl;
#endif
		}
	
	}
#ifdef DEBUG
	std::cout << "END Branch" << std::endl << std::endl;
#endif
	return list;
}


//Vergleichsoperatoren: Vergleichen die Lösungskandidaten anhand der unteren Schranke
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
	
	//Erzeuge irgendeine Lösung gegen die dan Verglichen wird
	bestSol = PartialSolution(n,matrix,assignments);
	
	//Erzuege leeren Lösungskandidaten
	PartialSolution initialSol = PartialSolution(n,matrix);
	queue.push(initialSol);
	
#if defined(DEBUG2)
	std::cout << std::endl << "initial solution: " << uBound;
#endif

}

std::vector<int> bab::solve()
{
	while(!queue.empty())
	{
		//Nehmen besten Lösungskandidaten(LK) aus der Queue und überprüfe ob es eine Lösung ist, wenn ja, ob
		// die Lösung besser ist als die bisher beste
		PartialSolution sol = queue.top();
		queue.pop();
		if(sol.lBound < uBound)
		{
			//NEVER HAPPENS
			if(sol.solution())
			{	
				uBound = sol.lBound;
				bestSol = sol;
#if defined(DEBUG) || defined(DEBUG2)	
				std::cout << std::endl << "New best sol1: " << sol.lBound << std::endl;
#endif
			}
		
			else{
			
				//sonst branchen und bounden und LK deren Lower bound geringer ist als die bisher beste lösung
				// werden verworfen
				std::list<PartialSolution> list;
				list = sol.branch();
				for(std::list<PartialSolution>::iterator it = list.begin(); it != list.end(); it++)
				{ 
#ifdef DEBUG
					std::cout << std::endl << "Queue lbound" << it->lBound;
#endif
					if(it->lBound < uBound)
					{
						if(it->solution())
						{ 
							uBound = it->lBound;
							bestSol = *it;

#if defined(DEBUG) || defined(DEBUG2)	
				std::cout << std::endl << "New best sol2: " << it->lBound << std::endl;
#endif
	
						}
						else
						{
							queue.push(*it);
						}
					}
				}//ENDFOR
			}//ENDELSE
		}//ENDIF
	}//ENDWHILE

	return bestSol.assignments;
}


