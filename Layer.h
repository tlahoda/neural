/**
 * \file Layer.h, Contains the basic_Layer and the Layer classes.
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
#ifndef NEURAL_LAYER_H
#define NEURAL_LAYER_H

#include <vector>
#include <algorithm>
#include <iostream>

#include <boost/lambda/lambda.hpp>
#include <boost/lambda/construct.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/bind.hpp>

namespace neural {
    /**
     * \struct basic_Layer, A base for Layers.
     */
    struct basic_Layer {};

    /**
     * \struct Layer, Represents a Layer of neurons.
     *
     * \tparam Neuron, The type of neuron.
     */
    template<class Neuron>
    struct Layer : public basic_Layer {
        /**
         * \typedef typename std::vector<Neuron>::iterator iterator,
         *          The type of the iterator.
         */
        typedef typename std::vector<Neuron>::iterator iterator;

        /**
         * \typedef typename std::vector<Neuron>::const_iterator const_iterator,
         *          The type of the const iterator.
         */
        typedef typename std::vector<Neuron>::const_iterator const_iterator;

        /**
         * \typedef Neuron neuron,
         *          The type of the neuron.
         */
        typedef Neuron neuron;

        /**
         * Constructs a Layer with a number of neurons.
         *
         * \param numNeurons unsigned int, The number of neurons.
         */
        explicit Layer (unsigned int numberOfNeurons)
            : basic_Layer (), neurons_ (numberOfNeurons) {
            std::for_each (neurons_.begin (), neurons_.end (), boost::lambda::_1 = boost::lambda::bind (boost::lambda::constructor<Neuron> ()));
        };

        /**
         * Returns the beginning of the neurons.
         *
         * \return iterator, The beginning of the neurons.
         */
        iterator begin () { return neurons_.begin (); };

        /**
         * Returns the beginning of the neurons.
         *
         * \return const_iterator, The beginning of the neurons.
         */
        const_iterator begin () const { return neurons_.begin (); };

        /**
         * Returns the end of the neurons.
         *
         * \return iterator, The end of the neurons.
         */
        iterator end () { return neurons_.end (); };

        /**
         * Returns the end of the neurons.
         *
         * \return const_iterator, The end of the neurons.
         */
        const_iterator end () const { return neurons_.end (); };

        /**
         * Returns the number of neurons.
         *
         * \return unsigned int, The number of neurons.
         */
        unsigned int size () const { return neurons_.size (); };

        /**
         * Calculates the value of each neuron.
         *
         * \return void.
         */
        void operator() () {
            std::for_each (neurons_.begin (), neurons_.end (), boost::bind (&Neuron::operator(), _1));
        };

        /**
         * Reads the Layer from an istream.
         *
         * \param is std::istream&, The istream from which to read.
         * \param layer Layer<Neuron>&, The Layer to read.
         *
         * \return std::istream&, A reference to the istream.
         */
        friend std::istream& operator>> (std::istream& is, Layer<Neuron>& layer) {
            std::for_each (layer.begin (), layer.end (), is >> boost::lambda::_1);
            return is;
        };

        /**
         * Writes a Layer to an ostream.
         *
         * \param os std::ostream&, The ostream from which to write.
         * \param layer const Layer<Neuron>&, The Layer to write.
         *
         * \return std::ostream&, A reference to the ostream.
         */
        friend std::ostream& operator<< (std::ostream& os, const Layer<Neuron>& layer) {
            std::for_each (layer.begin (), layer.end (), os << boost::lambda::_1 << ' ');
            return os;
        };

        private:
            /**
             * The Layer's neurons.
             */
            std::vector<Neuron> neurons_;
    }; //Layer
}; //neural

#endif //NEURAL_LAYER_H

