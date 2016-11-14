#include <vector>
#include <iostream>  


//Initialisation des constantes static
class Config	{
	public:
	Config();
	~Config();
	
	const double v_reset(10);         	   	 //[milliVolt]
    const double potential_amplitude(0.1);   //[milliVolt]
	const int  refractory_period(2);          //[milliseconde]
	const int firing_threshold(20);          //[milliVolt]
	const double transmission_delay(1.5);    //[milliseconde]
	const int membrane_time(20);             //[milliseconde]

    double connection_probability;
    int excitatory_connection;       //nb of excitatory connections for each neuron
	int inhibatory_connection;        //nb of inhibitory connections for each neuron
	int ext_excitatory_connection;   //nb of external excitatory connections for each neuron
	
	const int excitatory_neurons;    //nb of excitatory neurons in the network
    const int inhibatory_neurons;   	//nb of inhibitory neurons in the network
	const int env_neurons(excitatory_neurons+inhibatory_neurons);			//nb de neurones de l'environnement (pas du background)
	
		
	const static double periode;		//pour loi de poisson
 	const static double time_unit;	//unité de temps, 0.01ms ? 
 	
 	static double time_simu; 	//durée totale de la simuation
 	};
