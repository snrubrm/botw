#include "Game/AI/Action/actionFollowChallenge.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
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
    ksys::act::acquireActor(&ksys::act::PlayerInfo::instance()->getPlayerLink(), &_30);
    _4cc.set(mActor->getMtx().getTranslation());
    _4d8[0] = sead::SafeString("SheikerRingNo_00");
    _4d8[1] = sead::SafeString("SheikerRingNo_01");
    _4d8[2] = sead::SafeString("SheikerRingNo_02");
    _4d8[3] = sead::SafeString("SheikerRingNo_03");
    _4d8[4] = sead::SafeString("SheikerRingNo_04");
    _4d8[5] = sead::SafeString("SheikerRingNo_05");
    _4d8[6] = sead::SafeString("SheikerRingNo_06");
    _4d8[7] = sead::SafeString("SheikerRingNo_07");
    _4d8[8] = sead::SafeString("SheikerRingNo_08");
    _4d8[9] = sead::SafeString("SheikerRingNo_09");
    _4d8[10] = sead::SafeString("SheikerRingPoint");
    _4d8[11] = sead::SafeString("SheikerTarget");
    _4d8[12] = sead::SafeString("SheikerTargetAppear");
    _4d8[13] = sead::SafeString("SheikerTargetSuccess");
    _4d8[14] = sead::SafeString("SheikerTargetFailed");
    _4d8[15] = sead::SafeString("SheikerRingConvergence");
    _4d8[16] = sead::SafeString("SheikerRingConvergenceTwinkle");
    for (auto& effect : mEffects)
        effect.scale = 1.0f;
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

// NON_MATCHING: the native index is spilled before string assignment.
void FollowChallenge::sub_710004D950(s32 index, const char* name) {
    // called through a pointer in the original (not devirtualised)
    (&_4d8[index])->operator=(sead::SafeString(name));
}

void FollowChallenge::sub_710004DFF4() {
    for (auto& effect : mEffects)
        effect.handle.fadeXLink();
}

bool FollowChallenge::sub_710004FA3C() {
    return _4ba;
}

}  // namespace uking::action
