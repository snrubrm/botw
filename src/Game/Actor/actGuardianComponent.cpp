#include "Game/Actor/actGuardianComponent.h"
#include "Game/Actor/actGuardian.h"

namespace uking::act {

// 0x710003c2dc (shared with Unk_710235b408's) / D0 0x710003c2e0: empty.
GuardianComponentBind::~GuardianComponentBind() = default;

// 0x710003c2dc / D0 0x710003c2e4: empty.
Unk_710235b408::~Unk_710235b408() = default;

Guardian* GuardianComponent::sub_710003D2B4() {
    return sead::DynamicCast<Guardian>(_b90.getProc(nullptr, nullptr));
}

ksys::act::Actor* GuardianComponent::m31() {
    return sub_710003D2B4();
}

bool GuardianComponent::m55() {
    return true;
}

bool GuardianComponent::shouldUnload(s32* reason) {
    return false;
}

}  // namespace uking::act
