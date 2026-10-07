#include "Game/AI/AI/aiPriestBossPhaseThird.h"
#include "Game/DLC/aocHardModeManager.h"
#include "KingSystem/ActorSystem/actLifeRecoveryInfo.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "Game/AI/aiUnk_7102450fa8.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

PriestBossPhaseThird::PriestBossPhaseThird(const InitArg& arg) : PriestBossPhase(arg) {}

PriestBossPhaseThird::~PriestBossPhaseThird() = default;

bool PriestBossPhaseThird::init_(sead::Heap* heap) {
    return PriestBossPhase::init_(heap);
}

void PriestBossPhaseThird::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossPhase::enter_(params);
    ksys::act::ActorConstDataAccess accessor;
    if (sub_7100525B18(1, &accessor)) {
        sead::Matrix34f mtx = mActor->getMtx();
        const sead::Vector3f offset{0, 5, 0};
        mtx.m[0][3] += offset.x;
        mtx.m[1][3] += offset.y;
        mtx.m[2][3] += offset.z;
        accessor.setProperties(mtx, nullptr, nullptr, nullptr, false, 0, -1);
    } else {
        setFailed();
    }
    if (sub_7100525B18(0, &accessor))
        accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    auto* unit = sub_7100525A88();
    unit->_348 = *mBreakIronBallCount_s;
}

void PriestBossPhaseThird::calc_() {
    PriestBossPhase::calc_();
}

void PriestBossPhaseThird::leave_() {
    PriestBossPhase::leave_();
}

void PriestBossPhaseThird::loadParams_() {
    PriestBossPhase::loadParams_();
    getStaticParam(&mBreakIronBallCount_s, "BreakIronBallCount");
}

bool PriestBossPhaseThird::m37(f32* x) {
    ksys::act::ActorConstDataAccess accessor;
    if (sub_7100525B18(1, &accessor) && accessor.isStateCalc()) {
        const f32 life = accessor.getLife();
        const f32 max_life = accessor.getMaxLife();
        *x = 1.0f - (max_life - life) / (max_life * 0.5f);
        return true;
    }
    return false;
}

// NON_MATCHING: the same natural locals occupy different stack slots, including the enum checks
// and life recovery parameters. No stack layout steering is used.
void PriestBossPhaseThird::m35() {
    auto* hard_mode = aoc::HardModeManager::instance();
    if (!hard_mode || !hard_mode->checkFlag(aoc::HardModeManager::Flag::EnableHardMode) ||
        !hard_mode->isHardModeChangeOn(aoc::HardModeManager::HardModeChange::EnableLifeRegen))
        return;
    ksys::act::BaseProcLink link;
    ksys::act::ActorConstDataAccess accessor;
    if (sub_7100525B18(1, &accessor)) {
        accessor.linkAcquire(&link);
        if (link.hasProc()) {
            auto* actor = sead::DynamicCast<ksys::act::Actor>(link.getProc(nullptr, nullptr));
            actor->getLifeRecoverInfo();
            ksys::act::LifeRecoverParams params;
            ksys::act::getLifeRecoverParams(&params, actor);
            params._4 = *mPercentLifeTransition_s * *mMetaAIMaxLife_a;
            _88.sub_710070E254(params);
            _88.sub_710070DC38(actor, true);
        }
    }
}

}  // namespace uking::ai
