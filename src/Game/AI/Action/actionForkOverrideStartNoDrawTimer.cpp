#include "Game/AI/Action/actionForkOverrideStartNoDrawTimer.h"
#include "Game/Actor/actEnemy.h"

namespace uking::action {

ForkOverrideStartNoDrawTimer::ForkOverrideStartNoDrawTimer(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkOverrideStartNoDrawTimer::~ForkOverrideStartNoDrawTimer() = default;

bool ForkOverrideStartNoDrawTimer::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkOverrideStartNoDrawTimer::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    if (isRootAiParamINot5()) {
        if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
            enemy->sub_7100018A9C(*mTime_s);
    }
}

void ForkOverrideStartNoDrawTimer::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkOverrideStartNoDrawTimer::loadParams_() {
    getStaticParam(&mTime_s, "Time");
}

void ForkOverrideStartNoDrawTimer::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
