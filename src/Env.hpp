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
		double actualise_time();
		double get_time();
		double get_time_simu();
		double fact(double t);
		double get_periode();
		void get_times_spikes(double i);
		vector<Neuron*> graph_fifty_neurons();
		vector<vector<double>> spikes_list_fifty_neurons();		//tableau pour interface graphique
		
	private:
		vector<Neuron*> neurons_; 		//collection de neurones de l'env,
		double time;					//temps t où on en est
		double time_average_spike;
					
	public:
		const static double periode;		//pour loi de poisson
 		const static double time_unit;	//unité de temps, 0.01ms ? 
 		const static double time_simu; 	//durée totale de la simuation
};



