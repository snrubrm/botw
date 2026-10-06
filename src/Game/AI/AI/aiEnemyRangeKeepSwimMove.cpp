#include "Game/AI/AI/aiEnemyRangeKeepSwimMove.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71007320F0.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
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

// NON_MATCHING: register numbering of the XZ offset (x/z swap the roles of s11/s12 after the normalisation)
bool EnemyRangeKeepSwimMove::sub_71003ADEE4() {
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    const sead::Vector3f& player = sub_71005D9330(mActor);
    sead::Vector3f dir = pos - player;
    dir.y = 0;
    dir.normalize();
    sead::Vector3f target;
    target.setScaleAdd(5.0f, dir, pos);
    if (!sub_710072F8E4(mActor, target, nullptr, 3.0f))
        return true;
    auto result = ksys::phys::HavokAI::instance()->sub_7100F87ED0(nullptr, target, 3.0f);
    if (result.sub_7100F7EB40() && result.sub_7100F7EEE4() != 6)
        return true;
    return false;
}

// NON_MATCHING: the original loads both actor and player XZ before the first fsub
void EnemyRangeKeepSwimMove::sub_71003AED8C() {
    const sead::Vector3f& player = sub_71005D9330(mActor);
    const f32 x = mActor->getMtx().m[0][3];
    const f32 z = mActor->getMtx().m[2][3];
    const sead::Vector3f diff(player.x - x, 0, player.z - z);
    const f32 dist = diff.length();
    if (dist > *mBaseDist_s + *mOutDist_s + sub_71007320F0(mActor, *mWeaponIdx_s)) {
        if (_84.value > sead::Mathf::epsilon())
            _84.update();
    } else {
        _84.reset(s32(sead::GlobalRandom::instance()->getU32(7)) + 4);
    }
}

// NON_MATCHING: same load order as sub_71003AED8C
void EnemyRangeKeepSwimMove::sub_71003AEE84() {
    const sead::Vector3f& player = sub_71005D9330(mActor);
    const sead::Vector3f diff(player.x - mActor->getMtx().m[0][3], 0, player.z - mActor->getMtx().m[2][3]);
    const f32 dist = diff.length();
    if (!(dist < *mBaseDist_s + *mCloseDist_s + sub_71007320F0(mActor, *mWeaponIdx_s)) || sub_71003ADEE4()) {
        _78.reset(s32(sead::GlobalRandom::instance()->getU32(15)) + 15);
    } else if (_78.value > sead::Mathf::epsilon()) {
        _78.update();
    }
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

void EnemyRangeKeepSwimMove::changeToMoveSideways(s8 dir) {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    pack.addInt(dir, "RotDir", -1);
    changeChild("横移動", &pack);
}

}  // namespace uking::ai
