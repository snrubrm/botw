#include "Game/AI/Action/actionBlownOff.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

BlownOff::BlownOff(const InitArg& arg) : Ragdoll(arg) {}

BlownOff::~BlownOff() = default;

bool BlownOff::init_(sead::Heap* heap) {
    return Ragdoll::init_(heap);
}

void BlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    Ragdoll::enter_(params);
    _15c = true;

    const s32* life_ptr = mActor->getLife();
    const f32 life = life_ptr ? *life_ptr : 1.0f;
    const s32 max_life = mActor->getMaxLife();
    const f32 reflex_ratio = *mLifeReflexRatio_s;
    s32 time = *mTime_s;
    if (reflex_ratio > 0.0f) {
        const f32 life_ratio = life / max_life;
        if (life_ratio < reflex_ratio)
            time = time + (1.0f - life_ratio / reflex_ratio) * *mAddTime_s;
    }
    _158 = time;
    setDamageCallbackTiming(mActor, 0, &_130);
}

void BlownOff::leave_() {
    sub_71005DA114(mActor, &_130);
    Ragdoll::leave_();
}

void BlownOff::loadParams_() {
    getStaticParam(&mAddTime_s, "AddTime");
    getStaticParam(&mLifeReflexRatio_s, "LifeReflexRatio");
    getStaticParam(&mImpulseRatio_s, "ImpulseRatio");
    Ragdoll::loadParams_();
}

void BlownOff::calc_() {
    Ragdoll::calc_();
}

bool BlownOff::isChangeable() const {
    return _ec == 1;
}

}  // namespace uking::action
