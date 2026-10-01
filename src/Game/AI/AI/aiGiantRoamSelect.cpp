#include "Game/AI/AI/aiGiantRoamSelect.h"

namespace uking::ai {

GiantRoamSelect::GiantRoamSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GiantRoamSelect::~GiantRoamSelect() = default;

bool GiantRoamSelect::isFailed() const {
    if (ksys::act::ai::Ai::isFailed())
        return true;
    if (!getCurrentChild())
        return false;
    return getCurrentChild()->isFailed();
}

bool GiantRoamSelect::isFinished() const {
    if (ksys::act::ai::Ai::isFinished())
        return true;
    if (!getCurrentChild())
        return false;
    return getCurrentChild()->isFinished();
}

bool GiantRoamSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GiantRoamSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GiantRoamSelect::calc_() {}

void GiantRoamSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GiantRoamSelect::loadParams_() {
    getMapUnitParam(&mGiantRoamType_m, "GiantRoamType");
}

}  // namespace uking::ai
