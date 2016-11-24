#include <gtest/gtest.h>
#include <iostream>
#include "Env.hpp"
#include "neuron.hpp"
#include <vector>

using namespace std;

/*class EnvTest : public ::testing::Test {
 protected:
	virtual void SetUp() { 
  }
	Env network;
}; */



TEST(EnvTest,TestNumberOfNeuronsCreated) {
	Env network(10,1000, 2, 1);
	EXPECT_EQ(1600, network.number_of_neurons()) ;
	/* excitatory = 1000
	 * inhibitory = 500
	 * env neurons = 1500
	 * excitatory connection = 0.1 * 1000 = 100
	 * ext_excitatory_connection = 100
	 * total = 1600
	 *   */
}
	
TEST(EnvTest, TestNumberOfNeuronsForGraph) {
	Env network(10,1000, 2, 1);
	vector<Neuron*> vect(network.graph_fifty_neurons());
	EXPECT_EQ(50, vect.size()) ;
} 


TEST(EnvTest,neuron_excitatory) {
	Env network(10,1000, 2, 1);
	vector<Neuron*> vect(network.get_neurons_());
	for (unsigned int i(500); i<1600; ++i) {
		EXPECT_TRUE(vect[i]->is_excitatory()) ;
	}
}
 
TEST(EnvTest,neuron_inhibitory) {
	Env network(10,1000, 2, 1);
	vector<Neuron*> vect(network.get_neurons_());
	for (unsigned int i(0); i<500; ++i) {
		EXPECT_FALSE(vect[i]->is_excitatory()) ;
	}
}


TEST(new_connection, TestAddConnectionToNeuron) {
	Neuron neur1(10, 10000,1,3,true,true,1);
	Neuron neur2(10,10000,2,3,true,true,1);
	Neuron* neur(&neur2);
	cout << "nombre de connections de neur1: "<< neur1.get_connections_().size() << endl;
	neur1.add_connection(neur);
	cout << "nombre de connections de neur1: "<< neur1.get_connections_().size() << endl;
	EXPECT_EQ(1, neur1.get_connections_().size()) ;
}

TEST(new_connection, TestIsANewConnection) {
	Neuron neur1(10, 10000,1,3,true,true,1);
	Neuron neur2(10,10000,2,3,true,true,1);
	Neuron* neur2_(&neur2);
	
	EXPECT_TRUE(neur1.is_a_new_connection(neur2.get_numero()));
	neur1.add_connection(neur2_);
	EXPECT_FALSE(neur1.is_a_new_connection(neur2.get_numero()));
	EXPECT_FALSE(neur1.is_a_new_connection(neur1.get_numero()));
}


TEST(reset,reset_potential) {
	Neuron neur1(10, 10000,1,3,true,true,1); //valeurs obligatoires pour création d'un neurone mais sans importance
	EXPECT_EQ(10, neur1.get_potential()) ;
}

TEST(reset, state) {
	Neuron neur1(10, 10000,1,3,true,true,1);
	neur1.set_neuron_as_inactive();
	neur1.reset();
	EXPECT_TRUE(neur1.is_active_state()) ;
}




TEST(spike, TestReceiveSpikeFromInhibitoryNeuron) {
	Neuron neur_receive(10, 10000,1,3,true,true,1);
	Neuron neur_send(10,10000,2,3,false,true,1);
	EXPECT_EQ(10,neur_receive.get_potential()) ; // 10 est la valeur de vreset
	//neur_receive.set_potential(15);
	// valeur envoye est 0.1*3 = 0.3
	
	Neuron* neur_send_(&neur_send);
	neur_receive.add_connection(neur_send_);
	//neur_receive.receive_spike();
	
	
	//EXPECT_EQ(9.7,neur_receive.get_potential()) ; 
	}



	
	
int main(int ac, char* av[])
{
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}



