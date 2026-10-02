#include "Game/AI/AI/aiPriestBossPhaseFirst.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

PriestBossPhaseFirst::PriestBossPhaseFirst(const InitArg& arg) : PriestBossPhase(arg) {}

PriestBossPhaseFirst::~PriestBossPhaseFirst() = default;

bool PriestBossPhaseFirst::init_(sead::Heap* heap) {
    return PriestBossPhase::init_(heap);
}

void PriestBossPhaseFirst::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossPhase::enter_(params);
    ksys::act::ActorConstDataAccess accessor;
    if (sub_7100525B18(0, &accessor))
        accessor.wakeUp(ksys::act::BaseProc::SleepWakeReason::_0);
    else
        setFailed();
    _7c = false;
}

void PriestBossPhaseFirst::leave_() {
    PriestBossPhase::leave_();
    ksys::act::ActorConstDataAccess accessor;
    if (sub_7100525B18(0, &accessor))
        accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
}

void PriestBossPhaseFirst::loadParams_() {
    PriestBossPhase::loadParams_();
}

void PriestBossPhaseFirst::m39() {
    ksys::act::ActorConstDataAccess accessor;
    if (sub_7100525B18(0, &accessor))
        accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
}

}  // namespace uking::ai
