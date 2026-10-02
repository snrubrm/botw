#include "Game/AI/Action/actionSmallDamageDirectPreTargetBack.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

SmallDamageDirectPreTargetBack::SmallDamageDirectPreTargetBack(const InitArg& arg)
    : SmallDamageDirectPreTargetBone(arg) {}

SmallDamageDirectPreTargetBack::~SmallDamageDirectPreTargetBack() = default;

void SmallDamageDirectPreTargetBack::m32(sead::Vector3f* dir, ksys::act::Actor* actor,
                                         uking::dmg::DamageManager* mgr) {
    sub_71005E242C(dir, actor, mgr);
}

bool SmallDamageDirectPreTargetBack::m33(sead::Vector3f* dir, uking::dmg::DamageManager* mgr) {
    sub_71005E242C(dir, mActor, mgr);
    return true;
}

}  // namespace uking::action
