/**
 * \file ThreeLayerTopology.h, Contains the ThreeLayerTopology class.
 * 
 * Copyright (C) 2005 Thomas P. Lahoda
 * 
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#ifndef NEURAL_THREELAYERTOPOLOGY_H
#define NEURAL_THREELAYERTOPOLOGY_H

#include "neural/ActivationFunctions.h"
#include "neural/IntResponse.h"
#include "neural/StringResponse.h"
#include "neural/StringStimulus.h"
#include "neural/SingleInput.h"
#include "neural/MultiInput.h"
#include "neural/SingleOutput.h"
#include "neural/MultiOutput.h"
#include "neural/Neuron.h"
#include "neural/Layer.h"
#include "neural/Net.h"
#include "neural/BackPropagation.h"
#include "neural/Helpers.h"

namespace neural {
    /**
     * \struct ThreeLayerTopology, Represents a three layer brain topology.
     */
    struct ThreeLayerTopology {
        /**
         * \typedef StringStimulus Stimulus,
         *          The Brain's stimulus type.
         */
        typedef StringStimulus Stimulus;

        /**
         * \typedef StringResponse Response,
         *          The Brain's response type.
         */
        typedef StringResponse Response;

        /**
         * \typedef Neuron<Linear, SingleInput, MultiOutput> InputNeuron,
         *          The input layer neuron type.
         */
        typedef Neuron<Linear, SingleInput, MultiOutput> InputNeuron;

        /**
         * \typedef Neuron<Logistic, MultiInput, MultiOutput> HiddenNeuron,
         *          The hidden layer neuron type.
         */
        typedef Neuron<Logistic, MultiInput, MultiOutput> HiddenNeuron;

        /**
         * \typedef Neuron<Linear, MultiInput, SingleOutput> OutputNeuron,
         *          The output layer neuron type.
         */
        typedef Neuron<Linear, MultiInput, SingleOutput> OutputNeuron;

        /**
         * \typedef Layer<InputNeuron> InputLayer,
         *          The input layer type.
         */
        typedef Layer<InputNeuron> InputLayer;

        /**
         * \typedef Layer<HiddenNeuron> HiddenLayer,
         *          The hidden layer type.
         */
        typedef Layer<HiddenNeuron> HiddenLayer;

        /**
         * \typedef Layer<OutputNeuron> OutputLayer,
         *          The output layer type.
         */
        typedef Layer<OutputNeuron> OutputLayer;

        /**
         * \typedef BackPropagation LearningAlgorithm,
         *          The type of the learning algorithm.
         */
        typedef BackPropagation LearningAlgorithm;

        /**
         * \typedef FullyConnected<Attach<InputLayer>, Attach<HiddenLayer> > interconnectPattern,
         *          The neuron interconnect pattern.
         */
        typedef FullyConnected<Attach<InputLayer>, Attach<HiddenLayer> > interconnectPattern;

        /**
         * \typedef Net<InputLayer, HiddenLayer, OutputLayer, interconnectPattern> net,
         *          The neural network type.
         */
        typedef Net<InputLayer, HiddenLayer, OutputLayer, interconnectPattern> net;
    }; //ThreeLayerTopology
}; //neural

#endif //NEURAL_THREELAYERTOPOLOGY_H

