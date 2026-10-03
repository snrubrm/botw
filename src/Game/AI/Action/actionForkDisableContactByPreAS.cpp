#include "Game/AI/Action/actionForkDisableContactByPreAS.h"
#include <math/seadMathCalcCommon.h>
#include <prim/seadFormatPrint.h>

namespace uking::action {

ForkDisableContactByPreAS::ForkDisableContactByPreAS(const InitArg& arg)
    : ForkDisableContact(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
ForkDisableContactByPreAS::~ForkDisableContactByPreAS() {
    ;
}

bool ForkDisableContactByPreAS::init_(sead::Heap* heap) {
    return ForkDisableContact::init_(heap);
}

void ForkDisableContactByPreAS::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkDisableContact::enter_(params);
}

void ForkDisableContactByPreAS::leave_() {
    ForkDisableContact::leave_();
}

void ForkDisableContactByPreAS::loadParams_() {
    ForkDisableContact::loadParams_();
    getStaticParam(&mDisableTime_s, "DisableTime");
    sead::FixedSafeString<64> key;
    for (u32 i = 0; i < 5; i++) {
        (sead::StringCutOffPrintFormatter(&key) << "PreASName%d", i) << sead::flush;
        getStaticParam(&mPreASName_s[i], key);
    }
}

void ForkDisableContactByPreAS::calc_() {
    ForkDisableContact::calc_();
    mTimerActive = false;
    mTimer.update();
}

bool ForkDisableContactByPreAS::m32() {
    return mTimerActive;
}

bool ForkDisableContactByPreAS::m33() {
    return !(mTimer.value <= sead::Mathf::epsilon());
}

}  // namespace uking::action
