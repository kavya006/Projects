#include "iostream"
#include "string"
#include "vector"
#include "algorithm"
#include "queue"
#include "exprtonfa.cpp"


using namespace std;

/*
	Checks whether the input string belongs to L(M) where M is the NFA created by the given expression.
*/
struct stateInfo
{
	int data;
	int index;
};
bool check_string(string input, NFA nfa)
{
	int startState = nfa.getStartState();
	int finalState = nfa.getFinalState();
	/*Contains a queue in which the states are waiting to be processed.*/
	queue<stateInfo> listOfNextTransitions; 
	vector<int> listOfTransitions;
	vector<int> listOfZeroTransitions;
	vector<int>:: iterator it1;
	vector<int>:: iterator it2;
	stateInfo presState;
	presState.data = startState;
	presState.index = 0;
	listOfNextTransitions.push(presState);
	int index = 0;
	while(!listOfNextTransitions.empty())
	{
		/*Pops out the first state waiting to be processed*/
		presState = listOfNextTransitions.front();
		listOfNextTransitions.pop();
		/*Contains a list(vector) of states available from the current state by reading an input symbol*/
		listOfTransitions = nfa.getTransition(presState.data,presState.index,input);
		/*Contains a list of states available from the current state by an Epsilon transition */
		listOfZeroTransitions = nfa.getTransition(presState.data);
		it1 = find(listOfTransitions.begin(), listOfTransitions.end(), finalState);
		it2 = find(listOfZeroTransitions.begin(), listOfZeroTransitions.end(), finalState);
		/*Checks whether the final state is present in the list of transitions by the end of input string*/
		if(((it1 != listOfTransitions.end()) && presState.index == input.size() - 1 )\
			||(it2 != listOfZeroTransitions.end() && presState.index == input.size()))
		{
			return true;
		}
		if((it1 != listOfTransitions.end() && presState.index == input.size()) \
			&& (it2 != listOfZeroTransitions.end() && presState.index == input.size()))
		{
			return false;
		}
		/*the remaining states are added to the queue*/
		for(int i = 0;i < listOfZeroTransitions.size();i = i + 1)
		{
			stateInfo state;
			state.data = listOfZeroTransitions[i];
			state.index = presState.index;
			listOfNextTransitions.push(state);
		}
		if(presState.index != input.size())
		{
			for (int i = 0; i < listOfTransitions.size(); i = i + 1)
			{
				stateInfo state;
				state.data = listOfTransitions[i];
				state.index = presState.index + 1;
				listOfNextTransitions.push(state);
			}
		}
	}
	return false;
}

