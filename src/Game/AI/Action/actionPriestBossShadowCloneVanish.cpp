#include "Game/AI/Action/actionPriestBossShadowCloneVanish.h"

// Source namespace unknown; shared by the actor and screen consumers.
void sub_710071EBA4(ksys::act::Actor* actor);

namespace uking::action {

PriestBossShadowCloneVanish::PriestBossShadowCloneVanish(const InitArg& arg)
    : PriestBossWarpOrVanish(arg) {}

PriestBossShadowCloneVanish::~PriestBossShadowCloneVanish() = default;

bool PriestBossShadowCloneVanish::init_(sead::Heap* heap) {
    return PriestBossWarpOrVanish::init_(heap);
}

void PriestBossShadowCloneVanish::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossWarpOrVanish::enter_(params);
    const f32 delay = *mDelayFrames_s;
    _30.value = delay;
    _30.previous_value = delay;
}

void PriestBossShadowCloneVanish::leave_() {
    PriestBossWarpOrVanish::leave_();
}

void PriestBossShadowCloneVanish::loadParams_() {
    PriestBossWarpOrVanish::loadParams_();
    getStaticParam(&mDelayFrames_s, "DelayFrames");
}

void PriestBossShadowCloneVanish::calc_() {
    PriestBossWarpOrVanish::calc_();
    if (isFinished() || isFailed())
        return;
    _30.update();
    if (_30.value <= sead::Mathf::epsilon()) {
        sub_710071EBA4(mActor);
        setFinished();
    }
}

}  // namespace uking::action
