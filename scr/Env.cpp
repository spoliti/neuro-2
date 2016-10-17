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
    //CHOISIR L ALGORITHME -> CREATION ET UTILISATION D UN NOUVEL ATTRIBUT DE NEURON ?
    //BOUCLE SUR TOUS LES NEURONES DE neurones_ ?
    /*int a, b;
     a = rand() % 100; //valeur entre 0 et 99 -> pour faire entre 0 et 2500 ? remplacer 100 par 2501 ?
     b= rand() % 100 + 2; //valeur entre 2 et 101
     cout << a << endl; */
}


/*
Neuron* Env::addNeuron() {
		
		Neurone *neurone = new Neurone(*this);
		return neurone;
} 
*/
