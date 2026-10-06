#include "Game/AI/Action/actionSiteBossSwordAttackBase.h"
#include "Game/Actor/actSiteBoss.h"
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

SiteBossSwordAttackBase::SiteBossSwordAttackBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SiteBossSwordAttackBase::~SiteBossSwordAttackBase() = default;

bool SiteBossSwordAttackBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossSwordAttackBase::enter_(ksys::act::ai::InlineParamPack* params) {
    const sead::Vector3f up = sead::Vector3f::ey;
    const f32 speed = mActor->getAngVelocity().length();
    _a0.value = speed;
    _a0.prev_value = speed;
    sub_710073FA90(&_ac, mActor);

    sead::Vector3f to_target = *mTargetPos_d;
    mActor->getMtx().getTranslation(_d0);
    to_target -= _d0;
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
}

void SiteBossSwordAttackBase::leave_() {
    sub_71005D79AC(mActor, 0, act::Unk_71002edaec(1));
}

void SiteBossSwordAttackBase::loadParams_() {
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
    getStaticParam(&mMoveSpeed_s, "MoveSpeed");
    getStaticParam(&mKeepDistance_s, "KeepDistance");
    getStaticParam(&mIsIgnoreCancelAttack_s, "IsIgnoreCancelAttack");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void SiteBossSwordAttackBase::calc_() {
    ksys::act::ai::Action::calc_();
}

bool SiteBossSwordAttackBase::isChangeable() const {
    return true;
}

void SiteBossSwordAttackBase::m32() {}

int SiteBossSwordAttackBase::m33() {
    return 66;
}

int SiteBossSwordAttackBase::m35() {
    return *mAtMinDamage_s;
}

bool SiteBossSwordAttackBase::isFinished() const {
    return isFinishedAS(0, 0);
}

int SiteBossSwordAttackBase::m34() {
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
