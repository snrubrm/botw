#include "Game/AI/Action/actionEventChangeShadowNearAndFar.h"
#include "Game/gameGraphics.h"

namespace uking::action {

EventChangeShadowNearAndFar::EventChangeShadowNearAndFar(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventChangeShadowNearAndFar::~EventChangeShadowNearAndFar() = default;

bool EventChangeShadowNearAndFar::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventChangeShadowNearAndFar::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventChangeShadowNearAndFar::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventChangeShadowNearAndFar::loadParams_() {
    getDynamicParam(&mManualNearValue_d, "ManualNearValue");
    getDynamicParam(&mManualFarValue_d, "ManualFarValue");
    getDynamicParam(&mIsNearSetManual_d, "IsNearSetManual");
    getDynamicParam(&mIsFarSetManual_d, "IsFarSetManual");
}

// NON_MATCHING: register allocation of the flag / value temporaries only.
void EventChangeShadowNearAndFar::calc_() {
    if (auto* graphics = Graphics::instance()) {
        if (auto* shadow = graphics->getUnk_a98()) {
            if (*mIsNearSetManual_d) {
                shadow->mShadowNear = *mManualNearValue_d;
                shadow->mFlags |= 0x100;
            }
            if (*mIsFarSetManual_d) {
                shadow->mShadowFar = *mManualFarValue_d;
                shadow->mFlags |= 0x200;
            }
        }
    }
}

}  // namespace uking::action
