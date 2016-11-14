#ifndef ENV_H
#define ENV_H

#include <vector>
#include <iostream>  
#include "neuron.hpp"

using namespace std;


/*!
 * @class Env
 * 
 * @brief This class has a set of neurons, from the network and the background. This class allows to create connections between all these neurons during a simulation time. 
 */
class Env {
	public:
		/*!
		 * @brief Constructor
		 */
		Env(); 					
		
		/*!
		 * @brief Destructor
		 * 
		 * Destroys the collection of neurons and resets the size of the neurons to 0.
		 * 
		 * @see Env::neuron.clear()
		 */
		~Env();							
		
		/*!
		 * @brief Creates the connections within the neuron network.
		 * 
		 * Generation of connections with the neurons in the network and the neurons of the background.
		 * 
		 * @see Env::random.connection()
		 * @see Env::background.connection()
		 */
		void set_connections();
		
		/*!
		 * @brief Creates random connections between the neurons of the network.
		 * 
		 * @see Neuron::random.connection()
		 */
		void random_connection();		
		
		/*!
		 * @brief Creates connections between the neurons of the network and the neurons of the background. 
		 *
		 * Connections with the neurons of the background are modeled by the number of the neurons of the background, from 12500 to 13499 in normal conditions.
		 * For the general case : form (number of neurons in the environment) to (this number of neurons * (1+ %(nb of excitatory neurons in the network * connection probability))
		 * The second number corresponds to the number of neurons (network + background) -1. 
		 * 
		 * @see Neuron::add_connection()
		 */ 
		void background_connection();
		
		/*!
		 * @brief Programs spkikes accordind to a Poisson's law. 
		 */
		void random_spike();
		
		/*!
		 * @brief 
		 */ //actualise quoi ?
		void actualise();
		
		/*!
		 * @brief Updates the time.
		 * 
		 * Add a unit (0.01ms) to the time. 
		 * 
		 * @return The updated time. 
		 */  // unite de temps bien 0.01ms ??
		double actualise_time();
		
		/*!
		 * @brief Get the elapsed time.
		 * 
		 * @return The elapsed time. 
		 */   // get the elaped time  ??
		double get_time();
		
		/*!
		 * @brief Get the total duration of the simulation. 
		 * 
		 * @return The duration of the the simulation. 
		 */
		double get_time_simu();
		
		//Cette fonction n'est pas dans le cpp !!
		double fact(double t);
		
		/*!
		 * @brief Get the period...
		 * 
		 * This period is used for programming spikes according to a Poisson's law.
		 * 
		 * @return The period....
		 * 
		 * @see Env::random_spike()
		 */  //La periode de quoi exactement ??
		double get_periode();
		
		/*!
		 * @brief 
		 * 
		 * @param i the number of the given neuron. 
		 */   // Geter mais ne renvoie rien ? Qu'est ce que cette focntion fait ?
		void get_times_spikes(double i);
		
		/*!
		 * @brief Creates a vector of 50 randomly chosen neurons among the neurons of the network. 
		 * 
		 * @return A vector containing this 50 neurons. 
		 */
		vector<Neuron*> graph_fifty_neurons();
		
		/*!
		 * @brief Creates a vector of vector containing the randomly chosen neurons and their spikes times. 
		 * 
		 * Contains 50 randomly chosen neurons of the network, and for each of these neuron, the times he received a spike. 
		 *  
		 * @return The vector of vector of these neurons and thier spikes times. 
		 * 
		 * @see Env::graph_fifty_neurons()
		 * @see Neuron::get_times_spikes()
		 */
		vector<vector<double>> spikes_list_fifty_neurons();	
		
	private:
		vector<Neuron*> neurons_; 		//neurones du network et du background
		double time;					//temps t où on en est
		double time_average_spike;
					
	public:
		const static double periode; /*!< Period of ......... , usefull for programming random spikes. */		//periode de quoi precisement ?
 		const static double time_unit; /*!< Unit of time, 0.01ms. */	   //unité de temps, 0.01ms ? 
 		const static double time_simu; /*!< Total duration of the simulation. */
};



#endif
