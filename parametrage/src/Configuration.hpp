#ifndef CONFIG_H
#define CONFIG_H

#include <vector>
#include <iostream>  


//Initialisation des constantes static
class Config {
	
	public:
	Config(double time_simu_, int excitatory_neurons_, double gstrenght_ ,double r_);
	~Config();
	
	//Constantes
	
	const double v_reset;         	   		/*!< Value in millivolt */
    const double potential_amplitude;   	/*!< Value in millivolt */
	const unsigned int  refractory_period;	/*!< Value in millisecond */
	const unsigned int firing_threshold;	/*!< Value in millivolt */
	const double transmission_delay;		/*!< Value in millisecond */
	const unsigned int membrane_time;		/*!< Value in millisecond */

    const double connection_probability;	/*!< Connection probability of a neuron */
    
    const double periode;	/*!< Period of time in abstract unit, usefull for programming random spikes */
 	const double time_unit;	/*!< Unit of time, 0.1ms */ 
    
    
    //Potentiellement variables
    
    double time_simu; 	/*!< total duration of the simuation */
    double g;			/*!< relative strength of inhibitory synapses */
    double v_thr;   	/*!< frequency needed for a neuron to reach threshold in absence of feedback */
    double v_ext;   	/*!< external frequency (from the background) */
    
    unsigned int excitatory_connection;      /*!< number of excitatory connections for each neuron */
	unsigned int inhibatory_connection;      /*!< number of inhibitory connections for each neuron */
	unsigned int ext_excitatory_connection;  /*!< number of external excitatory connections for each neuron */
	
	unsigned int excitatory_neurons; 	/*!< number of excitatory neurons in the network */
    unsigned int inhibatory_neurons; 	/*!< number of inhibitory neurons in the network */
	unsigned int env_neurons;			/*!< number of neuron from the network only (not from the background) */
	unsigned int total_number_neurons; 	/*!< number of neurons in the network and in the background */

 	
 	
};

#endif

