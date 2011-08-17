/**
 * \file MultiOutput.h, Contains the MultiOutput class.
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
#ifndef NEURAL_MULTIOUTPUT_H
#define NEURAL_MULTIOUTPUT_H

#include <vector>

#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>

#include "neural/Synapse.h"

namespace neural {
    /**
     * \struct MultiOutput, Represents multiple synaptic output from a Neuron.
     */
    struct MultiOutput {
        /**
         * \typedef std::vector<boost::shared_ptr<Synapse> >::iterator iterator,
         *          Expose the type of the synapse iterator.
         */
        typedef std::vector<boost::shared_ptr<Synapse> >::iterator iterator;
        
        /**
         * Constructs a MultiOutput.
         */
        MultiOutput () : outputs_ () {};

        /**
         * Returns a new synapse.
         *
         * \return boost::shared_ptr<Synapse>, The synapse.
         */
        boost::shared_ptr<Synapse> grab () {
            boost::shared_ptr<Synapse> output (new Synapse ());
            outputs_.push_back (output);
            return output;
        };
        
        /**
         * Returns the beginning of the synapses.
         *
         * \return iterator, The beginning.
         */
        iterator begin () { return outputs_.begin (); };
        
        /**
         * Returns the end of the synapses.
         *
         * \return iterator, The end.
         */
        iterator end () { return outputs_.end (); };

        protected:
            /**
             * Sets the activation level for the synapses.
             *
             * \param activation float, The activation level.
             *
             * \return void.
             */
            void operator() (float activation) {
                std::for_each (outputs_.begin (), outputs_.end (), boost::bind (&Synapse::operator(), _1, activation));
            };

        private:
            /**
             * The output Synapses.
             */
            std::vector<boost::shared_ptr<Synapse> > outputs_;
    }; //MultiOutput
}; //neural

#endif //NEURAL_MULTIOUTPUT_H

