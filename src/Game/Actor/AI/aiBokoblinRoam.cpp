#include "Game/Actor/AI/aiBokoblinRoam.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include <random/seadGlobalRandom.h>
#include "Game/Actor/Player/actPlayerInfo.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::ai {

BokoblinRoam::BokoblinRoam(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

void BokoblinRoam::enter_(ksys::act::ai::InlineParamPack* params) {
    _dc = false;
    _dd = false;
    const s32 free_min = *mFreeIntervalMin_s;
    const s32 free_max = *mFreeIntervalMax_s;
    const s32 free_time = sead::GlobalRandom::instance()->getS32Range(free_min, free_max);
    _d0 = ksys::Timer(free_time, free_time);
    const s32 move_min = *mMoveIntervalMin_s;
    const s32 move_max = *mMoveIntervalMax_s;
    const s32 move_time = sead::GlobalRandom::instance()->getS32Range(move_min, move_max);
    _c4 = ksys::Timer(move_time, move_time);
    _bc = _c0 = *mSpAttackServiceTime_s;
    _b8 = _bc;
    changeChild("待機");
}

void BokoblinRoam::loadParams_() {
    getStaticParam(&mFreeIntervalMin_s, "FreeIntervalMin");
    getStaticParam(&mFreeIntervalMax_s, "FreeIntervalMax");
    getStaticParam(&mFreePer_s, "FreePer");
    getStaticParam(&mMoveIntervalMin_s, "MoveIntervalMin");
    getStaticParam(&mMoveIntervalMax_s, "MoveIntervalMax");
    getStaticParam(&mNoMoveTime_s, "NoMoveTime");
    getStaticParam(&mSpAttackServiceTime_s, "SpAttackServiceTime");
    getStaticParam(&mNoSpAttackMoveTime_s, "NoSpAttackMoveTime");
    getStaticParam(&mTerritory_s, "Territory");
    getStaticParam(&mTargetDistMin_s, "TargetDistMin");
    getStaticParam(&mTargetDistMax_s, "TargetDistMax");
    getStaticParam(&mSpAttackServiceDist_s, "SpAttackServiceDist");
    getStaticParam(&mSpAttackServiceAngle_s, "SpAttackServiceAngle");
    getDynamicParam(&mCentralPos_d, "CentralPos");
    getStaticParam(&mTurnCheckDist_s, "TurnCheckDist");
    getStaticParam(&mTurnCheckHeight_s, "TurnCheckHeight");
}

bool BokoblinRoam::sub_7100333E68() {
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&uking::act::PlayerInfo::getSomeProcLink(), &accessor);
    const sead::Vector3f player_position = accessor.getActorMtx().getTranslation();
    sead::Vector3f dir = player_position - mActor->getMtx().getTranslation();
    dir.y = 0.0f;
    const f32 dist = dir.normalize();
    if (dist > *mSpAttackServiceDist_s)
        return false;
    dir.negate();
    return dir.dot(mActor->getMtx().getBase(2)) >= sead::Mathf::cos(*mSpAttackServiceAngle_s);
}

bool BokoblinRoam::sub_710033433C() {
    if (*mTurnCheckDist_s < 0.0f)
        return false;
    if (*mTurnCheckHeight_s < 0.0f)
        return false;
    sead::Vector3f forward;
    mActor->getMtx().getBase(forward, 2);
    forward.normalize();
    sead::Vector3f from;
    mActor->getMtx().getTranslation(from);
    sead::Vector3f to = from + forward * *mTurnCheckDist_s;
    from.y += *mTurnCheckHeight_s;
    to.y += *mTurnCheckHeight_s;
    return sub_710072E928(from, to, nullptr, nullptr, nullptr, 0.5f);
}

void BokoblinRoam::changeToSearch() {
    const s32 min = *mFreeIntervalMin_s;
    const s32 max = *mFreeIntervalMax_s;
    _d0.reset(sead::GlobalRandom::instance()->getS32Range(min, max));
    changeChild("索敵", nullptr);
}

// NON_MATCHING: the two stores of the timer are not merged into one stp in the original
void BokoblinRoam::sub_7100333FEC() {
    ksys::act::acc::PlayerBase accessor;
    ksys::act::acquireActor(&uking::act::PlayerInfo::getSomeProcLink(), &accessor);
    if (accessor.getSpAttackTarget().hasProcById(mActor)) {
        const f32 time = *mNoSpAttackMoveTime_s;
        if (_c4.value < time) {
            _c4.value = time;
            _c4.previous_value = time;
        }
    } else {
        _c4.update();
    }
}

