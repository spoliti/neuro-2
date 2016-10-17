#ifndef NEURON_H
#define NEURON_H
#include <array>

class Neuron
{
    
public:
    //methodes
    
    //constructeur et destructeur
    Neuron(int neuron_number_, double g_, double rapport_vext_over_vthr_);
    ~Neuron();
    //getters
    int get_numero();
    double get_compteur();
    double get_potentiel();
    void reset();
    void refractory();
    void random_connection();
    void add_connection(int indice_tab, int neuron_number);
    
private:
    
    //attributs
	const int numero_neuron;
	double compteur_spikes; //nombre de spikes envoyés ? -> int ?
	double potential;       //potentiel de la membrane au temps t
	bool active_state;      //true if active state, false if in refractory period
	std::array<int, 1250> connections_;	//tab contenant les indices des neurones auquel l'instance est connectée
	//modifier la taille si on compte les connections avec le background (à 2250) 
 
    double g;		//relative strength of inhibitory synapses
    double v_thr;   //frequency needed for a neuron to reach threshold in absence of feedback
    double v_ext;   //external frequency (background ?)
    
    
    //constantes
public:
    //General 
	const static double v_reset;         	  	//[milliVolt]
    const static double potential_amplitude;	//[milliVolt]
	const static int refractory_period;   		//[milliseconde]
	const static int firing_threshold;         	//[milliVolt]
	const static double transmission_delay;    	//[milliseconde]
	const static int membrane_time;             //[milliseconde]
    
    //Connections
    const static double connection_probability;
    const static int excitatory_connection;    	//nb of excitatory connections for each neuron
    const static int inhibatory_connection;   	//nb of inhibitory connections for each neuron
    const static int ext_excitatory_connection;	//nb of external excitatory connections for each neuron
	
	const static int excitatory_neurons;    	//nb of excitatory neurons in the network
    const static int inhibatory_neurons;   		//nb of inhibitory neurons in the network
    
	

};

#endif 
