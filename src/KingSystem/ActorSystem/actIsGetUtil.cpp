#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/GameData/gdtManager.h"

// Link order puts these after mapDebug, apart from the actActorUtil block.

bool checkIsGet(const sead::SafeString& name, bool mode);
// 0x7100eea1f0 (declared only): sets IsGet_<name> (FixedSafeString<96>).
void setIsGetFlagEx(const sead::SafeString& name, bool value, bool mode);

// Source owner unknown: the event-flow caller uses this string prefix.
const char* sub_7100EE9E80() {
    return "IsGet_";
}

bool checkIsGetSameGroupActorName(const sead::SafeString& actor_name, bool mode) {
    sead::SafeString group_name;
    const bool has_group = ksys::act::getSameGroupActorName(&group_name, actor_name);
    return checkIsGet(has_group ? group_name : actor_name, mode);
}

// NON_MATCHING: the original selects the last getBool argument with a branch and normalizes the permission flag
// with cmp / cset; the result byte is returned without a compare.
bool checkIsGet(const sead::SafeString& name, bool mode) {
    sead::FixedSafeString<96> flag_name{"IsGet_"};
    flag_name.append(name);
    bool value = false;
    if (auto* mgr = ksys::gdt::Manager::instance()) {
        auto& ref = mgr->getParam();
        ref.get().getBuffer0()->getBool(&value, flag_name, ref.shouldCheckPermissions(), !mode);
    }
    return value;
}

// Placeholder name: sets the IsGet flag of the actor's same-group name (or of the name itself).
void setIsGetSameGroup(const sead::SafeString& actor_name, bool value, bool mode) {
    sead::SafeString group_name;
    if (ksys::act::getSameGroupActorName(&group_name, actor_name))
        setIsGetFlagEx(group_name, value, mode);
    else
        setIsGetFlagEx(actor_name, value, mode);
}

// Placeholder name (CSV act::checkIsGet): the same as checkIsGetSameGroupActorName for an actor.
bool checkIsGetSameGroupActor(ksys::act::Actor* actor, bool mode) {
    sead::SafeString group_name;
    const bool has_group = ksys::act::getSameGroupActorName(&group_name, actor);
    return checkIsGet(has_group ? group_name : actor->getName(), mode);
}
