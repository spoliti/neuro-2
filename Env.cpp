#include "neuron.hpp"
#include "neuron.cpp"
#include "Env.hpp"
#include <iostream>
#include <vector>
using namespace std;


Env::Env(){
	
    //FAIRE DES CONTROLES SUR LES VALEURS DE G ET DU RATIO

	double g;
	cout << "Valeur de g ? (relative strengh of excitatory and inhibitory neurons) " << endl;
	cin >> g;
	
	double ratio;
	cout << "Valeur de Vext/Vthr ? " << endl;
	cin >> ratio;
	
	int number_of_neurons(10);
	for(int i(0); i < number_of_neurons; ++i){
		Neuron A (i, g, ratio);
	}
}

//FAIRE LE MAIN DANS UN FICHIER A PART 
/*
int main(){
	Env(); // ici on appelera le constructeur de env pour creer des neurones
	
return 0;
} */

/*
Neurone* Env::addNeurone() {
		
		Neurone *neurone = new Neurone(*this);
		return neurone;
} 
*/
