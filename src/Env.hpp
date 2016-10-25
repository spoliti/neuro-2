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
		void actualise();
		int actualise_time();
		int get_time();
		int get_time_simu();
		double fact(double t);
		int time_average_spike;
		int get_periode();
		void get_times_spikes(int i);
	private:
		vector<Neuron*> neurons_; 		//collection de neurones de l'env,
		int time;	
		int time_simu;
		int periode;	
};



