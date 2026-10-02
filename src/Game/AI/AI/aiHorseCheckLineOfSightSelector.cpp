#include "Game/AI/AI/aiHorseCheckLineOfSightSelector.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

HorseCheckLineOfSightSelector::HorseCheckLineOfSightSelector(const InitArg& arg)
    : HorseCheckLineOfSightSelectorBase(arg) {}

HorseCheckLineOfSightSelector::~HorseCheckLineOfSightSelector() = default;

bool HorseCheckLineOfSightSelector::init_(sead::Heap* heap) {
    return HorseCheckLineOfSightSelectorBase::init_(heap);
}

void HorseCheckLineOfSightSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseCheckLineOfSightSelectorBase::enter_(params);
}

void HorseCheckLineOfSightSelector::calc_() {
    HorseCheckLineOfSightSelectorBase::calc_();
}

void HorseCheckLineOfSightSelector::leave_() {
    HorseCheckLineOfSightSelectorBase::leave_();
}

void HorseCheckLineOfSightSelector::loadParams_() {
    HorseCheckLineOfSightSelectorBase::loadParams_();
}

void HorseCheckLineOfSightSelector::m34(sead::Vector3f* out) {
    auto* rideable = mActor->getHorseOptionsMaybe();
    if (!rideable)
        return;
    if (rideable->_148.x != 0.0f || rideable->_148.z != 0.0f)
        out->set(rideable->_148);
}

}  // namespace uking::ai
