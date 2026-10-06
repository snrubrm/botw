#include "Game/AI/AI/aiBokoblinRoam.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "Game/AI/aiUnk_71007377D4.h"

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

// NON_MATCHING: the original loads the player's x and z before the actor's x (ours interleaves the loads x, x, z, z
// differently) and so numbers the registers differently; the load-order-only locals of earlier sessions were removed
bool BokoblinRoam::sub_7100333E68() {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&ksys::act::PlayerInfo::getSomeProcLink(), &accessor);
    const sead::Matrix34f& player_mtx = accessor.getActorMtx();
    const sead::Vector2f diff(player_mtx(0, 3) - mActor->getMtx()(0, 3),
                              player_mtx(2, 3) - mActor->getMtx()(2, 3));
    sead::Vector3f dir(diff.x, 0.0f, diff.y);
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

// NON_MATCHING: the original loads the three forward-axis components before the translation (ours the other way
// round); same instructions otherwise (session 26: the load-order-only locals were removed)
void BokoblinRoam::changeToIdle() {
    const s32 min = *mFreeIntervalMin_s;
    const s32 max = *mFreeIntervalMax_s;
    _d0.reset(sead::GlobalRandom::instance()->getS32Range(min, max));
    _dd = false;

    ksys::act::ai::InlineParamPack pack;
    const sead::Matrix34f& mtx = mActor->getMtx();
    const sead::Vector3f pos = mtx.getTranslation() + mtx.getBase(2);
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("暇つぶし", &pack);
}

// NON_MATCHING: same as changeToIdle (translation - forward; the original loads the forward axis first)
void BokoblinRoam::changeToRotate() {
    const s32 min = *mFreeIntervalMin_s;
    const s32 max = *mFreeIntervalMax_s;
    _d0.reset(sead::GlobalRandom::instance()->getS32Range(min, max));
    _dd = true;

    ksys::act::ai::InlineParamPack pack;
    const sead::Matrix34f& mtx = mActor->getMtx();
    const sead::Vector3f pos = mtx.getTranslation() - mtx.getBase(2);
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("回転", &pack);
}

}  // namespace uking::ai
