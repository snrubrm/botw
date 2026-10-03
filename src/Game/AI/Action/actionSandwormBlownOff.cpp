#include "Game/AI/Action/actionSandwormBlownOff.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actSandworm.h"

namespace uking::action {

SandwormBlownOff::SandwormBlownOff(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SandwormBlownOff::~SandwormBlownOff() = default;

bool SandwormBlownOff::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SandwormBlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SandwormBlownOff::leave_() {
    _80.getKey().reset();
    _b8.getKey().reset();
    if (auto* sandworm = sead::DynamicCast<act::Sandworm>(mActor))
        sandworm->_15a8 = 0;
}

void SandwormBlownOff::loadParams_() {
    getStaticParam(&mLimitDamage_s, "LimitDamage");
    getStaticParam(&mSandOffsetSpeed_s, "SandOffsetSpeed");
    getStaticParam(&mTargetSandOffset_s, "TargetSandOffset");
    getStaticParam(&mTimer_s, "Timer");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mDamageASName_s, "DamageASName");
    getStaticParam(&mSmallDamageASName_s, "SmallDamageASName");
    getStaticParam(&mDamageRigidName_s, "DamageRigidName");
}

void SandwormBlownOff::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
