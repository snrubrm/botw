#include "Game/AI/AI/aiEnemyEscapeMove.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

EnemyEscapeMove::EnemyEscapeMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyEscapeMove::~EnemyEscapeMove() = default;

bool EnemyEscapeMove::init_(sead::Heap* heap) {
    sub_71005E2C58(mActor);
    return true;
}

void EnemyEscapeMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool EnemyEscapeMove::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void EnemyEscapeMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyEscapeMove::loadParams_() {}

}  // namespace uking::ai
