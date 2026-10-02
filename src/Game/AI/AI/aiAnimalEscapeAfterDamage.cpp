#include "Game/AI/AI/aiAnimalEscapeAfterDamage.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

namespace uking::ai {

AnimalEscapeAfterDamage::AnimalEscapeAfterDamage(const InitArg& arg) : AnimalEscapeAI(arg) {}

AnimalEscapeAfterDamage::~AnimalEscapeAfterDamage() = default;

bool AnimalEscapeAfterDamage::init_(sead::Heap* heap) {
    return AnimalEscapeAI::init_(heap);
}

void AnimalEscapeAfterDamage::enter_(ksys::act::ai::InlineParamPack* params) {
    AnimalEscapeAI::enter_(params);
}

void AnimalEscapeAfterDamage::calc_() {
    AnimalEscapeAI::calc_();
}

void AnimalEscapeAfterDamage::leave_() {
    AnimalEscapeAI::leave_();
}

void AnimalEscapeAfterDamage::loadParams_() {
    AnimalEscapeAI::loadParams_();
}

bool AnimalEscapeAfterDamage::m36() {
    if (testRootAiFlag2(ksys::act::ai::RootAiFlag2::_0))
        return sub_7100304854();
    return AnimalEscapeAI::m36();
}

bool AnimalEscapeAfterDamage::m37() {
    return AnimalEscapeAI::m37() || isCurrentChild("ダメージ後");
}

}  // namespace uking::ai
