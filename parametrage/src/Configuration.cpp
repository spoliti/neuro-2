#include <vector>
#include <iostream>  
#include "Configuration.hpp"

Config::Config(int time ,int excitatory_neurons_, int gstrengh_ ,double ratio)
:v_reset(10),
potential_amplitude(0.1),
refractory_period(2),
firing_threshold(20),
transmission_delay(1.5),
membrane_time(20),
connection_probability(0.1),
periode(10),
time_unit(0.1),
time_simu(time),
g(gstrengh_),
excitatory_neurons(excitatory_neurons_)
{

inhibatory_neurons= (excitatory_neurons_/gstrengh_);
inhibatory_connection = connection_probability*inhibatory_neurons;

excitatory_connection = excitatory_neurons*connection_probability;
ext_excitatory_connection = excitatory_connection;
env_neurons = inhibatory_neurons+excitatory_neurons;

}

Config::~Config(){
	//vide
}

