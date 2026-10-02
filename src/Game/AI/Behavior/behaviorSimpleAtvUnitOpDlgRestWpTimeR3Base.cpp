#include "Game/AI/Behavior/behaviorSimpleAtvUnitOpDlgRestWpTimeR3Base.h"
#include "Game/AI/aiUnk_71025b2aa8.h"

namespace uking::behavior {

SimpleAtvUnitOpDlgRestWpTimeR3Base::SimpleAtvUnitOpDlgRestWpTimeR3Base(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

void SimpleAtvUnitOpDlgRestWpTimeR3Base::m8() {}

void SimpleAtvUnitOpDlgRestWpTimeR3Base::m9() {}

// NON_MATCHING: the original computes &mIsWeakPointAppearMode_a before the first call (as in NeckControl)
void SimpleAtvUnitOpDlgRestWpTimeR3Base::loadParams() {
    getStaticParam(&mCloseOption_s, "CloseOption");
    getStaticParam(&mTimer_s, "Timer");
    getStaticParam(&mType_s, "Type");
    getStaticParam(&mRestTime_s, "RestTime");
    getStaticParam(&mmstxtName_s, "mstxtName");
    getStaticParam(&mlabelName_s, "labelName");
    getAITreeVariable(&mInBeastGanonVoiceSequence_a, "InBeastGanonVoiceSequence");
    getAITreeVariable(&mIsWeakPointAppearMode_a, "IsWeakPointAppearMode");
    getAITreeVariable(&mWeakPointCounter_a, "WeakPointCounter");
    getAITreeVariable(&mSimpleDialogUnit_a, "SimpleDialogUnit");
}

const sead::SafeString* SimpleAtvUnitOpDlgRestWpTimeR3Base::m14() {
    return &mlabelName_s;
}

// NON_MATCHING: the original tests the decremented count with b.ne on the subs flags (cbnz here)
SimpleAtvUnitOpDlgRestWpTimeR3Base::~SimpleAtvUnitOpDlgRestWpTimeR3Base() {
    if (_88) {
        auto* unit = sead::DynamicCast<Unk_71025b2aa8>(*_88);
        if (unit && unit->_20 > 0 && --unit->_20 == 0) {
            *_88 = nullptr;
            delete unit;
        }
        _88 = nullptr;
    }
}

}  // namespace uking::behavior
