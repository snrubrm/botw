#include "Game/AI/AI/aiGearRangeSelect.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

GearRangeSelect::GearRangeSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GearRangeSelect::~GearRangeSelect() = default;

bool GearRangeSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the original compares two SEAD_ENUM-like values (both go through a stack round trip);
// RideableBase::S1::_9 / _b and the threshold are plain integers here
void GearRangeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* rideable = mActor->m132()) {
        const auto& gear = rideable->_18;
        if ((gear._b != 0 ? gear._b : gear._9) >= *mGearThreashold_s) {
            changeChild("高速ギア", params);
            return;
        }
    }
    changeChild("低速ギア", params);
}

// NON_MATCHING: same enum round trip as enter_
void GearRangeSelect::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed() || !child->isChangeable())
        return;
    if (*mCheckOnce_s)
        return;

    if (auto* rideable = mActor->m132()) {
        const auto& gear = rideable->_18;
        if ((gear._b != 0 ? gear._b : gear._9) >= *mGearThreashold_s) {
            if (!isCurrentChild("高速ギア"))
                changeChild("高速ギア");
            return;
        }
    }
    if (!isCurrentChild("低速ギア"))
        changeChild("低速ギア");
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
