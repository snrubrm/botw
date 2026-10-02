#include "Game/AI/Action/actionWizzrobeChanceTime.h"

namespace uking::action {

WizzrobeChanceTime::WizzrobeChanceTime(const InitArg& arg) : HoverBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
WizzrobeChanceTime::~WizzrobeChanceTime() {
    ;
}

bool WizzrobeChanceTime::init_(sead::Heap* heap) {
    return HoverBase::init_(heap);
}

void WizzrobeChanceTime::enter_(ksys::act::ai::InlineParamPack* params) {
    HoverBase::enter_(params);
    if (!mASName_s.isEmpty())
        playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    const f32 counter = *mDefaultCounter_s;
    if (counter <= 0.0f) {
        setFinished();
        return;
    }
    _68 = ksys::Timer(counter, counter);
}

void WizzrobeChanceTime::leave_() {
    HoverBase::leave_();
}

void WizzrobeChanceTime::loadParams_() {
    HoverBase::loadParams_();
    getStaticParam(&mDefaultCounter_s, "DefaultCounter");
    getStaticParam(&mDamageCounter_s, "DamageCounter");
    getStaticParam(&mASName_s, "ASName");
}

void WizzrobeChanceTime::calc_() {
    HoverBase::calc_();
}

}  // namespace uking::action
