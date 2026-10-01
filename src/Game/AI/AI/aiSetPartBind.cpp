#include "Game/AI/AI/aiSetPartBind.h"

namespace uking::ai {

SetPartBind::SetPartBind(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SetPartBind::~SetPartBind() = default;

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
