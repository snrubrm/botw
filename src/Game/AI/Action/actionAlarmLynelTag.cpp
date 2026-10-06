#include "Game/AI/Action/actionAlarmLynelTag.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"

namespace uking::action {

AlarmLynelTag::AlarmLynelTag(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AlarmLynelTag::~AlarmLynelTag() = default;

bool AlarmLynelTag::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AlarmLynelTag::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AlarmLynelTag::leave_() {
    ksys::act::ai::Action::leave_();
}

void AlarmLynelTag::loadParams_() {
    getMapUnitParam(&mAlarmPoint_m, "AlarmPoint");
}

void AlarmLynelTag::sub_710008B5A4() {
    _28.x(mAlarmPoint_m);
    auto* object = mActor->getMapObject();
    if (!object)
        return;
    auto* links = object->getLinkData();
    if (!links)
        return;

    auto objects = links->mObjects;
    for (auto it = objects.begin(), end = objects.end(); it != end; ++it) {
        ksys::act::ActorConstDataAccess accessor;
        (*it)->getActorWithAccessor(accessor);
        if (accessor.hasProc())
            _28.sub_710070DBB0(*accessor.getMessageTransceiverId(), true);
    }
}

void AlarmLynelTag::calc_() {
    if (mActor->checkBasicSig()) {
        sub_710008B5A4();
        mActor->m107();
    }
}

}  // namespace uking::action
