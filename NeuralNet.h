/**
 * \file NeuralNet.h, Contains the neural network class.
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
#ifndef NEURAL_NEURALNET_H
#define NEURAL_NEURALNET_H

#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdlib>

#include "math.h"

namespace neural { 
  using namespace std;

  template<typename iter>
  void calcOutputError (iter dBeg, iter oBeg, iter outBeg, iter outEnd) {
    for_each (outBeg, outEnd, [&dBeg, &oBeg] (float& ele) {
      ele = (*dBeg - *oBeg) * *oBeg * (1.0f - *oBeg);
      ++dBeg;
      ++oBeg;
    });
  };

  template<typename layerIter, typename vecIter>
  void calcHiddenError (vecIter wBeg, layerIter layerBeg, vecIter outBeg, vecIter outEnd) {
    //prod (thetaBeg, thetaEnd, errBeg, wBeg);
    for_each (outBeg, outEnd, [&wBeg, &layerBeg] (float& ele) {
      ele = *wBeg * *layerBeg * (1.0f - *layerBeg);
      ++wBeg;
      ++layerBeg;
    });
  };

  template<typename thetaIter, typename layerIter, typename errIter>
  void adjustTheta (thetaIter thetaBeg, thetaIter thetaEnd, layerIter layerBeg, errIter errBeg, float learningRate) {
    for_each (thetaBeg, thetaEnd, [&layerBeg, &errBeg, &learningRate] (Vector& row) {
      float adjustment = *layerBeg * *errBeg * learningRate;
      ++layerBeg;
      ++errBeg;
      for_each (row.begin (), row.end (), [&adjustment] (float& ele) {
        ele += adjustment;
    });});
  };

  float calcPlateauFactor (float err, float& oldErr, int& plateau) {
    float tempErr = round (err, 1000000);
    if (tempErr >= oldErr) {
      ++plateau;
      return ((plateau < 3) ? 1.0f : abs (log (static_cast<float> (plateau))));
    }
    oldErr = tempErr;
    plateau = 0;
    return 1.0f;
  };

  void randomInitThetas (vector<Matrix>& thetas) {
    for_each (thetas.begin (), thetas.end (), [] (Matrix& theta) {
      for_each (theta.begin (), theta.end (), [] (Vector& row) {
        for_each (row.begin (), row.end (), [] (float& ele) {
          ele = 0.4f / static_cast<float> (rand () % 10 + 1);
    });});});
  };

  class NeuralNet {
    public:
      template<typename TopoIter>
      NeuralNet (TopoIter topoBeg, TopoIter topoEnd)
        : layers_ (),
          thetas_ (distance (topoBeg, topoEnd) - 1) {

        for_each (topoBeg, topoEnd, [&layers_] (int n) {
          layers_.push_back (Vector (n + 1));
        });

        auto nextTopo = topoBeg;
        transform (topoBeg, --topoEnd, ++nextTopo, thetas_.begin (), [] (int m, int n) {
          Matrix mat;
          for (int i = 0; i < m + 1; ++i)
            mat.push_back (Vector (n + 1));
          return mat;
        });
      };

      template<typename TopoIter>
      NeuralNet (TopoIter topoBeg, TopoIter topoEnd, vector<Matrix>& thetas) 
        : layers_ (),
          thetas_ (distance (topoBeg, topoEnd) - 1) {

        for_each (topoBeg, topoEnd, [&layers_] (int n) {
          layers_.push_back (Vector (n + 1));
        });

        auto nextTopo = topoBeg;
        transform (topoBeg, --topoEnd, ++nextTopo, thetas_.begin (), [] (int m, int n) {
          Matrix mat;
          for (int i = 0; i < m + 1; ++i)
            mat.push_back (Vector (n + 1));
          return mat;
        });

        for (int i = 0, numThetas = thetas_.size (); i < numThetas; ++i)
          for (int j = 0, numRows = thetas[i].size (); j < numRows; ++j)
            copy (thetas[i][j].begin (), thetas[i][j].end (), thetas_[i][j].begin ());
      };

      Vector& operator() (const Vector& stimulus) {
        auto layerIter = layers_.begin ();
        copy (stimulus.begin (), stimulus.end (), ++(layerIter->begin ()));

        Vector z (layerIter->size ());
        for_each (thetas_.begin (), thetas_.end (), [&layerIter, &z] (Matrix& theta) {
          (*layerIter)[0] = 1.0f;

          prod (theta.begin (), theta.end (), layerIter->begin (), z.begin ());
          transform (z.begin (), z.end (), (++layerIter)->begin (), [] (float in) { 
            return 1.0f / (1.0f + exp (-in));
          });
        });

        (*layerIter)[0] = 0.0f;
        return *layerIter;
      };

      template<typename LearningRate>
      void learn (Vector& stimulus, Vector& desired, LearningRate& lr, float allowableErrorMargin) {
        Vector& obtained = operator() (stimulus);

        Matrix errors;
        Matrix w;
        for_each (++layers_.begin (), layers_.end (), [&errors, &w] (vector<float>& layer) {
          errors.push_back (Vector (layer.size ()));
          w.push_back (Vector (layer.size ()));
        });

        int count = 0;
        float err = 0.0f;
        while ((err = meanSquaredError (desired.begin (), desired.end (), obtained.begin (), obtained.end ())) > allowableErrorMargin) {
          Vector& error = errors[errors.size () - 1];
          calcOutputError (desired.begin (), obtained.begin (), error.begin (), error.end ());

          for (int i = thetas_.size () - 1; i > 0; --i) {
            prod (thetas_[i].begin (), thetas_[i].end (), errors[i].begin (), w[i].begin ());
            calcHiddenError (w[i].begin (), layers_[i + 1].begin (), errors[i - 1].begin (), errors[i - 1].end ());
          }

          float learningRate = lr (err);
          
          auto layerIter = layers_.begin (), errorIter = errors.begin ();
          for_each (thetas_.begin (), thetas_.end (), [&layerIter, &errorIter, &learningRate] (Matrix& theta) {
            adjustTheta (theta.begin (), theta.end (), (layerIter++)->begin (), (errorIter++)->begin (), learningRate);
          });

          obtained = operator() (stimulus);
          cout << ++count << " err " << err << " " << (learningRate / 4.0f) << endl;
        }
        cout << "learn " << count << endl;
      };

    private:
      NeuralNet (const NeuralNet& rhs);
      NeuralNet& operator= (const NeuralNet& rhs);

      Matrix layers_;
      vector<Matrix> thetas_;
  }; //NeuralNet
}; //neural

#endif //NEURAL_NEURALNET_H

