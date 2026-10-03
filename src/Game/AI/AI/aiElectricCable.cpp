#include "Game/AI/AI/aiElectricCable.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapRail.h"

namespace uking::ai {

ElectricCable::ElectricCable(const InitArg& arg) : ksys::act::ai::Ai(arg) {
    _40 = nullptr;
    _48 = nullptr;
}

ElectricCable::~ElectricCable() = default;

bool ElectricCable::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ElectricCable::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (!actor)
        return;

    _40 = actor->sub_71011D8A44(0);
    if (_40) {
        _48 = actor->sub_71011D8A44(1);
        if (_48) {
            auto* object = actor->getMapObject();
            if (object && object->getRails_0()) {
                _50 = static_cast<ksys::map::Rail**>(object->getRails_0())[0];
                if (_50) {
                    actor->getMtx().getTranslation(_58);
                    actor->getMtx().getTranslation(_64);
                    changeChild("Wait");
                    _78 = false;
                    return;
                }
            }
        }
    }
    changeChild("Wait");
}

void ElectricCable::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ElectricCable::loadParams_() {
    getMapUnitParam(&mIsDisplayOnUI_m, "IsDisplayOnUI");
}

}  // namespace uking::ai
