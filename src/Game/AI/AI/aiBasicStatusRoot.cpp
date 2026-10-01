#include "Game/AI/AI/aiBasicStatusRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

namespace uking::ai {

BasicStatusRoot::BasicStatusRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool BasicStatusRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void BasicStatusRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (mActor->checkFreezeSignal())
        changeChild("凍結");
    else if (mActor->getRootAi()->getI() == 3)
        changeChild("持ち運びボックス内");
    else
        changeChild("通常");
}

void BasicStatusRoot::calc_() {
    auto* child = getCurrentChild();
    if (mActor->checkFreezeSignal()) {
        if (!isCurrentChild("凍結"))
            changeChild("凍結");
    } else if (isCurrentChild("持ち運びボックス内")) {
        if (child->isFinished() || child->isFailed())
            changeChild("通常");
    } else if (!isCurrentChild("通常")) {
        changeChild("通常");
    }
}

void BasicStatusRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void BasicStatusRoot::loadParams_() {}

}  // namespace uking::ai
