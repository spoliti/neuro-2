#include "neuron.hpp"
#include "Env.cpp"
#include <iostream>
#include <vector>
using namespace std;

class Env; 

int main() {
	
	//Création de la simulation
	//Env(); //constructeur de env pour créer des neurones
	Env network;
	//appel de random_connection pour générer les connections
	network.Env::random_connection();

	
	//Mise en route de la simulation
    
    double time_simu(network.Env::get_time_simu());
    
    for(; network.get_time() <= time_simu; network.actualise_time()){
        
        //lancement des spikes pdt que le temps s'écoule
        network.Env::random_spike();
        
        //cout<< network.Env::get_time() << endl; //pour voir le temps passer
        
    }
    
    
    return 0;
} 

