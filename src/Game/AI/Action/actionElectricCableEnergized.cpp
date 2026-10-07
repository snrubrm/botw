#include "Game/AI/Action/actionElectricCableEnergized.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/World/worldChemicalMgr.h"
#include "KingSystem/World/worldManager.h"

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
    if (!_20 || !_28) {
        if (_20)
            _20->sub_7100D93B84();
        if (_28)
            _28->sub_7100D93B84();
        setFinished();
        return;
    }
    if (auto* world = ksys::world::Manager::instance())
        world->getChemicalMgr()->sub_71010CBDCC(_20, _28, 5);
    if (_20->_1b8 > 0.0f || _28->_1b8 > 0.0f)
        return;
    _20->sub_7100D93B84();
    _28->sub_7100D93B84();
    setFinished();
}

}  // namespace uking::action
