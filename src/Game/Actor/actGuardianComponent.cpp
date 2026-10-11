#include "Game/Actor/actGuardianComponent.h"
#include "Game/Actor/actGuardian.h"

namespace uking::act {

Guardian* GuardianComponent::sub_710003D2B4() {
    return sead::DynamicCast<Guardian>(_b90.getProc(nullptr, nullptr));
}

ksys::act::Actor* GuardianComponent::m31() {
    return sub_710003D2B4();
}

}  // namespace uking::act
