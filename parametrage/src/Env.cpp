#include "neuron.cpp"
#include "Env.hpp"
#include <iostream>
#include <vector>
#include <math.h>
#include <random>

using namespace std;
	

Env::Env(double time_simu_, int excitatory_neurons_, double gstrenght_, double ratio_) 
: Config(time_simu_, excitatory_neurons_, gstrenght_, ratio_),
time(0)
{
	//CREATION DES NEURONES
	//contructeur neuron : time, exci_neur, i, g, excitatory, is_env, ratio)
	for(unsigned int i(0); i < total_number_neurons; ++i){
		
		//les neurones d'indice 0-2499 sont inhibitory et env
		if(i <= inhibatory_neurons){										
			Neuron* A = new Neuron(time_simu_, excitatory_neurons_, i, gstrenght_, false, true, ratio_);
			neurons_.push_back(A);
		}
		
		//les neurones d'indice  2500-13499 sont excitatory et env
		else if(i >= inhibatory_neurons and i < env_neurons){									
			Neuron* A = new Neuron(time_simu_, excitatory_neurons_, i, gstrenght_, true, true, ratio_);		
			neurons_.push_back(A);
		}
		
		//ceux d'indice 12500-13499 sont du background (excitatory)
		else if(i>= env_neurons){									
			Neuron* A = new Neuron(time_simu_, excitatory_neurons_, i, gstrenght_, true, false, ratio_);		
			neurons_.push_back(A);
		}
	} 

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
//génération des connections pour les neurones du network (de qui on peut recevoir des spikes)
	
	cerr << "set_connections" << endl;
	
	//Connections avec les neurones du network
	random_connection();
	//Ajout des connections avec le background
	background_connection();
	
}

void Env::random_connection() {
	
	//Boucle sur tous les neurones du network
	for (unsigned int i(0); i < env_neurons; ++i) {
		
		if (neurons_[i] != 0) {
			neurons_[i]->Neuron::random_connection(neurons_);
			//cout << neurons_[i] << endl;
		}
		
	}
	
	/* pas besoin d'itérer sur les neurones du background 
	 * car on ne s'occupe pas de qui ils peuvent recevoir des spikes
	 * vu qu'ils suivent une loi de poisson
	 */
}

void Env::background_connection() {
	/* Les connections avec les neurones du background sont modélisées
	 * par les numéros du neurone du background, qui vont de 12500 à 13499 dans le cas normal
	 * cas général : 
	 * de env_neuron à env_neuron*(1 + %excitatory_neurons*connection_probability) 
	 * la borne supérieure correspond en fait à la taille de neurons_ -1
	 */
	 
	int EnvConnectionNumber;
	EnvConnectionNumber = connection_probability * env_neurons;
	
	//Pour tous les neurones du network
	for (unsigned int i(0); i < neurons_.size(); ++i) {
		
		//ajout des connections avec le background (les mêmes pour tous les neurones du network)
		for (unsigned int j(EnvConnectionNumber); j < neurons_.size(); ++j) {
			neurons_[i]->Neuron::add_connection(neurons_[j]);
		}
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
	
	//Envoie des spikes (pour neurones de env)
	for (unsigned int i(0); i < env_neurons; ++i) {
		
		if (neurons_[i] != nullptr) {
			neurons_[i]->send_spike(time);
		}
	}
	
	//rajouter envoie des spikes du background
	
	//Réception des spikes, seuls les neurones de env recoivent 
	for (unsigned int i(0); i < env_neurons; ++i) {
		if (neurons_[i]->get_refractory_time() <= time) {
			neurons_[i]->set_neuron_as_active();
		}
		//Si existe et n'est pas dans refractory period
		if ((neurons_[i] != nullptr) and (neurons_[i]->get_refractory_time() <= time)) {
			neurons_[i]->affect_potential(time);
		}
	}
	
	actualise_time();
	
	
	/*
	for (unsigned int i(0); i < neurons_.size(); ++i) {
		//lancement des spikes du background au temps t comme programmé au dessus
	
		if (neurons_[i]->Neuron::get_time_last_spike()== time){
			//neurons_[i]->receive_spike(i);
			//neurons_[i]->receive_spike();
		}
	
		//pour tous les neurones de env (i)
		if (neurons_[i]->is_in_env()) {
			
			//pour tous les neurones de env et du background (j)
			for (unsigned int j(0); j < neurons_.size(); ++i) {
				
				//le neurone i recoit les spikes des neurones j auxquels il est connecté si leur potentiel est > threshold
			}
		}
		
	} */
	
	//calcul du potentiel -> dans receive spike
	//send_spike
	/*
	for (unsigned int i(0); i < neurons_.size(); ++i) {
		if (neurons_[i]->is_in_env()) {
			for (unsigned int j(0); j < (neurons_[i].connections_).size(); ++j) {
				// envoyer spike
				
			}
			neurons_[i].potential = v_reset;		
		}
		
	}
	*/ 
	
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
	return periode;
}

vector<Neuron*> Env::graph_fifty_neurons(){
        vector<Neuron*> fifty_neurons;
        int number;
        for(unsigned int i(0); i<50 ; ++i){
                //if (is_env == true)
                number = rand() % env_neurons; //12500 , on ne sait pas si on peut avoir accès a env_neurons
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

