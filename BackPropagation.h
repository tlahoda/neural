/**
 * \file BackPropagation.h, Contains the BackPropagation class.
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
#ifndef NEURAL_BACKPROPAGATION_H
#define NEURAL_BACKPROPAGATION_H

#include "neural/Helpers.h"
#include "neural/Synapse.h"

namespace neural {
    /**
     * \class BackPropagation, Represents back propagation error correction.
     */
    class BackPropagation {
        public:
            /**
             * Returns the allowable margin of error.
             *
             * \return float, The allowable margin of error.
             */
            static float allowableErrorMargin () {
                static const float errorMargin_ = 0.000000005f;
                return errorMargin_;
            };
            
            /**
             * The rate of error correction.
             *
             * \return float, The rate of error correction.
             */
            static float learningRate () {
                static const float learningRate_ = 0.25f;
                return learningRate_;
            };

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
                 * \param obtained const Response&, The obtained Response.
                 * \param desired const Response&, The desired Response.
                 */
                OutputError (const Response& obtained, const Response& desired)
                  : i_ (0), obtained_ (obtained), desired_ (desired) {};

                /**
                 * Calculates a nueron's error.
                 *
                 * \tparam Neuron, The type of the neuron.
                 *
                 * \param neuron Neuron&, The neuron for which to calculate the error.
                 *
                 * \return void.
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
                     * The response obtained.
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
             * \tparam OutputLayer, The output layer feeding the hidden layer..
             */
            template<class OutputLayer>
            struct HiddenError {
                /**
                 * Constructs a Hidden error from the OutputLayer.
                 *
                 * \param outputLayer OutputLayer&, The output layer.
                 */
                explicit HiddenError (OutputLayer& outputLayer) 
                  : outputLayer_ (outputLayer) {};

                /**
                 * Calculates a neuron's error.
                 *
                 * \tparam Neuron, The type of the neuron.
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

            /**
             * \struct Adjust, Adjusts the threshold of a neuron.
             *
             * \tparam Structure, The neuron structure to adjust.
             */
            template<class Structure>
            struct Adjust {
                /**
                 * Adjusts the threshold of a neuron.
                 *
                 * \tparam Neuron, The type of the neuron.
                 *
                 * \param neuron Neuron&, The neuron to adjust.
                 *
                 * \return void.
                 */
                template<class Neuron>
                void operator() (Neuron& neuron) {
                    float adjustment = learningRate () * neuron.error ();
                    std::for_each (Begin::get<Structure> (neuron), End::get<Structure> (neuron), boost::bind (&Synapse::adjust, _1, adjustment * neuron.val ()));
                    neuron.threshold () += adjustment;
                };
            }; //Adjust

            /**
             * \struct MeanSquareError, Calculates the mean square error.
             */
            struct MeanSquareError {
                /**
                 * Calculates the mean square error between the obtain and desired responses.
                 *
                 * \tparam Response, The type of the response.
                 *
                 * \param desired const Response&, The desited response.
                 * \param obtained const Response&, The obtained response.
                 *
                 * \return float, The mean square error.
                 */
                template<class Response>
                static float calculate (const Response& desired, Response& obtained) {
                    std::vector<float>::iterator desCur = const_cast<Response&> (desired).begin ();
                    std::vector<float>::iterator obCur = const_cast<Response&> (obtained).begin ();
                    return std::accumulate (obtained.begin (), obtained.end (), 0.0f, boost::bind (&pow, *(desCur++) - *(obCur++), 2.0f)) / (float)obtained.size ();
                };
            }; //MeanSquareError

            /**
             * Trains a neural network.
             *
             * \tparam Net, The type of the neural network.
             * \tparam Response, The type of the Response.
             *
             * \param net Net&, The neural network.
             * \param desired const Response&, The desried response.
             * \param obtained const Response&, The obtained response.
             *
             * \return void.
             */
            template<class Net, class Response>
            static void learn (Net& net, const Response& desired, Response& obtained) {
                while (MeanSquareError::calculate (desired, obtained) > allowableErrorMargin ()) {
                    std::for_each (net.output ().begin (), net.output ().end (), OutputError<Response> (obtained, desired));
                    std::for_each (net.hidden ().begin (), net.hidden ().end (), HiddenError<typename Net::outputLayer> (net.output ()));
                    std::for_each (net.output ().begin (), net.output ().end (), Adjust<typename Net::outputLayer::Neuron::inputStructure> ());
                    std::for_each (net.hidden ().begin (), net.hidden ().end (), Adjust<typename Net::hiddenLayer::Neuron::inputStructure> ());
                    //obtained = Response (operator() (stimulus));
                }
            };
    }; //BackPropagation
}; //neural

#endif //NEURAL_BACKPROPAGATION_H

