#include "Game/AI/AI/aiItemConductor.h"

namespace uking::ai {

ItemConductor::ItemConductor(const InitArg& arg)
    : ksys::act::ai::Ai(arg), _38(), _58(), _78() {}

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
