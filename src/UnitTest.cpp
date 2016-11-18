#include <gtest/gtest.h>
#include <iostream>
#include "Env.hpp"
#include "neuron.hpp"
#include <vector>

using namespace std;



TEST(nb_of_neurons,TestNumberOfNeuronsCreated) {
	Env network;
	EXPECT_EQ(13500, network.number_of_neurons()) ;
}
	
TEST(graph_fifty_neurons_test, TestNumberOfNeuronsForGraph) {
	Env network;
	vector<Neuron*> vect(network.graph_fifty_neurons());
	EXPECT_EQ(50, vect.size()) ;
} 


TEST(reset,reset_potential) {
	Neuron neuron(1,1,true,true,1); //valeurs obligatoires pour création d'un neurone mais sans importance
	EXPECT_EQ(10, neuron.get_potential()) ;
}

TEST(reset, state) {
	Neuron neuron(1,1,true,true,1);
	neuron.set_neuron_as_inactive();
	neuron.reset();
	EXPECT_TRUE(neuron.is_active_state()) ;
}



TEST(basic_test_neuron,neuron_excitaroy) {
	Env network;
	vector<Neuron*> vect(network.get_neurons_());
	for (unsigned int i(2500); i<12500; ++i) {
		EXPECT_TRUE(vect[i]->is_excitatory()) ;
	}
}
 // comment avoir accès au tableau de neurones alors qu'il est privé ??
 
TEST(basic_test_neuron,neuron_inhibitory) {
	Env network;
	vector<Neuron*> vect(network.get_neurons_());
	for (unsigned int i(0); i<2500; ++i) {
		EXPECT_FALSE(vect[i]->is_excitatory()) ;
	}
}

TEST(new_connection, TestAddConnectionToNeuron) {
	Neuron neur1(1,1,true,true,1);
	Neuron neur2(1,1,true,true,1);
	Neuron* neur(&neur2);
	std::vector<Neuron*> vect(neur1.get_connections_());
	//cout << "nombre de connections de neur1: "<< vect.size() << endl;
	neur1.add_connection(neur);
	//cout << "nombre de connections de neur1: "<< vect.size() << endl;
	EXPECT_EQ(1, vect.size()) ;
}
//vérifier ici on a utliser la nouvelle méthode getconnections verifier quelle marche pour le test !!!!

	
	
int main(int ac, char* av[])
{
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}


