#include "neuron.hpp"
#include <iostream>
#include <cstdlib>		//pour fonction rand()


//Initialisation des constantes static
	const double Neuron::v_reset(10);         	   	 //[milliVolt]
    const double Neuron::potential_amplitude(0.1);   //[milliVolt]
	const int Neuron::refractory_period(2);          //[milliseconde]
	const int Neuron::firing_threshold(20);          //[milliVolt]
	const double Neuron::transmission_delay(1.5);    //[milliseconde]
	const int Neuron::membrane_time(20);             //[milliseconde]

    const double Neuron::connection_probability(0.1);
    const int Neuron::excitatory_connection(1000);       //nb of excitatory connections for each neuron
	const int Neuron::inhibatory_connection(250);        //nb of inhibitory connections for each neuron
    const int Neuron::ext_excitatory_connection(1000);   //nb of external excitatory connections for each neuron
	
	const int Neuron::excitatory_neurons(10000);    	//nb of excitatory neurons in the network
    const int Neuron::inhibatory_neurons(2500);   	//nb of inhibitory neurons in the network

//Methodes
	
Neuron::Neuron(int neuron_number_, double g_, bool excitatory_, double rapport_vext_over_vthr_)
    :numero_neuron(neuron_number_), //initialisation du numero du neuron
    compteur_spikes(0.0),           //initialisation du nb de spikes a 0
    potential(v_reset),             //initialisation du potentiel a la valeur de repos
    active_state(true),             //etat de départ est actif
    is_excitatory(excitatory_),
    last_spike(0),
    g(g_)                           //initialisation de g

{
    //Calcul des valeurs pour Vthr et Vext
    v_thr = firing_threshold / (potential_amplitude * excitatory_connection * membrane_time);
    v_ext = rapport_vext_over_vthr_ * v_thr;
    
}

Neuron::~Neuron() {
    //vide si pas d'utilisation de pointeurs
}
  
                   
int Neuron::get_numero(){
    return numero_neuron;
}
	
double Neuron::get_compteur(){
    return compteur_spikes;
}
	
double Neuron::get_potential(){
    return potential;
}
	
bool Neuron::get_type() {
	return is_excitatory;
}
	
void Neuron::reset(){
    //remet le potentiel du neurone a la valeur v_reset après avoir
    //envoyé un spike
    potential = v_reset;
}
	
void Neuron::refractory(){
    //rend le neurone incapable de produire un spike pendant un certain
    //temps (refractory_time)
   
   	active_state = false;
   		
    /*do {
		active_state = false;
		last_spike += Env::time_unit;
	} while (Env::time < last_spike + Neuron::refractory_period);
	* pb : pas de cohérence du temps (passe plus vite ici que dans env
	* et pas d'accès à Env::time dans ce fichier
	*/
	
}

void Neuron::random_connection() {
	  /* Pour un nombre random entre min et max :
      * a = min + rand() % (max - min + 1 );
      * exemple : nb entre 250 et 1249 : neurones excitateurs
      * a = 250 + rand() % 1000;
      */
     
    int number;
    
	//Connections avec les neurons inhibiteurs
	if (is_excitatory == false) {								 
		number = rand() % Neuron::inhibatory_neurons;
		this->Neuron::add_connection(numero_neuron, number);
	}
     
     //Connections avec les neurons excitateurs
	else if (is_excitatory == true) {									
		number = Neuron::inhibatory_neurons + rand() % Neuron::excitatory_neurons;
		this->Neuron::add_connection(numero_neuron, number);
	}

	
}

void Neuron::add_connection(int indice, int number) {
	this->connections_[indice] = number;
}

void Neuron::receive_spike(bool isExcitatory) {
	
	//isExcitatory est le bool du neurone qui ENVOIE le spike

	//Recu d'un neurone inhibiteur
	if (!isExcitatory) {
		
		if (this->potential >= g*Neuron::potential_amplitude) {
			this->potential -= g*Neuron::potential_amplitude;
			
		} else if (this->potential > 0) {
			this->potential = 0;
		
		}
		
		//dans les autres cas il ne se passe rien 
		//(en considérant que le potentiel ne peux pas etre negatif)
		//sinon mettre une limite minimale autre que 0 
	}
	
	//Recu d'un neurone excitateur (du network ou externe)
	if (isExcitatory) {
		this->potential += Neuron::potential_amplitude;
		compteur_spikes += 1;
	}
	
}

void Neuron::send_spike() {

	compteur_spikes += 1;
	this->reset();
	this->refractory();
	
	/* voir comment implémenter le tps pour que refractory soit appelé
	 * en boucle tant que Env::time < last_spike+Neuron::refractory_period
	 * (sachant que on n'a pas accès à time car on ne peux meme pas
	 * utiliser le getteur (on ne peux pas inclure Env ici)
	 */
}


