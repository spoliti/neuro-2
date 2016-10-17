#include <vector>
#include <iostream>
#include "neuron.hpp"

using namespace std;


class Env{
	public:
		Env(); 							//constructeur
		~Env();
		void random_connection();
		//Neurone* addNeurone();
	private:
		//A MODIFIER -> faire un tableau de références
		vector<Neuron*> neurones_; //collection de neurones de l'env,
		
		
};

