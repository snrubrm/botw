#include "Game/AI/Action/actionSmallDamage.h"

namespace uking::action {

SmallDamage::SmallDamage(const InitArg& arg) : SmallDamageBase(arg) {}

void SmallDamage::enter_(ksys::act::ai::InlineParamPack* params) {
    m38();
    SmallDamageBase::enter_(params);
    mFlags.set(Flag::Changeable);
}

bool SmallDamage::isFinished() const {
    return isFinishedAS(0, 0);
}

void SmallDamage::m38() {
    playAS("SmallDamage", false, 0, 0, -1.0f);
}

}  // namespace uking::action
