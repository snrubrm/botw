#include "Game/AI/AI/aiGerudoHeroSoulGiftRoot.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

GerudoHeroSoulGiftRoot::GerudoHeroSoulGiftRoot(const InitArg& arg) : HeroSoulGiftRoot(arg) {}

GerudoHeroSoulGiftRoot::~GerudoHeroSoulGiftRoot() = default;

bool GerudoHeroSoulGiftRoot::init_(sead::Heap* heap) {
    return HeroSoulGiftRoot::init_(heap);
}

void GerudoHeroSoulGiftRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _b8._18.x(mActor, 100.0f);
    HeroSoulGiftRoot::enter_(params);
    _9c = false;
    _9d = false;
    if (auto* awareness = mActor->getAwareness())
        awareness->enable();
    _98 = 10;
}

void GerudoHeroSoulGiftRoot::leave_() {
    HeroSoulGiftRoot::leave_();
    if (auto* awareness = mActor->getAwareness())
        awareness->disable();
    _9c = false;
}

void GerudoHeroSoulGiftRoot::calc_() {
    if (isCurrentChild("待機"))
        sub_710042EF94();
    HeroSoulGiftRoot::calc_();

    const s32 next = _98 - 1;
    if (next >= 0)
        _98 = next;

    if (!_9d)
        _9d = sub_71005DD780(mActor, 71, nullptr, 0, 0);
    if (_9c && _98 <= 0 && _9d && isCurrentChild("発動")) {
        sub_71003F3154();
        _9c = false;
    }

    if (isCurrentChild("待機")) {
        ksys::act::acc::PlayerBase player;
        player.getPlayerFromPlayerInfo();
        if (player.hasProc() && !player.m224() && !player.x_26())
            sub_710042EEB4();
    }
}

void GerudoHeroSoulGiftRoot::loadParams_() {
    HeroSoulGiftRoot::loadParams_();
    getStaticParam(&mMaxLength_s, "MaxLength");
}

bool GerudoHeroSoulGiftRoot::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x8000028 && isCurrentChild("待機")) {
        _9c = true;
        return true;
    }
    return false;
}

}  // namespace uking::ai
