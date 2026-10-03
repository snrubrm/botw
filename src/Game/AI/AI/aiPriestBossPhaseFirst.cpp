#include "Game/AI/AI/aiPriestBossPhaseFirst.h"
#include "KingSystem/ActorSystem/actActor.h"
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

bool PriestBossPhaseFirst::m37(f32* ratio) {
    ksys::act::BaseProcLink link;
    if (!sub_7100525BC0(0, &link))
        return false;

    auto* actor = sead::DynamicCast<ksys::act::Actor>(link.getProc(nullptr, nullptr));
    if (!actor || !actor->isAwakeMaybe())
        return false;

    auto* life = actor->getLife();
    const f32 life_value = life ? f32(*life) : 1.0f;
    *ratio = life_value / f32(actor->getMaxLife());
    return true;
}

bool PriestBossPhaseFirst::m36() {
    ksys::act::ActorConstDataAccess accessor;
    if (sub_7100525B18(0, &accessor))
        return accessor.getLife() == 0;
    return PriestBossPhase::m36();
}

}  // namespace uking::ai
