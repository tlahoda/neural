/**
 * \file Brain.h, Contains the Brain class.
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
#ifndef NEURAL_BRAIN_H
#define NEURAL_BRAIN_H

#include <algorithm>

namespace neural {
    /**
     * \struct Brain, Represents a brain.
     *
     * \tparam Traits, The characteristics of the Brain.
     */
    template<class Traits>
    struct Brain {
        /**
         * Constructs a three layer brain.
         *
         * \param numInput unsigned int, The number of neurons in the input layer.
         * \param numHidden unsigned int, The number of neurons in the hidden layer.
         * \param numOutput unsigned int, The number of neurons in the output layer.
         */
        Brain (unsigned int numInput, unsigned int numHidden, unsigned int numOutput) 
          : net_ (numInput, numHidden, numOutput) {};

        /**
         * Constructs a Brain from an istream.
         *
         * \param is std::istream&, The istream from which to construct the Brain.
         */
        explicit Brain (std::istream& is)
          : net_ (is) {};

        /**
         * Returns the neural network.
         *
         * \return net typename Traits::net&, The neural network.
         */
        typename Traits::net& net () { return net_; };

        /**
         * Applies a stimulus to the Brain.
         *
         * \param stimulus const Traits::Stimulus&, The stimulus to apply.
         *
         * \return Response, The response to the stimulus.
         */
        typename Traits::Response operator() (const typename Traits::Stimulus& stimulus) {
            stimulus (net_.input ());
            net_ ();
            return typename Traits::Response (net_.output ());
        };

        /**
         * Trains a Brain.
         *
         * \param quiet const Traits::Stimulus&, The stimulus on which to train.
         * \param desired const Response& , The correct response to the stimulus.
         *
         * \return void.
         */
        void learn (const typename Traits::Stimulus& stimulus, const typename Traits::Response& desired) {
            srand ((unsigned)time (0));
            typename Traits::Response obtained (operator() (stimulus));
            //Traits::LearningAlgorithm::learn (net_, desired, obtained);
        };

        /**
         * Writes a Brain to an ostream.
         *
         * \param os std::ostream& os, The ostream to which to write.
         * \param brain const Brain&, The Brain to write.
         *
         * \return std::ostream&, A reference to the ostream.
         */
        friend std::ostream& operator<< (std::ostream& os, const Brain& brain) {
            return os << brain.net_;
        };

        private:
            /**
             * The brain's neural network.
             */
            typename Traits::net net_;
    }; //Brain
}; //neural

#endif //NEURAL_BRAIN_H

