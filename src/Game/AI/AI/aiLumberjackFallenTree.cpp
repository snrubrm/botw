#include "Game/AI/AI/aiLumberjackFallenTree.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

void Unk_7102403e48::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, dmg::DamageCallbackInfo* a6) {
    if (*a5 != -1)
        *a1 = 0;
}

void Unk_7102403e80::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, dmg::DamageCallbackInfo* a6) {
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

LumberjackFallenTree::~LumberjackFallenTree() {
    if (_f8)
        _f8->clear();
    _100.sub_7100D786EC();
    _1b8.sub_7100D786EC();
}

// NON_MATCHING: the original loads `mActor` (the second argument) before the virtual slot of `_f8->init` (C++14
// evaluation order of the call; we compile as C++17)
bool LumberjackFallenTree::init_(sead::Heap* heap) {
    bool ok = true;
    if (*mLumberjackType_a == 1) {
        _f8 = new (heap, 8) act::Unk_710244eb00;
        if (_f8)
            ok = _f8->init(heap, mActor);
    }
    return ok & (_100.sub_7100D78564(heap) & _1b8.sub_7100D78564(heap));
}

void LumberjackFallenTree::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool LumberjackFallenTree::hasUpdateForPreDeleteCb() {
    return true;
}

bool LumberjackFallenTree::updateForPreDelete() {
    bool ok = true;
    if (_f8)
        ok = _f8->m5() & (_100.sub_7100D786D8() & _1b8.sub_7100D786D8());
    return ok;
}

void LumberjackFallenTree::leave_() {
    if (auto* damage_mgr = mActor->getDamageMgr()) {
        if (auto* manager = sead::DynamicCast<uking::dmg::DamageManager>(damage_mgr)) {
            manager->removeDamageCallback(&_38);
            manager->removeDamageCallback(&_68);
        }
    }
    if (_f8)
        _f8->sub_71006E2420();
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
