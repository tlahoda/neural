/**
 * \file linear_algebra.h, Contains a collection of linear algebra
 *                         and math operations.
 *
 * Copyright (c) 2011 Thomas P. Lahoda
 *
 * Permission is hereby granted, free of charge, to any
 * person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the
 * Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit
 * persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 * The above copyright notice and this permission notice shall
 * be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
 * KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
 * OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef NEURAL_LINEAR_ALGEBRA_H
#define NEURAL_LINEAR_ALGEBRA_H

#include <algorithm>
#include <vector>

namespace neural {
  using namespace std;
  typedef vector<float> Vector;
  typedef vector<vector<float>> Matrix;

  template<typename dIterator, typename oIterator>
  float meanSquaredError (dIterator dBegin, dIterator dEnd, oIterator oBegin, oIterator oEnd) {
    float error = accumulate (dBegin, dEnd, 0.0f, [&oBegin] (float result, float val) {
      return result + pow (val - *(oBegin++), 2.0f);
    });
    return error / distance (dBegin, dEnd);
  };

  template<typename mIterator, typename vIterator, typename resIterator>
  void prod (mIterator mBegin, mIterator mEnd, vIterator vBegin, resIterator resBegin) {
    while (mBegin != mEnd) {
      *(resBegin++) = accumulate (mBegin->begin (), mBegin->end (), 0.0f) * *(vBegin++);
      ++mBegin;
    }
  };

  template<typename aIterator, typename bIterator, typename resIterator>
  void element_prod (aIterator aBegin, aIterator aEnd, bIterator bBegin, resIterator resBegin) {
    transform (aBegin, aEnd, bBegin, resBegin, [] (float af, float bf) { return af * bf; });
  };

  template<typename aIterator, typename bIterator, typename resIterator>
  void element_sub (aIterator aBegin, aIterator aEnd, bIterator bBegin, resIterator resBegin) {
    transform (aBegin, aEnd, bBegin, resBegin, [] (float af, float bf) { return af - bf; });
  };

  float round (float x, float precision) {
    return floor (x * precision + ((x < 0.0f) ? -0.5 : 0.5)) / precision;
  };
}; //neural

#endif //NEURAL_LINEAR_ALGEBRA_H

