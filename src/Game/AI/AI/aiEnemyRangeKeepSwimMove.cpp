#include "Game/AI/AI/aiEnemyRangeKeepSwimMove.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

EnemyRangeKeepSwimMove::EnemyRangeKeepSwimMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyRangeKeepSwimMove::~EnemyRangeKeepSwimMove() = default;

bool EnemyRangeKeepSwimMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyRangeKeepSwimMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyRangeKeepSwimMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyRangeKeepSwimMove::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mCloseDist_s, "CloseDist");
    getStaticParam(&mFarDist_s, "FarDist");
    getStaticParam(&mOutDist_s, "OutDist");
    getStaticParam(&mBaseDist_s, "BaseDist");
    getStaticParam(&mSpaceDist_s, "SpaceDist");
    getStaticParam(&mIsCheckCliff_s, "IsCheckCliff");
}

void EnemyRangeKeepSwimMove::sub_71003AE3C4(s8 dir) {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    pack.addInt(dir, "RotDir", -1);
    changeChild("横移動", &pack);
}

}  // namespace uking::ai
