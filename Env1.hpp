#include <vector>
#include <iostream>
#include "Neurone.hpp"

using namespace std;


class Env1{
	public:
		Env1(); 							// le constructeur par défaut
		int number_of_neurons;
		//Neurone* addNeurone();
	private:
		vector<Neurone&> Neurones;
		
};
