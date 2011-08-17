/**
 * \file StringStimulus.h, Contains the StringStimulus class.
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
#ifndef NEURAL_STRINGSTIMULUS_H
#define NEURAL_STRINGSTIMULUS_H

#include <algorithm>
#include <string>
#include <iostream>

#include <boost/bind.hpp>

namespace neural {
    /**
     * \struct StringStimulus, Represents a string stimulus.
     */
    struct StringStimulus {
        private:
            /**
             * Returns the scaling factor.
             *
             * \return float, The scaling factor.
             */
            static float scaling () {
                static float scaling_ = 1.0f / 255.0f;
                return scaling_;
            };
        
        public:
            /**
             * Constructs a StringStimulus.
             */
            StringStimulus ()
                : stimulus_ ("") {};

            /**
             * Constructs a StingStimulus from a string.
             *
             * \param stimulus const std::string&, The stimulus.
             */
            explicit StringStimulus (const std::string& stimulus)
                : stimulus_ (stimulus) {};

            /**
             * Stimulates a Layer.
             *
             * \tparam Layer, The type of the Layer.
             *
             * \param layer Layer&, The Layer to stimulate.
             *
             * \return void.
             */
            template<class Layer>
            void operator() (Layer& layer) const {
                const char* c_strCur = stimulus_.c_str ();
                const char* c_strEnd = c_strCur + stimulus_.size ();
                std::for_each (layer.begin (), layer.end (), boost::bind (&Layer::neuron::input, _1, (c_strCur < c_strEnd) ? scaling () * (float)(*(c_strCur++)) : 0));
            };

            /**
             * Reads a StringStimulus from an istream.
             *
             * \param is std::istream&, The istream from which to read.
             * \param stimulus StringStimulus&, The StringStimulus to read.
             *
             * \return std::istream&, A reference to the istream.
             */
            friend std::istream& operator>> (std::istream& is, StringStimulus& stimulus) {
                return is >> stimulus.stimulus_;
            };

            /**
             * Writes a StringStimulus to an ostream.
             *
             * \param os std::ostream&, The ostream to which to write.
             * \param stimulus const StringStimulus&, The StringStimulus to write.
             *
             * \return std::ostream&, A reference to the ostream.
             */
            friend std::ostream& operator<< (std::ostream& os, const StringStimulus& stimulus) {
                return os << stimulus.stimulus_;
            };

        private:
            /**
             * The stimulus string.
             */
            std::string stimulus_;
    }; //StringStimulus
}; //neural

#endif //NEURAL_STRINGSTIMULUS_H

