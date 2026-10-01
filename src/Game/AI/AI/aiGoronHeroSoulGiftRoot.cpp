#include "Game/AI/AI/aiGoronHeroSoulGiftRoot.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"

namespace uking::ai {

GoronHeroSoulGiftRoot::GoronHeroSoulGiftRoot(const InitArg& arg) : HeroSoulGiftRoot(arg) {}

GoronHeroSoulGiftRoot::~GoronHeroSoulGiftRoot() = default;

bool GoronHeroSoulGiftRoot::init_(sead::Heap* heap) {
    return HeroSoulGiftRoot::init_(heap);
}

void GoronHeroSoulGiftRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _8c.reset(0, 1.0f / 3.0f);
    HeroSoulGiftRoot::enter_(params);
}

void GoronHeroSoulGiftRoot::leave_() {
    HeroSoulGiftRoot::leave_();
}

void GoronHeroSoulGiftRoot::loadParams_() {
    HeroSoulGiftRoot::loadParams_();
}

void GoronHeroSoulGiftRoot::calc_() {
    ksys::act::acc::PlayerBase player;
    player.getPlayerFromPlayerInfo();
    if (player.hasProc() && player.x_12())
        _8c.update();
    HeroSoulGiftRoot::calc_();
}

}  // namespace uking::ai
