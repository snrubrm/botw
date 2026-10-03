#include "Game/AI/Action/actionGanonThrowMultiIce.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

GanonThrowMultiIce::GanonThrowMultiIce(const InitArg& arg) : GanonThrowFireBall(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
GanonThrowMultiIce::~GanonThrowMultiIce() {
    ;
}

bool GanonThrowMultiIce::init_(sead::Heap* heap) {
    return GanonThrowFireBall::init_(heap);
}

void GanonThrowMultiIce::enter_(ksys::act::ai::InlineParamPack* params) {
    GanonThrowFireBall::enter_(params);
    _158 = 1;
    _15c = 0;
    _160 = true;
}

void GanonThrowMultiIce::leave_() {
    GanonThrowFireBall::leave_();
}

void GanonThrowMultiIce::loadParams_() {
    GanonThrowFireBall::loadParams_();
    getStaticParam(&mThrowNumAtSameTiming_s, "ThrowNumAtSameTiming");
    getDynamicParam(&mThrowPartsName1_d, "ThrowPartsName1");
    getDynamicParam(&mThrowPartsName2_d, "ThrowPartsName2");
    getDynamicParam(&mThrowPartsName3_d, "ThrowPartsName3");
    getDynamicParam(&mThrowPartsName4_d, "ThrowPartsName4");
    getDynamicParam(&mThrowPartsName5_d, "ThrowPartsName5");
    getDynamicParam(&mThrowPartsName6_d, "ThrowPartsName6");
    getDynamicParam(&mThrowPartsName7_d, "ThrowPartsName7");
    getDynamicParam(&mThrowPartsName8_d, "ThrowPartsName8");
}

// NON_MATCHING: the original evaluates `i < *mThrowNumAtSameTiming_s` and `idx + 1 < 8` as one ccmp chain at the loop
// bottom; ours tests `idx + 1 < 8` (before the load of the param) as a separate early exit.
void GanonThrowMultiIce::calc_() {
    GanonThrowFireBall::calc_();
    if (_160) {
        _160 = false;
        return;
    }
    if (_158 >= 1 && _158 <= 7) {
        sub_710017BBA0(_158);
        ++_158;
    }
    if (sub_71005DD780(mActor, 0x47, nullptr, 0, 0)) {
        const int start = _15c;
        if (start <= 7) {
            int i = 0;
            int idx;
            do {
                idx = start + i;
                sub_710017BE48(idx);
                ++_15c;
                ++i;
            } while (i < *mThrowNumAtSameTiming_s && idx + 1 < 8);
        }
    }
}

const sead::SafeString& GanonThrowMultiIce::m32(int idx) {
    switch (idx) {
    case 0:
        return GanonThrowFireBall::m32(0);
    case 1:
        return mThrowPartsName1_d;
    case 2:
        return mThrowPartsName2_d;
    case 3:
        return mThrowPartsName3_d;
    case 4:
        return mThrowPartsName4_d;
    case 5:
        return mThrowPartsName5_d;
    case 6:
        return mThrowPartsName6_d;
    case 7:
        return mThrowPartsName7_d;
    case 8:
        return mThrowPartsName8_d;
    default:
        return GanonThrowFireBall::m32(0);
    }
}

void GanonThrowMultiIce::m33(sead::Vector3f* out, int idx) {
    GanonThrowFireBall::m33(out, 0);
}

}  // namespace uking::action
