#include "neuron.hpp"
#include "Configuration.hpp"
#include <iostream>
#include <cstdlib>		//pour fonction rand()
#include <assert.h>

using namespace std;

	
Neuron::Neuron(double time_simu_, int excitatory_neurons, int neuron_number_, double g_, bool excitatory_, bool is_in_env, double ratio_)
    :Config(time_simu_, excitatory_neurons, g, ratio_),
    numero_neuron(neuron_number_), //initialisation du numero du neuron
    compteur_spikes(0.0),           //initialisation du nb de spikes a 0
    potential(v_reset),             //initialisation du potentiel a la valeur de repos
    active_state(true),             //etat de départ est actif
    is_excitatory_(excitatory_),
    is_in_env_(is_in_env),
    is_refractory_until_then(0.0)
{}

Neuron::~Neuron() {
	//vide
}
  
                   
int Neuron::get_numero(){
    return numero_neuron;
}

bool Neuron::is_excitatory() {
 	return is_excitatory_;
}

bool Neuron::is_in_env() {
		return is_in_env_;
}
	
double Neuron::get_compteur(){
    return compteur_spikes;
}
	
double Neuron::get_potential(){
    return potential;
}

double Neuron::get_refractory_time() {
	return is_refractory_until_then;
}


void Neuron::set_neuron_as_active() {
	active_state = true;
}

void Neuron::reset(){
    //remet le potentiel du neurone a la valeur v_reset après avoir
    //envoyé un spike
    potential = v_reset;
    active_state = true;
}
	
void Neuron::refractory(){
    //rend le neurone incapable de produire un spike pendant un certain
    //temps (refractory_time)
   
   	active_state = false;
	
}


void Neuron::random_connection(vector<Neuron*> &neurons) {
	  /* Pour un nombre random entre min et max :
      * a = min + rand() % (max - min + 1 );
      * exemple : nb entre 250 et 1249 : neurones excitateurs
      * a = 250 + rand() % 1000;
      */
    
    int number;
    
	//Connections avec les neurons inhibiteurs	
	assert(inhibatory_connection < inhibatory_neurons);
	for (unsigned int i(0); i < inhibatory_connection; ++i) {

		do {
			number = rand() % inhibatory_neurons;
		} while (!is_a_new_connection(number));
		
		
		if (neurons[number] != nullptr) {
			this->add_connection(neurons[number]);
		}
	}
     
    //Connections avec les neurons excitateurs
    assert(excitatory_connection < excitatory_neurons);
    unsigned int borne_max(excitatory_connection +  inhibatory_connection);
    
	for (unsigned int i(inhibatory_connection); i < borne_max; ++i) {
		
		do {
			number = inhibatory_neurons + rand() % excitatory_neurons;
		} while (!is_a_new_connection(number));
		
		if (neurons[number] != 0) {
			this->add_connection(neurons[number]);
		}
	}
	
}

void Neuron::add_connection(Neuron* neuron) {
	this->connections_.push_back(neuron);
	//cout << "Neuron::add_connec neuron " << neuron << endl;
}

//vérifie que la connection n'existe pas déja 
//et que l'on ne fait pas de connection avec soi même 
bool Neuron::is_a_new_connection(int number) {
	
	for (unsigned int i(0); i < connections_.size(); ++i) {
		
		if ((number == connections_[i]->get_numero())or (number == numero_neuron)) {
			return false;
		}
		
	}
	
	return true;
}

/*
void Neuron::receive_spike() {
	
	 * ATTENTION DANS CETTE VERSION ON RECOIT UN SPIKE DE TOUS LES NEURONS DE CONNECTIONS_ 
	 * -> créer une fonction bool qui dit si on doit recevoir un spike ou pas
	 * suivant la valeur du potentiel du neuron
	 * (pourquoi pas créer un attribut de neuron bool can_send_spike
	 *
	
	 * Modifier le calcul du potentiel suivant la formule
	 * rajouter des arguments dans la fonction si besoin
	 *
	
	bool isExcitatory(true);
	
	for (unsigned int i(0); i <= connections_.size(); ++i) {
	
		if (connections_[i] != nullptr) {
			isExcitatory = connections_[i]->is_excitatory(); 
		}
		
		//Recu d'un neurone inhibiteur
		if (!isExcitatory) {
		
			if (this->potential >= g*Neuron::potential_amplitude) {
				this->potential -= g*Neuron::potential_amplitude;
			
			} else if (this->potential > 0) {
				this->potential = 0;
			} 
			
			 * dans les autres cas il ne se passe rien 
			 * (en considérant que le potentiel ne peux pas etre negatif)
			 * sinon mettre une limite minimale autre que 0 
			 *
		}
	
		//Recu d'un neurone excitateur (du network ou externe)
		if (isExcitatory) {
			this->potential += Neuron::potential_amplitude;
		}
		
		compteur_spikes += 1;
	} 
} */

bool Neuron::is_times_spikes_empty() {
	if (times_spikes.size() == 0) {
		return true;
	}
	return false;
}

void Neuron::times_spikes_add(const double time){		
	//cerr << "ADD SOMETHING TO TIMES_SPIKES" << endl;
	//compteur_spikes += 1;
	//pour avoir des valeurs justes pour loi poisson, compter ici
	
	times_spikes.push_back(time);
}

double Neuron::get_time_last_spike(){
	int b(times_spikes.size());
	return times_spikes[b-1];
}

vector<double> Neuron::get_times_spikes(){
	return times_spikes;
}

//marquer si à un temps donné un spike est envoyé depuis le neuron en consideration
bool Neuron::send_spike(double const& time) {
	
	//voir si l utilisation du delay de transmission est juste
	if(potential>=firing_threshold) {	
		times_spikes_add(time - transmission_delay);
		potential = v_reset;
		active_state = false;
		is_refractory_until_then = time + refractory_period;
		return true;
	}
	else return false;
}

//ok si le tps est en milisec dans Env
void Neuron::affect_potential(double const& time) {
	int number_spikes_e(0);
	int number_spikes_i(0);
	int spike_contributions(0);
	

	//parcourt le tableau de neurones connectés a l'instance et compte ceux qui envoyent un spike au temps courant
	for(unsigned int i(0); i<connections_.size(); i++) {	
		
			if(connections_[i]->send_spike(time)) {
				
				if(connections_[i]->is_excitatory()) {
					++number_spikes_e;
				} else {
					++number_spikes_i;
				}
		}
	}
	
	compteur_spikes += number_spikes_e + number_spikes_i; 
	
	// spike_contributions = RI(t)
	spike_contributions = number_spikes_e*potential_amplitude - number_spikes_i*g*potential_amplitude; 		// spike_contributions = RI(t)
	potential = potential - (potential/firing_threshold)*time + spike_contributions;
}

/* if (numero_neuron == neurons[i]->connections[j]->numero_neuron) {//envoie du spike à i}
 * avec i parcourant tous les neurones de Env
 * et j parcourant le tableau de connection du neurone i
 */

