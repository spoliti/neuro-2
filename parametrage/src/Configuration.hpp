#ifndef CONFIG_H
#define CONFIG_H

#include <vector>
#include <iostream>  


//Initialisation des constantes static
class Config {
	public:
	Config(int time,int excitatory_neurons, int gstrenght,double r);
	~Config();
	
	//Constantes
	
	const double v_reset;         	   	//[milliVolt]
    const double potential_amplitude;   //[milliVolt]
	const int  refractory_period;       //[milliseconde]
	const int firing_threshold;         //[milliVolt]
	const double transmission_delay;    //[milliseconde]
	const int membrane_time;            //[milliseconde]

    const double connection_probability;
    
    const double periode;	//pour loi de poisson
 	const double time_unit;	//unité de temps, 0.1ms ? 
    
    
    //Potentiellement variables
    
    double time_simu; 	//durée totale de la simuation
    double g;
    
    int excitatory_connection;      //nb of excitatory connections for each neuron
	int inhibatory_connection;      //nb of inhibitory connections for each neuron
	int ext_excitatory_connection;  //nb of external excitatory connections for each neuron
	
	int excitatory_neurons; //nb of excitatory neurons in the network
    int inhibatory_neurons; //nb of inhibitory neurons in the network
	int env_neurons;		//nb de neurones de l'environnement (pas du background)
	
 	
 	
};

#endif

