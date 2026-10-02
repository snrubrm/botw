#include "Game/AI/AI/aiItemConductor.h"

namespace uking::ai {

// NON_MATCHING: the original zeroes _38.._79 with one memset (xlink handles without padding)
ItemConductor::ItemConductor(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ItemConductor::~ItemConductor() {
    _38.fadeXLink();
    if (_58.sub_7101241B6C())
        _58.fadeXLink();
}

void ItemConductor::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ItemConductor::loadParams_() {}

}  // namespace uking::ai
