#include "Game/AI/AI/aiSetPartBind.h"

namespace uking::ai {

SetPartBind::SetPartBind(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
SetPartBind::~SetPartBind() {
    ;
}

void SetPartBind::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_7100567E78();
    changeChild("行動", params);
}

void SetPartBind::calc_() {
    if (getCurrentChild()->isFinished()) {
        setFinished();
        return;
    }
    if (getCurrentChild()->isFailed())
        setFailed();
}

void SetPartBind::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SetPartBind::loadParams_() {
    getStaticParam(&mBaseNodeName_s, "BaseNodeName");
    getStaticParam(&mPartialNodeName_s, "PartialNodeName");
}

}  // namespace uking::ai
