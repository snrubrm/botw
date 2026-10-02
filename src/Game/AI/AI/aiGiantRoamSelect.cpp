#include "Game/AI/AI/aiGiantRoamSelect.h"
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

// NON_MATCHING: block order of the last two changeChild calls (tried if/else both ways, switch, else-if)
void GiantRoamSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* object = mActor->getMapObject();
    if (object && object->getRails_0() && static_cast<ksys::map::Rail**>(object->getRails_0())[0]) {
        changeChild("レール移動", params);
        return;
    }
    if (*mGiantRoamType_m == 1)
        changeChild("徘徊", params);
    else
        changeChild("待機", params);
}

void GiantRoamSelect::calc_() {}

void GiantRoamSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GiantRoamSelect::loadParams_() {
    getMapUnitParam(&mGiantRoamType_m, "GiantRoamType");
}

}  // namespace uking::ai
