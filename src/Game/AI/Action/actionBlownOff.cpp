#include "Game/AI/Action/actionBlownOff.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "Game/Damage/dmgDamageManager.h"
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
    const f32 reflex_ratio = *mParams.mLifeReflexRatio_s;
    s32 time = *mTime_s;
    if (reflex_ratio > 0.0f) {
        const f32 life_ratio = life / max_life;
        if (life_ratio < reflex_ratio)
            time = time + (1.0f - life_ratio / reflex_ratio) * *mParams.mAddTime_s;
    }
    _158 = time;
    setDamageCallbackTiming(mActor, 0, &_130);
}

void BlownOff::leave_() {
    sub_71005DA114(mActor, &_130);
    Ragdoll::leave_();
}

void BlownOff::loadParams_() {
    getStaticParam(&mParams.mAddTime_s, "AddTime");
    getStaticParam(&mParams.mLifeReflexRatio_s, "LifeReflexRatio");
    getStaticParam(&mParams.mImpulseRatio_s, "ImpulseRatio");
    Ragdoll::loadParams_();
}

void BlownOff::calc_() {
    if (auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor)) {
        if (actor->getCharacterController()) {
            if (_15c) {
                _15c = false;
            } else if (auto* manager = sub_710072BA90(actor)) {
                if (sub_7100736B94(manager->getField54())) {
                    if (_ec == 1)
                        _158 = sead::Mathf::min(f32(_158), f32(s32(_c0)));
                    sub_7100226488();
                }
            }
            Ragdoll::calc_();
        }
    }
}

bool BlownOff::isChangeable() const {
    return _ec == 1;
}

s32 BlownOff::m40() {
    return _158;
}

s32 BlownOff::m41(uking::dmg::DamageManager* manager) {
    return manager->getField50();
}

}  // namespace uking::action
