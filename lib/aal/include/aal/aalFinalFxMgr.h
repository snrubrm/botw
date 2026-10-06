#pragma once

#include <basis/seadTypes.h>
#include "aal/aalDeviceType.h"

namespace sead {
class Heap;
}

namespace aal {

class FinalFxCtrl;

/// Owns the table of the final effect controls (one per DeviceType). TODO: incomplete: the table is created by
/// OutputDevice::initializeFinalFxCtrl.
class FinalFxMgr {
public:
    FinalFxMgr();
    ~FinalFxMgr();

    void initialize(sead::Heap* heap);
    void finalize();
    void calc();
    void removeFinalFxCtrl(DeviceType device);

private:
    static FinalFxMgr* sInstance;

    FinalFxCtrl** mFinalFxCtrls = nullptr;
    f32 _8 = 32000.0f;
};

}  // namespace aal
