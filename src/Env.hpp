#include <vector>
#include <iostream>
#include "neuron.hpp"

using namespace std;

class Env {
	public:
		Env(); 							//constructeur
		~Env();							//destructeur
		void random_connection();
		void random_spike();
		void actualise_time();			//ajoute une unité de tps au tps
		double get_time();
		//double get_time_simu();
		double fact(double t);
		
	private:
		vector<Neuron*> neurons_; 	//collection de neurones de l'env,
		double time;				//temps auquel on est [ms]			
		//double time_simu; 		//durée totale de la simuation
		
	public:
		const static double time_unit;	//unité de temps, 0.01ms ? 
		const static double time_simu; 	//durée totale de la simuation
};


