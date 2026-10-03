#include "Game/AI/Action/actionBolt.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

Bolt::Bolt(const InitArg& arg) : ksys::act::ai::Action(arg) {}

Bolt::~Bolt() = default;

bool Bolt::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void Bolt::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* obj = mActor->getMapObject()) {
        if (auto* link_data = obj->getLinkData()) {
            if (auto* link = link_data->findLinkWithType(ksys::map::MapLinkDefType::ModelBind)) {
                if (auto* actor = link->getObjectActor())
                    _28.acquire(actor, false);
            }
        }
    }
}

void Bolt::leave_() {
    ksys::act::ai::Action::leave_();
}

void Bolt::loadParams_() {
    getMapUnitParam(&mIsNoBindAlive_m, "IsNoBindAlive");
}

bool Bolt::handleMessage_(const ksys::Message* message) {
    if (_38._30)
        return false;
    return _38.m2(*message);
}

void Bolt::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
