#include "neuron.hpp"
#include "Configuration.cpp"
#include <iostream>
#include <cstdlib>		//pour fonction rand()
#include <assert.h>
#include <math.h>
#include <stdio.h> //pour exp

using namespace std;

	
Neuron::Neuron(double time_simu_, int excitatory_neurons_, int neuron_number_, double g_, bool excitatory_, bool is_in_env, double ratio_)
    :Config(time_simu_, excitatory_neurons_, g_, ratio_),
    numero_neuron(neuron_number_), //initialisation du numero du neuron
    compteur_spikes_env(0.0),           //initialisation du nb de spikes a 0
    compteur_spikes_background(0.0),
    potential(v_reset),             //initialisation du potentiel a la valeur de repos
    active_state(true),             //etat de départ est actif
    is_excitatory_(excitatory_),
    is_in_env_(is_in_env),
    is_refractory_until_then(0.0)
{}

Neuron::~Neuron() {
	//vide
}
  
                   
int Neuron::get_numero(){
    return numero_neuron;
}

bool Neuron::is_excitatory() {
 	return is_excitatory_;
}

bool Neuron::is_inhibitory(){
	if(this->is_excitatory() == true){
		return false;
	}
	else{
		return true;
}
}

bool Neuron::is_in_env() {
		return is_in_env_;
}

bool Neuron::is_active_state() {
		return active_state;
}

	
bool Neuron::is_in_background() {
		bool a;
		a = this->is_in_env_;
		if( a== true){
			return false;
		}
		else{
			return true;
		}
}
	
double Neuron::get_compteur_background(){
    return compteur_spikes_background;
}

double Neuron::get_compteur_env(){
    return compteur_spikes_env;
}
	
double Neuron::get_potential(){
    return potential;
}

double Neuron::get_refractory_time() {
	return is_refractory_until_then;
}


void Neuron::set_neuron_as_active() {
	active_state = true;
}

void Neuron::set_neuron_as_inactive() {
	active_state = false;
}


void Neuron::reset(){
    //remet le potentiel du neurone a la valeur v_reset après avoir
    //envoyé un spike
    potential = v_reset;
    active_state = true;
}
	
void Neuron::refractory(){
    //rend le neurone incapable de produire un spike pendant un certain
    //temps (refractory_time)
   
   	active_state = false;
	
}


void Neuron::random_connection(vector<Neuron*> &neurons) { /// revoir accessibilité Neuron::
	  /* Pour un nombre random entre min et max :
      * a = min + rand() % (max - min + 1 );
      * exemple : nb entre 250 et 1249 : neurones excitateurs
      * a = 250 + rand() % 1000;
      */

    int number;
    
	//Connections avec les neurons inhibiteurs	
	assert(Neuron::inhibatory_connection < Neuron::inhibatory_neurons);
	
	for (unsigned int i(0); i < Neuron::inhibatory_connection; ++i) {

		do {
			number = rand() % Neuron::inhibatory_neurons;
		} while (!is_a_new_connection(number));
		
		
		if (neurons[number] != nullptr) {
			this->add_connection(neurons[number]);
		}
	}
     
    //Connections avec les neurons excitateurs
    assert(Neuron::excitatory_connection < Neuron::excitatory_neurons);
    unsigned int borne_max(Neuron::excitatory_connection +  Neuron::inhibatory_connection);
    
	for (unsigned int i(Neuron::inhibatory_connection); i < borne_max; ++i) {
		
		do {
			number = Neuron::inhibatory_neurons + rand() % Neuron::excitatory_neurons;
		} while (!is_a_new_connection(number));
		
		if (neurons[number] != 0) {
			this->add_connection(neurons[number]);
		}
	}
	
}

void Neuron::add_connection(Neuron* neuron) {
	this->connections_.push_back(neuron);
	//cout << "Neuron::add_connec neuron " << neuron << endl;
}

//vérifie que la connection n'existe pas déja 
//et que l'on ne fait pas de connection avec soi même 
bool Neuron::is_a_new_connection(int number) {
	
	for (unsigned int i(0); i < connections_.size(); ++i) {
		
		if ((number == connections_[i]->get_numero())or (number == numero_neuron)) {
			return false;
		}
		
	}
	
	return true;
}

void Neuron::receive_spike() {
	
	/* ATTENTION DANS CETTE VERSION ON RECOIT UN SPIKE DE TOUS LES NEURONS DE CONNECTIONS_ 
	 * -> créer une fonction bool qui dit si on doit recevoir un spike ou pas
	 * suivant la valeur du potentiel du neuron
	 * (pourquoi pas créer un attribut de neuron bool can_send_spike
	 */
	
	/* Modifier le calcul du potentiel suivant la formule
	 * rajouter des arguments dans la fonction si besoin
	 */
	
	bool isExcitatory(true);
	
	for (unsigned int i(0); i <= connections_.size(); ++i) {
	
		if (connections_[i] != nullptr) {
			isExcitatory = connections_[i]->is_excitatory(); 
		}
		
		//Recu d'un neurone inhibiteur
		if (!isExcitatory) {
		
			if (this->potential >= g*Neuron::potential_amplitude) {
				this->potential -= g*Neuron::potential_amplitude;
			
			} else if (this->potential > 0) {
				this->potential = 0;
			} 
			
			/* dans les autres cas il ne se passe rien 
			 * (en considérant que le potentiel ne peux pas etre negatif)
			 * sinon mettre une limite minimale autre que 0 
			 */
		}
	
		//Recu d'un neurone excitateur (du network ou externe)
		if (isExcitatory) {
			this->potential += Neuron::potential_amplitude;
		}
		
		compteur_spikes_background += 1;
	} 
}

