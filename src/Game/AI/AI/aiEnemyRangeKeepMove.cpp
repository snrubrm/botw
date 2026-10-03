#include "Game/AI/AI/aiEnemyRangeKeepMove.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

EnemyRangeKeepMove::EnemyRangeKeepMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyRangeKeepMove::~EnemyRangeKeepMove() = default;

bool EnemyRangeKeepMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyRangeKeepMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool EnemyRangeKeepMove::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void EnemyRangeKeepMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyRangeKeepMove::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mBackTimeMin_s, "BackTimeMin");
    getStaticParam(&mBackTimeMax_s, "BackTimeMax");
    getStaticParam(&mLeaveTimerMin_s, "LeaveTimerMin");
    getStaticParam(&mLeaveTimerMax_s, "LeaveTimerMax");
    getStaticParam(&mPosVibrateFrame_s, "PosVibrateFrame");
    getStaticParam(&mRotVelVibrateFrame_s, "RotVelVibrateFrame");
    getStaticParam(&mCloseDist_s, "CloseDist");
    getStaticParam(&mFarDist_s, "FarDist");
    getStaticParam(&mOutDist_s, "OutDist");
    getStaticParam(&mBaseDist_s, "BaseDist");
    getStaticParam(&mSpaceDist_s, "SpaceDist");
    getStaticParam(&mSpaceAngle_s, "SpaceAngle");
    getStaticParam(&mNoMoveDist_s, "NoMoveDist");
    getStaticParam(&mIsCheckBack_s, "IsCheckBack");
    getStaticParam(&mIsCheckReachable_s, "IsCheckReachable");
    getAITreeVariable(&mRefPosVibrateCheckerForAI_a, "RefPosVibrateCheckerForAI");
    getAITreeVariable(&mRefVelRotVibrateCheckerforAI_a, "RefVelRotVibrateCheckerforAI");
}

void EnemyRangeKeepMove::sub_71003AB8A0() {
    m38();
    _c8 = _cc == _d0 ? _cc : sead::GlobalRandom::instance()->getS32Range(_cc, _d0);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("戦闘後ずさり", &pack);
}

void EnemyRangeKeepMove::sub_71003ABF50() {
    m36();
    sub_71003AB3FC();
    _e0 = _e4 == _e8 ? _e4 : sead::GlobalRandom::instance()->getS32Range(_e4, _e8);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("戦闘待機", &pack);
}

bool EnemyRangeKeepMove::sub_71003AD058() {
    if (!*mIsCheckBack_s)
        return false;
    sead::Vector3f dir = mActor->getMtx().getTranslation();
    dir -= sub_71005D9330(mActor);
    dir.normalize();
    return sub_710072FEC4(mActor, dir, 3.0f, nullptr, false, nullptr);
}

// NON_MATCHING: the zero for the y term is materialised before the first square (scheduling)
bool EnemyRangeKeepMove::sub_71003AD1F8() {
    auto* actor = mActor;
    sead::Vector3f diff = sub_71005D9330(actor) - actor->getMtx().getTranslation();
    diff.y = 0.0f;
    const f32 dist = diff.length();
    return dist < *mBaseDist_s + sub_71007320F0(actor, m35());
}

// NON_MATCHING: the zero for the y term is materialised before the first square (scheduling)
bool EnemyRangeKeepMove::sub_71003AD298() {
    auto* actor = mActor;
    sead::Vector3f diff = sub_71005D9330(actor) - actor->getMtx().getTranslation();
    diff.y = 0.0f;
    const f32 dist = diff.length();
    return dist < *mBaseDist_s + *mCloseDist_s + sub_71007320F0(actor, m35());
}

// NON_MATCHING: the zero for the y term is materialised before the first square (scheduling)
bool EnemyRangeKeepMove::m34() {
    auto* actor = mActor;
    const auto& target_pos = sub_71005D9330(actor);
    sead::Vector3f diff = target_pos - actor->getMtx().getTranslation();
    diff.y = 0.0f;
    const f32 dist = diff.length();
    return dist > *mBaseDist_s + *mOutDist_s + sub_71007320F0(actor, m35());
}

bool EnemyRangeKeepMove::sub_71003AD160() {
    auto* actor = mActor;
    if (!actor)
        return false;
    f32 radius = 0;
    if (auto* nav = actor->m45())
        radius = nav->_2a8 * nav->_2ac;
    const sead::Vector3f target = sub_71005D9330(actor);
    return sub_710072CB78(actor, target, nullptr, radius, 3);
}

}  // namespace uking::ai
