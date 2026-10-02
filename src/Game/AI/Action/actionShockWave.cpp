#include "Game/AI/Action/actionShockWave.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ShockWave::ShockWave(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ShockWave::~ShockWave() = default;

bool ShockWave::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ShockWave::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ShockWave::leave_() {
    if (auto* body = mActor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkBody")) {
        sub_71007A3258(body, nullptr);
        sub_71007A2D34(body);
    }
    if (auto* lod = mActor->getLodState()) {
        lod->mFlags10.reset(0x40);
        if (*mIsReuseActor_m)
            mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_2000);
    }
}

void ShockWave::loadParams_() {
    getMapUnitParam(&mAttackPower_m, "AttackPower");
    getMapUnitParam(&mAttackAttr_m, "AttackAttr");
    getMapUnitParam(&mAtMinDamage_m, "AtMinDamage");
    getMapUnitParam(&mScaleTime_m, "ScaleTime");
    getMapUnitParam(&mIsReuseActor_m, "IsReuseActor");
}

void ShockWave::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
