#include "Neurone.hpp"
#include "Env1.hpp"
#include <iostream>
#include <vector>
using namespace std;


Env1::Env1(){
	int n;
	cout << "How many neurons?" << endl;
	cin >> n;
	
	number_of_neurons = n;
	
	for(int i(0); i < number_of_neurons; ++i){
		Neurone A ();
		//cout << A.numero << endl;
		Neurones.push_back(A);
		cout << Neurones[0].numero << endl; // c'est ici que j'aimerai creer les neurones en appelant le constructeur des neurones, mais je trouve plus comment faire
		
		}
}



int main(){
	Env1(); // ici on appelera le constructeur de env pour crer des neurones
	
return 0;
}

/*
Neurone* Env1::addNeurone() {
		
		Neurone *neurone = new Neurone(*this);
		return neurone;
} 
*/
