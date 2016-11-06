#ifndef NEURON_H
#define NEURON_H

#include <array>
#include <vector>
#include <iostream>

class Neuron
{
    
public:
    //methodes
    
    //constructeur et destructeur
    Neuron(int neuron_number_, double g_, bool excitatory_, bool is_env, double rapport_vext_over_vthr_);
    ~Neuron();
    //getters
    int get_numero();
    bool is_excitatory();
    bool is_in_env();
    double get_compteur();
    double get_potential();
    //autre
    void reset();
    void refractory();
    void random_connection();
    void add_connection(int neuron_number);
    bool is_a_new_connection(int number); 	//vérifie que la connection n'existe pas déjà
    void get_spike(bool isExcitatory);		//isExcitatory: bool du neurone qui ENVOIE le spike
	
	//utilisé par loi de Poisson
	bool is_times_spikes_empty();
	void times_spikes_add(int x);
	double get_time_last_spike();
	std::vector<double> get_times_spikes();
private:
    
    //attributs
	const int numero_neuron;
	
	int compteur_spikes; 	//nombre de spikes envoyés ?
	double potential;       //potentiel de la membrane au temps t
	bool active_state;      //true if active state, false if in refractory period
	bool is_excitatory_;	//initialisé dans constructuer de Env, true if excitatory, false if inhibitory
	bool is_in_env_;		//true si neuron dans l'environnement, false si du background
	
	std::vector<int> connections_;		//contient indices des neurones auquel l'instance est connectée
										//ie de qui l'instance peut RECEVOIR des spikes
	std::vector<double> times_spikes;	//temps auxquels les spikes sont recus
	
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
    const static int env_neurons;				// nb de neurones de l'environnement (pas du background)
	

};

#endif 
