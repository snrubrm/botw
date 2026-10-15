#include "Game/Actor/Behavior/behaviorSimpleAtvUnitOpDlgRestWpTimeR3Base.h"
#include "Game/Actor/aiUnk_71025b2aa8.h"
#include "Game/Actor/aiUnk_71025b27b8.h"

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

SimpleAtvUnitOpDlgRestWpTimeR3Base::~SimpleAtvUnitOpDlgRestWpTimeR3Base() = default;

bool SimpleAtvUnitOpDlgRestWpTimeR3Base::m6(sead::Heap* heap) {
    return _88.acquire(heap, static_cast<Unk_71025afb58**>(mSimpleDialogUnit_a));
}

// NON_MATCHING: the existing holder getData uses conditional selection instead of the native branch.
void SimpleAtvUnitOpDlgRestWpTimeR3Base::m7() {
    if (!_88._0)
        return;
    auto* unit = sead::DynamicCast<Unk_71025b2aa8>(*_88._0);
    if (!unit || unit->mRefCount < 1)
        return;
    if (!*mIsWeakPointAppearMode_a) {
        _90 = false;
        return;
    }
    if (_90)
        return;
    auto* counter = sead::DynamicCast<Unk_71025b27b8>(
        *static_cast<Unk_71025afb58**>(mWeakPointCounter_a));
    if (!counter || !(counter->_8 < static_cast<f32>(*mRestTime_s)) ||
        *mInBeastGanonVoiceSequence_a)
        return;
    m15();
    Unk_71025b2aa8Data::Request request;
    request._0 = &mmstxtName_s;
    request._8 = m14();
    request._10 = *mCloseOption_s;
    request._14 = *mType_s;
    request._18 = *mTimer_s;
    _88.getData()->sub_7100721DE4(&request);
    _90 = true;
}

}  // namespace uking::behavior
