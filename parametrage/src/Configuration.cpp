#include <vector>
#include <iostream>  

Config::Config(int time,int excitatory_neurons, int gstrenght,double r)
: time
excitatory_neurons
gsrenght
r
{
inhibitory_neurons=excitatory_neurons/g;
inhibatory_connection = connection_probability*inhibatory_neurons;
excitatory_connection = excitatory_neurons*connection_probability;
ext_excitatory_connection = excitatory_connection;
env_neurons = inhibatory_neurons+excitatory_neurons;

  





}

~Config::Config(){}
