#include "string"
#include "map"
#include "iostream"
#include "queue"

using namespace std;

struct Node{
	char symbol = 0;
	int freq = 0;
	Node *left = NULL;
	Node *right = NULL;

	Node(char data, unsigned freq)
	{
		this->symbol = data;
		this->freq = freq;
	}
};

struct comp{
	bool operator()(Node *left, Node *right) const
	{
		return left->freq > right->freq;
	}
};

class Huffman_Encoding
{
	public:
		void get_Code(Node *root, string str, map<char,string>& codeBook){
			if(!root) return;
			if(root->symbol != 0)
			{
			//	cout << root->symbol << " : " << str << endl;
				codeBook.insert(pair<char,string>(root->symbol,str));
			}
			get_Code(root->left, str+"0",codeBook);
			get_Code(root->right, str+"1",codeBook);
		}

		void create(map<char,int> Mapping,map<char,string>& codeBook)
		{
			Node *left, *right, *top;
			priority_queue<Node *, vector<Node *>, comp> pQueue;
			for(map<char,int>::iterator it = Mapping.begin();it != Mapping.end();it++)
			{
				if(it->second != 0)
				{
					pQueue.push(new Node(it->first,it->second));
				}
			}
			while(pQueue.size() != 1)
			{
				left = pQueue.top();
				pQueue.pop();
				right = pQueue.top();
				pQueue.pop();
				top = new Node(0,left->freq+right->freq);
				top->left = left;
				top->right = right;
				pQueue.push(top);
			}
			get_Code(pQueue.top(),"",codeBook);
		}
	
};