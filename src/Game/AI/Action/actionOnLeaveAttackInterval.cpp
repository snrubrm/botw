#include "Game/AI/Action/actionOnLeaveAttackInterval.h"
#include "Game/Actor/actEnemy.h"

namespace uking::action {

OnLeaveAttackInterval::OnLeaveAttackInterval(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OnLeaveAttackInterval::~OnLeaveAttackInterval() = default;

bool OnLeaveAttackInterval::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OnLeaveAttackInterval::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

void OnLeaveAttackInterval::leave_() {
    auto* enemy = static_cast<act::Enemy*>(mActor);
    if (!enemy)
        return;
    const s32 interval = enemy->_f28.sub_7100001AA4(1.0f);
    enemy->_e68 = ksys::Timer(interval, interval);
}

void OnLeaveAttackInterval::loadParams_() {}

void OnLeaveAttackInterval::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
