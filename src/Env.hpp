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
		int actualise_time();
		int get_time();
		int get_time_simu();
		double fact(double t);
	private:
		vector<Neuron*> neurons_; 		//collection de neurones de l'env,
		int time;	
		int time_simu;	
};


