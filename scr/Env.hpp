#include <vector>
#include <iostream>
#include "neuron.hpp"

using namespace std;

class Env {
	public:
		Env(); 							//constructeur
		~Env();							//destructeur
		void random_connection();
		//Neuron* addNeuron();
	private:
		vector<Neuron*> neurones_; 		//collection de neurones de l'env,
		
		
};

