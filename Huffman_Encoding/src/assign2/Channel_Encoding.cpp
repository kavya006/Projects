#include "iostream"
#include "fstream"
#include "map"
#include "string"
#include "cstring"

#include "divider.cpp"
#include "bitError.cpp"

using namespace std;

void splitText(string filename);
string channelEncoding(string data);
void encodeText(map<char,string> codeBook, string filename)
{
	ifstream inFile;
	inFile.open(filename);
	ofstream outFile;
	outFile.open("encodedFile.txt");
	while(1)
	{
		char ch;
		inFile >> ch;
		if(inFile.eof())
			break;
		map<char,string>::iterator it =  codeBook.find(ch);
		if(it != codeBook.end())
		{
			outFile << it->second ;
		}
	}
	outFile << "\0";
	inFile.close();
	outFile.close();
	filename = "encodedFile.txt";
	splitText(filename);
}

void splitText(string filename)
{
	ifstream inFile;
	inFile.open(filename);
	ofstream outFile;
	outFile.open("sendMessage.txt");
	while(1)
	{
		char str[1025] = "";
		if(inFile.eof())
			break;
		inFile.read(str, sizeof(str)-1);
		string data = str;
		//cout << data << endl;
		string message = channelEncoding(data);
		outFile << message;
	}
}

string channelEncoding(string data)
{
	string CRCPoly = "100000100110000010001110110110111";
	string remain;
	remain = divider(data,CRCPoly);
	while(remain.size() != 32)
	{
		remain = "0" + remain;
	}
	cout << data.size()<< " " <<remain.size() << endl;;
	data = data + remain;
	cout << data.substr(data.size() - 32) << " " << remain << endl;
	cout << compare(data.substr(data.size()-32), remain) << endl;
	//errorGen(data);
	return data;
}