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
	 
	//int EnvConnectionNumber;
	//EnvConnectionNumber = connection_probability * env_neurons;
	
	//Pour tous les neurones du network
	for (unsigned int i(0); i < env_neurons; ++i) {
		
		//ajout des connections avec le background (les mêmes pour tous les neurones du network)
		for (unsigned int j(env_neurons); j < neurons_.size(); ++j) {
			if ( neurons_[j] != nullptr) {
			neurons_[i]->Neuron::add_connection(neurons_[j]);
		}
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
	
	//lancement des spikes sur des cycles de 40 unités de temps (ms, s ?)        
        
     //modulo pour des nb doubles
     double modulo;
     modulo = fmod(time,periode);

        //lancement des spikes sur des cycles de 10 unités de temps (ms, s ?)
      if (modulo == 0) {
		cerr << "temps de mise en place spikes: " << time << endl;
        this->random_spike();
	   }
	   
	 //on a le potentiel à t de chaque neuronne, les spikes aléatoires st fixés pour la période de 40
	 //il faut désormais analyser la situation, voir pour chaque neurone le total de spikes de env ou de background
	 //qu'il va recevoir  
	 for (int i(0); i < env_neurons; ++i){ /// accès des valeurs env_neurons faire attention
		neurons_[i]->find_spikes_and_calculate_intermediary_potential(time);
	
	} 
	cout << time << endl;
	
	//on passe au temps suivant
	
	actualise_time();
	
	//on est à un nouveau temps on regarde d'abord si certain neurones st à nouveau actifs
	
	for (int i(0); i < env_neurons; ++i) {
		if (neurons_[i]->get_refractory_time() < time) {
			neurons_[i]->set_neuron_as_active();
		}
	}
	
	// on met la situation à jour, les neuronnes recoivent leurs spikes calcule le potentiel à v(t+dt)
	//SEPARER LES DEUX BOUCLES FOR PAS CHANGER
	for (int i(0); i<env_neurons; ++i){ 
		neurons_[i]->Neuron::reset_after_spike(time);
		neurons_[i]->Neuron::calculate_potential_and_give_spike_at_t(time);
		 // 
	}
	
	cout << "dans l'env potentiel neur 10: " << "au temps: " << time << "est: " << neurons_[10]->get_potential() << endl;
	cout << "dans l'env potentiel neur 1100: " << "au temps: " << time << "est: " << neurons_[1100]->get_potential() << endl;

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

/*    
 A REVOIR                                                                            
vector<vector<double>> Env::spikes_list_fifty_neurons(){
        vector<vector<double>> spikes_list;
        vector<Neuron*> list_neurons(graph_fifty_neurons());
        for(unsigned int i(0); i<list_neurons.size(); ++i){
                spikes_list.push_back(list_neurons[i]->Neuron::get_times_spikes());             
                                                                                               //autre façon: get_times_spikes(list_neurons[i]->get_numero());
        }
        return spikes_list;
}

*/
/*

void Env::get_liaisons_background(int b){
	double x;
	x = (neurons_[b]-> Neuron::get_connections_()).size();
	for (int i(0); i < x; ++i){
		if ((neurons_[b]-> Neuron::get_connections_()[i])->Neuron::is_in_background()){
			
			cout<<"neurone number: "<< b << "nombre de liaisons: " << x << "numero de la liaison: "<< i << "correspond au neuronne du backgrud numero: " << (neurons_[b]->Neuron::get_connections_()[i])->get_numero() << endl;
		}
	
	}
}
*/


void Env::get_liaisons_env(int b){
	double x;
	x = (neurons_[b]-> Neuron::get_connections_()).size();
	cout<< "numero du neuronne: " << b << " nombre de liaisons: " << x << endl;
	/*
	for (int i(0); i < x; ++i){
		if ((neurons_[b]-> Neuron::get_connections_()[i])->Neuron::is_in_env()){
			
			cout<<"neurone number: "<< b << "nombre de liaisons: " << x << "numero de la liaison: "<< i << "correspond au neuronne du backgrud numero: " << (neurons_[b]->Neuron::get_connections_()[i])->get_numero() << endl;
		}
	
	}*/
}

unsigned int Env::number_of_neurons () {
	return neurons_.size();
	}

vector<Neuron*> Env::get_neurons_() {
	return neurons_;
	}
