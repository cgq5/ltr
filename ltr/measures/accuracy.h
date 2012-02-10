// Copyright 2011 Yandex

#ifndef LTR_MEASURES_ACCURACY_H_
#define LTR_MEASURES_ACCURACY_H_

#include "ltr/measures/measure.h"

namespace ltr {
// Can be poinwise and pairwise, but not listwise
template <class TElement>
class Accuracy : public MoreIsBetterMeasure<TElement> {
  public:
  Accuracy(const ParametersContainer& parameters = ParametersContainer())
    :MoreIsBetterMeasure<TElement>("Accuracy") {
      this->setDefaultParameters();
      this->parameters().copyParameters(parameters);
  }
  private:
  double get_measure(const TElement& object) const;
};
}

#endif  // LTR_MEASURES_ACCURACY_H_
