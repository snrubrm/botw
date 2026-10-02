#include "Game/AI/AI/aiTiredDistSelect.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapAutoPlacementMgr.h"

namespace uking::ai {

TiredDistSelect::TiredDistSelect(const InitArg& arg) : TargetHomeRangeSelect(arg) {}

TiredDistSelect::~TiredDistSelect() = default;

bool TiredDistSelect::init_(sead::Heap* heap) {
    return TargetHomeRangeSelect::init_(heap);
}

void TiredDistSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetHomeRangeSelect::enter_(params);
}

void TiredDistSelect::calc_() {
    TargetHomeRangeSelect::calc_();
}

void TiredDistSelect::leave_() {
    TargetHomeRangeSelect::leave_();
}

void TiredDistSelect::loadParams_() {
    TargetHomeRangeSelect::loadParams_();
    getMapUnitParam(&mTerritoryArea_m, "TerritoryArea");
}

f32 TiredDistSelect::m34() {
    if (*mTerritoryArea_m <= 0)
        return RangeSelect::m34();
    return *mTerritoryArea_m + sub_71007320F0(mActor, *mWeaponIdx_s);
}

// NON_MATCHING: the original keeps the second isNonAutoPlacement result as a branch (`tbnz; mov w21,
// wzr`) instead of returning it directly
bool TiredDistSelect::m35() {
    auto* mgr = ksys::map::AutoPlacementMgr::instance();
    if (!mgr)
        return false;

    if (mgr->isNonAutoPlacement(mActor->getMtx().getTranslation(), true))
        return true;
    if (mgr->isNonAutoPlacement(sub_71005D9330(mActor), true))
        return true;
    return false;
}

}  // namespace uking::ai
