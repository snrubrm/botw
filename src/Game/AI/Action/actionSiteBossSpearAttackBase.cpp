#include "Game/AI/Action/actionSiteBossSpearAttackBase.h"
#include "Game/Actor/actSiteBoss.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"
#include "Game/Actor/actWeapon.h"

namespace uking::action {

SiteBossSpearAttackBase::SiteBossSpearAttackBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SiteBossSpearAttackBase::~SiteBossSpearAttackBase() = default;

bool SiteBossSpearAttackBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossSpearAttackBase::enter_(ksys::act::ai::InlineParamPack* params) {
    const sead::Vector3f up = sead::Vector3f::ey;
    const f32 speed = mActor->getAngVelocity().length();
    _c0.value = speed;
    _c0.prev_value = speed;
    sub_710073FA90(&_cc, mActor);

    sead::Vector3f to_target = *mTargetPos_d;
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    to_target -= pos;
    ksys::util::sub_71011EFA00(&to_target, to_target, up);
    to_target.normalize();

    sead::Vector3f front;
    mActor->getMtx().getBase(front, 2);
    ksys::util::sub_71011EFA00(&front, front, up);
    front.normalize();

    sead::Vector3f axis;
    f32 angle;
    ksys::util::sub_71011EEB08(&axis, &angle, front, to_target, sead::Vector3f::ey);
    mActor->getASList()->x_6(9, 0, sead::Mathf::rad2deg(angle) * axis.y);
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    mFlags.set(Flag::Changeable);
}

// NON_MATCHING: the original addresses _2378-_237b through one base register (as if they were
// members of a struct at SiteBoss+0x2378)
void SiteBossSpearAttackBase::leave_() {
    sub_71005D79AC(mActor, 0, act::Unk_71002edaec(1));
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        if (boss->_2378) {
            boss->_237a = boss->_237b;
            boss->_2378 = 0;
        }
        if (boss->_2379) {
            boss->_237c = boss->_2380;
            boss->_2384 = boss->_2388;
            boss->_2379 = 0;
        }
    }
}

void SiteBossSpearAttackBase::loadParams_() {
    getStaticParam(&mAtMinDamage_s, "AtMinDamage");
    getStaticParam(&mAttackPower_s, "AttackPower");
    getStaticParam(&mAddAttackPower_s, "AddAttackPower");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mBaseRotRatio_s, "BaseRotRatio");
    getStaticParam(&mJustAvoidAngle_s, "JustAvoidAngle");
    getStaticParam(&mJustAvoidSideDist_s, "JustAvoidSideDist");
    getStaticParam(&mJustAvoidBackDist_s, "JustAvoidBackDist");
    getStaticParam(&mTargetOffsetLowAtRotate_s, "TargetOffsetLowAtRotate");
    getStaticParam(&mTargetOffsetHighAtRotate_s, "TargetOffsetHighAtRotate");
    getStaticParam(&mCanBreakIceBlock_s, "CanBreakIceBlock");
    getStaticParam(&mIsOnSpine1Rotate_s, "IsOnSpine1Rotate");
    getStaticParam(&mIsOnSpine2Rotate_s, "IsOnSpine2Rotate");
    getStaticParam(&mIsOnSpine3Rotate_s, "IsOnSpine3Rotate");
    getStaticParam(&mCanJustAvoid_s, "CanJustAvoid");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void SiteBossSpearAttackBase::calc_() {
    ksys::act::ai::Action::calc_();
}

bool SiteBossSpearAttackBase::isFinished() const {
    return isFinishedAS(0, 0);
}

int SiteBossSpearAttackBase::m34() {
    return *mAtMinDamage_s;
}

int SiteBossSpearAttackBase::m32() {
    return 322;
}

int SiteBossSpearAttackBase::m33() {
    int level = getNumberOfDeadBlights();
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        const s32 kind = boss->_1534 & ~3;
        if (kind == 4)
            level = 3;
        else if (kind == 8)
            level = 4;
    }
    return *mAttackPower_s + *mAddAttackPower_s * level;
}

}  // namespace uking::action
