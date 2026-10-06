#include "aal/aalFinalFxMgr.h"

namespace aal {

FinalFxMgr* FinalFxMgr::sInstance = nullptr;

// 0x7100b8555c
FinalFxMgr::FinalFxMgr() {
    sInstance = this;
}

// 0x7100b85578
FinalFxMgr::~FinalFxMgr() {
    finalize();
    sInstance = nullptr;
}

// 0x7100b855b0
void FinalFxMgr::finalize() {
    if (mFinalFxCtrls) {
        delete[] mFinalFxCtrls;
        mFinalFxCtrls = nullptr;
    }
}

// 0x7100b855dc
void FinalFxMgr::initialize(sead::Heap* heap) {}

// 0x7100b855e0
void FinalFxMgr::calc() {}

// 0x7100b855e4
void FinalFxMgr::removeFinalFxCtrl(DeviceType device) {
    if (mFinalFxCtrls)
        mFinalFxCtrls[device] = nullptr;
}

}  // namespace aal
