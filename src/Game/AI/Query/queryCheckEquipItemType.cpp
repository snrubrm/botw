#include "Game/AI/Query/queryCheckEquipItemType.h"
#include <evfl/Query.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actInfoData.h"

namespace uking::query {

CheckEquipItemType::CheckEquipItemType(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckEquipItemType::~CheckEquipItemType() = default;

// NON_MATCHING: same logic and block structure; the original passes an unused `this`-like first argument to the
// out-of-line profile classifier (0x68af24, `mov x1, x0` at the call sites; ours has one parameter) and the stack
// slots of the two FixedSafeString<64> differ. The classifier is written as a local lambda (it is not checkable: it
// has no symbol).
int CheckEquipItemType::doQuery() {
    auto* info = ksys::act::InfoData::instance();
    if (!info)
        return 4;

    // 0: sword / spear, 1: shield, 2: bow, 3: armor, 5: bullet, 4: anything else.
    const auto doCheckEquipItemType = [](const sead::SafeString& profile) -> int {
        if (profile == "WeaponSmallSword" || profile == "WeaponLargeSword" ||
            profile == "WeaponSpear")
            return 0;
        if (profile == "WeaponShield")
            return 1;
        if (profile == "WeaponBow")
            return 2;
        if (profile.findIndex("Armor") != -1)
            return 3;
        if (profile == "Bullet")
            return 5;
        return 4;
    };

    if (mCheckTargetActorName.isEmpty()) {
        const int type = doCheckEquipItemType(mActor->getProfile());
        if (type != 4)
            return type;

        sead::FixedSafeString<64> group_name;
        if (!ksys::act::getSameGroupActorName(&group_name, mActor))
            return 4;
        const char* profile = nullptr;
        info->getActorProfile(&profile, group_name.cstr());
        if (!profile)
            return 4;
        return doCheckEquipItemType(sead::SafeString(profile));
    }

    const char* name_profile = nullptr;
    info->getActorProfile(&name_profile, mCheckTargetActorName.cstr());
    if (name_profile) {
        const int type = doCheckEquipItemType(sead::SafeString(name_profile));
        if (type != 4)
            return type;
    }

    sead::FixedSafeString<64> group_name;
    if (!ksys::act::getSameGroupActorName(&group_name, mCheckTargetActorName))
        return 4;
    const char* profile = nullptr;
    info->getActorProfile(&profile, group_name.cstr());
    if (!profile)
        return 4;
    return doCheckEquipItemType(sead::SafeString(profile));
}

void CheckEquipItemType::loadParams(const evfl::QueryArg& arg) {
    loadString(arg.param_accessor, "CheckTargetActorName");
}

void CheckEquipItemType::loadParams() {
    getDynamicParam(&mCheckTargetActorName, "CheckTargetActorName");
}

}  // namespace uking::query
