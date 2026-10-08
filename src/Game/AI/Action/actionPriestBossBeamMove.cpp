#include "Game/AI/Action/actionPriestBossBeamMove.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

PriestBossBeamMove::PriestBossBeamMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

PriestBossBeamMove::~PriestBossBeamMove() = default;

bool PriestBossBeamMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PriestBossBeamMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void PriestBossBeamMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void PriestBossBeamMove::loadParams_() {
    getStaticParam(&mAtMinDamage_s, "AtMinDamage");
    getStaticParam(&mShieldDamage_s, "ShieldDamage");
    getStaticParam(&mContactWaitFrame_s, "ContactWaitFrame");
    getStaticParam(&mReflectDeccel_s, "ReflectDeccel");
    getMapUnitParam(&mAttackPower_m, "AttackPower");
    getMapUnitParam(&mAttackPowerForPlayer_m, "AttackPowerForPlayer");
    getMapUnitParam(&mPosOffset_m, "PosOffset");
}

void PriestBossBeamMove::calc_() {
    ksys::act::ai::Action::calc_();
}

void PriestBossBeamMove::sub_710006566C(const sead::Vector3f& pos) {
    sead::Matrix34f mtx;
    _b8->getTransform(&mtx);
    if (pos != sead::Vector3f::zero) {
        mtx.setTranslation(pos);
        _b8->setTransform(mtx);
        _c0->setTransform(mtx);
        _c8->setTransform(mtx);
    }
    _b8->setLinearVelocity(sead::Vector3f::zero);
    _c0->setLinearVelocity(sead::Vector3f::zero);
    _c8->setLinearVelocity(sead::Vector3f::zero);
}

bool PriestBossBeamMove::isFinished() const {
    auto* actor = mActor;
    if (hasAttackInfo(actor)) {
        auto* info = getAttackInfo(actor, 0);
        if (info && (info->_18 & 0xb))
            return ksys::act::ai::Action::isFinished();
    }
    if (_d0)
        return ksys::act::ai::Action::isFinished();

    if (!_d3 || !ksys::act::ai::Action::isFinished())
        return false;
    if (_d4)
        return true;
    sead::Matrix34f mtx;
    _b8->getTransform(&mtx);
    _c8->setTransform(mtx);
    _c8->setLinearVelocity(sead::Vector3f::zero);
    _d4 = true;
    return true;
}

}  // namespace uking::action
