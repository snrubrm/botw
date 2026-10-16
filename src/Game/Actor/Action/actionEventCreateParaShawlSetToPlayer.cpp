#include "Game/Actor/Action/actionEventCreateParaShawlSetToPlayer.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actBaseProcHeapMgr.h"

namespace uking::action {

EventCreateParaShawlSetToPlayer::EventCreateParaShawlSetToPlayer(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventCreateParaShawlSetToPlayer::~EventCreateParaShawlSetToPlayer() = default;

bool EventCreateParaShawlSetToPlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventCreateParaShawlSetToPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* heap_mgr = ksys::act::BaseProcHeapMgr::instance();
    if (!heap_mgr) {
        setFailed();
        return;
    }
    auto* heap = heap_mgr->getHeap();
    if (!heap) {
        setFailed();
        return;
    }
    auto* creator = ksys::act::ActorCreator::instance();
    if (!creator) {
        setFailed();
        return;
    }

    sead::FixedSafeString<64> name;
    switch (*mParaShawlType_d) {
    case 0:
        name = "PlayerStole";
        break;
    case 1:
        name = "PlayerStole2";
        break;
    case 2:
        name = "PlayerStole2_Rental";
        break;
    default:
        setFailed();
        return;
    }
    creator->requestCreateActor(name.cstr(), heap, &_28, nullptr, nullptr, 2);
}

void EventCreateParaShawlSetToPlayer::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventCreateParaShawlSetToPlayer::loadParams_() {
    getDynamicParam(&mParaShawlType_d, "ParaShawlType");
}

void EventCreateParaShawlSetToPlayer::calc_() {
    if (isFinished() || isFailed())
        return;

    if (!_28.isAllocatedOrFailed()) {
        setFailed();
        return;
    }

    if (_28.isProcReady()) {
        if (sead::DynamicCast<ksys::act::Actor>(_28.getProc())) {
            ksys::act::acc::PlayerBase player;
            player.getPlayerFromPlayerInfo();
            if (player.hasProc()) {
                if (auto* actor = sead::DynamicCast<ksys::act::Actor>(_28.releaseAndWakeProc())) {
                    actor->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
                    setFinished();
                    return;
                }
            }
        }
        _28.deleteProc();
        setFailed();
    } else if (_28.hasProcCreationFailed()) {
        _28.deleteProcIfFailed();
        setFailed();
    }
}

}  // namespace uking::action
