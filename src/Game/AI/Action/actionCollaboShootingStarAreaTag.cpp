#include "Game/AI/Action/actionCollaboShootingStarAreaTag.h"

namespace uking::action {

CollaboShootingStarAreaTag::CollaboShootingStarAreaTag(const InitArg& arg) : AreaTagAction(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
CollaboShootingStarAreaTag::~CollaboShootingStarAreaTag() {
    ;
}

bool CollaboShootingStarAreaTag::init_(sead::Heap* heap) {
    return AreaTagAction::init_(heap);
}

void CollaboShootingStarAreaTag::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaTagAction::enter_(params);
}

void CollaboShootingStarAreaTag::leave_() {
    AreaTagAction::leave_();
}

void CollaboShootingStarAreaTag::loadParams_() {
    getMapUnitParam(&mcollaboSSFalloutFlagName_m, "collaboSSFalloutFlagName");
}

void CollaboShootingStarAreaTag::calc_() {
    AreaTagAction::calc_();
}

}  // namespace uking::action
