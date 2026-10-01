#include "Game/AI/AI/aiPrevASOR2SelectTwo.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

PrevASOR2SelectTwo::PrevASOR2SelectTwo(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PrevASOR2SelectTwo::~PrevASOR2SelectTwo() = default;

bool PrevASOR2SelectTwo::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PrevASOR2SelectTwo::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* as_list = mActor->getASList();
    if ((!mAS1_s.isEmpty() && as_list->x_1(0, 0) == mAS1_s) ||
        (!mAS2_s.isEmpty() && as_list->x_1(0, 0) == mAS2_s)) {
        changeChild("該当", params);
    } else {
        changeChild("非該当", params);
    }
}

void PrevASOR2SelectTwo::calc_() {}

void PrevASOR2SelectTwo::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PrevASOR2SelectTwo::loadParams_() {
    getStaticParam(&mAS1_s, "AS1");
    getStaticParam(&mAS2_s, "AS2");
}

bool PrevASOR2SelectTwo::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool PrevASOR2SelectTwo::isFinished() const {
    return ksys::act::ai::Ai::isFinished() || getCurrentChild()->isFinished();
}

}  // namespace uking::ai
