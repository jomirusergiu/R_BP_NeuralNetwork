R_BP_NeuralNetwork
=================

R_BP_NeuralNetwork is a small C++ project showing how to implement Backpropagation Algorithm for neural networks.
This sample shows how to teach the neural network to learn the XOR (or exclusive) gate.
There isn't much complexity to create any application like this. Please note that I am going to post only the basics here. You will have to do the rest. 

Backpropagation, an abbreviation for "backward propagation of errors", is a common method of training artificial neural networks. From a desired output, the network learns from many 
inputs, similar to the way a child learns to identify a dog from examples of dogs.

It is a supervised learning method, and is a generalization of the delta rule. It requires a dataset of the desired output for many inputs, making up the training set. It is most useful 
for feed-forward networks (networks that have no feedback, or simply, that have no connections that loop). Backpropagation requires that the activation function used by the artificial 
neurons (or "nodes") be differentiable.

Usage
-------------

```C++
#include <iostream>
#include "R_BP_Net.h"
using namespace std;
#define PATTERN_COUNT 4
#define PATTERN_SIZE 2
#define NETWORK_INPUTNEURONS 3
#define NETWORK_OUTPUT 1
#define HIDDEN_LAYERS 0
#define EPOCHS 50000

int main()
{

    //Create some patterns
    //playing with xor
    cout << "Creating XOR Patterns" << endl;

    //XOR input values
    float pattern[PATTERN_COUNT][PATTERN_SIZE]=
    {
        {0,0},
        {0,1},
        {1,0},
        {1,1}
    };

    //XOR desired output values
    float desiredout[PATTERN_COUNT][NETWORK_OUTPUT]=
    {
        {0},
        {1},
        {1},
        {0}
    };


    R_BP_Net net;//Our neural network object
    int i,j;
    float error;
    //We create the network
    cout << "Creating Neural Network" << endl;
    net.create(PATTERN_SIZE,NETWORK_INPUTNEURONS,NETWORK_OUTPUT,HIDDEN_LAYERS,HIDDEN_LAYERS);

    //Start the neural network training, 50.000 times
    cout << "Starting neural network training [50.000 epochs]" << endl;
    for(i=0;i<EPOCHS;i++)
    {
        error=0;
        for(j=0;j<PATTERN_COUNT;j++)
        {
            error+=net.train(desiredout[j],pattern[j],0.2f,0.1f);
        }
        error/=PATTERN_COUNT;
        //display error
        cout << "ERROR:" << error << "\r";
    }
    cout << "Neural network finshed training, testing all patterns" << endl;

    //once trained test all patterns
    for(i=0;i<PATTERN_COUNT;i++)
    {

        net.propagate(pattern[i]);

    //display result
        cout << "TESTED PATTERN " << i << " DESIRED OUTPUT: " << *desiredout[i] << " NET RESULT: "<< net.getOutput().neurons[0]->output << endl;
    }


    return 0;
}
```

```BASH
$ g++ main.cpp
$ ./a.out
```

You can change the precision level of final outputs by changing the number of epochs.

```BASH
[rockk@arch Demo]$ g++ main.cpp
[rockk@arch Demo]$ ./a.out 
Creating XOR Patterns
Creating Neural Network
Starting neural network training [50.000 epochs]
Neural network finshed training, testing all patterns
TESTED PATTERN 0 DESIRED OUTPUT: 0 NET RESULT: 0.0136057
TESTED PATTERN 1 DESIRED OUTPUT: 1 NET RESULT: 0.984795
TESTED PATTERN 2 DESIRED OUTPUT: 1 NET RESULT: 0.983194
TESTED PATTERN 3 DESIRED OUTPUT: 0 NET RESULT: 0.0125526
```

License
--------

This code is under the BSD license.
