#include "Game/Actor/Behavior/behaviorSetWindForceScale.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemical.h"

namespace uking::behavior {

SetWindForceScale::SetWindForceScale(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

SetWindForceScale::~SetWindForceScale() = default;

bool SetWindForceScale::init_(sead::Heap* heap) {
    return true;
}

void SetWindForceScale::calc() {}

void SetWindForceScale::leave() {}

void SetWindForceScale::loadParams() {
    getStaticParam(&mWindScale_s, "WindScale");
}

void SetWindForceScale::enter() {
    if (auto* chemical = mActor->sub_71011D8A44(0))
        chemical->_14c = *mWindScale_s;
}

}  // namespace uking::behavior
