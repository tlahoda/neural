/**
 * \file ActivationFunctions.h, Contains the Linear and Logistic classes.
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
#ifndef NEURAL_ACTIVATIONFUNCTIONS_H
#define NEURAL_ACTIVATIONFUNCTIONS_H

#include <cmath>

namespace neural {
    /**
     * \struct Linear, Represents a linear function.
     */
    struct Linear {
        /**
         * A Linear function, output = input.
         *
         * \param in float, The input value.
         *
         * \return float, The output value.
         */
        float operator() (float in) { return in; };
    }; //Linear

    /**
     * \struct Logistic, Represents the logistic function.
     */
    struct Logistic {
        /**
         * The Logistic function.
         *
         * \param in float, The input value.
         *
         * \return float, The output value.
         */
        float operator() (float in) { return 1.0f / (1.0f + exp (-in)); };
    }; //Logistic
}; //neural

#endif //NEURAL_ACTIVATIONFUNCTIONS_H

