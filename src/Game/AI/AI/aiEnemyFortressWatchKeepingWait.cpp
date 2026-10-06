#include "Game/AI/AI/aiEnemyFortressWatchKeepingWait.h"

namespace uking::ai {

EnemyFortressWatchKeepingWait::EnemyFortressWatchKeepingWait(const InitArg& arg)
    : EnemyWatchKeepingWait(arg) {}

EnemyFortressWatchKeepingWait::~EnemyFortressWatchKeepingWait() = default;

bool EnemyFortressWatchKeepingWait::init_(sead::Heap* heap) {
    if (!EnemyWatchKeepingWait::init_(heap))
        return false;
    return _80.sub_7100390930(heap);
}

void EnemyFortressWatchKeepingWait::enter_(ksys::act::ai::InlineParamPack* params) {
    _80.sub_7100390A90();
    EnemyWatchKeepingWait::enter_(params);
}

void EnemyFortressWatchKeepingWait::calc_() {
    _80.sub_7100390ABC();
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        _448 &= ~8;
        const s32 result = _80.sub_7100390D0C();
        if (result == 1)
            return;
        if (result == 2) {
            changeToWait();
            return;
        }
    } else if (child->isChangeable()) {
        const s32 result = _80.sub_7100391230();
        if (result == 1)
            return;
        if (result == 2) {
            changeToWait();
            return;
        }
    }
    EnemyWatchKeepingWait::calc_();
}

void EnemyFortressWatchKeepingWait::leave_() {
    EnemyWatchKeepingWait::leave_();
    _80.sub_7100392044();
}

void EnemyFortressWatchKeepingWait::loadParams_() {
    EnemyWatchKeepingWait::loadParams_();
    _80.sub_7100392230();
}

bool EnemyFortressWatchKeepingWait::handleMessage_(const ksys::Message* message) {
    return _80.sub_710039235C(*message);
}

bool EnemyFortressWatchKeepingWait::isChangeable() const {
    return getCurrentChild()->isChangeable() || (_448 & 1) || isCurrentChild("サボり");
}

}  // namespace uking::ai
