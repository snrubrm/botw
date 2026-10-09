#include "Game/AI/Action/actionForkDisableContactByPreAS.h"
#include <math/seadMathCalcCommon.h>
#include <prim/seadFormatPrint.h>
#include "KingSystem/ActorSystem/AS/ASList.h"

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

// NON_MATCHING: timer stores, array iteration and register allocation differ.
void ForkDisableContactByPreAS::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkDisableContact::enter_(params);
    mTimer = {};
    mTimerActive = false;
    auto* list = mActor->getASList();
    if (!list)
        return;

    sead::SafeString name;
    if (list->x_7(0, 0, &ksys::as::ASList::Unk2::sub_7101163940)) {
        if (auto* slots = list->mSlots.getBufferPtr()) {
            if (auto* entries = slots->_20.getBufferPtr()) {
                if (entries->_0)
                    name = entries->_0->mUnk18;
            }
        }
    } else {
        name = list->x_1(0, 0);
    }
    if (name.isEmpty())
        return;
    for (const auto& pre_as : mPreASName_s) {
        if (pre_as.isEmpty())
            return;
        if (name == pre_as) {
            mTimerActive = true;
            mTimer.reset(*mDisableTime_s);
            return;
        }
    }
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
