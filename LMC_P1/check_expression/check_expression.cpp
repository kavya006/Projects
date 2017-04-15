#include "iostream"
#include "string"
#include "algorithm"

#include "grammar_Rules.cpp"
#include "check_list.cpp"

using namespace std;

/*
	Contains the function CYK which checks for the expression is a regular expression or not
*/
bool CYK(string expr, productionSet Rules)
{
	int i = 0;
	int m = 2;
	int n = expr.size();
	int j = 0;
	int k = 0;
	int l = 0;
	check_list list(expr.size(), Rules.getSize());
	for(i = 0;i <= n - 1;i = i + 1)
	{
		string temp = expr.substr(i,1);
		string result;
		Rules.search(temp,result);
		if(result.size() != 0)
		{
			list.update(i,i+1,result);
		}
	}
	for(m = 2;m <= n;m = m + 1)
	{
		for(i = 0;i <= n - m;i = i + 1)
		{
			for(j = i + 1;j <= i+m-1;j = j + 1)
			{
				string res1 = list.getTerminals(i,j);
				string res2 = list.getTerminals(j,i+m);
				for(k = 0;k < res1.size();k = k + 1)
				{
					for(l = 0;l < res2.size();l = l + 1)
					{
						string temp;
						temp = res1.substr(k,1);
						temp = temp + res2.substr(l,1);
						string temp1;
						Rules.search(temp,temp1);
						if(temp1.size() != 0)
						{
							list.update(i,i+m,temp1);
						}
					}
				}
			}
		}
	}
	string result = list.getTerminals(0,n);
	string temp = string(1,Rules.get_startState());
	std::size_t found = result.find(temp);
	if(found==std::string::npos) return false;
	else return true;
} 

productionSet& createGrammarRules()
{
	productionSet temp('S');
	productionSet& Rules = temp;
	string s = "HM";
	Rules = Rules + productionRule('S',s);
	s = "HN";
	Rules = Rules + productionRule('S',s);
	s = "HI";
	Rules = Rules + productionRule('S',s);
	s = "LS";
	Rules = Rules + productionRule('H',s);
	s = "SR";
	Rules = Rules + productionRule('J',s);
	s = "PJ";
	Rules = Rules + productionRule('M',s);
	s = "KR";
	Rules = Rules + productionRule('I',s);
	s = "DJ";
	Rules = Rules + productionRule('N',s);
	s = "(";
	Rules = Rules + productionRule('L',s);
	s = ")";
	Rules = Rules + productionRule('R',s);
	s = "+";
	Rules = Rules + productionRule('P',s);
	s = ".";
	Rules = Rules + productionRule('D',s);
	s = "*";
	Rules = Rules + productionRule('K',s);
	char ch = 'a';
	for(int i = 0;i < 26;i = i + 1)
	{
		s = string(1,char(ch+i));
		Rules = Rules + productionRule('S',s);
	}
	ch = 'A';
	for(int i = 0;i < 26;i = i + 1)
	{
		s = string(1,char(ch+i));
		Rules = Rules + productionRule('S',s);
	}
	return Rules;
}

bool check_expression(string expr)
{
	productionSet Rules = createGrammarRules();
	return CYK(expr,Rules);
}
