#include "Game/Actor/AI/aiLandHumEnemyFindBait.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007368A4.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actBoneControl.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include <cmath>
#include "KingSystem/System/VFR.h"

namespace uking::ai {

LandHumEnemyFindBait::LandHumEnemyFindBait(const InitArg& arg) : UnarmedEnemySearch(arg) {}

LandHumEnemyFindBait::~LandHumEnemyFindBait() = default;

void LandHumEnemyFindBait::enter_(ksys::act::ai::InlineParamPack* params) {
    UnarmedEnemySearch::enter_(params);
    _b4 = 10;
    _b8 = 45;
    _b0 = sead::GlobalRandom::instance()->getS32Range(10, 45);
    if (*mIsNotice_d)
        changeToNotice();
    else
        m37();
}

void LandHumEnemyFindBait::changeToNotice() {
    sead::Vector3f pos = sead::Vector3f::zero;
    if (mTargetBait_d->hasProc()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(mTargetBait_d, &accessor);
        accessor.getActorMtx().getTranslation(pos);
    }
    ksys::act::ai::InlineParamPack params;
    params.addVec3(pos, "TargetPos", -1);
    changeChild("気づき", &params);
}

// NON_MATCHING: the bait accessor address is kept in a register for its destructor (two instructions).
void LandHumEnemyFindBait::calc_() {
    if (isCurrentChild("餌発見")) {
        auto* child = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcChild());
        if (child) {
            if (auto* unk = sub_71005D9D68(mActor))
                unk->sub_71002DC3A8(child, 0x100);
        }
    } else {
        UnarmedEnemySearch::calc_();
    }

    if (isGoStraightOrMove()) {
        ksys::act::ActorLinkConstDataAccess bait;
        if (mTargetBait_d->hasProc()) {
            ksys::act::acquireActor(mTargetBait_d, &bait);
            sead::Vector3f pos;
            bait.getActorMtx().getTranslation(pos);
            sub_71005DB068(mActor, pos);
        } else {
            sub_71005DB3EC(mActor);
        }
    } else {
        sub_71005DB3EC(mActor);
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("気づき")) {
            m37();
            return;
        }
        if (isCurrentChild("怒り")) {
            setFinished();
            return;
        }
        if (isCurrentChild("疑似餌発見") || isCurrentChild("餌発見")) {
            if (auto* unit = ksys::act::sub_7100D82FFC(mActor->getBoneControl()))
                unit->_8c &= 0xffcf;
            sub_71005DB498(mActor);
            if (getCurrentChild()->isFinished()) {
                setFinished();
                return;
            }
            if (sub_71005DEC08(mTargetBait_d, mActor, 999.0f, 999.0f, sead::Mathf::pi())) {
                changeToAngry();
                return;
            }
            m37();
            return;
        }
    }

    if (!getCurrentChild()->isChangeable())
        return;

    if (isCurrentChild("怒り") && _a0.hasProc()) {
        ksys::act::ActorLinkConstDataAccess target;
        ksys::act::acquireActor(&_a0, &target);
        const sead::Vector3f pos = target.getActorMtx().getTranslation();
        getCurrentChild()->setDynamicParam(pos, "TargetPos");
        return;
    }

    if (!isCurrentChild("餌発見"))
        return;
    ksys::act::ActorLinkConstDataAccess bait;
    ksys::act::acquireActor(mTargetBait_d, &bait);
    const sead::Vector3f pos = bait.getActorMtx().getTranslation();
    getCurrentChild()->setDynamicParam(pos, "TargetPos");
    if (*mIsValidForceNeck_s)
        sub_710045F398();
}

// NON_MATCHING: scheduling of the FixedObjList free-list initialisation (same stores).
void LandHumEnemyFindBait::m37() {
    if (!mTargetBait_d->hasProc()) {
        setFailed();
        return;
    }
    _90.reset(*mRepathTime_s);
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(mTargetBait_d, &accessor);
    sead::Vector3f target;
    accessor.getActorMtx().getTranslation(target);
    if (!sub_710072E154(mActor, target, nullptr, -1)) {
        if (!isGoStraightOrMove())
            changeToLookAround();
        sead::FixedObjList<sead::Vector3f, 8> points;
        points.emplaceBack(target);
        m41(points);
    } else if (!isGoStraight()) {
        startMoveToTargetMaybe(target);
    } else {
        getCurrentChild()->setDynamicParam(target, "TargetPos");
    }
}

// NON_MATCHING: register allocation of the direction and the accessor address kept for its destructor.
// Turns the neck towards the bait (yaw / pitch relative to the actor axes, smoothed by VFR::lerp); releases the
// neck control when the bait is gone.
void LandHumEnemyFindBait::sub_710045F398() {
    ksys::act::ActorLinkConstDataAccess bait;
    ksys::act::acquireActor(mTargetBait_d, &bait);
    if (!bait.hasProc() || bait.sub_7100D10E6C(30)) {
        if (auto* unit = ksys::act::sub_7100D82FFC(mActor->getBoneControl()))
            unit->_8c &= 0xffcf;
        sub_71005DB498(mActor);
        return;
    }

    sead::Vector3f dir = bait.getActorMtx().getTranslation();
    auto* unit = ksys::act::sub_7100D82FFC(mActor->getBoneControl());
    if (!unit)
        return;
    unit->_8c |= 0x20;
    sead::Vector3f base;
    unit->sub_7100D88CF4(&base);
    dir -= base;
    dir.normalize();

    const sead::Matrix34f& mtx = mActor->getMtx();
    const f32 side = dir.dot(mtx.getBase(0));
    const f32 up = dir.dot(mtx.getBase(1));
    const f32 front = dir.dot(mtx.getBase(2));
    f32 angle = -std::atan2(side, front);
    ksys::VFR::lerp(&_bc, angle, 0.15f, 0.20943952f, 0.017453292f);
    angle = std::atan2(up, std::sqrt(side * side + front * front));
    ksys::VFR::lerp(&_c0, angle, 0.15f, 0.20943952f, 0.017453292f);
    sub_71005DB44C(mActor, _bc, _c0);
}

