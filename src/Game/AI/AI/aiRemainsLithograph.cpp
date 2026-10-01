#include "Game/AI/AI/aiRemainsLithograph.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

RemainsLithograph::RemainsLithograph(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RemainsLithograph::~RemainsLithograph() = default;

bool RemainsLithograph::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RemainsLithograph::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (actor->isWaitRevivalForUsed())
        changeChild("動作完了");
    else if (!actor->hasPlacementLinkForBasicSig() || actor->checkBasicSig())
        changeChild("オン待機");
    else
        changeChild("オフ待機");
}

// NON_MATCHING: the original keeps the SafeString vtable pointer (+0x10) in a register across the first two isCurrentChild calls
void RemainsLithograph::calc_() {
    auto* actor = mActor;
    auto* child = getCurrentChild();
    if (child->isChangeable() || child->isFinished() || child->isFailed()) {
        if (isCurrentChild("オフ待機") && actor->checkBasicSig()) {
            changeChild("オン");
            return;
        }
        if (isCurrentChild("オン待機") && actor->hasPlacementLinkForBasicSig() &&
            !actor->checkBasicSig()) {
            changeChild("オフ");
            return;
        }
    }
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("オン"))
            changeChild("オン待機");
        else if (isCurrentChild("オフ"))
            changeChild("オフ待機");
    }
}

void RemainsLithograph::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RemainsLithograph::loadParams_() {}

}  // namespace uking::ai
