#ifndef NEURON_H
#define NEURON_H
#include <vector>

class Neuron
{
//attributs
private:
	const int numero_neuron;
	double compteur_spikes;
	double potentiel;
	bool state;
	
	const static int v_reset(10); //[milliVolt]
	const static int refractory_period(2); //[milliseconde]
	const static double connection_probability(0.1);
	const static int firing_threshold(20); //[milliVolt]
	const static double transmission_delay(1.5); //[milliseconde]
	const static int membrane_time(20); //[milliseconde]
	
	static double freq_thr(); //frequency needed for a neuron to reach
								//threshold in absence of feedback
	double g; //relative strength of inhibitory synapses
	


//methodes

//constructeur
	Neuron
//getters
	int get_numero();
	double get compteur();
	double get_potentiel();
	
	
	void reset();
	void refractory();

	

};

#endif 
