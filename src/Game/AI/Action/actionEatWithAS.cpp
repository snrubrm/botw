#include "Game/AI/Action/actionEatWithAS.h"

namespace uking::action {

EatWithAS::EatWithAS(const InitArg& arg) : Eat(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
EatWithAS::~EatWithAS() {
    ;
}

void EatWithAS::loadParams_() {
    Eat::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void EatWithAS::m32() {
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
}

}  // namespace uking::action
