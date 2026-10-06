#include "Game/AI/AI/aiLynelBattle.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

LynelBattle::LynelBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
LynelBattle::~LynelBattle() {
    ;
}

bool LynelBattle::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LynelBattle::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LynelBattle::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mCloseBattleRepeatMax_s, "CloseBattleRepeatMax");
    getStaticParam(&mThroughAttackRepeatNum_s, "ThroughAttackRepeatNum");
    getStaticParam(&mCloseBattleStartDist_s, "CloseBattleStartDist");
    getStaticParam(&mCloseBattleStartAngle_s, "CloseBattleStartAngle");
    getStaticParam(&mHornAttackRate_s, "HornAttackRate");
    getStaticParam(&mRoarRate_s, "RoarRate");
    getStaticParam(&mBreathStartLifeRate_s, "BreathStartLifeRate");
    getStaticParam(&mRoarStartLifeRate_s, "RoarStartLifeRate");
    getStaticParam(&mBattleEndDist_s, "BattleEndDist");
    getStaticParam(&mSkipBreathRoarRate_s, "SkipBreathRoarRate");
    getStaticParam(&mRoarFlamePartsKey_s, "RoarFlamePartsKey");
    getStaticParam(&mBreathPartsKey0_s, "BreathPartsKey0");
    getStaticParam(&mBreathPartsKey1_s, "BreathPartsKey1");
    getStaticParam(&mBreathPartsKey2_s, "BreathPartsKey2");
    getAITreeVariable(&mLynelAIFlags_a, "LynelAIFlags");
}

void LynelBattle::changeToThroughAttack() {
    ++_dc;
    *mLynelAIFlags_a = (*mLynelAIFlags_a & ~0xfc0) | 0x40;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    pack.addVec3(sub_71005D9548(mActor), "TargetVel", -1);
    pack.addBool(false, "IsSkipPrepare", -1);
    changeChild("斬り抜け", &pack);
}

void LynelBattle::changeToChargeAttack(bool skip_prepare) {
    _dc = 0;
    _e0 = sead::Mathi::clamp(_e0 - 1, -5, 5);
    *mLynelAIFlags_a = (*mLynelAIFlags_a & ~0xfc0) | 0x80;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    pack.addVec3(sub_71005D9548(mActor), "TargetVel", -1);
    pack.addBool(skip_prepare, "IsSkipPrepare", -1);
    changeChild("突進切り", &pack);
}

void LynelBattle::changeToSixLegAttack(bool skip_prepare) {
    _dc = 0;
    _e0 = sead::Mathi::clamp(_e0 + 1, -5, 5);
    *mLynelAIFlags_a = (*mLynelAIFlags_a & ~0xfc0) | 0x100;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    pack.addVec3(sub_71005D9548(mActor), "TargetVel", -1);
    pack.addBool(skip_prepare, "IsSkipPrepare", -1);
    changeChild("6足攻撃", &pack);
}

void LynelBattle::changeToBreath() {
    _e4 = sead::Mathi::clamp(_e4 - 1, -5, 5);
    _dc = 0;
    *mLynelAIFlags_a = (*mLynelAIFlags_a & ~0xfc0) | 0x200;
    *mLynelAIFlags_a |= 4;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("ブレス", &pack);
}

void LynelBattle::changeToRoarAttack() {
    _e4 = sead::Mathi::clamp(_e4 + 1, -5, 5);
    _dc = 0;
    *mLynelAIFlags_a = (*mLynelAIFlags_a & ~0xfc0) | 0x400;
    *mLynelAIFlags_a |= 8;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("咆哮攻撃", &pack);
}

void LynelBattle::changeToMeleeBattle() {
    ++_d8;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("近接戦闘", &pack);
}

}  // namespace uking::ai
