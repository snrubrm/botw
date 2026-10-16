#include "Game/Actor/Action/actionBlownOff.h"
#include "Game/Actor/aiUnk_71007368A4.h"
#include "Game/Actor/aiUnk_710072BA90.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "Game/Actor/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actUnk_71006ecc78.h"

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

void BlownOff::m38() {
    auto* actor = mActor;
    auto* manager = sub_710072BA90(actor);
    if (manager && manager->checkDamageFlags(21)) {
        Ragdoll::m38();
        return;
    }
    sub_7100227134();
    if (auto* dynamic_actor = sead::DynamicCast<ksys::act::DynamicActor>(actor)) {
        ksys::act::Unk_71006ED100Arg arg;
        arg._5e = !isBgGroundHit(dynamic_actor, false);
        if (manager) {
            manager->getAttackSourceMtx(&arg._0);
            arg._5f = manager->getAttackInfoFlagFC();
            arg._30 = m41(manager);
            arg._34 = manager->getField54();
            manager->getAttackDirType(&arg._38);
            manager->getDamageImpulse(&arg._40);
            arg._40 *= *mParams.mImpulseRatio_s;
            manager->getPosition(&arg._4c);
            arg._3c = manager->getField40();
            arg._5c = manager->sub_71006EE2B0();
            arg._5d = *manager->getAttacker() == *manager->m37();
            arg._61 = manager->checkDamageFlags(0);
            arg._62 = manager->checkDamageFlags(10);
            arg._58 = arg._62 ? 1.0f : manager->sub_71006D8DE8();
        }
        dynamic_actor->sub_71006DD8F8(arg);
    }
    sub_7100227184();
}

s32 BlownOff::m40() {
    return _158;
}

s32 BlownOff::m41(uking::act::DamageManager* manager) {
    return manager->getField50();
}

}  // namespace uking::action
