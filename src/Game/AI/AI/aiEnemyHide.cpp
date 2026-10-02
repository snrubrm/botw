#include "Game/AI/AI/aiEnemyHide.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

EnemyHide::EnemyHide(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyHide::~EnemyHide() = default;

bool EnemyHide::init_(sead::Heap* heap) {
    sub_71005E2C58(mActor);
    return true;
}

void EnemyHide::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool EnemyHide::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void EnemyHide::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyHide::loadParams_() {}

}  // namespace uking::ai
