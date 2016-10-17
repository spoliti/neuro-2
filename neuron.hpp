#ifndef NEURON_H
#define NEURON_H
#include <vector>

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
    
private:
    
    //attributs
	const int numero_neuron;
	double compteur_spikes; //nombre de spikes envoyés ? -> int ?
	double potential;       //potentiel de la membrane au temps t
	bool active_state;      //true if active state, false if in refractory period
    
    /* static double g; //ne peux pas etre declaré comme static
     * car on ne connait pas sa valeur avant de créer un neurone
     */
    
    double g;				//relative strength of inhibitory synapses
    double v_thr;    //frequency needed for a neuron to reach threshold in absence of feedback
    double v_ext;    //external frequency (background ?)
    //pk erreur pour g et pas pour v_ext et v_thr ??
    
    
    //constantes
    
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
	
    
    
    /*Apparement on ne peux pas initialiser ici les valeurs static
     * il faut le faire dans le cpp en dehors de toute classe ou fonction
     * (en dehors ud main notamment )
	
	//constantes
	const static double v_reset(10);         	    //[milliVolt]
    const static double potential_amplitude(0.1);   //[milliVolt]
	const static int refractory_period(2);          //[milliseconde]
	const static int firing_threshold(20);          //[milliVolt]
	const static double transmission_delay(1.5);    //[milliseconde]
	const static int membrane_time(20);             //[milliseconde]
    
    //Connections
    const static double connection_probability(0.1);
    const static int excitatory_connection(1000);       //nb of excitatory connections for each neuron
    const static int inhibatory_connection(250);        //nb of inhibitory connections for each neuron
    const static int ext_excitatory_connection(1000);   //nb of external excitatory connections for each neuron
	
	*/
	

};

#endif 
