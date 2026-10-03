#include "Game/AI/AI/aiZoraHeroRelicBattleRidePlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

ZoraHeroRelicBattleRidePlayer::ZoraHeroRelicBattleRidePlayer(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

ZoraHeroRelicBattleRidePlayer::~ZoraHeroRelicBattleRidePlayer() = default;

bool ZoraHeroRelicBattleRidePlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ZoraHeroRelicBattleRidePlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    _c0 = false;
    _50.reset();
    _60.reset();
    _40.reset();
    sub_71006138CC();
}

void ZoraHeroRelicBattleRidePlayer::sub_71006138CC() {
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f pos;
    pos.setMul(mActor->getMtx(), sead::Vector3f{0.0f, 0.0f, 15.0f});
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("待機", &pack);
}

void ZoraHeroRelicBattleRidePlayer::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ZoraHeroRelicBattleRidePlayer::loadParams_() {
    getAITreeVariable(&mZoraHeroShowMsgUnit_a, "ZoraHeroShowMsgUnit");
}

bool ZoraHeroRelicBattleRidePlayer::handleMessage_(const ksys::Message& message) {
    if (!_70._30 && _70.m2(message)) {
        sub_7100614194(_70._38.mLink);
        _70.x();
        return true;
    }
    if (message.getType() == 0x800006a) {
        _c0 = true;
        return true;
    }
    return false;
}

}  // namespace uking::ai
