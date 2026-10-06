#include "Game/AI/Action/actionBolt.h"
#include "Game/Actor/actModelMaterialUtil.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
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
    if (_38._30) {
        const auto key = mActor->getModel()->searchMaterial("Mt_Rope");
        if (key.isValid())
            act::setMaterialVisible(mActor->getModel(), key, false);
        _38.x();
    }

    if (!*mIsNoBindAlive_m) {
        ksys::act::ActorConstDataAccess accessor;
        if (!ksys::act::acquireActor(&_28, &accessor) || accessor.isStateSleep())
            mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
}

}  // namespace uking::action
