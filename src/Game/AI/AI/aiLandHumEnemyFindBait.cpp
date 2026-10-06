#include "Game/AI/AI/aiLandHumEnemyFindBait.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actBoneControl.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

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
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(mTargetBait_d, &accessor);
        accessor.getActorMtx().getTranslation(pos);
    }
    ksys::act::ai::InlineParamPack params;
    params.addVec3(pos, "TargetPos", -1);
    changeChild("気づき", &params);
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
    ksys::act::ActorConstDataAccess accessor;
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
    ksys::act::ActorConstDataAccess accessor;
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
