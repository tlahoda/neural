/**
 * \file neural.cpp, Contains an example of using the neural network.
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
#include <algorithm>
#include <numeric>
#include <cstdlib>
#include <iostream>
#include <vector>

#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "math.h"
#include "NeuralNet.h"

int main (int argc, char** argv) {
  using namespace std;
  using namespace boost;
  using namespace neural;

  srand ((unsigned)time (0));

  int numNodes = 100;
  Vector input (numNodes);
  for (int i = 0; i < numNodes; ++i)
    input[i] = ((float)i) / ((float)numNodes);

  Vector desired (numNodes + 1);
  desired[0] = 0.0f;
  for (int i = 0; i < numNodes; ++i)
    desired[i + 1] = 1.0f - (((float)i) / ((float)numNodes));

  vector<int> topology = {numNodes, numNodes, numNodes};

  thread_group threads;

  NeuralNet net1 (topology.begin (), topology.end ());
  net1.learn1 (input, desired);
  //threads.create_thread (bind (&NeuralNet::learn1, &net1, input, desired));

  NeuralNet net3 (topology.begin (), topology.end ());
  net3.learn3 (input, desired);
  //threads.create_thread (bind (&NeuralNet::learn3, &net3, input, desired));

  threads.join_all ();

  Vector& results1 = net1 (input);
  Vector& results3 = net3 (input);

  cout << "results" << endl;
  int i = 0;
  for (auto cur1 = results1.begin (), cur3 = results3.begin (), end = results3.end (); cur3 != end; ++cur1, ++cur3)
    cout << ++i << ".\t" << round (*cur3, numNodes) << "\t" << round (*cur1, numNodes) << endl;

  return 0;
};

