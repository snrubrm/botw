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
    auto* actor = mActor;
    auto* life = actor->getLife();
    _100 = life ? *life : 1;
    _f4 = _f8 = *mTimer_s;
    _fc = -1.0f;
    if (auto* sandworm = sead::DynamicCast<act::Sandworm>(mActor)) {
        sandworm->_15b0 = *mTargetSandOffset_s;
        sandworm->_1638 = true;
        sandworm->_15ac = *mSandOffsetSpeed_s;
        sandworm->_1638 = true;
    }
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    _104 = true;
    if (auto* model = mActor->getModel()) {
        _80.search(model, "Spine_4");
        _b8.search(model, "Spine_8");
    }
    _f0 = 0;
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
