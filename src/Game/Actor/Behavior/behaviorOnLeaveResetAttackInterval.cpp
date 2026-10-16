#include "Game/Actor/Behavior/behaviorOnLeaveResetAttackInterval.h"
#include "Game/Actor/actEnemy.h"

namespace uking::behavior {

OnLeaveResetAttackInterval::OnLeaveResetAttackInterval(const InitArg& arg)
    : ksys::act::ai::Behavior(arg) {}

OnLeaveResetAttackInterval::~OnLeaveResetAttackInterval() = default;

bool OnLeaveResetAttackInterval::init_(sead::Heap* heap) {
    return true;
}

void OnLeaveResetAttackInterval::calc() {}

void OnLeaveResetAttackInterval::enter() {}

void OnLeaveResetAttackInterval::loadParams() {

}

void OnLeaveResetAttackInterval::leave() {
    auto* enemy = static_cast<uking::act::Enemy*>(mActor);
    if (!enemy)
        return;
    const f32 interval = enemy->_f28.sub_7100001AA4(1.0f);
    enemy->_e68 = ksys::Timer(interval, interval);
}

}  // namespace uking::behavior
