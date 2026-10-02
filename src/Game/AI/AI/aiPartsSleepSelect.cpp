#include "Game/AI/AI/aiPartsSleepSelect.h"

namespace uking::ai {

PartsSleepSelect::PartsSleepSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
PartsSleepSelect::~PartsSleepSelect() {
    ;
}

bool PartsSleepSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PartsSleepSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (sub_71004F50A0())
        changeChild("寝てる", params);
    else
        changeChild("起きてる", params);
}

void PartsSleepSelect::calc_() {
    if (!getCurrentChild()->isChangeable())
        return;

    const bool is_on = isCurrentChild("寝てる");
    const bool should_be_on = sub_71004F50A0();
    if (is_on) {
        if (!should_be_on)
            changeChild("起きてる");
    } else if (should_be_on) {
        changeChild("寝てる");
    }
}

void PartsSleepSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PartsSleepSelect::loadParams_() {
    getStaticParam(&mPartsName_s, "PartsName");
}

}  // namespace uking::ai
