#include "Game/AI/aiUnk_710071edf8.h"
#include "Game/AI/aiUnk_7102450fa8.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

Unk_710071edf8::Unk_710071edf8(ksys::act::Actor* actor) : mActor(actor) {}

bool sub_710071E208() {
    auto* manager = ksys::evt::Manager::instance();
    return manager && manager->hasActiveEvent() && manager->isActiveEventNameEqualTo("Demo648_0", "");
}

bool sub_710071EB88(ksys::act::Actor* actor) {
    if (!actor)
        return false;
    return sub_71005DD798(actor, 0x13, nullptr, 0, 0);
}

bool sub_710071EDAC(ksys::act::Actor* actor) {
    if (!actor)
        return false;
    auto* physics = actor->getPhysics();
    if (!physics)
        return false;
    return !physics->getFlags().isOn(ksys::phys::InstanceSet::Flag::_80000);
}

void sub_710071EB3C(ksys::act::Actor* actor) {
    if (!actor)
        return;
    const sead::Vector3f pos = sub_71005D960C(actor);
    sub_71005DB068(actor, pos);
}

// NON_MATCHING: the original computes both flag words and selects (csel); TypedBitFlag::change branches
void sub_710071EDD0(ksys::act::Actor* actor, bool enable) {
    if (!actor)
        return;
    if (auto* physics = actor->getPhysics())
        physics->getFlags().change(ksys::phys::InstanceSet::Flag::_80000, !enable);
}

// NON_MATCHING: stage-radius load and arithmetic scheduling differ.
bool sub_710071E600(const sead::Vector3f* pos, f32 radius_rate) {
    const f32 dx = pos->x - sUnk_71025c8cf8.x;
    const f32 dz = pos->z - sUnk_71025c8cf8.z;
    const f32 radius = sUnk_7102450fa0 * radius_rate;
    return dx * dx + dz * dz < radius * radius;
}
