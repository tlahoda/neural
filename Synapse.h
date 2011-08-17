/**
 * \file Synapse.h, Contains the Synapse class.
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
#ifndef NEURAL_SYNAPSE_H
#define NEURAL_SYNAPSE_H

#include <cstdlib>
#include <iostream>

namespace neural {
    /**
     * \struct Synapse, Represents a synapse.
     */
    struct Synapse {
        /**
         * Constructs a Synapse.
         */
        Synapse () : val_ (0.0f), weight_ (0.4f / (float)((rand () % 10) + 1)) {};

        /**
         * Calculates the weight of the synapse.
         *
         * \param input float, The synapse input.
         *
         * \return void.
         */
        void operator() (float input) {
            val_ = input * weight_;
        };

        /**
         * Returns the value of the synapse.
         *
         * \return float, The value.
         */
        float val () const { return val_; };

        /**
         * Returns the weight of the synapse.
         *
         * \return float, The weight.
         */
        float weight () const { return weight_; };

        /**
         * Adjust the weight of the synapse.
         *
         * \param w float, The weight to which to set the synapse's weight.
         *
         * \return void.
         */
        void adjust (float w) {
            weight_ = w;
        };

        /**
         * Reads a Synapse from an istream.
         *
         * \param is std::istread, The istream from which to read.
         * \param synsapse Synapse&, The Synapse to read.
         *
         * \return std::istream&, A references to the istream.
         */
        friend std::istream& operator>> (std::istream& is, Synapse& synapse) {
            return is >> synapse.weight_;
        };

        /**
         * Writes a Synapse to an ostream.
         *
         * \param os std::ostream&, The ostream to which to write the Synapse.
         * \param synapse const Synapse&, The Synaspe to write.
         *
         * \return std::ostream&, A reference to the ostream.
         */
        friend std::ostream& operator<< (std::ostream& os, const Synapse& synapse) {
            return os << synapse.weight_;
        };

        private:
            /**
             * The Synapse's value.
             */
            float val_;
            
            /**
             * The weight of the Synapse.
             */
            float weight_;
    }; //Synapse
}; //neural

#endif //NEURAL_SYNAPSE_H

