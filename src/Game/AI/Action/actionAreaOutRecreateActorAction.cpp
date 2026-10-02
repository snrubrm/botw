#include "Game/AI/Action/actionAreaOutRecreateActorAction.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"

namespace uking::action {

AreaOutRecreateActorAction::AreaOutRecreateActorAction(const InitArg& arg) : AreaTagAction(arg) {}

AreaOutRecreateActorAction::~AreaOutRecreateActorAction() {
    _38.freeBuffer();
}

bool AreaOutRecreateActorAction::init_(sead::Heap* heap) {
    _38.tryAllocBuffer(2, heap);
    if (!_38.isBufferReady())
        return false;
    _38[0]._0 = ksys::phys::ContactLayer::SensorObject;
    _38[1]._0 = ksys::phys::ContactLayer::SensorSmallObject;
    return true;
}

bool AreaOutRecreateActorAction::m15(const ksys::act::ActorConstDataAccess& accessor) {
    if (!mActor)
        return true;
    auto* object = mActor->getMapObject();
    if (!object)
        return true;
    auto* link_data = object->getLinkData();
    if (!link_data)
        return true;

    for (auto& link : link_data->mLinksOther.links) {
        if (link.type != ksys::map::MapLinkDefType::Recreate)
            continue;
        auto* other = link.other_obj;
        if (other && other == accessor.getMapObject()) {
            _48[_58] = other->getIdx();
            ++_58;
            break;
        }
    }
    return _58 > 3;
}

void AreaOutRecreateActorAction::m5() {
    auto* actor = mActor;
    if (!actor)
        return;
    auto* object = actor->getMapObject();
    if (!object)
        return;
    auto* link_data = object->getLinkData();
    if (!link_data)
        return;

    for (auto& link : link_data->mLinksOther.links) {
        if (link.type != ksys::map::MapLinkDefType::Recreate)
            continue;
        auto* other = link.other_obj;
        if (!other)
            continue;

        ksys::act::ActorConstDataAccess accessor;
        other->getActorWithAccessor(accessor);
        if (!accessor.hasProc() || !accessor.isStateCalc())
            continue;

        bool entered = false;
        for (int i = 0; i < _58; ++i) {
            if (_48[i] == other->getIdx()) {
                entered = true;
                break;
            }
        }
        if (!entered)
            actor->sub_71011DA808(accessor);
    }
}

}  // namespace uking::action
