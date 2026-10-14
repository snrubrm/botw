#include "Game/Actor/AI/aiHorseCheckLineOfSightSelector.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

HorseCheckLineOfSightSelector::HorseCheckLineOfSightSelector(const InitArg& arg)
    : CheckLineOfSightSelector(arg) {}

HorseCheckLineOfSightSelector::~HorseCheckLineOfSightSelector() = default;

bool HorseCheckLineOfSightSelector::init_(sead::Heap* heap) {
    return CheckLineOfSightSelector::init_(heap);
}

void HorseCheckLineOfSightSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    CheckLineOfSightSelector::enter_(params);
}

void HorseCheckLineOfSightSelector::calc_() {
    CheckLineOfSightSelector::calc_();
}

void HorseCheckLineOfSightSelector::leave_() {
    CheckLineOfSightSelector::leave_();
}

void HorseCheckLineOfSightSelector::loadParams_() {
    CheckLineOfSightSelector::loadParams_();
}

void HorseCheckLineOfSightSelector::m34(sead::Vector3f* out) {
    auto* rideable = mActor->getHorseOptionsMaybe();
    if (!rideable)
        return;
    if (rideable->_148.x != 0.0f || rideable->_148.z != 0.0f)
        out->set(rideable->_148);
}

}  // namespace uking::ai
