#pragma once

#include "aal/aalSpatialCalculatorPool.h"

namespace aal {

/// The factory that the SpatialCalculatorPool uses unless it is given another one.
class SpatialCalculatorFactory : public ISpatialCalculatorFactory {
public:
    SpatialCalculator* create(sead::Heap* heap) override;
    void destroy(SpatialCalculator* calculator) override;
};

}  // namespace aal
