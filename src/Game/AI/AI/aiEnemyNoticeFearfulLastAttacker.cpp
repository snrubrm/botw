#include "Game/AI/AI/aiEnemyNoticeFearfulLastAttacker.h"
#include "Game/Actor/actEnemy.h"

namespace uking::ai {

EnemyNoticeFearfulLastAttacker::EnemyNoticeFearfulLastAttacker(const InitArg& arg)
    : EnemyNoticeTerror(arg) {}

EnemyNoticeFearfulLastAttacker::~EnemyNoticeFearfulLastAttacker() = default;

bool EnemyNoticeFearfulLastAttacker::init_(sead::Heap* heap) {
    return EnemyNoticeTerror::init_(heap);
}

void EnemyNoticeFearfulLastAttacker::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNoticeTerror::enter_(params);
}

void EnemyNoticeFearfulLastAttacker::calc_() {
    EnemyNoticeTerror::calc_();
}

void EnemyNoticeFearfulLastAttacker::leave_() {
    EnemyNoticeTerror::leave_();
}

void EnemyNoticeFearfulLastAttacker::loadParams_() {
    EnemyNoticeTerror::loadParams_();
}

bool EnemyNoticeFearfulLastAttacker::m34(Unk* out) {
    out->_0.reset();
    out->_1c = 0;
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (enemy && enemy->_e08._0.hasProcInCalcState()) {
        out->_0 = enemy->_e08._0;
        out->_1c |= 1;
        return true;
    }
    return false;
}

}  // namespace uking::ai
