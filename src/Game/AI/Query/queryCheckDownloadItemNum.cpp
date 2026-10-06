#include "Game/AI/Query/queryCheckDownloadItemNum.h"
#include <evfl/Query.h>
#include "Game/UI/uiUtils.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::query {

CheckDownloadItemNum::CheckDownloadItemNum(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckDownloadItemNum::~CheckDownloadItemNum() = default;

// NON_MATCHING: same logic; the original branches on the comparison (`b.le`) instead of selecting both
// results, and keeps `this` in x19 / the count in w20.
int CheckDownloadItemNum::doQuery() {
    s32 count = ui::sub_7100A9D03C();
    if (*mIsUnityCheckBomb && ksys::gdt::getFlag_IsGet_Obj_RemoteBomb())
        count = -1;
    s32 result;
    if (*mCheckNum < count) {
        result = 0;
    } else {
        result = 1;
        if (count < *mCheckNum)
            result = 2;
    }
    return result;
}

void CheckDownloadItemNum::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "CheckNum");
    loadBool(arg.param_accessor, "IsUnityCheckBomb");
}

void CheckDownloadItemNum::loadParams() {
    getDynamicParam(&mCheckNum, "CheckNum");
    getDynamicParam(&mIsUnityCheckBomb, "IsUnityCheckBomb");
}

}  // namespace uking::query
