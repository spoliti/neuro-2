#ifndef NEURON_H
#define NEURON_H
#include <array>

class Neuron
{
    
public:
    //methodes
    
    //constructeur et destructeur
    Neuron(int neuron_number_, double g_, bool excitatory_, double rapport_vext_over_vthr_);
    ~Neuron();
    //getters
    int get_numero();
    double get_compteur();
    double get_potential();
    bool get_type(); 			//true si excitatory, false sinon
    //autre
    void reset();
    void refractory();
    void random_connection();
    void add_connection(int indice_tab, int neuron_number);
    void get_spike(bool is_excitatory); 	//is_excitatory est le bool du neurone qui ENVOIE le spike
	
private:
    
    //attributs
	const int numero_neuron;
	int compteur_spikes; 	//nombre de spikes envoyés ?
	double potential;       //potentiel de la membrane au temps t
	bool active_state;      //true if active state, false if in refractory period
	bool is_excitatory;		//initialisé dans constructuer de Env, true if excitatory, false if inhibitory
	std::array<int, 2250> connections_;	//tab contenant les indices des neurones auquel l'instance est connectée
	//modifier la taille si on compte les connections avec le background (à 2250) -> fait
 
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
