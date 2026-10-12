#include "Game/AI/Action/actionHorseFollowBase.h"
#include <limits>
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::action {

HorseFollowBase::HorseFollowBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HorseFollowBase::~HorseFollowBase() = default;

bool HorseFollowBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HorseFollowBase::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    _b0 = -1;
    _b4 = 0.0f;
    if (auto* nav = mActor->m45()) {
        if (!*mIsAvoidNavMeshActor_s) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(m33(), &accessor);
            if (auto* other = accessor.sub_7100D0F57C())
                _b0 = nav->sub_7100F7D1CC(other);
        }
        if (*mNavMeshCharacterRadiusScale_s != 1.0f) {
            _b4 = nav->_2ac;
            const f32 radius_scale = _b4 * *mNavMeshCharacterRadiusScale_s;
            if (!sead::Mathf::isNan(radius_scale) &&
                !(sead::Mathf::abs(radius_scale) > sead::Mathf::maxNumber()) &&
                nav->_2ac != radius_scale) {
                auto lock = sead::makeScopedLock(nav->_1e0);
                nav->_2ac = radius_scale;
                nav->_220 |= 0x10;
            }
        }
    }
    _b8 = 0.0f;
    _bc = false;
}

void HorseFollowBase::leave_() {
    if (auto* nav = mActor->m45()) {
        if (_b0 >= 0)
            nav->sub_7100F7D2C8();
        const f32 radius_scale = _b4;
        if (radius_scale != 0.0f && !sead::Mathf::isNan(radius_scale) &&
            !(sead::Mathf::abs(radius_scale) > sead::Mathf::maxNumber()) &&
            nav->_2ac != radius_scale) {
            auto lock = sead::makeScopedLock(nav->_1e0);
            nav->_2ac = radius_scale;
            nav->_220 |= 0x10;
        }
        nav->sub_7100F76314();
    }
}

void HorseFollowBase::loadParams_() {
    getStaticParam(&mUseGearType_s, "UseGearType");
    getStaticParam(&mWaitDistanceToLeader_s, "WaitDistanceToLeader");
    getStaticParam(&mGear1DistanceToLeader_s, "Gear1DistanceToLeader");
    getStaticParam(&mGear2DistanceToLeader_s, "Gear2DistanceToLeader");
    getStaticParam(&mGear3DistanceToLeader_s, "Gear3DistanceToLeader");
    getStaticParam(&mDistanceFactorAtGearDown_s, "DistanceFactorAtGearDown");
    getStaticParam(&mWaitDistanceIncreaseDistance_s, "WaitDistanceIncreaseDistance");
    getStaticParam(&mWaitDistanceIncreasePerFrame_s, "WaitDistanceIncreasePerFrame");
    getStaticParam(&mAutoStopAndTurnDistance_s, "AutoStopAndTurnDistance");
    getStaticParam(&mDesiredDirAngleDeltaSecMax_s, "DesiredDirAngleDeltaSecMax");
    getStaticParam(&mNavMeshCharacterRadiusScale_s, "NavMeshCharacterRadiusScale");
    getStaticParam(&mCanUseHorseGearInput_s, "CanUseHorseGearInput");
    getStaticParam(&mIsAutoGearDownEnabled_s, "IsAutoGearDownEnabled");
    getStaticParam(&mIsEndAtAutoStop_s, "IsEndAtAutoStop");
    getStaticParam(&mUseMinRadius_s, "UseMinRadius");
    getStaticParam(&mIsAvoidNavMeshActor_s, "IsAvoidNavMeshActor");
    getStaticParam(&mIsTargetPosEqualToLeaderPos_s, "IsTargetPosEqualToLeaderPos");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void HorseFollowBase::calc_() {
    ksys::act::ai::Action::calc_();
}

float HorseFollowBase::m32() {
    return 0.0f;
}

ksys::act::BaseProcLink* HorseFollowBase::m33() {
    return &ksys::act::sUnk_71026505e0;
}

}  // namespace uking::action
