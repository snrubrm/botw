#include "Game/AI/Action/actionSimpleGrabWithASBase.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SimpleGrabWithASBase::SimpleGrabWithASBase(const InitArg& arg) : Grab(arg) {}

SimpleGrabWithASBase::~SimpleGrabWithASBase() = default;

void SimpleGrabWithASBase::loadParams_() {
    Grab::loadParams_();
}

bool SimpleGrabWithASBase::m34() {
    auto* target = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcChild());
    if (!target)
        return false;
    if (sub_7100738FA8(mActor, target))
        return true;
    return (mActor->getMtx().getTranslation() - target->getMtx().getTranslation()).length() <=
           *mCheckRadius_s;
}

}  // namespace uking::action
