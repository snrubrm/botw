#include "Game/AI/Action/actionOwnedHorseObserveAction.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::action {

OwnedHorseObserveAction::OwnedHorseObserveAction(const InitArg& arg) : AreaTagAction(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
OwnedHorseObserveAction::~OwnedHorseObserveAction() {
    ;
}

bool OwnedHorseObserveAction::init_(sead::Heap* heap) {
    if (!_48.tryAllocBuffer(1, heap))
        return false;
    _48[0]._0 = ksys::phys::ContactLayer::SensorHorse;
    return true;
}

void OwnedHorseObserveAction::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaTagAction::enter_(params);
    _59 = 0xff;
}

void OwnedHorseObserveAction::loadParams_() {
    getMapUnitParam(&mSaveFlag_m, "SaveFlag");
}

// TODO: 0x7100e2416c uses the horse manager singleton (GOT 0x710257c190, not decompiled).
void OwnedHorseObserveAction::calc_() {
    AreaTagAction::calc_();
}

bool OwnedHorseObserveAction::m15(const ksys::act::ActorConstDataAccess& accessor) {
    act::Unk_7100e8b2b8* horse = accessor.getHorseOptions();
    if (!horse)
        return false;
    if (!horse->sub_7100E8BFF4())
        return false;
    _58 = true;
    return true;
}

}  // namespace uking::action
