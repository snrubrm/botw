#include "Game/AI/Action/actionEatWithAS.h"

namespace uking::action {

EatWithAS::EatWithAS(const InitArg& arg) : Eat(arg) {}

EatWithAS::~EatWithAS() = default;

void EatWithAS::loadParams_() {
    Eat::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void EatWithAS::m32() {
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
}

}  // namespace uking::action
