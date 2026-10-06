#include "aal/aalSpatialPlayingParamPool.h"
#include <prim/seadScopedLock.h>

namespace aal {

// 0x7100b91318
SpatialPlayingParamPool::SpatialPlayingParamPool() : mSearchStart(0) {}

// 0x7100b9133c (D1) / 0x7100b91494 (D0)
SpatialPlayingParamPool::~SpatialPlayingParamPool() {
    finalize();
}

// 0x7100b913ec
void SpatialPlayingParamPool::finalize() {
    if (!mParams.isBufferReady())
        return;
    for (s32 i = 0; i < mParams.size(); ++i) {
        mParams[i]->finalize();
        delete mParams[i];
    }
    mParams.freeBuffer();
}

// 0x7100b9154c
void SpatialPlayingParamPool::initialize(s32 num, sead::Heap* heap) {
    if (mParams.isBufferReady())
        return;
    mParams.allocBuffer(num, heap, 8);
    for (s32 i = 0; i < num; ++i) {
        auto* param = new (heap, 8) SpatialPlayingParam;
        if (param) {
            param->initialize(heap);
            mParams.pushBack(param);
        }
    }
    mSearchStart = 0;
}

// NON_MATCHING: same code, but the original shares the final `at(index)` + activate() between the two search loops
// 0x7100b915f4
SpatialPlayingParam* SpatialPlayingParamPool::alloc() {
    if (!mParams.isBufferReady())
        return nullptr;

    const s32 size = mParams.size();
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    const s32 start = mSearchStart;
    for (s32 i = start; i < size; ++i) {
        if (!mParams[i]->isActivated()) {
            mSearchStart = i + 1 < mParams.size() ? i + 1 : 0;
            SpatialPlayingParam* param = mParams[i];
            param->activate();
            return param;
        }
    }
    for (s32 i = 0; i < start; ++i) {
        if (!mParams[i]->isActivated()) {
            mSearchStart = i + 1 < mParams.size() ? i + 1 : 0;
            SpatialPlayingParam* param = mParams[i];
            param->activate();
            return param;
        }
    }
    return nullptr;
}

// 0x7100b916fc
void SpatialPlayingParamPool::free(SpatialPlayingParam* param) {
    if (!param || !mParams.isBufferReady())
        return;
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    param->deactivate();
}

}  // namespace aal
