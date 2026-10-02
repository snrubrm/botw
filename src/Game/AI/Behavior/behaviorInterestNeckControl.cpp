#include "Game/AI/Behavior/behaviorInterestNeckControl.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapObject.h"

namespace uking::behavior {

InterestNeckControl::InterestNeckControl(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

InterestNeckControl::~InterestNeckControl() = default;

void InterestNeckControl::loadParams() {
    getStaticParam(&mIgnorePlayerByTimePass_s, "IgnorePlayerByTimePass");
}

void InterestNeckControl::m9() {
    auto* actor = mActor;
    if (!actor || actor->get1a0())
        return;
    if (auto* obj = actor->getMapObject()) {
        if (obj->getFlags0().isOn(ksys::map::Object::Flag0::_20000))
            return;
    }
    sub_71005DB3EC(actor);
}

}  // namespace uking::behavior
