#include "Game/Actor/actCamera.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::act {

// inline-only in the original; name is a guess. The proc-null/type-check sequence
// at 0x7100791a0c repeats in acc::Weapon::isShield (0x71002efb9c) and
// acc::Armor::getArmorDefenceAddLevel (0x7100e2bcc4).
static inline ksys::act::BaseProc* getProcIfActor(ksys::act::BaseProc* proc) {
    if (proc && sead::IsDerivedFrom<ksys::act::Actor>(proc))
        return proc;
    return nullptr;
}

EditCamera* sub_7100791A0C(const ksys::act::ActorConstDataAccess& accessor) {
    auto* proc = accessor.getProc();
    if (!proc)
        return nullptr;
    auto* actor = static_cast<ksys::act::Actor*>(getProcIfActor(proc));
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
