#include "Game/Actor/aiUnk_71007130BC.h"
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectNpc.h"

// NON_MATCHING: only the offset of the array from the guard variable (+0x10 in the original: the array is 16-byte
// aligned there, ours is 8-byte aligned so it follows the guard at +8)
const sead::SafeString& sub_710071300C(s32 idx) {
    static const sead::SafeString sNames[] = {"", "Crouch", "Sit", "SitOnObject"};
    return sNames[idx];
}

void sub_71007130BC(ksys::act::Actor* actor, bool on) {
    if (!actor)
        return;
    if (on)
        ksys::act::x_6(actor);
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

namespace wm {
bool callIsRainingOrSnowingOrThunderStorm(bool a1) {
    return isRainingOrSnowingOrThunderStorm(a1);
}
}  // namespace wm

void sub_71007132E4(ksys::act::Actor* actor) {
    if (!actor)
        return;
    const sead::SafeString on_flag =
        actor->getParam()->getRes().mGParamList->getNpc()->mOnFlagWhenDelete.ref();
    const sead::SafeString off_flag =
        actor->getParam()->getRes().mGParamList->getNpc()->mOffFlagWhenDelete.ref();
    auto* manager = ksys::gdt::Manager::instance();
    if (!manager)
        return;
    if (!on_flag.isEmpty())
        manager->setBool(true, on_flag);
    if (!off_flag.isEmpty())
        manager->setBool(false, off_flag);
}

void sub_71007136BC(ksys::act::Actor* actor) {
    if (!actor)
        return;
    const char* name = actor->getName().getStringTop();
    auto* info = ksys::act::InfoData::instance();
    if (info && !info->hasTag(name, ksys::act::tags::Unk_0x207CBCE1))
        return;
    auto* manager = ksys::gdt::Manager::instance();
    sead::FormatFixedSafeString<64> reward("%s_Reward", name);
    bool received = false;
    if (!manager)
        return;
    auto& param = manager->getParam();
    const bool found =
        param.get().getBuffer()->getBool(&received, reward, param.shouldCheckPermissions(), true);
    if (received && found) {
        sead::FormatFixedSafeString<64> saved("%s_Saved", name);
        manager->setBool(true, saved);
    }
}

