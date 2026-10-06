#include "Game/AI/Action/actionStrangeBeacon.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"

namespace uking::action {

StrangeBeacon::StrangeBeacon(const InitArg& arg) : ksys::act::ai::Action(arg) {}

StrangeBeacon::~StrangeBeacon() = default;

bool StrangeBeacon::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void StrangeBeacon::enter_(ksys::act::ai::InlineParamPack* params) {
    bool linked_calc = false;
    if (auto* obj = mActor->getMapObject()) {
        auto* link_data = obj->getLinkData();
        if (link_data && link_data->mObjects.size() >= 1) {
            if (auto* linked = link_data->mObjects[0]) {
                ksys::act::ActorConstDataAccess accessor;
                linked->getActorWithAccessor(accessor);
                linked_calc = accessor.hasProc() && accessor.isStateCalc();
            }
        }
    }
    if (linked_calc && !ksys::gdt::getBoolByKey(mSaveFlag_s, false))
        return;
    xlinkSearchAndEmit(mActor, mKeyName_s.cstr(), 2, &_50);
}

void StrangeBeacon::leave_() {
    _50.fadeXLink();
}

void StrangeBeacon::loadParams_() {
    getStaticParam(&mSaveFlag_s, "SaveFlag");
    getStaticParam(&mCalcStartFlag_s, "CalcStartFlag");
    getStaticParam(&mKeyName_s, "KeyName");
}

void StrangeBeacon::calc_() {
    bool linked_calc = false;
    if (auto* obj = mActor->getMapObject()) {
        auto* link_data = obj->getLinkData();
        if (link_data && link_data->mObjects.size() >= 1) {
            if (auto* linked = link_data->mObjects[0]) {
                ksys::act::ActorConstDataAccess accessor;
                linked->getActorWithAccessor(accessor);
                linked_calc = accessor.hasProc() && accessor.isStateCalc();
            }
        }
    }

    if (linked_calc) {
        if (!ksys::gdt::getBoolByKey(mSaveFlag_s, false)) {
            _50.fadeXLink();
            return;
        }
        if (_50.sub_7101241B6C())
            return;
    } else {
        const bool hidden = mActor->sub_7100EE1E94();
        const bool active = _50.sub_7101241B6C();
        if (hidden) {
            if (active)
                _50.fadeXLink();
            return;
        }
        if (active || mActor->x_40())
            return;
    }
    xlinkSearchAndEmit(mActor, mKeyName_s.cstr(), 2, &_50);
}

}  // namespace uking::action
