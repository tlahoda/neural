/**
 * \file Neuron.h, Contains the Neuron class.
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
#ifndef NEURAL_NEURON_H
#define NEURAL_NEURON_H

#include <cstdlib>
#include <iostream>

namespace neural {
    /**
     * \struct Neuron, Represents a neuron.
     *
     * \tparam ActivationFunction, The type of the neuron activation function.
     * \tparam InputStructure, The type of the input structure.
     * \tparam OutputStructure, The type of the output structure.
     */
    template<class ActivationFunction, class InputStructure, class OutputStructure>
    struct Neuron : public InputStructure, public OutputStructure, private ActivationFunction {
        /**
         * \typedef InputStructure inputStructure, 
         *          Exposes the type of the input structure.
         */
        typedef InputStructure inputStructure;
        
        /**
         * \typedef OutputStructure outputStructure, 
         *          Exposes the type of the output structure.
         */
        typedef OutputStructure outputStructure;

        /**
         * Constructs a Neuron.
         */
        Neuron () 
            : InputStructure (),
              OutputStructure (),
              ActivationFunction (),
              val_ (0.0f),
              threshold_ (0.4f / (float)((rand () % 10) + 1)),
              error_ (0.0f) {};

        /**
         * Runs the neuron's activation function.
         *
         * \return void.
         */
        void operator () () {
            val_ = ActivationFunction::operator() (InputStructure::operator() () + threshold_);
            OutputStructure::operator() (val_);
        };

        /**
         * Returns the value of the neuron.
         *
         * \return float, The value of the neuron.
         */
        float val () { return val_; };

        /**
         * Returns the threshold of the neuron.
         *
         * \return float&, The threshold.
         */
        float& threshold () { return threshold_; };

        /**
         * Returns the neuron error.
         *
         * \return float&, The error.
         */
        float& error () { return error_; };

        /**
         * Reads a Neuron from an istream.
         *
         * \param is std::istream&, The istream from which to read the Neuron.
         * \param neuron Neuron<ActivationFunction, InputStructure, OutputStructure>&, The Neuron to read.
         *
         * \return std::istream&, A reference to the istream.
         */
        friend std::istream& operator>> (std::istream& is, Neuron<ActivationFunction, InputStructure, OutputStructure>& neuron) {
            return is >> static_cast<typename Neuron<ActivationFunction, InputStructure, OutputStructure>::inputStructure&> (neuron) >> neuron.threshold_;
        };

        /**
         * Writes a Neuron to an ostream.
         *
         * \param os std::ostream&, The ostream to whc=ich to write.
         * \param neuron const Neuron<ActivationFunction, InputStructure, OutputStructure>&, The Neuron to write.
         *
         * \return std::ostream&, A reference to the ostream.
         */
        friend std::ostream& operator<< (std::ostream& os, const Neuron<ActivationFunction, InputStructure, OutputStructure>& neuron) {
            return os << static_cast<const typename Neuron<ActivationFunction, InputStructure, OutputStructure>::inputStructure&> (neuron) << neuron.threshold_;
        };

        private:
            /**
             * The value of the neuron.
             */
            float val_;

            /**
             * The activation threshold.
             */
            float threshold_;
            
            /**
             * The neuron's error.
             */
            float error_;
    }; //Neuron
}; //neural

#endif //NEURAL_NEURON_H

