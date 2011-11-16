/**
 * \file math.h, Contains a collection of math operations.
 *
 * Copyright (c) 2011 Thomas P. Lahoda
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
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
#ifndef NEURAL_MATH_H
#define NEURAL_MATH_H

#include <algorithm>
#include <vector>

namespace neural {
  using namespace std;

  typedef vector<float> Vector;
  typedef vector<Vector> Matrix;

  /**
   * Calculates the mean squared error of two sequences.
   *
   * \tparam dIter, The type of iterator of the desired sequence.
   * \tparam oIter, The type of iterator of the obtained sequence.
   *
   * \param dBeg, The beginning of the desired sequence.
   * \param dEnd, The end of the desired sequence.
   * \param oBeg, The beginning of the obtained sequence.
   * \param oEnd, The end of the obtained sequence.
   *
   * \returns float, The mean squared error.
   */
  template<typename dIter, typename oIter>
  float meanSquaredError (dIter dBeg, dIter dEnd, oIter oBeg, oIter oEnd) {
    float error = accumulate (dBeg, dEnd, 0.0f, [&oBeg] (float result, float val) {
      float res = result + pow (val - *oBeg, 2.0f);
      ++oBeg;
      return res;
    });
    return error / distance (dBeg, dEnd);
  };

  /**
   * Calculates the product of a matrix and a vector.
   *
   * \tparam mIter, The type of the iterator of the matrix.
   * \tparam vIter, The type of the iterator of the vector
   * \tparam resIter, The type of the result vector.
   *
   * \param mBegin, The beginning of the matrix to be multiplied.
   * \param mEnd, The end of the matrix to be multiplied.
   * \param vBegin, The beginning of the vector to be multiplied.
   * \param resBegin, The beginning of the result vector.
   */
  template<typename mIter, typename vIter, typename resIter>
  void prod (mIter mBeg, mIter mEnd, vIter vBeg, resIter resBeg) {
    while (mBeg != mEnd) {
      *resBeg = accumulate (mBeg->begin (), mBeg->end (), 0.0f) * *vBeg;
      ++resBeg;
      ++vBeg;
      ++mBeg;
    }
  };

  /**
   * Rounds a number to a given precision.
   *
   * \param x, The number to round.
   * \param precision, The precision to which to round.
   *
   * \returns float, The rounded number.
   */
  float round (float x, float precision = 10.0f) {
    return floor (x * precision + ((x < 0.0f) ? -0.5 : 0.5)) / precision;
  };
}; //neural

#endif //NEURAL_MATH_H

