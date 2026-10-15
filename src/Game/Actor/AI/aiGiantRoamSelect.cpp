#include "Game/Actor/AI/aiGiantRoamSelect.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapRail.h"

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

// NON_MATCHING: the last child selection uses a conditional select instead of branches.
void GiantRoamSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* object = mActor->getMapObject();
    const char* child;
    if (object && object->getRails_0() && object->getRails_0()[0])
        child = "レール移動";
    else if (*mGiantRoamType_m != 1)
        child = "待機";
    else
        child = "徘徊";
    changeChild(child, params);
}

void GiantRoamSelect::calc_() {}

void GiantRoamSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GiantRoamSelect::loadParams_() {
    getMapUnitParam(&mGiantRoamType_m, "GiantRoamType");
}

}  // namespace uking::ai
