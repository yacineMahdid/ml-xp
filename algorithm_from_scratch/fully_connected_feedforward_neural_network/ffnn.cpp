/*
    Code created by Yacine Mahdid 2019-10-19
    Here a good explanation of backprop : https://mattmazur.com/2015/03/17/a-step-by-step-backpropagation-example/
*/

#include <iostream>

// Neuron
class Neuron{
	
	// Non-Static Variables
    private:
        // arrays
        float* weights;
        float* cacheWeights;
        // variables
        float gradient;
        float bias;
        float value = 0;

    // Static variables
    public:
	    static float minWeightValue;
	    static float maxWeightValue;

        Neuron(){

        }

    
};


int main(){
    std::cout << "TESTING" << "\n";
}