#include "neuron.hpp"
#include "Env.cpp"
#include "Configuration.hpp"
#include <iostream>
#include <vector>
#include <math.h>
#include "../lib/tclap/include/tclap/CmdLine.h" 

using namespace TCLAP; 
//using namespace std;

class Env; 

int main(int argc, char** argv) { 

	int time_simu(20), number_excitatory(10000);
	double g(4.0), ratio(2.0);
	
	try {
		
		CmdLine cmd( "My TCLAP test" );
		
//parametre temps qu on veut modifier. il peut être appleer dans le terminal grace à -t ou --time suivit de la valeur que l'on veut lui mettre. 
//le 0 est la valeur par défaut , et on a le type.
		ValueArg< int > time_simu_arg( "t", "time_simu", "Give me the time",  false, 20, "int" );
		cmd.add( time_simu_arg );
		
		ValueArg<int>number_of_excitatory_neurons_arg("ne","Excitatory", "Give me the number of excitatory neurones", false, 10000, "int");
		cmd.add(number_of_excitatory_neurons_arg);
		   
		ValueArg<double>g_arg( "g", "Relative_strength_inhibitory_synapses", "Give me g", false,4, "int");
		cmd.add(g_arg);
		 
		ValueArg<double>ratio_arg("r","ratio","Give me ratio Vext/Vthr", false,2.0, "double");
		cmd.add(ratio_arg); 
		
		cmd.parse( argc, argv ); 
										
		
		//convertir les valeurs
		time_simu = time_simu_arg.getValue();
		number_excitatory = number_of_excitatory_neurons_arg.getValue();
		g = g_arg.getValue();
		ratio = ratio_arg.getValue();
																	
	} 
	
	catch (TCLAP::ArgException &e)
	
	{ cerr << "error: " << e.error() << " for arg " << e.argId() << endl; }
	
	

	
	//Création de la simulation
	Env network(time_simu, number_excitatory, g, ratio); 
	 
	//appel de random_connection pour générer les connections
	network.Env::random_connection();


	//Mise en route de la simulation
	//int time_simu(network.Env::get_time_simu());
    
    
    for(int i(0); i <= time_simu; ++i){ //  ceci peut rester exactement comme ceci
    //for (int i(0); i < time_simu; i += Env::time_unit) {
        
        //lancement des spikes sur des cycles de 10 unités de temps (ms, s ?)
        //if(network.Env::get_time()%(network.Env::get_periode()) == 0){
        
        //modulo pour des nb doubles
        double modulo;
        modulo = fmod(network.Env::get_time(), network.Env::get_periode());

        //lancement des spikes sur des cycles de 10 unités de temps (ms, s ?)
        if (modulo == 0) {
        cerr << "temps de mise en place spikes: " << network.Env::get_time() << endl;
        network.Env::random_spike();
		}
        
        //cout<< network.Env::get_time() << endl; //pour voir le temps passer
        network.Env::actualise_time(); 
        network.Env::actualise();    
	}
    
    
    int a(1);
	network.Env::get_times_spikes(a);  //affichage des temps auquels les spikes distribués ont été recu pour neurone i
	
    int b(2);
    network.Env::get_times_spikes(b);
    
    
    return 0;
} 

	/*
	 * VOIR GESTION DES ERREURS POUR GTEST
	double g;
	do {
		cout << "Valeur de g ? (relative strengh of excitatory and inhibitory neurons, > 0) " << endl;
		cin >> g;
	} while (g <= 0.0);
	
	double ratio;
	do {
		cout << "Valeur de Vext/Vthr ? ( ratio > 0) " << endl;
		cin >> ratio;
	} while (ratio <= 0.0);
	
	cout << "Valeur de g ? (relative strengh of excitatory and inhibitory neurons, > 0) " << endl;
		cin >> g;
		if (g<=0.0) throw string ("g doit être supérieur à zéro");

	double ratio;
	cout << "Valeur de Vext/Vthr ? ( ratio > 0) " << endl;
	cin >> ratio;
	if (ratio<= 0.0) throw string ("Le ratio doit être supérieur à zéro"); 
	*/
