#include "neuron.hpp"
#include "neuron.cpp"
#include "Env.hpp"
#include <iostream>
#include <vector>
#include <math.h>
#include <random>

using namespace std;


Env::Env() : time(0), time_simu(12), periode(10){
	
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
	
	
	unsigned int number_of_neurons(3);
	for(unsigned int i(0); i < number_of_neurons; ++i){
		if(i<=2){										//les neurones d'indice 0-2499 sont inhibitory
			Neuron* A = new Neuron(i, g, false, ratio);
			neurons_.push_back(A);
		}
		else if(i>=3 ){									//les neurones d'indice  2500-13499 sont excitatory
			Neuron* A = new Neuron(i, g, true, ratio);		//(ceux d'indice 12500-13499 sont le background)
			neurons_.push_back(A);
		}
	}
	/*
	unsigned int number_of_neurons(13499);
	for(unsigned int i(0); i < number_of_neurons; ++i){
		if(i<=2499){										//les neurones d'indice 0-2499 sont inhibitory
			Neuron* A = new Neuron(i, g, false, ratio);
			neurons_.push_back(A);
		}
		else if(i>= 2500){									//les neurones d'indice  2500-13499 sont excitatory
			Neuron* A = new Neuron(i, g, true, ratio);		//(ceux d'indice 12500-13499 sont le background)
			neurons_.push_back(A);
		}
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

void Env::random_connection() {
	//Boucle sur tous les neurones du network
	for (unsigned int i(0); i < neurons_.size(); ++i) {
		neurons_[i]->Neuron::random_connection();
	}

}

//programmation des spikes selon loi de poisson selon cycle de 10 (à t=0, on dit ce qu'il se passe jusqu'a t+10)
void Env::random_spike() {
	
	int b = (time/periode);
	
	time_average_spike = (b)*periode + periode/2;
	
	cout << "temps moyen pour loi de poisson: " << time_average_spike << endl;
		
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
		
		if (neurons_[i]->Neuron::is_times_spikes_empty() == 0){                    //premier spike        
		neurons_[i]->Neuron::times_spikes_add(a);
		cout << "temps delivres par loi poisson: " << a << endl;
		}
		
		else if (neurons_[i]->Neuron::is_times_spikes_empty() >=1){			// faut avoir passé un certain délais depuis le dernier spike disons 4 unités de temps
			if((time - neurons_[i]->Neuron::get_time_last_spike())>=4){
			neurons_[i]->Neuron::times_spikes_add(a);
			
			}					
		}
	}
}

//lancement des spikes au temps t comme programmé au dessus
void Env::actualise() {
	unsigned int number_of_neurons = neurons_.size();
	for (unsigned int i(0); i<= number_of_neurons-1; ++i){
		if (neurons_[i]->Neuron::get_time_last_spike()== time){
		neurons_[i]->get_spike(i);
		}
	}
}

void Env::get_times_spikes(int i){
	neurons_[i]->Neuron::get_times_spikes();
	unsigned int size ((neurons_[i]->Neuron::get_times_spikes()).size());
	for (unsigned int j(0); j<= size-1; ++j){
		cout << "neuron: " << i << " spike numero: " << j << " receptionné au temps: " << (neurons_[i]->Neuron::get_times_spikes())[j] << endl;
	}
}
		
int Env::get_time(){
	return time;
}

int Env::get_time_simu(){
	return time_simu;
}

int Env::actualise_time(){
	time = time + 1;
	return time;
}

int Env::get_periode(){
	return periode;
}
