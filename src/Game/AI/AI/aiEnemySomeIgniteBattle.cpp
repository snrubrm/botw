#include "Game/AI/AI/aiEnemySomeIgniteBattle.h"

namespace uking::ai {

EnemySomeIgniteBattle::EnemySomeIgniteBattle(const InitArg& arg) : BreathAttackEnemyBattle(arg), _b8() {}

EnemySomeIgniteBattle::~EnemySomeIgniteBattle() = default;

void EnemySomeIgniteBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    BreathAttackEnemyBattle::enter_(params);
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

}  // namespace uking::ai
