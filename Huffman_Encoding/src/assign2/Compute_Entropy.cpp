#include "iostream"
#include "fstream"
#include "vector"
#include "algorithm"
#include "map"
#include "cmath"

#include "Huffman_Encoding.cpp"
#include "Channel_Encoding.cpp"

using namespace std;


int main()
{
	string filename = "Sample.txt";
	ifstream myfile;
	myfile.open(filename);
	map<char, int> freqMapping;
	map<char, int>::iterator it;
	char ch;
	long long int sum=0;
	double entropy = 0.0;
	while(myfile)
	{
		myfile >> ch;
		it = freqMapping.find(ch);
		if(it == freqMapping.end())
		{
			freqMapping.insert(pair<char,int>(ch,1));
		}
		else
		{
			it->second = it->second + 1;
		}
		sum = sum + 1;
	}
	float prob = 0.0;
	for (map<char,int>::iterator i = freqMapping.begin(); i != freqMapping.end(); ++i)
	{
		prob = i->second/(float)sum;
		entropy = entropy - (prob * log2(prob));
	}
	cout << entropy << endl;
	map<char,string> codeBook;
	Huffman_Encoding HTree;
	HTree.create(freqMapping,codeBook);
	ofstream codeFile;
	codeFile.open("codeBook.txt");
	for (map<char,string>::iterator i = codeBook.begin(); i != codeBook.end(); ++i)
	{
		codeFile << i->first << i->second << endl; 
	}
	codeFile.close();
	encodeText(codeBook,filename);
}

