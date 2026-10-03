#include "Game/AI/AI/aiGearRangeSelect.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

GearRangeSelect::GearRangeSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GearRangeSelect::~GearRangeSelect() = default;

bool GearRangeSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GearRangeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* rideable = mActor->m132();
    if (rideable &&
        Gear(rideable->_18._b == 0 ? rideable->_18._9 : rideable->_18._b) >=
            Gear(*mGearThreashold_s)) {
        changeChild("高速ギア", params);
    } else {
        changeChild("低速ギア", params);
    }
}

// NON_MATCHING: stack slots of the two SEAD_ENUM temporaries (the original puts the gear value in the
// slot shared with the SafeString temporaries and the threshold after them)
void GearRangeSelect::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed() || !child->isChangeable())
        return;
    if (*mCheckOnce_s)
        return;

    auto* rideable = mActor->m132();
    if (rideable &&
        Gear(rideable->_18._b == 0 ? rideable->_18._9 : rideable->_18._b) >=
            Gear(*mGearThreashold_s)) {
        if (!isCurrentChild("高速ギア"))
            changeChild("高速ギア");
    } else {
        if (!isCurrentChild("低速ギア"))
            changeChild("低速ギア");
    }
}

bool GearRangeSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool GearRangeSelect::isFailed() const {
    return getCurrentChild()->isFailed();
}

void GearRangeSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GearRangeSelect::loadParams_() {
    getStaticParam(&mGearThreashold_s, "GearThreashold");
    getStaticParam(&mCheckOnce_s, "CheckOnce");
}

}  // namespace uking::ai
