/**
 * \file Net.h, Contains the Net class.
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
#ifndef NEURAL_NET_H
#define NEURAL_NET_H

#include <algorithm>
#include <iostream>

#include <boost/bind.hpp>

#include "neural/Helpers.h"

namespace neural {
    /**
     * \struct Net, Represents a neural network.
     *
     * \tparam InputLayer, The type of the input layer.
     * \tparam HiddenLayer, The type of the hidden layer.
     * \tparam OutputLayer, The type of the output layer.
     * \tparam InterconnectPattern, The type of the interconnect pattern.
     */
    template<class InputLayer, class HiddenLayer, class OutputLayer, class InterconnectPattern>
    struct Net {
        public:
            /**
             * \typedef InputLayer inputLayer,
             *          The type of the input layer.
             */
            typedef InputLayer inputLayer;

            /**
             * \typedef HiddenLayer hiddenLayer,
             *          Exposes the type of the hidden layer.
             */
            typedef HiddenLayer hiddenLayer;
            
            /**
             * \typedef OutputLayer outputLayer,
             *          Expose the type of the output layer.
             */
            typedef OutputLayer outputLayer;

            /**
             * Constructs a Net with the given numbers of neurons.
             *
             * \param numInput unsigned int, The number of neurons in the input layer.
             * \param numHidden unsigned int, The number of neurons in the hidden layer.
             * \param numOutput unsigned int, The number of neurons in the output layer.
             */
            Net (unsigned int numInput, unsigned int numHidden, unsigned int numOutput)
                : inputLayer_ (numInput),
                  hiddenLayer_ (numHidden),
                  outputLayer_ (numOutput) {
                InterconnectPattern::connect (inputLayer_, hiddenLayer_, outputLayer_);
            };

            /**
             * Constructs a Net from an istream.
             *
             * \param is std::istream&, The istream from which to construct the Net.
             */
            explicit Net (std::istream& is)
                : inputLayer_ (ReadInt::get (is)),
                  hiddenLayer_ (ReadInt::get (is)),
                  outputLayer_ (ReadInt::get (is)) {
                InterconnectPattern::connect (inputLayer_, hiddenLayer_, outputLayer_);
                is >> inputLayer_ >> hiddenLayer_ >> outputLayer_;
            };

            /**
             * Returns the input layer.
             *
             * \return InputLayer&, The input layer.
             */
            InputLayer& input () { return inputLayer_; };

            /**
             * Returns the hidden layer.
             *
             * \return HiddenLayer&, The hidden layer.
             */
            HiddenLayer& hidden () { return hiddenLayer_; };

            /**
             * Returns the output layer.
             *
             * \return OutputLayer&, The output layer.
             */
            OutputLayer& output () { return outputLayer_; };

            /**
             * Runs the nerual network.
             *
             * \return void.
             */
            void operator() () {
                inputLayer_ ();
                hiddenLayer_ ();
                outputLayer_ ();
            };

            /* 
             * Writes the neural network to an ostream.
             *
             * \param os std::ostream&, The ostream to which to write.
             * \param net const Net<InputLayer, HiddenLayer, OutputLayer, InterconnectPattern>&, The neural network to write.
             *
             * \return std::ostream&, A reference to the ostream.
             */
            friend std::ostream& operator<< (std::ostream& os, const Net<InputLayer, HiddenLayer, OutputLayer, InterconnectPattern>& net) {
                return os << net.inputLayer_.size () << net.hiddenLayer_.size () << net.outputLayer_.size () << net.inputLayer_ << net.hiddenLayer_ << net.outputLayer_;
            };

        protected:
            /**
             * The input layer.
             */
            InputLayer inputLayer_;

            /**
             * The hidden layer.
             */
            HiddenLayer hiddenLayer_;

            /**
             * The output layer.
             */
            OutputLayer outputLayer_;
    }; //Net
}; //neural

#endif //NEURAL_NET_H

