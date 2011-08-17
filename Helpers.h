/**
 * \file Helpers.h, Contains the Begin, End, ReadInt, Attach, and FullyConnected classes.
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
#ifndef NEURAL_HELPERS_H
#define NEURAL_HELPERS_H

#include <cmath>
#include <numeric>
#include <vector>

#include <boost/bind.hpp>

#include "neural/Synapse.h"

namespace neural {
    /**
     * \struct Begin, Gets the beginning of an object.
     */
    struct Begin {
        /**
         * Returns the beginning.
         *
         * \tparam T, The type of the object.
         *
         * \param t T&, The object from which to get the beginning.
         *
         * \return typename T::iterator, The beginning.
         */
        template<class T>
        static typename T::iterator get (T& t) { return t.begin (); };
    }; //Begin

    /**
     * \struct End, Gets the ending of an object.
     */
    struct End {
        /**
         * Return the end.
         *
         * \tparam T, The type of the object.
         *
         * \param t T&, The object from which to get the ending.
         *
         * \return typename T::iterator, The ending.
         */
        template<class T>
        static typename T::iterator get (T& t) { return t.end (); };
    }; //End

    /**
     * \struct ReadInt, Reads an int from an istream.
     */
    struct ReadInt {
        /**
         * Reads an int from an istream.
         *
         * \param is std::istream, The std::istream from which to read.
         *
         * \return unsigned int, The int read.
         */
        static unsigned int get (std::istream& is) {
            unsigned int temp;
            is >> temp;
            return temp;
        };
    }; //ReadInt

    /**
     * \struct Attach, Opens a Layer for attaching neurons.
     *
     * \tparam Layer, The type of the Layer to open.
     */
    template<class Layer>
    struct Attach {
        /**
         * Opens a layer for attaching neurons.
         *
         * \param layer Layer&, The layer to open.
         */
        explicit Attach (Layer& layer) : layer_ (layer) {};

        /**
         * Attaches a Neuron to the Layer.
         *
         * \tparam Neuron. The type of the neuron.
         *
         * \param neuron Neuron&, The Neuron to attach.
         *
         * \return void.
         */
        template<class Neuron>
        void operator() (Neuron& neuron) {
            std::for_each (layer_.begin (), layer_.end (), boost::bind (&Neuron::attach, neuron, boost::bind (&Layer::neuron::grab, _1)));
        };

        private:
            /**
             * The opened Layer.
             */
            Layer& layer_;
    }; //Attach

    /**
     * \struct FullyConnected, Represents a fully connected neural netowrk.
     *
     * \tparam IHAttach, The input to hidden layer attachment.
     * \tparam HOAttach, The hidden to output layer attachment.
     */
    template<class IHAttach, class HOAttach>
    struct FullyConnected {
        /**
         * Connects the input to the hidden layer and the hidden to the output layer.
         *
         * \tparam InputLayer, The input layer type.
         * \tparam HiddenLayer, The hidden layer type.
         * \tparam OutputLayer, The output layer type.
         *
         * \param inputLayer InputLayer&, The input layer.
         * \param hiddenLayer HiddenLayer&, The hidden layer.
         * \param outputLayer OutputLayer&, The output layer.
         *
         * /return void.
         */
        template<class InputLayer, class HiddenLayer, class OutputLayer>
        static void connect (InputLayer& inputLayer, HiddenLayer& hiddenLayer, OutputLayer& outputLayer) {
            std::for_each (hiddenLayer.begin (), hiddenLayer.end (), IHAttach (inputLayer));
            std::for_each (outputLayer.begin (), outputLayer.end (), HOAttach (hiddenLayer));
        };
    }; //FullyConnected
}; //neural

#endif //NEURAL_HELPERS_H

