#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/GameData/gdtManager.h"

// Link order puts these after mapDebug, apart from the actActorUtil block.

bool checkIsGet(const sead::SafeString& name, bool mode);

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
