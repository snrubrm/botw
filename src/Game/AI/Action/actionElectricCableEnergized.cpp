#include "Game/AI/Action/actionElectricCableEnergized.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ElectricCableEnergized::ElectricCableEnergized(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ElectricCableEnergized::~ElectricCableEnergized() = default;

bool ElectricCableEnergized::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ElectricCableEnergized::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (!actor)
        return;
    if (!_20) {
        _20 = actor->sub_71011D8A44(0);
        if (!_20)
            return;
    }
    if (!_28)
        _28 = actor->sub_71011D8A44(1);
}

void ElectricCableEnergized::leave_() {
    ksys::act::ai::Action::leave_();
}

void ElectricCableEnergized::loadParams_() {}

void ElectricCableEnergized::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
