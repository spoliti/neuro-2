//#include <neuro-2/neuron.hpp>
#include "neuron.hpp"

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
	

//Methodes
	
Neuron::Neuron(int neuron_number_, double g_, double rapport_vext_over_vthr_)
    :numero_neuron(neuron_number_), //initialisation du numero du neuron
    compteur_spikes(0.0),           //initialisation du nb de spikes a 0
    potential(v_reset),             //initialisation du potentiel a la valeur de repos
    active_state(true),             //etat de départ est actif
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
	
double Neuron::get_potentiel(){
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


