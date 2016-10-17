#include "neuron.hpp"
#include "neuron.cpp"
#include "Env.hpp"
#include <iostream>
#include <vector>
using namespace std;


Env::Env() {
	
	double g;
	do {
		cout << "Valeur de g ? (relative strengh of excitatory and inhibitory neurons, > 0) " << endl;
		cin >> g;
	} while (g <= 0.0);
	
	double ratio;
	do {
		cout << "Valeur de Vext/Vthr ? ( ratio > 0) " << endl;
		cin >> ratio;
	} while (ratio <= 0.0);
	
	
	unsigned int number_of_neurons(10);
	for(unsigned int i(0); i < number_of_neurons; ++i){
		Neuron* A = new Neuron(i, g, ratio);
		neurones_.push_back(A);
	}

	cout << neurones_.size() << " neurons created ! :) " << endl;
}


Env::~Env() {
	
	//destruction de la collection de neurones
    for (unsigned int i(0); i < neurones_.size(); ++i) {
        delete neurones_[i];
    }
	
	//réinitialise la taille de neurons_ à 0
	neurones_.clear();
}

void Env::random_connection() {
	//Boucle sur tous les neurones du network
	for (unsigned int i(0); i < neurones_.size(); ++i) {
		neurones_[i]->Neuron::random_connection();
	}

}


/*
Neuron* Env::addNeuron() {
		
		Neurone *neurone = new Neurone(*this);
		return neurone;
} 
*/
