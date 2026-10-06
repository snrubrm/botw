#include "Game/AI/AI/aiLumberjackFallenTree.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

void Unk_7102403e48::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) {
    if (*a5 != -1)
        *a1 = 0;
}

void Unk_7102403e80::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) {
    if (*a5 == -1)
        return;
    auto* damage_mgr = sub_710072BA90(_28->getActor());
    if (!damage_mgr)
        return;
    const bool flag = damage_mgr->checkDamageFlags(4);
    sead::Vector3f position;
    damage_mgr->getPosition(&position);
    _28->sub_71004855DC(position);
    if (flag)
        *a1 = 0;
}

LumberjackFallenTree::LumberjackFallenTree(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LumberjackFallenTree::~LumberjackFallenTree() = default;

bool LumberjackFallenTree::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LumberjackFallenTree::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool LumberjackFallenTree::hasUpdateForPreDeleteCb() {
    return true;
}

void LumberjackFallenTree::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LumberjackFallenTree::loadParams_() {
    getStaticParam(&mToLogAngVel_s, "ToLogAngVel");
    getStaticParam(&mMaxCheckAng_s, "MaxCheckAng");
    getStaticParam(&mCheckDis_s, "CheckDis");
    getStaticParam(&mCheckHeightRate_s, "CheckHeightRate");
    getStaticParam(&mTerrorRegistAng_s, "TerrorRegistAng");
    getStaticParam(&mTerrorUnregistTimelimit_s, "TerrorUnregistTimelimit");
    getStaticParam(&mNoiseLevel_s, "NoiseLevel");
    getStaticParam(&mIsCheckHeight_s, "IsCheckHeight");
    getStaticParam(&mTerrorOffsetPos4Falling_s, "TerrorOffsetPos4Falling");
    getAITreeVariable(&mLumberjackType_a, "LumberjackType");
    getAITreeVariable(&mForceSetDropPos_a, "ForceSetDropPos");
    getAITreeVariable(&mMoveDirection_a, "MoveDirection");
}

}  // namespace uking::ai
