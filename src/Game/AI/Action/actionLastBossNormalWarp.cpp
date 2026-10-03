#include "Game/AI/Action/actionLastBossNormalWarp.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::action {

LastBossNormalWarp::LastBossNormalWarp(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LastBossNormalWarp::~LastBossNormalWarp() = default;

bool LastBossNormalWarp::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LastBossNormalWarp::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void LastBossNormalWarp::leave_() {
    if (!_b2) {
        _b2 = true;
        if (auto* cc = mActor->getCharacterController()) {
            cc->sub_7100F60604();
            if (auto* physics = mActor->getPhysics()) {
                physics->sub_7100FBDFA4(physics->get178(0));
                if (!*mIsKeepDisableDraw_d)
                    physics->sub_7100FBAD74();
            }
        }
    }
    if (auto* cc = mActor->getCharacterController()) {
        cc->sub_7100F63554(true);
        cc->sub_7100F5E764(true);
        cc->sub_7100F62CA8(true);
    }
}

void LastBossNormalWarp::loadParams_() {
    getStaticParam(&mOffsetLength_s, "OffsetLength");
    getStaticParam(&mOffsetY_s, "OffsetY");
    getStaticParam(&mWarpTime_s, "WarpTime");
    getStaticParam(&mCheckShapeRadius_s, "CheckShapeRadius");
    getStaticParam(&mIsUseChangePos_s, "IsUseChangePos");
    getStaticParam(&mIsEscapeFromPlayer_s, "IsEscapeFromPlayer");
    getStaticParam(&mIsWarpAtGround_s, "IsWarpAtGround");
    getStaticParam(&mIsChasePlayer_s, "IsChasePlayer");
    getStaticParam(&mDisableGroundHit_s, "DisableGroundHit");
    getStaticParam(&mDisableAirWallHit_s, "DisableAirWallHit");
    getStaticParam(&mChaseDist_s, "ChaseDist");
    getStaticParam(&mChaseDistOffset_s, "ChaseDistOffset");
    getStaticParam(&mHomePosOffset_s, "HomePosOffset");
    getDynamicParam(&mIsReturnHome_d, "IsReturnHome");
    getDynamicParam(&mIsForceWarp_d, "IsForceWarp");
    getDynamicParam(&mIsPartsActorTgOn_d, "IsPartsActorTgOn");
    getDynamicParam(&mIsKeepDisableDraw_d, "IsKeepDisableDraw");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void LastBossNormalWarp::calc_() {
    ksys::act::ai::Action::calc_();
}

bool LastBossNormalWarp::m32() {
    return *mIsWarpAtGround_s;
}

float LastBossNormalWarp::m33() {
    return *mOffsetY_s;
}

}  // namespace uking::action
