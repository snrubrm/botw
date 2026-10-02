#include "Game/AI/AI/aiNoticePartsRangeSelector.h"

namespace uking::ai {

NoticePartsRangeSelector::NoticePartsRangeSelector(const InitArg& arg) : RangeSelect(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
NoticePartsRangeSelector::~NoticePartsRangeSelector() {
    ;
}

bool NoticePartsRangeSelector::init_(sead::Heap* heap) {
    return RangeSelect::init_(heap);
}

void NoticePartsRangeSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    RangeSelect::enter_(params);
}

void NoticePartsRangeSelector::calc_() {
    RangeSelect::calc_();
}

void NoticePartsRangeSelector::leave_() {
    RangeSelect::leave_();
}

void NoticePartsRangeSelector::loadParams_() {
    RangeSelect::loadParams_();
    getStaticParam(&mPartsName_s, "PartsName");
}

}  // namespace uking::ai
