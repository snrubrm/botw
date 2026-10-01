#include "KingSystem/World/worldDofMgr.h"

namespace ksys::world {

// NON_MATCHING: reset() is inlined - same store merging difference as in reset()
DofMgr::DofMgr() {
    reset();
    sub_71010D16EC();
}

// NON_MATCHING: the original merges a different set of constant stores into 64-bit stores
void DofMgr::reset() {
    _20 = 0;
    _24 = 100.0;
    _28 = 30.0;
    _2c = 2.0;
    _f0 = 100.0;
    _168 = 0.0;
    _16c = 0.0;
    _170 = false;
    _174 = 1.0;
    _178 = 0.0;
    _17c = 0.0;
    _180 = false;
    _181 = false;
    _184 = 15.0;
    _188 = 300.0;
    _18c = 0.002;
    _190 = 0.001;
    _194 = 0.004;
    _198 = 0.7;
    _19c = 0.0;
    _1a0 = 0.0;
    _1a4 = 8.0;
    _1a8 = 8.0;
    _1ac = 0.0;
    _1b0 = 0.0;
    _1b4 = 0.0;
    _1b8 = 30.0;
    _1bc = 1.5;
}

void DofMgr::sub_71010D16EC() {
    mDefaultDist.init(3000.0, "DefaultDist", "", &mDofMgrParamObj);
    mDefaultF.init(22.0, "DefaultF", "", &mDofMgrParamObj);
    mDefaultBlur.init(0.7, "DefaultBlur", "", &mDofMgrParamObj);
    mRemainsDist.init(3000.0, "RemainsDist", "", &mDofMgrParamObj);
    mRemainsF.init(22.0, "RemainsF", "", &mDofMgrParamObj);
    mRemainsBlur.init(0.7, "RemainsBlur", "", &mDofMgrParamObj);
    mLockOnF.init(2.5, "LockOnF", "", &mDofMgrParamObj);
    mLockOnBlur.init(1.0, "LockOnBlur", "", &mDofMgrParamObj);
}

DofMgr::~DofMgr() = default;

void DofMgr::init_(sead::Heap* heap) {}

void DofMgr::calc_() {}

void DofMgr::sub_71010D20FC(float a, float b, float c) {
    _20 = 1;
    _24 = a;
    _28 = b;
    _2c = c;
}

}  // namespace ksys::world
