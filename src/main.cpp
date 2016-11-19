#include "neuron.hpp"
#include "Env.cpp"
#include <iostream>
#include <vector>
#include <math.h>
     
using namespace std;

class Env; 

int main() {
	
	//Création de la simulation
	Env network;
	//appel de random_connection pour générer les connections (de qui on peut recevoir des spikes)
	
	network.Env::set_connections();
	
	int d(10);
    network.Env::get_liaisons_env(d);
    
    int e(1100);
    network.Env::get_liaisons_env(e);
	
	/*
	//Mise en route de la simulation
    
    int time_simu(network.Env::get_time_simu());
    
    for(int i(0); i <= time_simu; ++i){     
        //cout<< network.Env::get_time() << endl; //pour voir le temps passer
        network.Env::actualise();    
        
	} 
    /*
    int d(100);
    network.Env::get_liaisons_background(d);
    
    int e(24);
    network.Env::get_liaisons_background(e);
    */
    
    /*
    int a(1250);// n
	network.Env::get_times_spikes(a);  //affichage des temps auquels les spikes ont didribuées été recu pour neuronne i
	
    int b(1251);
    network.Env::get_times_spikes(b);
    */

    
     return 0;
} 

