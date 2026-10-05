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
    if (sub_710044EC60())
        sub_710044ED64();
    else
        sub_710044EF44();
    _78 = false;
}

void ItemConductor::loadParams_() {}

}  // namespace uking::ai
