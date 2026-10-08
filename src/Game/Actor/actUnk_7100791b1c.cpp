#include "Game/Actor/actCamera.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::act {

// NON_MATCHING: the original tests the proc for null before the type info guard and selects the first cast with csel
EditCamera* sub_7100791A0C(const ksys::act::ActorConstDataAccess& accessor) {
    auto* actor = sead::DynamicCast<ksys::act::Actor>(accessor.getProc());
    return sead::DynamicCast<EditCamera>(actor);
}

// NON_MATCHING: the original calls sub_71007917C4 with bl + ret instead of a tail call
EditCamera::CameraNames* sub_7100791B00(const ksys::act::ActorConstDataAccess& accessor) {
    if (auto* camera = sub_7100791A0C(accessor))
        return camera->sub_71007917C4();
    return nullptr;
}

Unk_7100791b1c::Unk_7100791b1c() = default;

void Unk_7100791b1c::sub_7100791B88() {
    _0.clear();
    _58 = -1;
    _60.reset();
}

}  // namespace uking::act
