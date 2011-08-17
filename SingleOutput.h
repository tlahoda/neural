/**
 * \file SingleOutput.h, Contains the SingleOutput class.
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
#ifndef NEURAL_SINGLEOUTPUT_H
#define NEURAL_SINGLEOUTPUT_H

namespace neural {
    /**
     * \struct SingleOutput, Represents a single output connection to a Neuron.
     */
    struct SingleOutput {
        /**
         * Constructs a SingleOutput.
         */
        SingleOutput () : output_ (0.0f) {};

        /**
         * Returns the output.
         *
         * \return float, The output.
         */
        float output () { return output_; };

        protected:
            /**
             * Sets the output from the activation.
             *
             * \param activation float, The activation level.
             *
             * \return void.
             */
            void operator () (float activation) {
                output_ = activation;
            };

        private:
            /**
             * The output.
             */
            float output_;
    }; //SingleOutput
}; //neural

#endif //NEURAL_SINGLEOUTPUT_H

