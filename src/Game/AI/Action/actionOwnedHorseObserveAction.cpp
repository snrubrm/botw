#include "Game/AI/Action/actionOwnedHorseObserveAction.h"
#include "Game/Actor/actRideable.h"
#include "Game/gameHorseMgr.h"
#include "KingSystem/GameData/gdtManager.h"
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

void OwnedHorseObserveAction::calc_() {
    _58 = false;
    bool update_flag = true;
    u32 calc_tag = false;
    if (auto* mgr = HorseMgr::instance()) {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&mgr->mOwnedHorse, &accessor)) {
            if (accessor.isStateSleep()) {
                ActorObserverBase::calc();
                update_flag = false;
            } else {
                calc_tag = accessor.isStateCalc();
            }
        }
    }
    if (!update_flag)
        return;

    if (calc_tag)
        AreaTagAction::calc_();
    else
        ActorObserverBase::calc();

    if (_58) {
        if (_59 != 1) {
            ksys::gdt::Manager::instance()->setBool(true, mSaveFlag_m);
            _59 = 1;
        }
    } else if (_59 != 0) {
        ksys::gdt::Manager::instance()->setBool(false, mSaveFlag_m);
        _59 = 0;
    }
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
