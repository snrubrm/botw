#include "Game/AI/Behavior/behaviorSimpleAtvUnitOpenSimpleDialog.h"
#include "Game/AI/aiUnk_71025b2aa8.h"
#include "KingSystem/System/Timer.h"

namespace uking::behavior {

SimpleAtvUnitOpenSimpleDialog::SimpleAtvUnitOpenSimpleDialog(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

void SimpleAtvUnitOpenSimpleDialog::m7() {
    if (m15() || _85 || _84)
        return;
    if (_80 <= 0)
        sub_7100641EB8();
    else
        ksys::Timer::update(&_80, -1.0f);
}

// NON_MATCHING: the original keeps the second cast's `unit ? unit + 8 : nullptr` as branches (ours
// speculates the add and uses a csel); everything else is identical.
void SimpleAtvUnitOpenSimpleDialog::sub_7100641EB8() {
    if (!_78._0)
        return;
    auto* unit = sead::DynamicCast<Unk_71025b2aa8>(*_78._0);
    if (!unit || unit->mRefCount < 1)
        return;

    Unk_71025b2aa8Data::Request request;
    request._0 = &mmstxtName_s;
    request._8 = m14();
    request._10 = *mCloseOption_s;
    request._14 = *mType_s;
    request._18 = *mTimer_s;
    _78.getData()->sub_7100721DE4(&request);

    _84 = true;
    if (*mOnce_s)
        _85 = true;
}

void SimpleAtvUnitOpenSimpleDialog::m16() {
    _84 = false;
    f32 delay;
    if (*mDelayTimer_s <= 0) {
        delay = 0.0f;
        if (!m15())
            sub_7100641EB8();
    } else {
        delay = *mDelayTimer_s;
    }
    _80 = delay;
}

bool SimpleAtvUnitOpenSimpleDialog::updateForPreDelete() {
    _78.release();
    return true;
}

void SimpleAtvUnitOpenSimpleDialog::m8() {
    if (_85)
        return;
    m16();
}

void SimpleAtvUnitOpenSimpleDialog::m9() {}

void SimpleAtvUnitOpenSimpleDialog::loadParams() {
    getStaticParam(&mCloseOption_s, "CloseOption");
    getStaticParam(&mTimer_s, "Timer");
    getStaticParam(&mDelayTimer_s, "DelayTimer");
    getStaticParam(&mType_s, "Type");
    getStaticParam(&mOnce_s, "Once");
    getStaticParam(&mmstxtName_s, "mstxtName");
    getStaticParam(&mlabelName_s, "labelName");
    getAITreeVariable(&mSimpleDialogUnit_a, "SimpleDialogUnit");
}

const sead::SafeString* SimpleAtvUnitOpenSimpleDialog::m14() {
    return &mlabelName_s;
}

SimpleAtvUnitOpenSimpleDialog::~SimpleAtvUnitOpenSimpleDialog() = default;

bool SimpleAtvUnitOpenSimpleDialog::m6(sead::Heap* heap) {
    if (!_78.acquire(heap, static_cast<Unk_71025afb58**>(mSimpleDialogUnit_a)))
        return false;
    _85 = false;
    return true;
}

}  // namespace uking::behavior
