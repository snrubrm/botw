#include "Game/AI/AI/aiEnemyNoticeFearfulTarget.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

EnemyNoticeFearfulTarget::EnemyNoticeFearfulTarget(const InitArg& arg) : EnemyNoticeTerror(arg) {}

EnemyNoticeFearfulTarget::~EnemyNoticeFearfulTarget() = default;

bool EnemyNoticeFearfulTarget::init_(sead::Heap* heap) {
    return EnemyNoticeTerror::init_(heap);
}

void EnemyNoticeFearfulTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNoticeTerror::enter_(params);
}

void EnemyNoticeFearfulTarget::calc_() {
    EnemyNoticeTerror::calc_();
}

void EnemyNoticeFearfulTarget::leave_() {
    EnemyNoticeTerror::leave_();
}

void EnemyNoticeFearfulTarget::loadParams_() {
    EnemyNoticeTerror::loadParams_();
}

bool EnemyNoticeFearfulTarget::m34(Unk* out) {
    auto& link = sub_71005D94AC(mActor);
    if (!link.hasProcInCalcState())
        return false;
    out->_0 = link;
    return true;
}

}  // namespace uking::ai
