#include "Game/AI/AI/aiEnemySomeIgniteBattle.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"

namespace uking::ai {

EnemySomeIgniteBattle::EnemySomeIgniteBattle(const InitArg& arg) : BreathAttackEnemyBattle(arg), _b8() {}

EnemySomeIgniteBattle::~EnemySomeIgniteBattle() = default;

void EnemySomeIgniteBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    BreathAttackEnemyBattle::enter_(params);
}

void EnemySomeIgniteBattle::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("戦闘攻撃")) {
            for (s32 i = 0; i < *mIgniteNum_s; ++i) {
                if (_b8[i].isAllocatedOrFailed())
                    _b8[i].deleteProcIfFailed();
            }
        }
    }
    BreathAttackEnemyBattle::calc_();
}

void EnemySomeIgniteBattle::leave_() {
    for (s32 i = 0; i < *mIgniteNum_s; ++i)
        _b8[i].deleteProc();
    BreathAttackEnemyBattle::leave_();
}

void EnemySomeIgniteBattle::loadParams_() {
    BreathAttackEnemyBattle::loadParams_();
    getStaticParam(&mIgniteNum_s, "IgniteNum");
}

bool EnemySomeIgniteBattle::m39() {
    if (!m40())
        return false;
    return m44();
}

void EnemySomeIgniteBattle::m42() {
    ksys::act::InstParamPack pack;
    sub_710033F490(&pack);
    for (s32 i = 0; i < *mIgniteNum_s; ++i) {
        ksys::act::ActorCreator::instance()->requestCreateActor(
            m36().cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &_b8[i], &pack,
            nullptr, 1);
    }
}

void EnemySomeIgniteBattle::m43() {
    for (s32 i = 0; i < *mIgniteNum_s; ++i) {
        if (_b8[i].hasProcCreationFailed())
            _b8[i].deleteProcIfFailed();
    }
    for (s32 i = 0; i < *mIgniteNum_s; ++i) {
        if (_b8[i].isAllocatedOrFailed())
            return;
    }
}

bool EnemySomeIgniteBattle::m44() {
    for (s32 i = 0; i < *mIgniteNum_s; ++i) {
        if (!_b8[i].isProcReady())
            return false;
    }
    return true;
}

// 0x71003be17c
// NON_MATCHING: callee-saved register numbering (one extra live value shifts x20-x24 by one) and
// addPointer argument-setup order; all three DynamicCast blocks, all pack calls and the dtor loop match.
void EnemySomeIgniteBattle::m37() {
    m41();
    if (auto* bullet = sead::DynamicCast<ksys::act::Bullet>(_b8[0].getProc()))
        bullet->sub_710000497C(mActor);
    if (auto* bullet = sead::DynamicCast<ksys::act::Bullet>(_b8[1].getProc()))
        bullet->sub_710000497C(mActor);
    if (auto* bullet = sead::DynamicCast<ksys::act::Bullet>(_b8[2].getProc()))
        bullet->sub_710000497C(mActor);

    ksys::act::ai::InlineParamPack pack;
    pack.addPointer(&_b8[0], "IgniteHandle", ksys::AIDefParamType::BaseProcHandle, -1);
    pack.addPointer(&_b8[1], "IgniteHandle2", ksys::AIDefParamType::BaseProcHandle, -1);
    pack.addPointer(&_b8[2], "IgniteHandle3", ksys::AIDefParamType::BaseProcHandle, -1);
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("戦闘攻撃", &pack);
}

}  // namespace uking::ai
