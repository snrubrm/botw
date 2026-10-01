#include "Game/AI/AI/aiEnemyEscape.h"

namespace uking::ai {

EnemyEscape::EnemyEscape(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyEscape::~EnemyEscape() = default;

void EnemyEscape::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool EnemyEscape::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void EnemyEscape::loadParams_() {}

}  // namespace uking::ai
