#include "Game/AI/Action/actionEventOffWaitRevivalAction.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Map/mapPlacementMgr.h"

bool offWaitRevivalSomeActorCheck();
bool offWaitRevivalUnknown_0();
void offWaitRevivalForAirOcta();

namespace uking::action {

EventOffWaitRevivalAction::EventOffWaitRevivalAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventOffWaitRevivalAction::~EventOffWaitRevivalAction() = default;

bool EventOffWaitRevivalAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventOffWaitRevivalAction::enter_(ksys::act::ai::InlineParamPack* params) {
    _1c = 0;
    _1d = 0;
    _1e = 0;
}

void EventOffWaitRevivalAction::loadParams_() {}

// NON_MATCHING: flag-index operations fold directly instead of retaining temporary index storage.
void EventOffWaitRevivalAction::calc_() {
    using PlacementMgr = ksys::map::PlacementMgr;
    using Manager = ksys::gdt::Manager;
    if (_1d & 2) {
        auto* placement = PlacementMgr::instance();
        if (!placement || placement->mFlags.isOn(PlacementMgr::MgrFlag::_4))
            return;
        setFinished();
        return;
    }

    if (_1c == 1) {
        if (!offWaitRevivalUnknown_0() || ++_1e >= 601) {
            offWaitRevivalForAirOcta();
            _1c = 2;
        }
    } else if (_1c == 0) {
        if (offWaitRevivalSomeActorCheck()) {
            _1e = 0;
            _1c = 1;
        } else {
            _1c = 2;
        }
    }

    auto* manager = Manager::instance();
    if (!manager)
        return;
    if (!(_1d & 1)) {
        if (!manager->mResetFlags.isZero())
            return;
        manager->mBitFlags.set(Manager::BitFlag::_8);
        manager->mResetFlags.setDirect(Manager::ResetFlag::_2);
        _1d |= 1;
    } else {
        if (_1c != 2 || manager->mResetFlags.isOn(Manager::ResetFlag::_2))
            return;
        auto* placement = PlacementMgr::instance();
        if (!placement)
            return;
        placement->mFlags.set(PlacementMgr::MgrFlag::_1);
        _1d |= 2;
    }
}

}  // namespace uking::action
