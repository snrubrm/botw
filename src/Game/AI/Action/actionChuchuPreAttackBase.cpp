#include "Game/AI/Action/actionChuchuPreAttackBase.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::action {

ChuchuPreAttackBase::ChuchuPreAttackBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ChuchuPreAttackBase::~ChuchuPreAttackBase() = default;

bool ChuchuPreAttackBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ChuchuPreAttackBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ChuchuPreAttackBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void ChuchuPreAttackBase::loadParams_() {
    getStaticParam(&mJumpNum_s, "JumpNum");
    getStaticParam(&mMoveBoneRotRatio_s, "MoveBoneRotRatio");
    getStaticParam(&mMoveBoneRotSpeedMin_s, "MoveBoneRotSpeedMin");
    getStaticParam(&mTurnSpeed_s, "TurnSpeed");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void ChuchuPreAttackBase::calc_() {
    ksys::act::ai::Action::calc_();
}

void ChuchuPreAttackBase::m32(u32) {}

bool ChuchuPreAttackBase::isFinished() const {
    if (ksys::act::ai::Action::isFinished())
        return true;
    if (_68 != *mJumpNum_s)
        return false;
    return isBgGroundHit(mActor, false) || sub_71005E1064(mActor);
}

}  // namespace uking::action
