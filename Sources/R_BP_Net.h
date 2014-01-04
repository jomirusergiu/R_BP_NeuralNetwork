//
//  R_BP_Net.cpp
//  R_BP_NeuralNetwork
//
//  Created by RocKK on 12/19/13.
//  Copyright (c) 2013 RocKK.
//  All rights reserved.
//
//  Redistribution and use in source and binary forms are permitted
//  provided that the above copyright notice and this paragraph are
//  duplicated in all such forms and that any documentation,
//  advertising materials, and other materials related to such
//  distribution and use acknowledge that the software was developed
//  by the RocKK.  The name of the
//  RocKK may not be used to endorse or promote products derived
//  from this software without specific prior written permission.
//  THIS SOFTWARE IS PROVIDED ''AS IS'' AND WITHOUT ANY EXPRESS OR
//  IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
//  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// Special thanks to Daniel Rios. Written based on his work.


#ifndef R_BP_NET_H
#define R_BP_NET_H

struct neuron
{
    float *weights; // neuron input weights or synaptic connections
    float *deltavalues; //neuron delta values
    float output; //output value
    float gain;//Gain value
    float wgain;//Weight gain value

    neuron();//Constructor
    ~neuron();//Destructor
    void create(int inputcount);//Allocates memory and initializates values
};

struct layer
{
    neuron **neurons;//The array of neurons
    int neuroncount;//Contains the total number of neurons
    float *layerinput;//The layer input
    int inputcount;//The total count of elements in layerinput

    layer();//Object constructor. Initializates all values as 0

    ~layer();//Destructor. Frees the memory used by the layer

    void create(int inputsize, int _neuroncount);//Creates the layer and allocates memory
    void calculate();//Calculates all neurons performing the network formula
};

class R_BP_Net
{
private:
    layer m_inputlayer;//input layer of the network
    layer m_outputlayer;//output layer..contains the result of applying the network
    layer **m_hiddenlayers;//Additional hidden layers
    int m_hiddenlayercount;//the count of additional hidden layers

public:
//function tu create in memory the network structure
    R_BP_Net();//Construction..initialzates all values to 0
    ~R_BP_Net();//Destructor..releases memory
    //Creates the network structure on memory
    void create(int inputcount,int inputneurons,int outputcount,int *hiddenlayers,int hiddenlayercount);

    void propagate(const float *input);//Calculates the network values given an input pattern
    //Updates the weight values of the network given a desired output and applying the backpropagation
    //Algorithm
    float train(const float *desiredoutput,const float *input,float alpha, float momentum);

    //Updates the next layer input values
    void update(int layerindex);

    //Returns the output layer..this is useful to get the output values of the network
    inline layer &getOutput()
    {
        return m_outputlayer;
    }

};

#endif // R_BP_NET_H
