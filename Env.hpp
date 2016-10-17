#include <vector>
#include <iostream>
#include "neuron.hpp"

using namespace std;


class Env{
	public:
		Env(); 							//constructeur
		//Neurone* addNeurone();
	private:
		//A MODIFIER -> faire un tableau de références
		vector<Neuron> neurones; //collection de neurones de l'env,
		
};

