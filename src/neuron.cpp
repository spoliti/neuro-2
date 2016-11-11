#include "neuron.hpp"
#include <iostream>
#include <cstdlib>		//pour fonction rand()

using namespace std;

//Initialisation des constantes static
	const double Neuron::v_reset(10);         	   	 //[milliVolt]
    const double Neuron::potential_amplitude(0.1);   //[milliVolt]
	const int Neuron::refractory_period(2);          //[milliseconde]
	const int Neuron::firing_threshold(20);          //[milliVolt]
	const double Neuron::transmission_delay(1.5);    //[milliseconde]
	const int Neuron::membrane_time(20);             //[milliseconde]

//NORMALEMENT 10 FOIS PLUS DE NEURONES ET DE CONNECTIONS
    const double Neuron::connection_probability(0.1);
    const int Neuron::excitatory_connection(100);       //nb of excitatory connections for each neuron
	const int Neuron::inhibatory_connection(25);        //nb of inhibitory connections for each neuron
    const int Neuron::ext_excitatory_connection(100);   //nb of external excitatory connections for each neuron
	
	const int Neuron::excitatory_neurons(1000);    //nb of excitatory neurons in the network
    const int Neuron::inhibatory_neurons(250);   	//nb of inhibitory neurons in the network
	const int Neuron::env_neurons(1250);			//nb de neurones de l'environnement (pas du background)

//Methodes
	
Neuron::Neuron(int neuron_number_, double g_, bool excitatory_, bool is_in_env, double rapport_vext_over_vthr_)
    :numero_neuron(neuron_number_), //initialisation du numero du neuron
    compteur_spikes(0.0),           //initialisation du nb de spikes a 0
    potential(v_reset),             //initialisation du potentiel a la valeur de repos
    active_state(true),             //etat de départ est actif
    is_excitatory_(excitatory_),
    is_in_env_(is_in_env),
    g(g_)                           //initialisation de g

{
    //Calcul des valeurs pour Vthr et Vext
    
    /* 
    if (potential_amplitude==0 or excitatory_connection==0 or membrane_time==0) throw string("div by 0");
    */

    v_thr = firing_threshold / (potential_amplitude * excitatory_connection * membrane_time);
    v_ext = rapport_vext_over_vthr_ * v_thr;
    
}

Neuron::~Neuron() {
	//destruction de la collection de connections
    for (unsigned int i(0); i < connections_.size(); ++i) {
        delete connections_[i];
    }
	
	//réinitialise la taille de neurons_ à 0
	connections_.clear();
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
	for (unsigned int i(0); i < Neuron::inhibatory_connection; ++i) {

		do {
			number = rand() % Neuron::inhibatory_neurons;
		} while (!is_a_new_connection(number));
		
		
		if (neurons[number] != nullptr) {
			this->add_connection(neurons[number]);
			//cerr << "neurons[number]" << neurons[number] << endl;
		}
	}
     
    //Connections avec les neurons excitateurs
    unsigned int borne_max(Neuron::excitatory_connection +  Neuron::inhibatory_connection);
    
	for (unsigned int i(Neuron::inhibatory_connection); i < borne_max; ++i) {
		
		do {
			number = Neuron::inhibatory_neurons + rand() % Neuron::excitatory_neurons;
		} while (!is_a_new_connection(number));
		
		if (neurons[number] != 0) {
			this->add_connection(neurons[number]);
		}
	}
	
}

void Neuron::add_connection(Neuron* neuron) {
	this->connections_.push_back(neuron);
	cout << "Neuron::add_connec neuron " << neuron << endl;
}

bool Neuron::is_a_new_connection(int number) {
	
	for (unsigned int i(0); i < connections_.size(); ++i) {
		
		if (number == connections_[i]->get_numero()) {
			return false;
		}
		
	}
	
	return true;
}


void Neuron::receive_spike() {
	//cerr << "RECEIVE SPIKE " << endl;
	
	/* ATTENTION DANS CETTE VERSION ON RECOIT UN SPIKE DE TOUS LES NEURONS DE CONNECTIONS_ 
	 * -> créer une fonction bool qui dit si on doit recevoir un spike ou pas
	 * suivant la valeur du potentiel du neuron
	 * (pourquoi pas créer un attribut de neuron bool can_send_spike
	 */
	
	/* Modifier le calcul du potentiel suivant la formule
	 * rajouter des arguments dans la fonction si besoin
	 */
	
	//bool isExcitatory(true);
	//cerr << "receive spike, taille connection : " << connections_.size();
	/*
	//<= PROVISOIRE
	for (unsigned int i(0); i <= connections_.size(); ++i) {
	
		//isExcitatory = connections_[i]->is_excitatory();
		
		//Recu d'un neurone inhibiteur
		if (!isExcitatory) {
		
			if (this->potential >= g*Neuron::potential_amplitude) {
				this->potential -= g*Neuron::potential_amplitude;
			
			} else if (this->potential > 0) {
				this->potential = 0;
			} */
			
			/* dans les autres cas il ne se passe rien 
			 * (en considérant que le potentiel ne peux pas etre negatif)
			 * sinon mettre une limite minimale autre que 0 
			 */
		/* }
	
		//Recu d'un neurone excitateur (du network ou externe)
		if (isExcitatory) {
			this->potential += Neuron::potential_amplitude;
		}
		
		compteur_spikes += 1;
	} */
}

void Neuron::send_spike(std::vector<Neuron*> &neurons) {
	//voir si utilise reset() et refractory()
	/* utilise neurons_ pour chercher dans tous les tableaux de connections_ si un neurone peut recevoir
	 * un spike de l'instance courante (this) 
	 * (utiliser le numero de l'instance pour l'identifier,
	 * par exemple faire dans des boucles une condition du genre 
	 * if (numero_neuron == neurons[i]->connections[j]->numero_neuron) {//envoie du spike à i}
	 * avec i parcourant tous les neurones de Env
	 * et j parcourant le tableau de connection du neurone i
	 */
	 
}

bool Neuron::is_times_spikes_empty() {
	if (times_spikes.size() == 0) {
		return true;
	}
	return false;
}

void Neuron::times_spikes_add(int x){
	//cerr << "ADD SOMETHING TO TIMES_SPIKES" << endl;
	//compteur_spikes += 1;
	//pour avoir des valeurs justes pour loi poisson, compter ici
	
	times_spikes.push_back(x);
}

double Neuron::get_time_last_spike(){
	int b(times_spikes.size());
	return times_spikes[b-1];
}

vector<double> Neuron::get_times_spikes(){
	return times_spikes;
}


