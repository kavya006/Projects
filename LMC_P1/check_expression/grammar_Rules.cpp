#include <string>

using namespace std;
/*
	This file contains classes for the production rules and grammar production rules set.
*/

/*
	Class for production rules. 
	contains methods for comparing and assigning production rules. 
	Production rules are of the form S->AB.
*/
class productionRule
{
	private:
		char LHS;
		string RHS;
	public:
		productionRule(char pre, string post)
		{
			LHS = pre;
			RHS = post;
		}
		void display()
		{
			cout << "(" << LHS<<","<< RHS<<")" <<endl;
		}
		char get_LHS()
		{
			return this->LHS;
		}
		string& get_RHS()
		{
			return this->RHS;
		}
		/*This method allows to assign the production rule b to the this pointer like a = b*/
		productionRule& operator=(const productionRule& b)
		{
			this->LHS = b.LHS;
			this->RHS = b.RHS;
			return *this;
		}
		/*This method allows to check for the equality of two production rules like a == b*/
		bool operator==(const productionRule& b)
		{
			if(this->LHS == b.LHS)
			{
				if(this->RHS == b.RHS)
				{
					return 1;
				}
			}
			return 0;
		}
};

/*
	Class for the production rule set. Contains the methods for assigning two grammars, 
	adding a new production rule to the existing grammar, search the grammar for productions 
	using two different methods and to display the production rules set.
*/
class productionSet
{
	private:
		vector<productionRule> setOfRules;
		char startState;
	public:
		productionSet(char start_State)
		{
			startState = start_State;
		}
		char get_startState()
		{
			return this->startState;
		}
		/*This method allows to assign a production set to another. like a = b*/
		productionSet& operator=(productionSet b)
		{
			if(&b != this && this->setOfRules.size() < b.getSize())
			{
				*this = b;
			}
			return *this;
		}
		/*This method allows to add a new member to existing grammar*/
		productionSet& operator+(const productionRule b)
		{
				this->setOfRules.push_back(b);
				return *this;
		}
		/*This method lets us to search for a certain rule in the grammar*/
		void search(const productionRule b, string& result)
		{
			int i = 0;
			while(i < this->setOfRules.size())
			{
				if(this->setOfRules[i] == b) 
				{
					result = result + (this->setOfRules[i]).get_LHS();
				}
				i = i + 1;
			}
		}
		/*This method lets us to compare the string b and the RHS of rules 
		in the set of rules in grammar to find the LHS*/
		void search(const string b,string& result)
		{
			int i = 0;
			while(i < this->setOfRules.size())
			{
				if(b.compare(this->setOfRules[i].get_RHS()) == 0)
				{	
					std::size_t  found = result.find(b);
					if(found == std::string::npos)
					{
						result = result + (this->setOfRules[i]).get_LHS();
					}
					else 
					{
						continue;
					}
				} 
				i = i + 1;
			}
		}
		int getSize()
		{
			return setOfRules.size();
		}
		void display()
		{
			int i = 0;
			while (i < setOfRules.size())
			{
				setOfRules[i].display();
				i = i + 1;
			}
		}
	
};