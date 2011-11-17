#ifndef NEURAL_LEARNING_RATES_H
#define NEURAL_LEARNING_RATES_H

#include <math.h>

namespace neural {
  struct ConstantLearningRate {
    ConstantLearningRate (float rate) : rate_ (rate) {};
    
    float operator() (float err) { return rate_; };

    private:
      float rate_;
  }; //ConstantLearningRate

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

  struct SawtoothLearningRate {
    SawtoothLearningRate (float err) : err_ (err), plateau_ (0) {};

    float operator() (float err) {
      float plateauFactor = calcPlateauFactor (err, err_, plateau_);
      //if (plateauFactor > 3.0f) {
      //  plateauFactor = 1.0f;
      //  plateau = 0;
      //}
      return ((err == 0.0f || err == 1.0f) ? 1.0f : 1.0f / abs (log (err))) * plateauFactor;
    };

    private:
      float err_;
      int plateau_;
  }; //SawtoothLearningRate
}; //neural

#endif //NEURAL_LEARNING_RATES_H
