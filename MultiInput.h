/**
 * \file MultiInput.h, Contains the MultiInput class.
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
#ifndef NEURAL_MULTIINPUT_H
#define NEURAL_MULTIINPUT_H

#include <vector>
#include <iostream>
#include <algorithm>

#include <boost/shared_ptr.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>

#include "neural/Synapse.h"

namespace neural {
    /**
     * \struct MultiInput, Represents multiple synaptic inputs to a Neuron.
     */
    struct MultiInput {
        /**
         * typedef std::vector<boost::shared_ptr<Synapse> >::iterator iterator,
         *         Exposes the type of the synapse iterator.
         */
        typedef std::vector<boost::shared_ptr<Synapse> >::iterator iterator;

        /**
         * Constructs a MultiInput.
         */
        MultiInput () : inputs_ () {};

        /**
         * Attaches a Synapse.
         *
         * \param synapse boost::shared_ptr<Synapse>&, The Synapse to attach.
         *
         * \return void.
         */
        void attach (const boost::shared_ptr<Synapse>& synapse) {
            inputs_.push_back (synapse);
        };

        /**
         * The beginning of the synapses.
         *
         * \return iterator, The beginning.
         */
        iterator begin () { return inputs_.begin (); };
        
        /**
         * The end of the synapse.
         *
         * \return iterator, The end.
         */
        iterator end () { return inputs_.end (); };

        /**
         * Reads a MultiInput from an istream.
         *
         * \param is std::istream&, The istream from which to read.
         * \param mi MultiInput&, The MultiInput to read.
         *
         * \return std::istream&, A reference to the istream.
         */
        friend std::istream& operator>> (std::istream& is, MultiInput& mi) {
            std::for_each (mi.inputs_.begin (), mi.inputs_.end (), is >> *boost::lambda::_1);
            return is;
        };

        /**
         * Writes a MultiInput to an ostream.
         *
         * \param os std::ostream&, The ostream to which to write.
         * \param mi const MultiInput&, The MultiInput to write.
         *
         * \return std::ostream&, A reference to the ostream.
         */
        friend std::ostream& operator<< (std::ostream& os, const MultiInput& mi) {
            std::for_each (mi.inputs_.begin (), mi.inputs_.end (), os << *boost::lambda::_1 << ' ');
            return os;
        };

        protected:
            /**
             * Calculates the sum of the inputs.
             *
             * \return float, The sum of the inputs.
             */
            float operator () () {
                float sum = 0.0f;
                std::for_each (inputs_.begin (), inputs_.end (), sum += boost::lambda::bind (&Synapse::val, boost::lambda::bind (&boost::shared_ptr<Synapse>::get, boost::lambda::_1)));
                return sum;
            };

        private:
            /**
             * The input synapses.
             */
            std::vector<boost::shared_ptr<Synapse> > inputs_;
    }; //MultiInput
}; //neural

#endif //NEURAL_MULTIINPUT_H