bool Neuron::is_times_spikes_env_empty() {
	if (times_spikes_env.size() == 0) {
		return true;
	}
	return false;
}

bool Neuron::is_times_spikes_background_empty() {
	if (times_spikes_background.size() == 0) {
		return true;
	}
	return false;
}

void Neuron::times_spikes_env_add(const double time){		
	//cerr << "ADD SOMETHING TO TIMES_SPIKES" << endl;
	//compteur_spikes += 1;
	//pour avoir des valeurs justes pour loi poisson, compter ici
	
	times_spikes_env.push_back(time);
}

void Neuron::times_spikes_background_add(const double time){		
	//cerr << "ADD SOMETHING TO TIMES_SPIKES" << endl;
	//compteur_spikes += 1;
	//pour avoir des valeurs justes pour loi poisson, compter ici
	
	this->times_spikes_background.push_back(time);
}

double Neuron::get_time_last_spike_env(){
	int b(times_spikes_env.size());
	return times_spikes_env[b-1];
}

double Neuron::get_time_last_spike_background(){
	int b(times_spikes_background.size());
	return times_spikes_background[b-1];
}

vector<double> Neuron::get_times_spikes_env(){
	return times_spikes_env;
}

vector<double> Neuron::get_times_spikes_background(){
	return times_spikes_background;
}


//marquer si à un temps donné un spike est envoyé depuis le neuron en consideration
void Neuron::reset_after_spike(double const& time) {
	
	//voir si l utilisation du delay de transmission est juste
	if (time>=2){ //si depassement à time ==1, on fait le 1er reset à time == 2
		//cout << "valeur du potentiels: " << this->list_potential[time-2] << " au temps :" << time << endl;
		
		//if(this->list_potential[time-2]>=firing_threshold) {			//la premiere valeur de la liste correspond à time ==1 pour indice 0.
		if(this->list_potential[time-2]>=firing_threshold) {
		
		
		
		//times_spikes_env_add(time - (Neuron::transmission_delay/0.1));   // ATTENTION LA CONSTANTE 0.1 EST TIME_UNIT dans ENV
		//times_spikes_env_add(time);
		this->potential = v_reset;
		this->list_potential.push_back(potential);
		this-> seuil_depassement = true;
		this->active_state = false;
		this->is_refractory_until_then = time + (Neuron::refractory_period/0.1); //ATTENTION AU 0.1
		
		if(this->numero_neuron==180){
		cout << "seuil dépassé" << "au temps: " << time << endl;
		cout << "apres depassement" << " l'attribut potentiel vaut: " << this-> potential << endl;
		}
	}
	}
}

void Neuron::find_spikes_and_calculate_intermediary_potential(double const& time) {
	int number_spikes_e(0);
	int number_spikes_i(0);
	int number_spikes_b(0);
	//int spike_contributions(0);
	
	//envoie de spikes entre les neuronnes
	//parcourt le tableau de neurones connectés a l'instance et compte ceux qui envoyent un spike au temps courant
	for(unsigned int i(0); i<connections_.size(); i++) {	
		//on s'occupe des spikes entre neurones
				if(connections_[i]->is_in_env()){
					if(connections_[i]->is_excitatory()) {
						if(connections_[i]->potential >=firing_threshold){ //OOOOOOuand ON A ENVOYE TOUS LES SPIKES IL FAUT METTRE LES POTENYIELS DE TOUS LES NEUR A RESET§§§§§§§§§§§
						++number_spikes_e;
						}
					}
				else if(connections_[i]->is_inhibitory()) {
					
					if(connections_[i]->potential >=firing_threshold){ //OOOOOOuand ON A ENVOYE TOUS LES SPIKES IL FAUT METTRE LES POTENYIELS DE TOUS LES NEUR A RESET§§§§§§§§§§§
						++number_spikes_i;
						}
						
					}
				}			
		//on s'occupe des spikes deu background
				if(connections_[i]->is_in_background()) {
					
					//TROUVER LA CONDITION SI LE NEURONE VEUT ENVOYER UN SPIJE
					if(connections_[i]-> times_spikes_background.size() != 0){
						for(unsigned int j(0); j< connections_[i]->times_spikes_background.size(); ++j){
							
							//cout<< "les temps : " << connections_[i]->times_spikes_background[j] << endl;
							if(connections_[i]->times_spikes_background[j]==time){
								number_spikes_b = number_spikes_b +1;
								/*
								if(this->numero_neuron==23){
									cout << "b: "<< number_spikes_b << endl; 
								}*/
							}
						}
					}
		}
	
}
	/*
	if(this->numero_neuron==180){
	cout << "b definitif de 180: " << number_spikes_b << endl;
	}*/
	
	if(this->numero_neuron==180){
	cout << "e definitif de 180: " << number_spikes_e << endl;
	cout << "i definitif de 180: " << number_spikes_i << endl;
	}	
	
	
	if(this->numero_neuron==2501){
	cout << "e definitif de 2501: " << number_spikes_e << endl;
	cout << "i definitif de 2501: " << number_spikes_i << endl;
	}		
	
	compteur_spikes_env += number_spikes_e + number_spikes_i; 
	compteur_spikes_background += number_spikes_b;
	
	// spike_contributions = RI(t)
	if (number_spikes_e !=0 or number_spikes_i !=0 or number_spikes_b !=0){
		to_delivery t;
		t.time = time + Neuron::transmission_delay /0.1 ;	//ATTENTION AU 0.1
		t.potential_provisory_env = number_spikes_e*potential_amplitude - number_spikes_i*g*potential_amplitude;
		t.potential_provisory_background= number_spikes_b*potential_amplitude;
		/*
		if(this->numero_neuron == 180){
		cout << "!!!!!numero du neurone: " << this->numero_neuron << " pot env: " <<t.potential_provisory_env<< "pot back: " <<t.potential_provisory_background<<  endl;
		}*/
		to_delivery_at_t.push_back(t);
	}

}



