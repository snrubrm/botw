#include "Game/AI/AI/aiEnemyVacuumChangeItemSelect.h"
#include "Game/AI/aiUnk_710073CDFC.h"

namespace uking::ai {

EnemyVacuumChangeItemSelect::EnemyVacuumChangeItemSelect(const InitArg& arg)
    : EnemyVacuumBombSelect(arg) {}

EnemyVacuumChangeItemSelect::~EnemyVacuumChangeItemSelect() = default;

bool EnemyVacuumChangeItemSelect::init_(sead::Heap* heap) {
    return EnemyVacuumBombSelect::init_(heap);
}

void EnemyVacuumChangeItemSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyVacuumBombSelect::enter_(params);
}

void EnemyVacuumChangeItemSelect::calc_() {
    EnemyVacuumBombSelect::calc_();
}

void EnemyVacuumChangeItemSelect::leave_() {
    EnemyVacuumBombSelect::leave_();
}

void EnemyVacuumChangeItemSelect::loadParams_() {
    EnemyVacuumBombSelect::loadParams_();
}

bool EnemyVacuumChangeItemSelect::m34(ksys::act::BaseProcLink* link) {
    return sub_710073CDFC(mActor, link) >= 0;
}

}  // namespace uking::ai
