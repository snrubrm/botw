#include "Game/AI/AI/aiRitoHeroSoulGiftRoot.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

RitoHeroSoulGiftRoot::RitoHeroSoulGiftRoot(const InitArg& arg) : HeroSoulGiftRoot(arg) {}

RitoHeroSoulGiftRoot::~RitoHeroSoulGiftRoot() {
    _a8.reset();
}

bool RitoHeroSoulGiftRoot::init_(sead::Heap* heap) {
    return HeroSoulGiftRoot::init_(heap);
}

void RitoHeroSoulGiftRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    HeroSoulGiftRoot::enter_(params);
}

// NON_MATCHING: stack layout (the original's isCurrentChild string temporaries use two slots)
void RitoHeroSoulGiftRoot::calc_() {
    if (!isCurrentChild("退場"))
        setPosition();
    HeroSoulGiftRoot::calc_();
    if (isCurrentChild("待機")) {
        bool rising;
        {
            ksys::act::acc::PlayerBase player;
            player.getPlayerFromPlayerInfo();
            rising = player.isRisingInAirMaybe();
        }
        if (!rising)
            sub_710042EEB4();
    }
}

void RitoHeroSoulGiftRoot::leave_() {
    HeroSoulGiftRoot::leave_();
}

void RitoHeroSoulGiftRoot::loadParams_() {
    HeroSoulGiftRoot::loadParams_();
    getStaticParam(&mActorName_s, "ActorName");
    getStaticParam(&mScale_s, "Scale");
}

void RitoHeroSoulGiftRoot::m36() {
    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(&_a8, &accessor))
        accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    HeroSoulGiftRoot::m36();
}

bool RitoHeroSoulGiftRoot::m37() {
    bool rising;
    {
        ksys::act::acc::PlayerBase player;
        player.getPlayerFromPlayerInfo();
        rising = player.isRisingInAirMaybe();
    }
    bool ret = false;
    if (rising) {
        ksys::act::acc::PlayerBase player;
        player.getPlayerFromPlayerInfo();
        ret = player.m200();
    }
    return ret;
}

void RitoHeroSoulGiftRoot::setPosition() {
    if (_b8 || !_a8.hasProc())
        return;

    ksys::act::ActorConstDataAccess accessor;
    if (!ksys::act::acquireActor(&_a8, &accessor))
        return;

    if (accessor.isStateSleep()) {
        accessor.setProperties(mActor->getMtx(), nullptr, nullptr, nullptr, false, 0, -1);
        _b8 = true;
    } else if (accessor.isStateCalc()) {
        accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    }
}

}  // namespace uking::ai
