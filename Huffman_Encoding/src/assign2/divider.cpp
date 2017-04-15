#include "iostream"
#include "string"

using namespace std;

string exor(char a,char b,bool c)
{
	if(a == b) return string(1,(c) + 48);
	return string(1,(!c)+48);	
}

int compare (const string s1,const string s2)
{
	if(s1.size() == s2.size())
	{
		return s1.compare(s2);
	}
	else 
	{
		if(s1.size() > s2.size()) return 1;
		else return -1;
	}
}

string rem(string s1,string s2)
{
	for (int i = 0; i < s2.size()-1; ++i)
	{
		string temp = exor(s1[i],49,0);
		s1[i] = temp[0];
		// cout << s2.size() <<" i " << i << endl;
	}
	return s1;
}

string rem(string s1)
{
	size_t pos = s1.find('1');
	string temp;
	if(pos != string::npos)
		temp = s1.substr(pos);
	return temp;
}

string divider(string s1, string s2)
{
	s1 = rem(s1,s2);
	s1 = rem(s1);
	bool tag = true;
	int j = 0;
	while(s1.size() >= s2.size())
	{
		if(compare(s1,s2) == 0)
		{
			return "0";
		}
		string temp1 = s1.substr(0,s2.size());
		s1 = s1.substr(temp1.size());
		string subt;
		for(int i = 0;i < s2.size();i = i + 1)
		{
			subt = subt + exor(temp1[i],s2[i],0);
		}
		j = j + 1;
		s1 = subt+s1;
		s1 = rem(s1);
	}
	return s1;
}
