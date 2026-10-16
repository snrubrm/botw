#include "Game/Actor/Behavior/behaviorUnderSelectedReactionNoAction.h"

namespace uking::behavior {

UnderSelectedReactionNoAction::UnderSelectedReactionNoAction(const InitArg& arg)
    : SetDamageCallback(arg) {}

UnderSelectedReactionNoAction::~UnderSelectedReactionNoAction() = default;

bool UnderSelectedReactionNoAction::init_(sead::Heap* heap) {
    if (!SetDamageCallback::init_(heap))
        return false;
    _38._24 = *mReactionID_s == 0 ? 29 : 0;
    return true;
}

void UnderSelectedReactionNoAction::calc() {
    SetDamageCallback::calc();
}

void UnderSelectedReactionNoAction::enter() {
    SetDamageCallback::enter();
}

void UnderSelectedReactionNoAction::leave() {
    SetDamageCallback::leave();
}

void UnderSelectedReactionNoAction::loadParams() {
    SetDamageCallback::loadParams();
    getStaticParam(&mReactionID_s, "ReactionID");
}

uking::act::DamageCallback* UnderSelectedReactionNoAction::m14() {
    return &_38;
}

}  // namespace uking::behavior
