#include "iostream"
#include "string"
#include "vector"
#include "algorithm"
using namespace std;

/*
	This file contains the class for creating a NFA from a regular expression 
	and struct construct for an edge in the NFA
*/
struct edge
{
	int v1;
	int v2;
	char weight = '0';
};
/*
	This class contains the methods for creating a NFA from the input expression.
	Methods present are:
	Add a new Edge, kleenestar , concatenate and  union operations on the symbols, 
	searching for all possible transitions from a given state on reading input symbol 
	and on empty epsilon , and finally to print all the edges in the NFA
*/
class NFA
{
	private:
		string expr;
		vector<edge> listOfEdges;	//list of all the edges in the NFA
		vector<int> listOfStates;
		int startState;
		int finalState;
		int count;
		void add_edge(char weight)
		{
			edge e1;
			e1.v1 = count;
			e1.v2 = count + 1;
			e1.weight = weight;
			listOfEdges.push_back(e1);
			listOfStates.push_back(count+1);
			listOfStates.push_back(count);
			count = count + 2;
		}
		bool checkForOperands(int i)
		{
			bool check = (expr[i] == '*' || expr[i] == '.' || expr[i] == '+');
			return check;
		}
		void kleenestar()
		{
			int start = listOfStates.back();
			listOfStates.pop_back();
			int final = listOfStates.back();
			listOfStates.pop_back();
			edge e1, e2, e3,e4;
			e1.v1 = count;
			e1.v2 = start;
			e2.v1 = final;
			e2.v2 = start;
			e3.v1 = count;
			e3.v2 = count + 1;
			e4.v1 = final;
			e4.v2 = count + 1;
			listOfEdges.push_back(e1);
			listOfEdges.push_back(e2);
			listOfEdges.push_back(e3);
			listOfEdges.push_back(e4);
			listOfStates.push_back(count+1);
			listOfStates.push_back(count);
			startState = count;
			finalState = count + 1;
			count = count + 2;
		}
		void concatenate()
		{
			int start2 = listOfStates.back();
			listOfStates.pop_back();
			int final2 = listOfStates.back();
			listOfStates.pop_back();
			int start1 = listOfStates.back();
			listOfStates.pop_back();
			int final1 = listOfStates.back();
			listOfStates.pop_back();
			edge e1;
			e1.v1 = final1;
			e1.v2 = start2;
			listOfEdges.push_back(e1);
			listOfStates.push_back(final2);
			listOfStates.push_back(start1);
			startState = start1;
			finalState = final2;
		}
		void unionOfStates()
		{
			int start2 = listOfStates.back();
			listOfStates.pop_back();
			int final2 = listOfStates.back();
			listOfStates.pop_back();
			int start1 = listOfStates.back();
			listOfStates.pop_back();
			int final1 = listOfStates.back();
			listOfStates.pop_back();
			edge e1,e2,e3,e4;
			e1.v1 = e2.v1 = count;
			e1.v2 = start1;
			e2.v2 = start2;
			e3.v1 = final1;
			e4.v1 = final2;
			e3.v2 = e4.v2 = count + 1;
			listOfEdges.push_back(e1);
			listOfEdges.push_back(e2);
			listOfEdges.push_back(e3);
			listOfEdges.push_back(e4);
			listOfStates.push_back(count+1);
			listOfStates.push_back(count);
			startState = count;
			finalState = count + 1;
			count = count + 2;
		}
		void constructNFA()
		{
			vector<char> listOfOperations;
			int i = 0;
			for(i = 0;i < expr.size();i = i + 1)
			{
				if(!checkForOperands(i))
				{
					if(expr[i] != '(' && expr[i] != ')')
					{
						add_edge(expr[i]);
					}
				}
				else
				{
					listOfOperations.push_back(expr[i]);
				}
				if(expr[i] == ')')
				{
					char ch = listOfOperations.back();
					listOfOperations.pop_back();
					switch(ch)
					{
						case '*':
							kleenestar();
							break;
						case '.':
							concatenate();
							break;
						case '+':
							unionOfStates();
							break;
					}
				}
			}
		}
	public:
		NFA(string input)
		{
			expr = input;
			startState = 0;
			finalState = 1;
			count = 0;
			constructNFA();
		}
		void print_edges()
		{
			int i = 0;
			cout << startState << " " << finalState << endl;
			for(i = 0;i < listOfEdges.size();i = i + 1)
			{
				cout <<" " <<listOfEdges[i].v1 << " " << listOfEdges[i].weight << " " << listOfEdges[i].v2 << endl;
			}
		}
		int getStartState()
		{
			return startState;
		}
		int getFinalState()
		{
			return finalState;
		}
		vector<int> getTransition(int preState, int index, string input)
		{
			int i = 0;
			vector<int> listOfTransitions;
			char weight = input[index];
			for(i = 0;i < listOfEdges.size();i = i + 1)
			{
				if(listOfEdges[i].v1 == preState && listOfEdges[i].weight == weight)
				{
					listOfTransitions.push_back(listOfEdges[i].v2);
				}
			}
			return listOfTransitions;
		}
		vector<int> getTransition(int preState)
		{
			int i = 0;
			vector<int> listOfTransitions;
			for(i = 0;i < listOfEdges.size();i = i + 1)
			{
				if(listOfEdges[i].v1 == preState && listOfEdges[i].weight == '0')
				{
					listOfTransitions.push_back(listOfEdges[i].v2);
				}
			}
			return listOfTransitions;
		}
		int getCount()
		{
			return count;
		}
		
};
