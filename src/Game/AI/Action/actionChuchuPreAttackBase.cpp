#include "Game/AI/Action/actionChuchuPreAttackBase.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "Game/Actor/actGelEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::action {

ChuchuPreAttackBase::ChuchuPreAttackBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ChuchuPreAttackBase::~ChuchuPreAttackBase() = default;

bool ChuchuPreAttackBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ChuchuPreAttackBase::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    _68 = 0;
    sub_710073FA90(&_6c, actor);
    const f32 speed = actor->getAngVelocity().length();
    _b4.value = speed;
    _b4.prev_value = speed;
    if (auto* gel = sead::DynamicCast<act::GelEnemy>(actor)) {
        sead::Matrix34f mtx;
        mtx = gel->_14c8._68;
        sub_710073FB74(&_90, mtx);
        gel->_1678 |= 1;
        gel->_1620.x = 0.8f;
        gel->_1620.y = 0.8f;
    }
}

void ChuchuPreAttackBase::leave_() {
    if (auto* gel = sead::DynamicCast<act::GelEnemy>(mActor)) {
        gel->_1678 &= ~1;
        gel->_14c8._68 = sead::Matrix34f::ident;
        gel->sub_7100026AD4();
        gel->sub_7100026AA8();
    }
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
