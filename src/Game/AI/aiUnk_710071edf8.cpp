#include "Game/AI/aiUnk_710071edf8.h"
#include "Game/AI/aiUnk_71005D6D10.h"

Unk_710071edf8::Unk_710071edf8(ksys::act::Actor* actor) : mActor(actor) {}

void sub_710071EB3C(ksys::act::Actor* actor) {
    if (!actor)
        return;
    const sead::Vector3f pos = sub_71005D960C(actor);
    sub_71005DB068(actor, pos);
}
