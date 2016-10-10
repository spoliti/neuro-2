#include <neuro-2/neuron.hpp>


//constructeur destructeur?


//methodes
	
	Neuron::Neuron(int numero_neuron, double compteur_spikes,

	int Neuron:: get_numero(){
		return numero_neuron;
	}
	
	double Neuron:: get compteur(){
		return compteur_spikes;
	}
	
	double Neuron::get_potentiel(){
		return potentiel;
	}
	
	void Neuron :: reset(){
		//remet le potentiel du neurone a la valeur v_reset après avoir
		//envoyé un spike
		potentiel = v_reset;
	}
	
	void Neuron ::refractory(){
		//rend le neurone incapable de produire un spike pendant un certain
		//temps (refractory_time)
		
	}
