#include "Game/AI/Action/actionFollowChallenge.h"
#include "KingSystem/Event/evtManager.h"

namespace uking::action {

FollowChallenge::FollowChallenge(const InitArg& arg) : ksys::act::ai::Action(arg) {}

FollowChallenge::~FollowChallenge() = default;

bool FollowChallenge::init_(sead::Heap* heap) {
    _4bc = *mGimmickTimeLimit_m;
    _4c8 = 0.090909091f;
    return true;
}

void FollowChallenge::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void FollowChallenge::leave_() {
    ksys::act::ai::Action::leave_();
}

void FollowChallenge::loadParams_() {
    getMapUnitParam(&mGimmickTimeLimit_m, "GimmickTimeLimit");
    getMapUnitParam(&mIsBillboard_m, "IsBillboard");
}

void FollowChallenge::calc_() {
    auto* mgr = ksys::evt::Manager::instance();
    if (mgr->hasActiveEvent() || mgr->sub_7100DB20D0())
        _4b9 = true;
    else
        _4b9 = false;
}

void FollowChallenge::sub_710004E108() {
    _4bc = -*mGimmickTimeLimit_m;
}

void FollowChallenge::sub_710004E0A4() {
    _4bc = *mGimmickTimeLimit_m;
    for (auto& effect : mEffects)
        effect.scale = 1.0f;
    _4c4 = 0.0f;
}

void FollowChallenge::sub_710004D9A4() {
    // called through a pointer in the original (not devirtualised)
    xlinkSearchAndEmit(mActor, (&_4d8[13])->cstr(), 2, &_458);
    sub_710004D9FC(&_458);
}

void FollowChallenge::sub_710004DFF4() {
    for (auto& effect : mEffects)
        effect.handle.fadeXLink();
}

bool FollowChallenge::sub_710004FA3C() {
    return _4ba;
}

}  // namespace uking::action
