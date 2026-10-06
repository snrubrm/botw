#pragma once

#include <container/seadPtrArray.h>
#include <thread/seadCriticalSection.h>
#include "aal/aalSpatialCalculator.h"

namespace aal {

/// A fixed set of SpatialPlayingParam that the sound sources take from (`alloc`) and give back (`free`).
class SpatialPlayingParamPool {
public:
    SpatialPlayingParamPool();
    virtual ~SpatialPlayingParamPool();

    void initialize(s32 num, sead::Heap* heap);
    void finalize();
    /// The next free param, nullptr if all of them are in use.
    SpatialPlayingParam* alloc();
    void free(SpatialPlayingParam* param);

private:
    sead::PtrArray<SpatialPlayingParam> mParams;
    /// Where the search for a free param starts.
    s32 mSearchStart;
    sead::CriticalSection mCS;
};

}  // namespace aal
