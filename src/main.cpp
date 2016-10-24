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
	
	//toutes les actions doivent etre appelées dans la boucle
	//chaque itération correspond à une unité de temps (soit 0.01 ms)
	//on peut changer l'unité de tps dans Env.cpp si trop petit
    
    for(; network.get_time() <= Env::time_simu; network.actualise_time()){
        
        //lancement des spikes pdt que le temps s'écoule
        network.Env::random_spike();
        
        //cout<< network.Env::get_time() << endl; //pour voir le temps passer
        
    }
    
    
    return 0;
} 

