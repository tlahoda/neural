/**
 * \file SingleInput.h, Contains the SingleInput class.
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
#ifndef NEURAL_SINGLEINPUT_H
#define NEURAL_SINGLEINPUT_H

#include <iostream>

namespace neural {
    /**
     * \struct SingleInput, Represents a single input to a Neuron.
     */
    struct SingleInput {
        /**
         * Constructs a SingleInput.
         */
        SingleInput () : input_ (0.0f) {};

        /**
         * Sets the input level.
         *
         * \param in float, The input level.
         *
         * \return void.
         */
        void input (float in) { input_ = in; };

        /**
         * Read a SingleInput from an istream.
         *
         * \param is std::istream&, The istream from which to read.
         * \param si SingleInput&, The SingleInput to read.
         *
         * \return std::istream&, A reference to the istream.
         */
        friend std::istream& operator>> (std::istream& is, SingleInput& si) {
            return is >> si.input_;
        };

        /**
         * Writes a SinlgeInput to an ostream.
         *
         * \param os syd::stream&, The ostream to which to write.
         * \param si const SingleInput&, The SingleInput to write.
         *
         * \return std::ostream&, A reference to the ostream.
         */
        friend std::ostream& operator<< (std::ostream& os, const SingleInput& si) {
            return os << si.input_ << ' ';
        };

        protected:
            /**
             * Return the input level.
             *
             * /return float, The input level.
             */
            float operator () () { return input_; };

        private:
            /**
             * The input.
             */
            float input_;
    }; //SingleInput
}; //neural

#endif //NEURAL_SINGLEINPUT_H

