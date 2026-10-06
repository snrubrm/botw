#include "aal/aalSpatialCalculatorFactory.h"

namespace aal {

// 0x7100bb8268
SpatialCalculator* SpatialCalculatorFactory::create(sead::Heap* heap) {
    return new (heap, 8) SpatialCalculator;
}

// 0x7100bb8298
void SpatialCalculatorFactory::destroy(SpatialCalculator* calculator) {
    delete calculator;
}

}  // namespace aal
