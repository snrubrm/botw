#include "Game/AI/Behavior/behaviorUnderSelectedReactionNoAction.h"

namespace uking::behavior {

UnderSelectedReactionNoAction::UnderSelectedReactionNoAction(const InitArg& arg)
    : SetDamageCallback(arg) {}

UnderSelectedReactionNoAction::~UnderSelectedReactionNoAction() = default;

bool UnderSelectedReactionNoAction::m6(sead::Heap* heap) {
    if (!SetDamageCallback::m6(heap))
        return false;
    _38._24 = *mReactionID_s == 0 ? 29 : 0;
    return true;
}

void UnderSelectedReactionNoAction::m7() {
    SetDamageCallback::m7();
}

void UnderSelectedReactionNoAction::m8() {
    SetDamageCallback::m8();
}

void UnderSelectedReactionNoAction::m9() {
    SetDamageCallback::m9();
}

void UnderSelectedReactionNoAction::loadParams() {
    SetDamageCallback::loadParams();
    getStaticParam(&mReactionID_s, "ReactionID");
}

uking::dmg::DamageCallback* UnderSelectedReactionNoAction::m14() {
    return &_38;
}

}  // namespace uking::behavior
