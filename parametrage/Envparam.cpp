//A rajouter dans Environnement


int Env::get_excitatory_neurons() {
	return Neuron::excitatory_neurons;

}	

int Env::get_inhibatory_neurons () {
	return Neuron::inhibatory_neurons;
}

/*
	unsigned int number_of_neurons=excitatory_neurons+inhibitory_neurons ;
	for(unsigned int i(0); i < number_of_neurons; ++i){
		if(i<=inhibitory_neurons){										//les neurones d'indice 0-2499 sont inhibitory
			Neuron* A = new Neuron(i, g, false, ratio);
			neurons_.push_back(A);
		}
		else if(i>= inhibitory_neurons and i<= excitatory_neurons){									//les neurones d'indice  2500-13499 sont excitatory
			Neuron* A = new Neuron(i, g, true, ratio);		//(ceux d'indice 12500-13499 sont le background)
			neurons_.push_back(A);
		} else {
		 Neuron A = new Neuron(i, g, true, false, ratio);		//ceux d'indice 12500-13499 sont le background (pas env mais excitatory)
		neurons_.push_back(A);
		 }
	}*/ 
  //la modification tu tableau


