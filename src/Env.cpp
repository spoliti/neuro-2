#include "neuron.hpp"
#include "neuron.cpp"
#include "Env.hpp"
#include <iostream>
#include <vector>
#include <math.h>
#include <random>

using namespace std;

//Initialisation des constantes statiques
	const double Env::time_unit(0.01);		//[millisecondes]
	const double Env::time_simu(20); 		//[ms] = 2s
	const double Env::periode(10); 		//[ms], 10 unités de temps pour le moment
	

Env::Env() 
: time(0)
{
	
	double g;
	do {
		cout << "Valeur de g ? (relative strengh of excitatory and inhibitory neurons, > 0) " << endl;
		cin >> g;
	} while (g <= 0.0);
	
	double ratio;
	do {
		cout << "Valeur de Vext/Vthr ? ( ratio > 0) " << endl;
		cin >> ratio;
	} while (ratio <= 0.0);
	
	
	unsigned int number_of_neurons(4);
	for(unsigned int i(0); i < number_of_neurons; ++i){
		if(i<=2){										//les neurones d'indice 0-2499 sont inhibitory et env
			Neuron* A = new Neuron(i, g, false, true, ratio);
			neurons_.push_back(A);
		}
		else if(i>2 and i<=3 ){									//les neurones d'indice  2500-13499 sont excitatory et env
			Neuron* A = new Neuron(i, g, true, true, ratio);
			neurons_.push_back(A);
		}
		else if(i>3){
			Neuron* A = new Neuron(i, g, true, false, ratio);		//ceux d'indice 12500-13499 sont le background (pas env mais excitatory)
			neurons_.push_back(A);
		}
	}
	/*
	//CREATION DES NEURONES
	unsigned int number_of_neurons(13499);
	//contructeur neuron : i, g, excitatory, is_env, ratio)
	for(unsigned int i(0); i < number_of_neurons; ++i){
		if(i<=2499){										//les neurones d'indice 0-2499 sont inhibitory et env
			Neuron* A = new Neuron(i, g, false, true, ratio);
			neurons_.push_back(A);
		}
		else if(i>= 2500 and i<12500){									//les neurones d'indice  2500-13499 sont excitatory et env
			Neuron* A = new Neuron(i, g, true, true, ratio);		//(ceux d'indice 12500-13499 sont le background)
			neurons_.push_back(A);
		}
		else if(i>= 12500){									
			Neuron* A = new Neuron(i, g, true, false, ratio);		//ceux d'indice 12500-13499 sont le background (pas env mais excitatory)
			neurons_.push_back(A);
	}*/

	cout << neurons_.size() << " neurons created ! :) " << endl;
	
}


Env::~Env() {
	
	//destruction de la collection de neurones
    for (unsigned int i(0); i < neurons_.size(); ++i) {
        delete neurons_[i];
    }
	
	//réinitialise la taille de neurons_ à 0
	neurons_.clear();
}

void Env::set_connections() {
	
	//Connections entre neurones du network
	random_connection();
	//Ajout des connections avec le background
	background_connection();
	
}

void Env::random_connection() {
	//Boucle sur tous les neurones du network
	for (unsigned int i(0); i < neurons_.size(); ++i) {
		neurons_[i]->Neuron::random_connection();
	}

}

void Env::background_connection() {
	for (unsigned int i(0); i < neurons_.size(); ++i) {
		//neurons_[i]->Neuron::add_connection();
	}
	
}

//programmation des spikes selon loi de poisson selon cycle de 10 (à t=0, on dit ce qu'il se passe jusqu'a t+10)
void Env::random_spike() {
	
	double b = (time/periode);
	
	time_average_spike = (b)*periode + periode/2;
	
	cerr << "temps moyen pour loi de poisson: " << time_average_spike << endl;
		
	std::random_device rd;
    std::mt19937 gen(rd());
 
    std::poisson_distribution<> d(time_average_spike); //moyenne
		
	unsigned int number_of_neurons = neurons_.size();
	
	for (unsigned int i(0); i<= (number_of_neurons-1); ++i){
		int a (d(gen));
		if (a >= (time_average_spike + periode/2)){
			a = time_average_spike + periode/2;
		}
		if (a <= (time_average_spike - periode/2)){
			a = time_average_spike - periode/2;
		}
		
                         
		if (neurons_[i]->Neuron::is_times_spikes_empty()) { 		//premier spike  
			neurons_[i]->Neuron::times_spikes_add(a);
			cerr << "temps delivres par loi poisson: " << a << endl;
		
		} else if (!neurons_[i]->Neuron::is_times_spikes_empty()){	// faut avoir passé un certain délais depuis le dernier spike disons 4 unités de temps

			if((time - neurons_[i]->Neuron::get_time_last_spike())>=4){
				neurons_[i]->Neuron::times_spikes_add(a);
			}					
		}
	}
}

void Env::actualise() {
	
	//receive spike -> from background and network 
	//seuls les neurones de env recoivent 
	
	//pour les neurones de env
	//pour tous les neurones du backgroung et de env
	//neurons_[i]->get_spike (neurons_[j]->get_type)
	
	for (unsigned int i(0); i < neurons_.size(); ++i) {
		//lancement des spikes du background au temps t comme programmé au dessus
	
		if (neurons_[i]->Neuron::get_time_last_spike()== time){
			neurons_[i]->get_spike(i);
		}
	/*
		//pour tous les neurones de env (i)
		if (neurons_[i]->is_in_env()) {
			
			//pour tous les neurones de env et du background (j)
			for (unsigned int j(0); j < neurons_.size(); ++i) {
				
				//le neurone i recoit les spikes des neurones j auxquels il est connecté si leur potentiel est > threshold
			}
		}*/
		
	}
	
	
	//calcul du potentiel -> dans receive spike
	
	
	//send_spike
	
	
	//si a envoyé spike : calcul du potentiel et inactif
	
	
	//actif -> peut de nouveau recevoir on recommence la boucle

	
	
}

void Env::get_times_spikes(double i){
	neurons_[i]->Neuron::get_times_spikes();
	unsigned int size ((neurons_[i]->Neuron::get_times_spikes()).size());
	for (unsigned int j(0); j<= size-1; ++j){
		cerr << "neuron: " << i << " spike numero: " << j << " receptionné au temps: " << (neurons_[i]->Neuron::get_times_spikes())[j] << endl;
	}
	cerr << "For neuron " << i << " , compteur spikes : " << neurons_[i]->get_compteur() << endl;
}
		
double Env::get_time(){
	return time;
}

double Env::get_time_simu(){
	return Env::time_simu;
}

double Env::actualise_time(){
	time += 1;
	return time;
}

double Env::get_periode(){
	return Env::periode;
}

vector<Neuron*> Env::graph_fifty_neurons(){
        vector<Neuron*> fifty_neurons;
        int number;
        for(unsigned int i(0); i<50 ; ++i){
                //if (is_env == true)
                number = rand() % Neuron::env_neurons; //12500 , on ne sait pas si on peut avoir accès a env_neurons
                fifty_neurons.push_back(neurons_[number]);
        }
        return fifty_neurons;
}      
                                                                                  
vector<vector<double>> Env::spikes_list_fifty_neurons(){
        vector<vector<double>> spikes_list;
        vector<Neuron*> list_neurons(graph_fifty_neurons());
        for(unsigned int i(0); i<list_neurons.size(); ++i){
                spikes_list.push_back(list_neurons[i]->Neuron::get_times_spikes());             
                                                                                               //autre façon: get_times_spikes(list_neurons[i]->get_numero());
        }
        return spikes_list;
}

