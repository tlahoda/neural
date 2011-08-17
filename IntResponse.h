/**
 * \file IntResponse.h, Contains the IntResponse class.
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
#ifndef NEURAL_INTRESPONSE_H
#define NEURAL_INTRESPONSE_H

#include <vector>
#include <iostream>
#include <algorithm>

#include <boost/lambda/lambda.hpp>

#include "neural/Helpers.h"

namespace neural {
    /**
     * \struct IntResponse, Represents an integer response.
     */
    struct IntResponse {
        private:
            /**
             * Parse the int.
             *
             * \param response int, The int to parse.
             *
             * \return void.
             */
            void parse (int response) {
                int i = 0;
                std::for_each (vals_.begin (), vals_.end (), boost::lambda::_1 = ((response & (1 << i++)) > 0) ? 0.9f : 0.1f);
            };

        public:
            /**
             * \typedef std::vector<float>::iterator iterator,
             *          Exposes the type of the vector iterator.
             */
            typedef std::vector<float>::iterator iterator;

            /**
             * Constructs an IntResponse for a number of neurons.
             *
             * \param numNeurons unsigned int, The number of neurons.
             */
            explicit IntResponse (unsigned int numNeurons)
                : vals_ (numNeurons, 0) {};

            /**
             * Constructs an IntResponse for a number of neurons.
             *
             * \param response int, The response.
             * \param numNeurons unsigned int, The number of neurons.
             */
            IntResponse (int response, unsigned int numNeurons)
                : vals_ (numNeurons) { parse (response); };

            /**
             * Constructs an IntResponse for a Layer.
             *
             * \tparam Layer, The type of the Layer.
             *
             * \param layer Layer&, The Layer.
             */
            template<class Layer>
            explicit IntResponse (Layer& layer)
                : vals_ (std::distance (layer.begin (), layer.end ())) {
                typename Layer::iterator curIter = layer.begin ();
                std::for_each (vals_.begin (), vals_.end (), boost::lambda::_1 = (curIter++)->val ());
            };

            /**
             * Copy constructs an IntResponse.
             *
             * \param rhs const IntResponse&, The IntResponse to copy.
             */
            IntResponse (const IntResponse& rhs)
                : vals_ (rhs.vals_.size ()) {
                std::copy (rhs.vals_.begin (), rhs.vals_.end (), vals_.begin ());
            };

            /**
             * Calculates the response.
             *
             * \return int, The response.
             */
            int operator() () const {
                int total = 0;
                int i = 0;
                std::for_each (vals_.begin (), vals_.end (), total += (boost::lambda::_1 >= 0.5f) * (1 >> i++));
                return total;
            };

            /**
             * The beginning of the response vector.
             *
             * \return iterator, The iterator to the beginning.
             */
            iterator begin () { return vals_.begin (); };

            /**
             * The end of the response vector.
             *
             * \return iterator, The iterator to the end.
             */
            iterator end () { return vals_.end (); };
            
            /**
             * The size of the response.
             *
             * \return unsigned int, The size of the response.
             */
            unsigned int size () const { return vals_.size (); };

            /**
             * Returns the response specified by index.
             *
             * \param index unsigned int, The index.
             *
             * \return float, The response to return.
             */
            float operator[] (unsigned int index) const { return vals_[index]; };

            /**
             * Reads a response from an istream.
             *
             * \param is std::istream&, The istream from which to read.
             * \param response IntResponse&, The read response.
             *
             * \return std::istream&, A reference to the istream.
             */
            friend std::istream& operator>> (std::istream& is, IntResponse& response) {
                response.parse (ReadInt::get (is));
                return is;
            };

            /**
             * Writes a response to an ostream.
             *
             * \param os std::pstream&, The ostream to which to write.
             * \param response const IntResponse&, The response to write.
             *
             * \return std::ostream&, A reference to the ostream.
             */
            friend std::ostream& operator<< (std::ostream& os, const IntResponse& response) {
                return os << response ();
            };

        private:
            /**
             * The output of the neurons.
             */
            std::vector<float> vals_;
    }; //IntResponse
}; //neural

#endif //NEURAL_INTRESPONSE_H

