#include "Game/AI/AI/aiEnemyNoticeSoundSensitiveTimer.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

EnemyNoticeSoundSensitiveTimer::EnemyNoticeSoundSensitiveTimer(const InitArg& arg)
    : EnemyNoticeSoundSensitive(arg) {}

EnemyNoticeSoundSensitiveTimer::~EnemyNoticeSoundSensitiveTimer() = default;

bool EnemyNoticeSoundSensitiveTimer::isFinished() const {
    if (ksys::act::ai::Ai::isFinished() ||
        (isCurrentChild("行動") && getCurrentChild()->isFinished())) {
        return true;
    }
    return getCurrentChild()->isChangeable() && _78 <= 0.0f;
}

bool EnemyNoticeSoundSensitiveTimer::init_(sead::Heap* heap) {
    return EnemyNoticeSoundSensitive::init_(heap);
}

void EnemyNoticeSoundSensitiveTimer::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNoticeSoundSensitive::enter_(params);
    _78 = *mTimer_s;
}

void EnemyNoticeSoundSensitiveTimer::calc_() {
    EnemyNoticeSoundSensitive::calc_();
    if (isCurrentChild("行動"))
        ksys::Timer::update(&_78, -1.0f);
}

void EnemyNoticeSoundSensitiveTimer::leave_() {
    EnemyNoticeSoundSensitive::leave_();
}

void EnemyNoticeSoundSensitiveTimer::loadParams_() {
    EnemyNoticeSoundSensitive::loadParams_();
    getStaticParam(&mTimer_s, "Timer");
}

}  // namespace uking::ai
