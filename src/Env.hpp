#include <vector>
#include <iostream>
#include "neuron.hpp"

using namespace std;

class Env {
	public:
		Env(); 							//constructeur
		~Env();							//destructeur
		void actualise_time();			//ajoute une unité de tps au tps
		double get_time();
		void random_connection();
		void random_spike();
		double fact(double t);
		void refractory_neuron();
		
		
	private:
		vector<Neuron*> neurons_; 	//collection de neurones de l'env,
		double time;				//temps auquel on est [ms]			

	public:
		const static double time_unit;	//unité de temps, 0.01ms ? 
		const static double time_simu; 	//durée totale de la simuation
};


