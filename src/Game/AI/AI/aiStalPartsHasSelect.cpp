#include "Game/AI/AI/aiStalPartsHasSelect.h"
#include "Game/AI/aiUnk_7100724C64.h"

namespace uking::ai {

StalPartsHasSelect::StalPartsHasSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StalPartsHasSelect::~StalPartsHasSelect() = default;

bool StalPartsHasSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StalPartsHasSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (sub_7100726004(mActor, *mPartsID_s))
        changeChild("ある", params);
    else
        changeChild("ない", params);
}

void StalPartsHasSelect::calc_() {
    if (!getCurrentChild()->isChangeable())
        return;

    if (sub_7100726004(mActor, *mPartsID_s)) {
        if (isCurrentChild("ない"))
            changeChild("ある");
    } else {
        if (isCurrentChild("ある"))
            changeChild("ない");
    }
}

bool StalPartsHasSelect::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool StalPartsHasSelect::isFinished() const {
    return ksys::act::ai::Ai::isFinished() || getCurrentChild()->isFinished();
}

void StalPartsHasSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void StalPartsHasSelect::loadParams_() {
    getStaticParam(&mPartsID_s, "PartsID");
}

}  // namespace uking::ai
