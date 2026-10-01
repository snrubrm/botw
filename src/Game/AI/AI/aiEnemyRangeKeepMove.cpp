#include "Game/AI/AI/aiEnemyRangeKeepMove.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71005D6D10.h"
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

}  // namespace uking::ai
