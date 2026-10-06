#include "Game/AI/Action/actionForkSetJustAvoid.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include <cstring>

namespace uking::action {

ForkSetJustAvoid::ForkSetJustAvoid(const InitArg& arg) : ksys::act::ai::Action(arg) {
    std::memset(&mWeaponIdx_s, 0, 0x48);
}

ForkSetJustAvoid::~ForkSetJustAvoid() = default;

bool ForkSetJustAvoid::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkSetJustAvoid::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

void ForkSetJustAvoid::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkSetJustAvoid::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mJustAvoidAngleL_s, "JustAvoidAngleL");
    getStaticParam(&mJustAvoidAngleR_s, "JustAvoidAngleR");
    getStaticParam(&mJustAvoidDistFar_s, "JustAvoidDistFar");
    getStaticParam(&mJustAvoidDistNear_s, "JustAvoidDistNear");
    getStaticParam(&mIsAddRangeToFar_s, "IsAddRangeToFar");
    getStaticParam(&mIsAddRangeToNear_s, "IsAddRangeToNear");
    getStaticParam(&mTargetBone_s, "TargetBone");
    getStaticParam(&mSeqBank_s, "SeqBank");
}

void ForkSetJustAvoid::calc_() {
    auto* actor = mActor;
    ksys::as::ASList::Unk4 query;
    if (!sub_71005DAF0C(actor, &query, *mTargetBone_s, *mSeqBank_s, true))
        return;

    ksys::act::acc::PlayerBase player;
    player.getPlayerFromPlayerInfo();
    const sead::Vector3f player_pos = player.getActorMtx().getTranslation();
    sead::Matrix34f mtx;
    m32(&mtx);
    sead::Matrix34f inverse;
    inverse.setInverse(mtx);
    sead::Vector3f local;
    local.setMul(inverse, player_pos);

    const f32 distance = sead::Mathf::sqrt(local.x * local.x + local.z * local.z);
    const f32 angle = sead::Mathf::atan2(local.x, local.z);
    f32 near_dist = *mJustAvoidDistNear_s;
    if (*mIsAddRangeToNear_s)
        near_dist += sub_71007322E8(mActor, *mWeaponIdx_s);
    if (distance > near_dist) {
        f32 far_dist = *mJustAvoidDistFar_s;
        if (*mIsAddRangeToFar_s)
            far_dist += sub_71007322E8(mActor, *mWeaponIdx_s);
        if (distance <= far_dist && angle >= -*mJustAvoidAngleR_s && angle <= *mJustAvoidAngleL_s) {
            if (player.slowTimeStuff()) {
                sead::FixedSafeString<9> key;
                sub_71005D7C94(&key, &query.name);
                player.x_1(true, key, actor);
            }
        }
    }
}

void ForkSetJustAvoid::m32(sead::Matrix34f* mtx) {
    *mtx = mActor->getMtx();
}

}  // namespace uking::action
