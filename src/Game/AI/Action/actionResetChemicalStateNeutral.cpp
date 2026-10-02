#include "Game/AI/Action/actionResetChemicalStateNeutral.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ResetChemicalStateNeutral::ResetChemicalStateNeutral(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ResetChemicalStateNeutral::~ResetChemicalStateNeutral() = default;

bool ResetChemicalStateNeutral::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ResetChemicalStateNeutral::loadParams_() {}

bool ResetChemicalStateNeutral::oneShot_() {
    if (auto* chemical = mActor->getChemicalStuff())
        chemical->sub_7100D8EEE0();
    return true;
}

}  // namespace uking::action
