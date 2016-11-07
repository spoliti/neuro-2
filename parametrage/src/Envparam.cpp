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
void Env::actualise() {
	
	//Reception des spikes, seuls les neurones de env recoivent 
	for (int i(0); i < Neuron::env_neurons; ++i) { /// il faudrait changer en inibatory_neurons+excitatory_neurons????
		neurons_[i]->receive_spike();
	}
	
	//pour les neurones de env
	//pour tous les neurones du backgroung et de env
	//neurons_[i]->get_spike (neurons_[j]->get_type)
	
	for (unsigned int i(0); i < neurons_.size(); ++i) {
		//lancement des spikes du background au temps t comme programmé au dessus
	
		if (neurons_[i]->Neuron::get_time_last_spike()== time){
			//neurons_[i]->receive_spike(i);
			neurons_[i]->receive_spike();
		}
	/*
		//pour tous les neurones de env (i)
		if (neurons_[i]->is_in_env()) {
			
			//pour tous les neurones de env et du background (j)
			for (unsigned int j(0); j < neurons_.size(); ++i) {
				
				//le neurone i recoit les spikes des neurones j auxquels il est connecté si leur potentiel est > threshold
			}
		}*/
		
	}
	
//A changer dans Neuron:	
	
	//int env_neuron= inhibitory+excitatory


