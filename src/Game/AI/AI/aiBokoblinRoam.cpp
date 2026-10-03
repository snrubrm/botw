#include "Game/AI/AI/aiBokoblinRoam.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

BokoblinRoam::BokoblinRoam(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BokoblinRoam::~BokoblinRoam() = default;

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
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&ksys::act::PlayerInfo::getSomeProcLink(), &accessor);
    const sead::Matrix34f& player_mtx = accessor.getActorMtx();
    const f32 target_x = player_mtx(0, 3);
    const f32 target_z = player_mtx(2, 3);
    const f32 pos_x = mActor->getMtx()(0, 3);
    const f32 pos_z = mActor->getMtx()(2, 3);
    sead::Vector3f dir(target_x - pos_x, 0.0f, target_z - pos_z);
    const f32 dist = dir.normalize();
    if (dist > *mSpAttackServiceDist_s)
        return false;
    dir.negate();
    return dir.dot(mActor->getMtx().getBase(2)) >= sead::Mathf::cos(*mSpAttackServiceAngle_s);
}

void BokoblinRoam::sub_7100333F7C() {
    const s32 min = *mFreeIntervalMin_s;
    const s32 max = *mFreeIntervalMax_s;
    _d0.reset(sead::GlobalRandom::instance()->getS32Range(min, max));
    changeChild("索敵", nullptr);
}

// NON_MATCHING: the two stores of the timer are not merged into one stp in the original
void BokoblinRoam::sub_7100333FEC() {
    ksys::act::acc::PlayerBase accessor;
    ksys::act::acquireActor(&ksys::act::PlayerInfo::getSomeProcLink(), &accessor);
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

bool BokoblinRoam::isChangeable() const {
    return ksys::act::ai::Ai::isChangeable() || isCurrentChild("索敵") || isCurrentChild("暇つぶし");
}

// NON_MATCHING: the original schedules the forward-axis loads before the translation loads (vector sum); same instructions otherwise
void BokoblinRoam::sub_71003349E0() {
    const s32 min = *mFreeIntervalMin_s;
    const s32 max = *mFreeIntervalMax_s;
    _d0.reset(sead::GlobalRandom::instance()->getS32Range(min, max));
    _dd = false;

    ksys::act::ai::InlineParamPack pack;
    const sead::Matrix34f& mtx = mActor->getMtx();
    const f32 fx = mtx(0, 2);
    const f32 fy = mtx(1, 2);
    const f32 fz = mtx(2, 2);
    sead::Vector3f pos(mtx(0, 3) + fx, mtx(1, 3) + fy, mtx(2, 3) + fz);
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("暇つぶし", &pack);
}

// NON_MATCHING: same as sub_71003349E0 (translation - forward)
void BokoblinRoam::sub_71003344AC() {
    const s32 min = *mFreeIntervalMin_s;
    const s32 max = *mFreeIntervalMax_s;
    _d0.reset(sead::GlobalRandom::instance()->getS32Range(min, max));
    _dd = true;

    ksys::act::ai::InlineParamPack pack;
    const sead::Matrix34f& mtx = mActor->getMtx();
    const f32 fx = mtx(0, 2);
    const f32 fy = mtx(1, 2);
    const f32 fz = mtx(2, 2);
    sead::Vector3f pos(mtx(0, 3) - fx, mtx(1, 3) - fy, mtx(2, 3) - fz);
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("回転", &pack);
}

}  // namespace uking::ai
