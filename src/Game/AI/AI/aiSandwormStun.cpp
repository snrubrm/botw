#include "Game/AI/AI/aiSandwormStun.h"
#include "Game/AI/aiAwarenessFilters.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

SandwormStun::SandwormStun(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SandwormStun::~SandwormStun() = default;

bool SandwormStun::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SandwormStun::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("気絶");
}

void SandwormStun::calc_() {
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        return;

    if (isCurrentChild("気絶"))
        changeChild("復帰");
    else
        setFinished();
}

// NON_MATCHING: same calls and block order; the original rematerialises &filter (add x0, sp, #8) for
// the destructor and calls sub_71005D8E9C inside the awareness block, ours keeps &filter in x21
void SandwormStun::leave_() {
    if (auto* awareness = mActor->getAwareness()) {
        auto* link = sub_71005D9050(mActor);
        Unk_7102451740 filter;
        if (link)
            filter._28 = *link;
        auto* sensor = awareness->_260[0];
        if (!sensor || !ksys::act::sub_7100D7EEE8(&sensor->_8, &filter))
            sub_71005D8E9C(mActor);
    } else {
        sub_71005D8E9C(mActor);
    }
}

void SandwormStun::loadParams_() {}

}  // namespace uking::ai
