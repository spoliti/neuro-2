
#include <vector>

class Neuron
{
//attributs
double compteur_spikes;
vector <Neuron> neurones_voisins(10000); //je ne sais pas s'il est possible 
										//de faire un tableau de neurones 
										//à l'intérieur de la classe neuron elle meme

//methodes
//constructeur destructeur?

void recoit_spike();
};

#endif 
