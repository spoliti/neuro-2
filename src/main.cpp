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
	//network.Env::random_connection();

	
	//Mise en route de la simulation
    
    int time_simu = network.Env::get_time_simu();
    
    for(int i(0); i <= time_simu; ++i){
        
        //lancement des spikes sur des cycles de 10 unités de temps (ms, s ?)
        if(network.Env::get_time()%(network.Env::get_periode()) == 0){
        cout << "temps de mise en place spikes: " << network.Env::get_time() << endl;
        network.Env::random_spike();
		}
        
        //cout<< network.Env::get_time() << endl; //pour voir le temps passer
        network.Env::actualise_time(); 
        network.Env::actualise();    }
    
    
    int a(1);// n
	network.Env::get_times_spikes(a);  //affichage des temps auquels les spikes ont didribuées été recu pour neuronne i
    
    int b(2);
    network.Env::get_times_spikes(b);
    return 0;
} 