// NON_MATCHING: parameter-pack lifetime and target-direction scheduling differ.
s32 BokoblinRoam::sub_7100334070(bool force) {
    _dc = false;
    const s32 minimum = *mMoveIntervalMin_s;
    const s32 maximum = *mMoveIntervalMax_s;
    _c4.reset(sead::GlobalRandom::instance()->getS32Range(minimum, maximum));
    sead::Vector3f direction = mActor->getMtx().getBase(2);
    ksys::util::sub_71011EF010(&direction,
                             sead::GlobalRandom::instance()->getF32() * 0.8726646304130554f -
                                 0.4363323152065277f);
    const f32 min_distance = *mTargetDistMin_s;
    const f32 max_distance = *mTargetDistMax_s;
    const f32 distance = min_distance + (max_distance - min_distance) *
                                          sead::GlobalRandom::instance()->getF32();
    const auto target = mActor->getMtx().getTranslation() + direction * distance;
    if (!force) {
        if (!sub_710072FAB0(mActor, target, nullptr, -1, -1.0f, -1.0f))
            return 2;
        auto to_center = *mCentralPos_d - mActor->getMtx().getTranslation();
        const f32 center_distance = to_center.normalize();
        if (center_distance > (*mTerritory_s + *mTerritory_s) / 3.0f &&
            !(to_center.dot(mActor->getMtx().getBase(2)) >= 0.4999999701976776f))
            return 1;
    }
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target, "TargetPos", -1);
    changeChild("移動", &pack);
    return 0;
}

// NON_MATCHING: source shares rotation-target construction across the native direction branches.
void BokoblinRoam::sub_71003345EC(bool toward_center) {
    const s32 minimum = *mFreeIntervalMin_s;
    const s32 maximum = *mFreeIntervalMax_s;
    _d0.reset(sead::GlobalRandom::instance()->getS32Range(minimum, maximum));
    _dd = true;
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f direction;
    if (toward_center) {
        direction = *mCentralPos_d - mActor->getMtx().getTranslation();
        const f32 horizontal = sead::Vector2f(direction.x, direction.z).length();
        const auto forward = mActor->getMtx().getBase(2);
        if (horizontal <= sead::Mathf::epsilon() && horizontal >= -sead::Mathf::epsilon())
            direction = forward;
        sead::Vector3f axis;
        f32 angle;
        ksys::util::sub_71011EEB08(&axis, &angle, forward, direction, sead::Vector3f::ey);
        f32 turn;
        if (angle > 0.7853981852531433f) {
            turn = sead::GlobalRandom::instance()->getF32() * 1.0471975803375244f -
                   0.5235987901687622f;
        } else {
            direction = forward;
            const f32 sign = axis.y > 0.0f ? 1.0f : -1.0f;
            turn = sign * (sead::GlobalRandom::instance()->getF32() * 0.3490658700466156f +
                           0.4363323152065277f);
        }
        ksys::util::sub_71011EF010(&direction, turn);
    } else {
        direction = mActor->getMtx().getBase(2);
        const f32 sign = f32(s32(sead::GlobalRandom::instance()->getU32() & 2) - 1);
        const f32 turn = sign * (sead::GlobalRandom::instance()->getF32() * 0.3490658700466156f +
                                 0.4363323152065277f);
        ksys::util::sub_71011EF010(&direction, turn);
        const auto position = mActor->getMtx().getTranslation();
        const auto target = position + direction * 5.0f;
        if (sub_710072E928(position, target, nullptr, nullptr, nullptr, 0.5f))
            direction.negate();
    }
    const auto target = mActor->getMtx().getTranslation() + direction;
    pack.addVec3(target, "TargetPos", -1);
    changeChild("回転", &pack);
}

bool BokoblinRoam::isChangeable() const {
    return ksys::act::ai::Ai::isChangeable() || isCurrentChild("索敵") || isCurrentChild("暇つぶし");
}

void BokoblinRoam::changeToIdle() {
    const s32 min = *mFreeIntervalMin_s;
    const s32 max = *mFreeIntervalMax_s;
    _d0.reset(sead::GlobalRandom::instance()->getS32Range(min, max));
    _dd = false;

    ksys::act::ai::InlineParamPack pack;
    const sead::Matrix34f& mtx = mActor->getMtx();
    sead::Vector3f pos = mtx.getBase(2);
    pos += mtx.getTranslation();
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("暇つぶし", &pack);
}

void BokoblinRoam::changeToRotate() {
    const s32 min = *mFreeIntervalMin_s;
    const s32 max = *mFreeIntervalMax_s;
    _d0.reset(sead::GlobalRandom::instance()->getS32Range(min, max));
    _dd = true;

    ksys::act::ai::InlineParamPack pack;
    const sead::Matrix34f& mtx = mActor->getMtx();
    const sead::Vector3f forward = mtx.getBase(2);
    const sead::Vector3f pos = mtx.getTranslation() - forward;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("回転", &pack);
}

}  // namespace uking::ai
