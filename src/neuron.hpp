#ifndef NEURON_H
#define NEURON_H

#include <array>
#include <vector>
#include <iostream>


/*!
 * @class Class Neuron
 *
 * @brief Class description
 */

class Neuron
{
    
public:
    //methodes
    
    //constructeur et destructeur
/*!
 * @brief Constructor of class Neuron
 * 
 * 
 *
 * @param int neuron_number
 * @param double g_
 * @param bool excitatory_
 * @param is_env
 * @param double rapport_vext_over_vthr
 * 
 *  
 **/     
    Neuron(int neuron_number_, double g_, bool excitatory_, bool is_env, double rapport_vext_over_vthr_);
/*!  
 * @brief Desctructor of neuron class
 * Delete the colection of connections
 * reinitialize the number of connections at 0
 */     
    ~Neuron();
    //getters
   
/*!
 * @brief getter for the neuron number
 * 
 * This method returns the neuron number
 *  
 * 
 * @return neuron number(int)
 * 
 **/     
    int get_numero();

/*!
 * @brief getter for excititory state
 * 
 * This method give the information if the neuron is excitatory or not
 * 
 * 
 * @return True if the neuron is an excitatory neuron, false if not (boolean)
 * 
 **/      
    bool is_excitatory();
/*! 
 * @brief getter to see if the neuron is in the environment
 * 
 * This method tells if the neuron is in the environment 
 * 
 * 
 * @return booleen value, true if the neuron is in the environment, false if not
 * 
 **/    
    bool is_in_env();
    
/*!
 * @brief getter for the spikes counter
 * 
 * 
 * @return compteur_spike value (double)
 * 
 **/         
    double get_compteur();
/*!
 * @brief getter for the potential value
 * 
 * 
 * @return potential value (double) 
 * 
 **/      
    double get_potential();
	
    double get_refractory_time();
    //autre
    void set_neuron_as_active();
	
/*! 
 * @brief Reset the potential value at the v_reset value
 * 
 * This method reset the potential value of the neuron at the v_reset value
 * The v_reset value is a static constant double value equal to 10 millivolt
 * The method also reset th e neuro in an active state
 * 
 * 
 **/    
    void reset();

/*! 
 * @brief Put the neuron in a refractory state
 * 
 * The function modify the boolean attribut active_state. Define the value as false
 * so that the neuron cannot produce a spike during a certain time(refractory time)
 * 
 * 
 **/     
    void refractory();
    
/*!
 * @brief Add connections to a vector of pointer on neurons
 * 
 * @param vector<Neuron*> neurons
 * vector of pointers on neurons
 * 
 **/    
    void random_connection(std::vector<Neuron*> &neurons);

    
    void add_connection(Neuron* neuron);

/*! 
 * @brief Method to check if a connection already exhists
 * The method scan the vector connection_ containing all connetions value to see if "number" already exists
 * 
 * @param int number representing a connection
 * 
 * @return boolean value
 * If the number of "number" already exist in connection_ the method will return false. Else return true
 * 
 **/      
    bool is_a_new_connection(int number); 	//vérifie que la connection n'existe pas déjà
	void receive_spike();
	
/*! 
 * @brief not definied yet
 * 
 * @param vector of pointers in neurons 
 * 
 **/ 	
	bool send_spike(double const& time); //ok si tps de env est en milisec 
	void affect_potential(double const& time); //ok si le tps de env est en milisec
	
	//utilisé par loi de Poisson
	
/*!
 * @brief Indicates if times_spikes is empty
 *The method looks at the size of the vector times_spikes
 * 
 * @return boolean
 * True if the size of times_spikes is 0, else False.  
 * 
 **/ 	
	bool is_times_spikes_empty();

	
/*!
 * @brief Add a value to the vector<int> times_spikes
 * 
 * @param int value representing a time for a spike (const double)
 * 
 **/ 	
	void times_spikes_add(const double time);

/*! 
 * @brief getter for times_spikes
 * 
 * @return vector<double>
 * times_spikes contains times where spikes are recieved 
 **/ 	
	double get_time_last_spike();

/*! 
 * @brief getter for times_spikes
 * 
 * @return vector<double>
 * times_spikes contains times where spikes are recieved 
 **/	
	std::vector<double> get_times_spikes();
	
/*!
 * @brief Determine if a spike is send at this time by this neuron
 * If there is a spike, the method times_add_spikes is used to add this time in the vector 
 * and the method reset() is used to change the neuron potential and to put the neuron in an active state
 * 
 * 
 * @see void Neuron::times_spikes_add(const double time)
 * void Neuron::reset(){
 * 
 * @param double type, the parameter is the time where we want to know if a spike is sended or not
 * 
 * @return true if a spike is sended, else false
 * 
 * 
 * 
 **/		

	
private:
    
    //attributs
	const int numero_neuron;
	
	int compteur_spikes; 	//nombre de spikes envoyés ?
	double potential;       //potentiel de la membrane au temps t
	bool active_state;      //true if active state, false if in refractory period
	bool is_excitatory_;	//initialisé dans constructuer de Env, true if excitatory, false if inhibitory
	bool is_in_env_;		//true si neuron dans l'environnement, false si du background
	
	std::vector<Neuron*> connections_;		//contient indices des neurones auquel l'instance est connectée
										//ie de qui l'instance peut RECEVOIR des spikes
	std::vector<double> times_spikes;	//temps auxquels les spikes sont recus
	double is_refractory_until_then; 	//temps jusqu'auquel le neurone est avec active_state = false
	//EST CE QUE LE TEMPS EST EN MILISEC ? sinon le convertir dans send_spike
	
    double g;		//relative strength of inhibitory synapses
    double v_thr;   //frequency needed for a neuron to reach threshold in absence of feedback
    double v_ext;   //external frequency (background ?)
    
    
    //constantes
public:
    //General 
	const static double v_reset;         	  	/*!< Value in millivolt */
    const static double potential_amplitude;	/*!< Value in milliVolt */
	const static int refractory_period;   		/*!< Value in millisecond */
	const static int firing_threshold;         	/*!< Value in milliVolt */
	const static double transmission_delay;    	/*!< Value millisecond */
	const static int membrane_time;             /*!< Value millisecond */
    
    //Connections
    const static double connection_probability;
    const static int excitatory_connection;    	/*!< number of excitatory connections for each neuron */
    const static int inhibatory_connection;   	/*!< number of inhibitory connections for each neuron */
    const static int ext_excitatory_connection;	/*!< number of external excitatory connections for each neuron */
	
	const static int excitatory_neurons;    	/*!< number of excitatory neurons in the network */
    const static int inhibatory_neurons;   		/*!< number of inhibitory neurons in the network */
    const static int env_neurons;				/*!< number of neuron in the environment(not from the background) */
	

};

#endif 
