#include "Game/AI/AI/aiMiniBeamAttack.h"
#include "Game/Actor/actEnemy.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

// NON_MATCHING: the original zeroes _230 (the xlink handle pair) with four 8-byte stores
MiniBeamAttack::MiniBeamAttack(const InitArg& arg) : BreathAttackEnemyBattle(arg) {}

MiniBeamAttack::~MiniBeamAttack() = default;

bool MiniBeamAttack::init_(sead::Heap* heap) {
    return BreathAttackEnemyBattle::init_(heap);
}

void MiniBeamAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    BreathAttackEnemyBattle::enter_(params);
}

void MiniBeamAttack::leave_() {
    BreathAttackEnemyBattle::leave_();
    if (*mIsValidGuide_s)
        _100.sub_71006F2D08();
    _230.fadeXLink();
    sub_71005DA114(mActor, &_1f8);
}

void MiniBeamAttack::loadParams_() {
    BreathAttackEnemyBattle::loadParams_();
    getStaticParam(&mFluctuationRange_s, "FluctuationRange");
    getStaticParam(&mFluctuationSpan_s, "FluctuationSpan");
    getStaticParam(&mTargetOffsetY_s, "TargetOffsetY");
    getStaticParam(&mNodeName_s, "NodeName");
    getStaticParam(&mIsValidGuide_s, "IsValidGuide");
    getStaticParam(&mIsIgnoreSmallHit_s, "IsIgnoreSmallHit");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getStaticParam(&mAimEffectName_s, "AimEffectName");
}

bool MiniBeamAttack::isChangeable() const {
    if (!*mIsChangeable_s)
        return false;
    return ksys::act::ai::Ai::isChangeable();
}

const sead::Vector3f* MiniBeamAttack::m35() {
    return &sub_71005D9330(mActor);
}

void MiniBeamAttack::m37() {
    _220 = *m35();
    BreathAttackEnemyBattle::m37();
}

void MiniBeamAttack::m41() {
    if (*mIsValidGuide_s)
        _100.end("Target_End");
    _230.fadeXLink();
}

s32 MiniBeamAttack::m45() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        return enemy->_e68.value;
    return 100;
}

}  // namespace uking::ai
