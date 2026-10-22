#include "Game/Actor/aiUnk_710070284C.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "Game/Actor/aiUnk_71025b2d88.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

int sub_710070284C(ksys::act::Actor* actor) {
    static const int sTable[] = {3, 3, 2, 1, 1, 1, 0, 0, 0};
    auto* life = actor->getLife();
    const s32 value = life ? *life : 1;
    if (value >= 0 && value <= 8)
        return sTable[value];
    return 0;
}

bool sub_7100702894(ksys::act::Actor* actor) {
    auto* life = actor->getLife();
    if (!life)
        return true;
    return *life == 1;
}

bool sub_71007028CC(ksys::act::Actor* actor) {
    auto* life = actor->getLife();
    return life && *life < 1;
}

bool sub_7100703BC8(ksys::act::Actor* actor) {
    auto* life = actor->getLife();
    const s32 value = life ? *life : 1;
    switch (value) {
    case 1:
    case 2:
    case 5:
        return true;
    default:
        return false;
    }
}

void sub_710070427C(ksys::act::Actor* actor) {
    sub_71007A3900(
        actor->findPhysicsBodyByName(ksys::act::getStr_Tgt().cstr(), "WeakPointLast"));

    ksys::phys::InstanceSet* physics = actor->getPhysics();
    if (!physics)
        return;
    ksys::phys::RigidBody* neck =
        actor->findPhysicsBodyByName(ksys::act::getStr_Body().cstr(), "Neck");
    if (!neck)
        return;
    physics->sub_7100FBAF18(neck);
}

ksys::phys::RigidBody* sub_710070431C(ksys::act::Actor* actor) {
    return actor->findPhysicsBodyByName(ksys::act::getStr_Tgt().cstr(), "WeakPoint_EyeLid");
}

void sub_71007041F0(ksys::act::Actor* actor) {
    sub_71007A3768(
        actor, actor->findPhysicsBodyByName(ksys::act::getStr_Tgt().cstr(), "WeakPointLast"));

    ksys::phys::RigidBody* neck =
        actor->findPhysicsBodyByName(ksys::act::getStr_Body().cstr(), "Neck");
    if (neck)
        neck->setContactLayer(ksys::phys::ContactLayer::EntityNPC);
}

// NON_MATCHING: the original's final selection keeps the index 32-bit, clamps a negative index and
// keeps the 4-entry table load behind a bounds branch (200 vs 168 bytes); the counting and the
// max/tie-break order match.
// 0x7100704128: the suffix ("F", "B", "L" or "R") of the weak point group with the most active
// points; ties go to the earlier group. Bits 0-17 of the flag word are the weak points.
const char* sub_7100704128(const u32* active_flags) {
    s32 front = 0;
    s32 back = 0;
    s32 left = 0;
    s32 right = 0;

    for (s32 i = 0; i < 18; ++i) {
        if ((*active_flags & (1u << i)) == 0)
            continue;
        switch (i) {
        case 0:
        case 4:
        case 6:
        case 9:
        case 10:
            ++left;
            break;
        case 1:
        case 13:
            ++back;
            break;
        case 2:
        case 3:
        case 5:
        case 8:
        case 11:
            ++right;
            break;
        case 7:
        case 12:
        case 14:
        case 15:
        case 16:
        case 17:
            ++front;
            break;
        }
    }

    static const char* const sSuffixes[] = {"F", "B", "L", "R"};
    s32 index = 0;
    s32 count = front;
    if (back > count) {
        count = back;
        index = 1;
    }
    if (left > count) {
        count = left;
        index = 2;
    }
    if (right > count)
        index = 3;
    return sSuffixes[index];
}
