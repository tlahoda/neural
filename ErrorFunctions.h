/**
 * \file ErrorFunctions.h, Contains the OutputError and HiddenError classes.
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
#ifndef NEURAL_ERRORFUNCTIONS_H
#define NEURAL_ERRORFUNCTIONS_H

#include <algorithm>

#include <boost/shared_ptr.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>

#include "neural/Helpers.h"
#include "neural/Synapse.h"

namespace neural {
    /**
     * \struct OutputError, Represents the output layer error.
     *
     * \tparam Response, The type of the Response.
     */
    template<class Response>
    struct OutputError {
        /**
         * Constructs an OutputError from the obtained and desired responses.
         *
         * \param obtained const Response&, The obtained response.
         * \param desired const Response&, The desired response.
         */
        OutputError (const Response& obtained, const Response& desired)
          : i_ (0), obtained_ (obtained), desired_ (desired) {};

        /**
         * Calculates the neuron's error.
         *
         * \tparam Neuron, The type of the neuron.
         *
         * \param neuron Neuron&, The neuron for which to calculate the error.
         *
         * /return void.
         */
        template<class Neuron>
        void operator() (Neuron& neuron) {
            neuron.error () = (desired_[i_] - obtained_[i_]) * obtained_[i_] * (1.0f - obtained_[i_]);
            ++i_;
        };

        private:
            /**
             * A counter to ensure the appropriate parts of the Response are compared.
             */
            unsigned int i_;

            /**
             * The obtained response.
             */
            const Response& obtained_;

            /**
             * The desired response.
             */
            const Response& desired_;
    }; //OutputError

    /**
     * \struct HiddenError, Represents the hidden layer error.
     *
     * \tparam OutputLayer, The type of the output layer.
     */
    template<class OutputLayer>
    struct HiddenError {
        /**
         * Constructs a HiddenError for the output layer.
         *
         * \param outputLayer OutputLayer&, The output layer.
         */
        explicit HiddenError (OutputLayer& outputLayer) 
            : outputLayer_ (outputLayer) {};

        /**
         * Calculates the neuron's error.
         *
         * \tparam Neruon, The type of the neuron.
         *
         * \param neuron Neuron&, The neuron for which to calculate the error.
         *
         * \return void.
         */
        template<class Neuron>
        void operator() (Neuron& neuron) {
            namespace b = boost;
            namespace l = boost::lambda;
            float sum = 0.0f;
            typename OutputLayer::iterator outCur = outputLayer_.begin ();
            std::for_each (Begin::get<typename Neuron::outputStructure> (neuron), End::get<typename Neuron::outputStructure> (neuron),
                           sum += outCur++->error () * l::bind (&Synapse::weight, l::bind (&b::shared_ptr<Synapse>::get, l::_1))); 
            neuron.error () = sum * neuron.val () * (1.0f - neuron.val ());
        };

        private:
            /**
             * The output layer.
             */
            OutputLayer& outputLayer_;
    }; //HiddenError
}; //neural

#endif //NEURAL_ERRORFUNCTIONS_H