bool LandHumEnemyFindBait::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void LandHumEnemyFindBait::leave_() {
    UnarmedEnemySearch::leave_();
    sub_71005DB3EC(mActor);
    if (auto* unit = ksys::act::sub_7100D82FFC(mActor->getBoneControl()))
        unit->_8c &= 0xffcf;
    sub_71005DB498(mActor);
    mActor->resetConnectedCalcChild(true);
    if (*mIsDropWeapon_s && !sub_71005D8B60(mActor)) {
        if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
            enemy->sub_7100007A1C(sead::Vector3f::zero, false, false, nullptr, false);
    }
}

void LandHumEnemyFindBait::loadParams_() {
    UnarmedEnemySearch::loadParams_();
    getStaticParam(&mRepathTime_s, "RepathTime");
    getDynamicParam(&mTargetBait_d, "TargetBait");
    getDynamicParam(&mIsNotice_d, "IsNotice");
    getStaticParam(&mIsDropWeapon_s, "IsDropWeapon");
    getStaticParam(&mIsValidForceNeck_s, "IsValidForceNeck");
}

void LandHumEnemyFindBait::changeToAngry() {
    s32 value = _b4;
    if (_b8 != _b4)
        value = sead::GlobalRandom::instance()->getS32Range(_b4, _b8);
    _b0 = value;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_58, "TargetPos", -1);
    changeChild("怒り", &pack);
}

bool LandHumEnemyFindBait::sub_710045FC10() {
    if (sub_71005DEC08(mTargetBait_d, mActor, 999.0f, 999.0f, sead::Mathf::pi()))
        return false;
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(mTargetBait_d, &accessor);
    const auto& target_pos = accessor.getActorMtx().getTranslation();
    const auto& pos = mActor->getMtx().getTranslation();
    if ((target_pos - pos).length() <= getReachDistanceMaybe())
        return true;
    return sub_7100739030(mActor, *mTargetBait_d);
}

// NON_MATCHING: the original keeps &_b0 in a register across the branches (a reference local reproduced
// it but was rejected as register steering).
void LandHumEnemyFindBait::m38() {
    if (sub_71005DEC08(mTargetBait_d, mActor, 999.0f, 999.0f, sead::Mathf::pi())) {
        ksys::Timer::update(&_b0, -1.0f);
    } else {
        _b0 = _b4 == _b8 ? _b4 : sead::GlobalRandom::instance()->getS32Range(_b4, _b8);
    }
    if (_b0 <= 0.0f) {
        changeToAngry();
        return;
    }
    if (sub_710045FC10()) {
        if (ksys::act::isWeaponProfile(mTargetBait_d)) {
            ksys::act::ai::InlineParamPack params;
            params.addActor(*mTargetBait_d, "TargetWeapon", -1);
            changeChild("疑似餌発見", &params);
        } else {
            changeToFindBait();
        }
    } else {
        _90.update();
        if (_90.value <= sead::Mathf::epsilon())
            m37();
    }
}

// NON_MATCHING: the original keeps &_b0 in a register across the branches (a reference local reproduced
// it but was rejected as register steering).
void LandHumEnemyFindBait::m39() {
    if (sub_71005DEC08(mTargetBait_d, mActor, 999.0f, 999.0f, sead::Mathf::pi())) {
        ksys::Timer::update(&_b0, -1.0f);
    } else {
        _b0 = _b4 == _b8 ? _b4 : sead::GlobalRandom::instance()->getS32Range(_b4, _b8);
    }
    if (_b0 <= 0.0f) {
        changeToAngry();
        return;
    }
    if (sub_710045FC10()) {
        if (ksys::act::isWeaponProfile(mTargetBait_d)) {
            ksys::act::ai::InlineParamPack params;
            params.addActor(*mTargetBait_d, "TargetWeapon", -1);
            changeChild("疑似餌発見", &params);
        } else {
            changeToFindBait();
        }
    } else {
        m37();
    }
}

void LandHumEnemyFindBait::changeToFindBait() {
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(mTargetBait_d, &accessor);
    sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x8000001), mActor);
    sead::Vector3f pos;
    accessor.getActorMtx().getTranslation(pos);
    _bc = sub_71005DB4DC(mActor);
    _c0 = sub_71005DB4FC(mActor);
    ksys::act::ai::InlineParamPack pack;
    pack.addActor(*mTargetBait_d, "TargetActor", -1);
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("餌発見", &pack);
}

}  // namespace uking::ai
