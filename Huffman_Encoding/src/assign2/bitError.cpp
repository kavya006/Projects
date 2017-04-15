#include <random>
#include <chrono>

using namespace std;


double randomGen()
{
    std::mt19937_64 rng;
    // initialize the random number generator with time-dependent seed
    uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
    rng.seed(ss);
    // initialize a uniform distribution between 0 and 1
    std::uniform_real_distribution<double> unif(0, 1);
    // ready to generate random numbers
    //const int nSimulations = 10;
    //for (int i = 0; i < nSimulations; i++)
    {
        double currentRandomNumber = unif(rng);
        return currentRandomNumber;
    }
    return 0;
}
bool isCheck()
{
	double r = randomGen();
	double prob = 0.000000000;
	//cout << r << endl;
	if(prob > r){
		return true;
	}
	return false;
}

void errorGen(string& message)
{
	for (int i = 0; i < message.size(); ++i)
	{
		if(isCheck())
		{
			string temp = exor(message[i],49,0);
			message[i] = temp[0];
		}
	}
}
/*
int main()
{
	string filename = "sendMessage.txt";
	ifstream inFile;
	ofstream outFile;
	inFile.open(filename);
	outFile.open("finalSendMessage.txt");
	while(1)
	{
		if(inFile.eof())
			break;
		char ch;
		inFile >> ch;
		if(isCheck())
		{
			outFile << exor(ch,'1',0);
		}
		else
		{
			outFile << ch;
		}
	}
	inFile.close();
	outFile.close();
}*/