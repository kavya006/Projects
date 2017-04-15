#include <string>
#include <algorithm>

using namespace std;

/*
	This file contains the matrix used in CYK algorithm. It has methods to update the matrix and 
	get the terminals in a matrix cell.
*/
class check_list
{
	private:
		int size;
		string **list;
		int *S;
	public:
		check_list(int sizeOfInput, int sizeOfRuleSet)
		{
			list = new string *[sizeOfInput+1];
			S = new int [sizeOfInput + 1];
			int i = 0;
			for(i = 0;i < sizeOfInput + 1; i = i + 1)
			{
				list[i] = new string[i+1];
				S[i] = i + 1;
			}
			size = sizeOfInput + 1;
		}
		void update(int index_row, int index_col, string result)
		{
			if(index_col < size && index_row < index_col + 1)
			{	
				string& temp = list[index_col][index_row];
				int i = 0;
				for(i = 0;i < result.size();i = i + 1)
				{
					string terminal = result.substr(i,1);
					std::size_t  found = temp.find(terminal);
					if(found == std::string::npos)
					{
						string term = terminal;
						temp = temp + term;
					}
				}
				return;
			}
			cout << "Invalid Access" << endl;
		}
		string& getTerminals(int index_row, int index_col)
		{
			if(index_col < size && index_row < index_col + 1)
			{
				string& temp = list[index_col][index_row];
				return temp;
			}
			cout << "Invalid Access" << endl;
		}
		void print_S()
		{
			int i = 0;
			for(i = 0;i < size;i = i + 1)
			{
				cout << S[i] << " ";
			}
			cout << "\n";
		}
};