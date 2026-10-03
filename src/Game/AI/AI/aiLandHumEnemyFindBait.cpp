#include "Game/AI/AI/aiLandHumEnemyFindBait.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
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

}  // namespace uking::ai
