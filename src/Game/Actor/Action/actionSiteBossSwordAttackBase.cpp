#include "Game/Actor/Action/actionSiteBossSwordAttackBase.h"
#include "Game/Actor/actSiteBoss.h"
#include "Game/Actor/actWeapon.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/System/VFR.h"
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

// NON_MATCHING: register allocation (position x / z swapped between w23 and w25).
void SiteBossSwordAttackBase::calc_() {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }

    const sead::Vector3f up = sead::Vector3f::ey;
    sub_710073FA94(&_ac, mActor);
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    sead::Vector3f dir = *mTargetPos_d;
    dir -= pos;
    dir.y = 0.0f;

    if (sub_71005DD798(mActor, 0x29, nullptr, 0, 0)) {
        _a0.lerp(*mRotSpd_s, 0.16f, *mRotSpd_s / 10.0f);
        _a0.updateStats();
        sub_710074006C(&_ac, dir, up, true, *mBaseRotRatio_s, _a0.value, _a0.value / 10.0f);
        const f32 distance = dir.length();
        if (distance > 0.0f)
            dir *= 1.0f / distance;
        const f32 keep_dist = *mKeepDistance_s;
        if (distance > keep_dist * 1.1f) {
            const f32 speed = *mMoveSpeed_s;
            const f32 move = sead::Mathf::min(distance > keep_dist * 2 ? distance * 0.9f : speed, speed);
            dir *= move * ksys::VFR::instance()->getDeltaFrame();
            pos += dir;
        } else if (distance < keep_dist * 0.9f) {
            const f32 move = sead::Mathf::min(distance, *mMoveSpeed_s);
            dir *= move * ksys::VFR::instance()->getDeltaFrame();
            pos -= dir;
        }
        controller->sub_7100F5F938(sead::Matrix34f(_ac, pos));
    } else {
        sead::Vector3f linear_velocity;
        sead::Vector3f velocity;
        controller->sub_7100F635BC(&velocity);
        velocity *= 0.75f;
        controller->sub_7100F5FB24(velocity);
        controller->sub_7100F5F598(&linear_velocity);
        velocity = linear_velocity;
        velocity *= *mPosReduceRatio_s;
        controller->sub_7100F5F6FC(velocity);
    }

    sub_71005DAB2C(mActor, *mJustAvoidSideDist_s + 2.0f, *mJustAvoidBackDist_s + 2.0f,
                   *mJustAvoidAngle_s, 0);

    ksys::as::ASList::Unk4 query;
    if (sub_71005DD66C(mActor, &query, 0, 0) || sub_71005DD780(mActor, 0x51, &query, 0, 0)) {
        auto* actor = mActor;
        const u32 attack_flags = m33();
        const f32 power = f32(m34());
        sub_71005D7ADC(actor, 0, attack_flags, &query.name, nullptr, m35(), 1, 0, 1, power, 1.0f);
    } else if (sub_71005DD74C(mActor, nullptr, 0, 0)) {
        sub_71005D79AC(mActor, 0, act::Unk_71002edaec(1));
    }

    if (isFinishedAS(0, 0))
        setFinished();
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
