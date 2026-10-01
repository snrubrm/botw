#include "Game/AI/AI/aiWolfLinkReaction.h"
#include "Game/Actor/actWolfLink.h"

namespace uking::ai {

WolfLinkReaction::WolfLinkReaction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WolfLinkReaction::~WolfLinkReaction() = default;

bool WolfLinkReaction::init_(sead::Heap* heap) {
    _40 = sead::DynamicCast<act::WolfLink>(mActor);
    return true;
}

void WolfLinkReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    m34();
    _38 = true;
}

void WolfLinkReaction::leave_() {}

void WolfLinkReaction::loadParams_() {}

bool WolfLinkReaction::isFinished() const {
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        return false;
    return true;
}

}  // namespace uking::ai
