#include "Game/AI/AI/aiNPCAttack.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include <random/seadGlobalRandom.h>
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectNpc.h"

namespace uking::ai {

NPCAttack::NPCAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCAttack::~NPCAttack() = default;

bool NPCAttack::init_(sead::Heap* heap) {
    _98 = sead::DynamicCast<act::NPC>(mActor);
    return true;
}

void NPCAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    if (_98)
        _98->_fe8 |= 0x800;

    _90 = true;
    _91 = false;

    const int base_time = *mActionBaseTime_s;
    const int sign = (sead::GlobalRandom::instance()->getU32() & 2) - 1;
    const int time = base_time + sign * s32(sead::GlobalRandom::instance()->getU32(*mActionTimePlay_s));
    _a0 = ksys::Timer(time, time);
    _b8 = ksys::Timer(*mEnemyChanceTime_s, *mEnemyChanceTime_s);
    _ac = ksys::Timer(*mGuardModeTime_s, *mGuardModeTime_s);
    _94 = mActor->getParam()->getRes().mGParamList->getNpc()->mTolerantCount.ref();

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    pack.addBool(true, "TerrorOccurring", -1);
    changeChild("待機", &pack);
}

void NPCAttack::leave_() {
    if (_98) {
        _98->_fe8 &= ~0x800;
        _98->_fe8 &= ~0x1000;
    }
}

void NPCAttack::loadParams_() {
    getStaticParam(&mActionBaseTime_s, "ActionBaseTime");
    getStaticParam(&mActionTimePlay_s, "ActionTimePlay");
    getStaticParam(&mActionRate_s, "ActionRate");
    getStaticParam(&mAttackRate_s, "AttackRate");
    getStaticParam(&mAttackModeTime_s, "AttackModeTime");
    getStaticParam(&mGuardModeTime_s, "GuardModeTime");
    getStaticParam(&mEnemyChanceTime_s, "EnemyChanceTime");
    getDynamicParam(&mTerrorLevel_d, "TerrorLevel");
    getDynamicParam(&mIsBattleStart_d, "IsBattleStart");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mEnemyLink_d, "EnemyLink");
}

bool NPCAttack::isChangeable() const {
    return !isCurrentChild("攻撃") && !isCurrentChild("勝利");
}

// 0x71004c064c
void NPCAttack::sub_71004C064C() {
    _98->_fe8 |= 0x1000;
    mActor->getASList()->x_6(9, 0, 0.0f);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("接近", &pack);
}

}  // namespace uking::ai
