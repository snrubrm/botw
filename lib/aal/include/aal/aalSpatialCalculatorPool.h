#pragma once

#include <container/seadBuffer.h>
#include "aal/aalSpatialCalculator.h"

namespace aal {

/// Creates and destroys the spatial calculators of a SpatialCalculatorPool.
class ISpatialCalculatorFactory {
public:
    virtual ~ISpatialCalculatorFactory() = default;
    virtual SpatialCalculator* create(sead::Heap* heap) = 0;
    virtual void destroy(SpatialCalculator* calculator) = 0;
};

/// The spatial calculators that the sound sources take from (`alloc`) and give back (`free`). Sources with the same
/// setting share one calculator.
class SpatialCalculatorPool {
public:
    SpatialCalculatorPool();
    virtual ~SpatialCalculatorPool();

    /// Creates `num` calculators with `factory` (or the default factory if it is null).
    void initialize(s32 num, sead::Heap* heap, ISpatialCalculatorFactory* factory);
    void finalize();
    /// A calculator that is set up with `setting`: unless `exclusive`, an existing calculator with the same setting
    /// is shared. nullptr if there is none left.
    SpatialCalculator* alloc(const SpatialCalculator::Setting& setting, bool exclusive);
    void free(SpatialCalculator* calculator);
    /// Makes the calculators recalculate (the counter skips over -1).
    void resetDirtyAll();

private:
    struct Entry {
        SpatialCalculator* calculator;
        /// The hash of the setting of the calculator, 0 if it is not in use.
        u32 setting_hash;
    };

    sead::Buffer<Entry> mCalculators;
    s32 mNumCalculators;
    /// Where the search for an unused calculator starts.
    s32 mSearchStart;
    u32 mDirtyCounter;
    ISpatialCalculatorFactory* mFactory;
};

}  // namespace aal
