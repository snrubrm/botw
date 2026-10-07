#include "aal/aalFinalFxCtrl.h"
#include "aal/aalFinalFxMgr.h"
#include "aal/aalSystemAccessor.h"

namespace aal {

FinalFxCtrl::FinalFxCtrl(DeviceType device) : mDevice(device) {
    mEffects.initOffset(offsetof(Element, mNode));
}

FinalFxCtrl::~FinalFxCtrl() {
    clearFinalFx();
}

void FinalFxCtrl::clearFinalFx() {
    auto lock = sead::makeScopedLock(mCriticalSection);
    if (!mEffects.isEmpty()) {
        auto inner_lock = sead::makeScopedLock(mCriticalSection);
        for (Element& effect : mEffects)
            effect.m7();
        mEffects.clear();
        FinalFxMgr* mgr = SystemAccessor::getFinalFxMgr();
        if (mgr)
            mgr->removeFinalFxCtrl(mDevice);
    }
}

}  // namespace aal
