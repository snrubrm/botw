#include "Game/AI/AI/aiEnemyTargetGearSelect.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

EnemyTargetGearSelect::EnemyTargetGearSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyTargetGearSelect::~EnemyTargetGearSelect() = default;

bool EnemyTargetGearSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyTargetGearSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

// NON_MATCHING: only the operand order of the final compare (the original loads the gear first and compares
// `threshold, gear` with `b.le`; ours `gear, threshold` with `b.ge`; `threshold > gear` loads the threshold first)
void EnemyTargetGearSelect::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed() || !child->isChangeable() || !*mIsSelectEveryFrame_s)
        return;

    u64 value = 0;
    if (auto* link = sub_71005D9050(mActor)) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(link, &accessor);
        value = accessor.sub_7100D142E0();
    }
    const Gear gear(value);
    if (gear < *mGearThreashold_s) {
        if (isCurrentChild("対象高速ギア"))
            changeChild("対象低速ギア");
    } else {
        if (isCurrentChild("対象低速ギア"))
            changeChild("対象高速ギア");
    }
}

bool EnemyTargetGearSelect::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool EnemyTargetGearSelect::isFinished() const {
    return ksys::act::ai::Ai::isFinished() || getCurrentChild()->isFinished();
}

void EnemyTargetGearSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyTargetGearSelect::loadParams_() {
    getStaticParam(&mGearThreashold_s, "GearThreashold");
    getStaticParam(&mIsSelectEveryFrame_s, "IsSelectEveryFrame");
}

}  // namespace uking::ai
