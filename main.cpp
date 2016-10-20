#include "neuron.hpp"
#include "env.cpp"
#include <iostream>
#include <vector>
using namespace std;

class Env; 

int main() {
	
	//Création de la simulation
	Env network;
	//appel de random_connection pour générer les connections
	network.Env::random_connection();
	
	int time_simu = network.Env::get_time_simu();
	
	for(int i(0); i <= time_simu; ++i){
		network.Env::actualise_time();
		
		//lancement des spikes pdt que le temps s'écoule
		network.Env::random_spike();
		
		//cout<< network.Env::get_time() << endl; //pour voir le temps passer
		
	}
	
	return 0;
} 
