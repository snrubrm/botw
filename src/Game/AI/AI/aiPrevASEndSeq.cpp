#include "Game/AI/AI/aiPrevASEndSeq.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

PrevASEndSeq::PrevASEndSeq(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PrevASEndSeq::~PrevASEndSeq() = default;

bool PrevASEndSeq::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PrevASEndSeq::enter_(ksys::act::ai::InlineParamPack* params) {
    if (mActor->getASList()->x_1(0, 0) == mPrevASName_s)
        changeChild("終了", params);
    else
        changeChild("行動", params);
}

void PrevASEndSeq::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("終了"))
            changeChild("行動");
        else if (child->isFinished())
            setFinished();
        else
            setFailed();
        return;
    }
    child->isChangeable();
}

void PrevASEndSeq::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PrevASEndSeq::loadParams_() {
    getStaticParam(&mPrevASName_s, "PrevASName");
}

bool PrevASEndSeq::isFailed() const {
    if (ksys::act::ai::Ai::isFailed())
        return true;
    if (isCurrentChild("行動"))
        return getCurrentChild()->isFailed();
    return false;
}

bool PrevASEndSeq::isFinished() const {
    if (ksys::act::ai::Ai::isFinished())
        return true;
    if (isCurrentChild("行動"))
        return getCurrentChild()->isFinished();
    return false;
}

}  // namespace uking::ai
