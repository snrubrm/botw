#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actActorUtil.h"

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
