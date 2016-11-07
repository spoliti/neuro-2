#include "neuron.hpp"
#include "Env.cpp"
#include <iostream>
#include <vector>
#include <math.h>
#include <tclap/CmdLine.h> //il faut télécharger et installer tclap
using namespace TCLAP; 
//using namespace std;

class Env; 

int main(int argc, char** argv) {
	
	
	//Création de la simulation
	//Env(); //constructeur de env pour créer des neurones
	Env network; 
	
	try {
	CmdLine cmd( "My TCLAP test" );  /// on doit mettre des valeurs dans les parenthèse? j'ai pas compris
	
									// je déclare des variables mises en paramètre
	ValueArg< int > time_simu_arg( "t", "time_simu", "Give me the time",  false, network.Env::get_time_simu(), "int" ); // c'est le parametre temps qu on veut modifier. il peut être appleer dans le terminal grace à -t ou --time suivit de la valeur que l'on veut lui mettre. le 0 est la valeur par défaut , eton a le type.
      	cmd.add( time_simu_arg );
       
									/*ValueArg< int > excitatory_neurons_arg( "ne", "excitatory_neurons", "Give me some numbers",  false, 10000,"int" ); /il faut empecher les valeurs abberrante plus valeur par défaut? get_numberofexcitatory_neurons() dans Env.
											cmd.add( excitatory_neurons_arg ); 
		
										ValueArg< int > inhibatory_neurons_arg( "ni", " inhibatory_neurons", "Give me some number", false,2500, "int" ); 
										cmd.add(  inhibatory_neurons_arg);*/
	ValueArg<int>number_of_excitatory_neurons_arg("ne","Excitatory", "Give me the totale number of excitatory neurones", false, 12500, "int");
	cmd.add(number_of_excitatory_neurons_arg);
       
     	ValueArg<int>g_arg( "g", "Relative_strength_inhibitory_synapses", false,4, "int")
   	cmd.add(g_arg);
     
  
    	MultiArg<double>ratio_arg("r","ratio","Give me ratio Vext/Vthr", false, double);
    	cmd.add(ratio_arg); 
    
	cmd.parse( argc, argv ); 
									/ est ce que je dois faire une "boucle if"? qu il me change la valeur du temps si et seulement si on a changé la valeur via ValueArg
	network.Env::time_simu=time_simu_arg.getValue();  				// va attribuer la nouvelle valeur choisie pour l'attribut temps
											/*excitatory_neurons=excitatory_neurons_arg.getValue(); / je peux déclarer le temps dans le main. Mais mes valeurs des neurones sont dans le fichier neurones, mais en plus je veux un tableau de neurones
											inhibitory_neurons=inhibatory_neurons_arg.getValue();/ qui lui est un Env.il faudrai donc un getters dans les fonctions de Env, pour de nouveau déclarer avant int excitatory_neurons(network.Env::get_neurones())*/
	
	
	network.Env::ratio = ratio_arg.getValue();
	
	network.Env::get_excitatory_neurons()= number_of_excitatory_neurons_arg.getValue();
	
	network.Env::get_inhibitory_neurons()=network.Env::get_excitatory_neurons*network.Env::g;
	
	double ratio ( network.Env::ratio);
	int excitatory_neurons(network.Env::get_excitatory_neurons());
	int inhibatory_neurons(network.Env::get_inhibatory_neurons());
	int g(network.Env::g);
	int time_simu(network.Env::get_time_simu());
	/*const int Neuron::inhibatory_connection(250);        //nb of inhibitory connections for each neuron
    const int Neuron::ext_excitatory_connection(1000); */
	

	
	
																	
	} catch (TCLAP::ArgException &e)  /// je ne suis pas sur de ou l'insérer ce try catch et je ne suis pas sur d'avoir bien "gérer" les erreurs
	
	{ std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl; }
	//appel de random_connection pour générer les connections
	network.Env::random_connection();


	//Mise en route de la simulation
    
    
    
    for(int i(0); i <= time_simu; ++i){ /  ceci peut rester exactement comme ceci
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
    
    
    int a(1);// n
	network.Env::get_times_spikes(a);  //affichage des temps auquels les spikes ont didribuées été recu pour neuronne i
	
    int b(2);
    network.Env::get_times_spikes(b);
    return 0;
} 

