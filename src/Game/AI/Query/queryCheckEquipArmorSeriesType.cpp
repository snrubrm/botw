#include "Game/AI/Query/queryCheckEquipArmorSeriesType.h"
#include <evfl/Query.h>
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "Game/Actor/actArmorStrings.h"

namespace uking::query {

CheckEquipArmorSeriesType::CheckEquipArmorSeriesType(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

CheckEquipArmorSeriesType::~CheckEquipArmorSeriesType() = default;

// NON_MATCHING: same logic; stack slot assignment differs (the original shares the series string's slot
// with the accessors of the other paths and keeps `&mCheckType` computed before the part checks).
int CheckEquipArmorSeriesType::doQuery() {
    u8 parts = *mCheckHead;
    if (*mCheckUpper)
        parts = *mCheckHead | 2;
    if (*mCheckLower) {
        parts |= 4;
        if (parts == 7) {
            if (mCheckType == ksys::act::sUnk_71026024c8[2]) {
                bool result;
                {
                    ksys::act::acc::PlayerBase accessor;
                    accessor.getPlayerFromPlayerInfo();
                    result = accessor.ArmorSeriesTypeStuff();
                }
                return result;
            }
            sead::FixedSafeString<64> series;
            {
                ksys::act::acc::PlayerBase accessor;
                accessor.getPlayerFromPlayerInfo();
                accessor.getArmorSeriesType(&series);
            }
            return series == mCheckType;
        }
    }

    bool result;
    {
        ksys::act::acc::PlayerBase accessor;
        if (auto* info = ksys::act::PlayerInfo::instance())
            ksys::act::acquireActor(&info->getPlayerLink(), &accessor);
        if ((parts & 1) && !accessor.armorSeriesStuff(0, mCheckType)) {
            result = false;
        } else if ((parts >> 1 & 1) && !accessor.armorSeriesStuff(1, mCheckType)) {
            result = false;
        } else if ((parts >> 2 & 1) && !accessor.armorSeriesStuff(2, mCheckType)) {
            result = false;
        } else {
            result = true;
        }
    }
    return result;
}

void CheckEquipArmorSeriesType::loadParams(const evfl::QueryArg& arg) {
    loadBool(arg.param_accessor, "CheckHead");
    loadBool(arg.param_accessor, "CheckUpper");
    loadBool(arg.param_accessor, "CheckLower");
    loadString(arg.param_accessor, "CheckType");
}

void CheckEquipArmorSeriesType::loadParams() {
    getDynamicParam(&mCheckHead, "CheckHead");
    getDynamicParam(&mCheckUpper, "CheckUpper");
    getDynamicParam(&mCheckLower, "CheckLower");
    getDynamicParam(&mCheckType, "CheckType");
}

}  // namespace uking::query
