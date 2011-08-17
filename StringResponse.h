/**
 * \file StringResponse.h, Contains the StringResponse class.
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
#ifndef NEURAL_STRINGRESPONSE_H
#define NEURAL_STRINGRESPONSE_H

#include <vector>
#include <iostream>
#include <algorithm>

#include <boost/lambda/lambda.hpp>

#include "neural/Helpers.h"

namespace neural {
    /**
     * \struct StringResponse, Represents a string response.
     */
    struct StringResponse {
        private:
            /**
             * Parses a string.
             *
             * \param response const std::string&, .
             *
             * \return void.
             */
            void parse (const std::string& response) {
                //int i = 0;
                //std::for_each (vals_.begin (), vals_.end (), boost::lambda::_1 = ((response & (1 << i++)) > 0) ? 0.9f : 0.1f);
                //std::for_each (vals_.begin (), vals_.end (), response[i++]);
            };

        public:
            /**
             * \typedef std::vector<float>::iterator iterator,
             *          Exposes the type of the iterator.
             */
            typedef std::vector<float>::iterator iterator;

            /**
             * Constructs a StringResponse for a number of neurons.
             *
             * \param numNeurons unsigned int, The number of neurons.
             */
            explicit StringResponse (unsigned int numNeurons)
              : vals_ (numNeurons, 0) {};

            /**
             * Constructs a StrinResponse from a string for a number of neurons.
             *
             * \param response std::string, The response.
             * \param numNeurons unsigned int, The number of neurons.
             */
            StringResponse (std::string response, unsigned int numNeurons)
              : vals_ (numNeurons) { parse (response); };

            /**
             * Constructs a StringResponse from a Layer.
             *
             * \tparam Layer, The type of the Layer.
             *
             * \param layer Layer&, The Layer.
             */
            template<class Layer>
            explicit StringResponse (Layer& layer)
              : vals_ (std::distance (layer.begin (), layer.end ())) {
                typename Layer::iterator curIter = layer.begin ();
                std::for_each (vals_.begin (), vals_.end (), boost::lambda::_1 = (curIter++)->val ());
            };

            /**
             * Copies constructs a StringResponse.
             *
             * \param rhs const StringResponse&, The StringResponse to copy.
             */
            StringResponse (const StringResponse& rhs)
              : vals_ (rhs.vals_.size ()) {
                std::copy (rhs.vals_.begin (), rhs.vals_.end (), vals_.begin ());
            };

            /**
             * Returns the response as a string.
             *
             * \return std::string, The response.
             */
            std::string operator() () const {
                std::string total ("");
                int i = 0;
                std::for_each (vals_.begin (), vals_.end (), total += (boost::lambda::_1 >= 0.5f) * (1 >> i++));
                return total;
            };

            /**
             * The beginning of the responses.
             *
             * \return iterator, The beginning.
             */
            iterator begin () { return vals_.begin (); };

            /**
             * The end of the responses.
             *
             * \return iterator, The end.
             */
            iterator end () { return vals_.end (); };
            
            /**
             * The size of the response.
             *
             * \return unsigned int, The size.
             */
            unsigned int size () const { return vals_.size (); };

            /**
             * Returns the response specified by index.
             *
             * \param index unsigned int, The index of the response to return.
             *
             * \return float, The response.
             */
            float operator[] (unsigned int index) const { return vals_[index]; };

            /**
             * Reads a StringResponse from an istream.
             *
             * \param is std::istream&, The istream from which to read.
             * \param response StringResponse&, The StringResponse to read.
             *
             * \return std::istream&, A reference to the istream.
             */
            friend std::istream& operator>> (std::istream& is, StringResponse& response) {
                /*std::string res ("");
                is >> res;
                response.parse (res);*/
                return is;
            };

            /**
             * Write a StringResponse to an ostream.
             *
             * \param os std::ostream, The ostream to which to write.
             * \param response const StringResponse&, The StringResponse to write.
             *
             * \return std::ostream&, A reference to the ostream.
             */
            friend std::ostream& operator<< (std::ostream& os, const StringResponse& response) {
                return os << response ();
            };

        private:
            /**
             * The output of the neurons.
             */
            std::vector<float> vals_;
    }; //StringResponse
}; //neural

#endif //NEURAL_STRINGRESPONSE_H

