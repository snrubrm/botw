#include "Game/AI/aiUnk_71007130BC.h"
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/GameData/gdtManager.h"

void sub_71007130BC(ksys::act::Actor* actor, bool on) {
    if (!actor)
        return;
    if (on)
        actor->x_6();
    else
        ksys::act::setEnabledTalkAndLockOn(actor, false);
}

void sub_7100713564(ksys::act::Actor* actor, s32 count) {
    if (!actor)
        return;
    const char* name = actor->getName().getStringTop();
    if (auto* info = ksys::act::InfoData::instance()) {
        if (!info->hasTag(name, ksys::act::tags::Unk_0x207CBCE1))
            return;
    }
    auto* manager = ksys::gdt::Manager::instance();
    if (!manager)
        return;
    const f32 state = count < 3 ? count : 3;
    sead::FormatFixedSafeString<64> key("%s_AttackedState", name);
    manager->setS32(count < 0 ? 0 : s32(state), key);
}