void Neuron::calculate_potential_and_give_spike_at_t(double const& time){ //A FUSIONER AVEC FONCTION AU DESSUS
	//REGLER LE PROB DU NOMBRE TAU
	
	
	if (this->seuil_depassement == false){
	//double b (2);
	// si le neurone est à un temps t ou il vient de faire reset, on ne touche pas au potentiel seuil_depassement == true;
	
	this->potential = exp(-0.1) * potential;
	
	//potential = potential - (potential/firing_threshold)*time + spike_contributions;
	/*
	if(this->numero_neuron == 23){
		cout << "numero: " << this->numero_neuron << endl;
		cout << "temps :" << time << "coucou" << endl;
	}*/
	
	int numero_t_delivery (-1);
	/*
	cout << "taille: " << this->to_delivery_at_t.size() << endl;
	cout << "time du to_delivery" << this->to_delivery_at_t[time-1].time << endl;
	cout << "numero du neurone concerné: " << this->numero_neuron;
	*/
	for(unsigned int i(0); i< this->to_delivery_at_t.size();++i){
		if (time == to_delivery_at_t[i].time){
			numero_t_delivery = i;	
			if (numero_t_delivery != -1 and this-> active_state== true){
			//le neurone doit etre actif pour recevoir un spike sinon chute de potentiel normale
		
			//Neuron::send_spike(double const& time);
			//this->potential += (to_delivery_at_t[numero_t_delivery].potential_provisory_env + to_delivery_at_t[numero_t_delivery].potential_provisory_background) * (1-exp(-2));
			this->potential += (to_delivery_at_t[numero_t_delivery].potential_provisory_env + to_delivery_at_t[numero_t_delivery].potential_provisory_background);
			}
	
		//cout << "nouveau potentiel: " << (to_delivery_at_t[numero_t_delivery].potential_provisory_env + to_delivery_at_t[numero_t_delivery].potential_provisory_background) * (1-exp(-b)) << endl;
		

	//si pas de reception spikes en vue, chute normale de V
	
	//ATTENTION LE 1 CORRESPOND A 0.1 *10
	}		
	
}

this->list_potential.push_back(potential);
	/*
	if(this->numero_neuron==180){
		cout << "potentiel a ajouter: " << potential << endl;
		cout<< "size à 180: " << (this->list_potential).size() << endl;
		cout<< "dernier potentiel ajouté à 180: " << this->list_potential[(this->list_potential).size()-1] << endl;
	}*/
	}
else{
	(this->seuil_depassement = false);
	/*
	if (this->numero_neuron == 180){
	cout << "ON A PAS FAIT DE CALCUL CAR RESET ET RETOUR A LA NORMAL" << endl;
	}*/
}
}

vector<Neuron*> Neuron::get_connections_(){
	return this->connections_;
}

vector<double> Neuron::get_list_potential(){
	return this->list_potential;
}
/****

// on fait les send à part
if(connections_[i]->send_spike(time)) {

void Neuron::calculate_potential_env(double const& time)

potential_provisory = potential - (potential/firing_threshold)*time + spike_contributions;

void Neuron::affect_potentiel(){
	
}****/

/* if (numero_neuron == neurons[i]->connections[j]->numero_neuron) {//envoie du spike à i}
 * avec i parcourant tous les neurones de Env
 * et j parcourant le tableau de connection du neurone i
 */
