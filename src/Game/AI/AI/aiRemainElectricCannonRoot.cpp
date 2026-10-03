#include "Game/AI/AI/aiRemainElectricCannonRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::ai {

RemainElectricCannonRoot::RemainElectricCannonRoot(const InitArg& arg)
    : RemainElectricCannonRootBase(arg) {}

RemainElectricCannonRoot::~RemainElectricCannonRoot() = default;

bool RemainElectricCannonRoot::init_(sead::Heap* heap) {
    return RemainElectricCannonRootBase::init_(heap);
}

void RemainElectricCannonRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    RemainElectricCannonRootBase::enter_(params);
}

void RemainElectricCannonRoot::calc_() {
    RemainElectricCannonRootBase::calc_();
}

void RemainElectricCannonRoot::leave_() {
    RemainElectricCannonRootBase::leave_();
}

void RemainElectricCannonRoot::loadParams_() {
    RemainElectricCannonRootBase::loadParams_();
    getStaticParam(&mSearchMaxDistLoiter_s, "SearchMaxDistLoiter");
}

// NON_MATCHING: the original loads the actor's y before the player's y (all else identical)
bool RemainElectricCannonRoot::m35() {
    bool x;
    {
        ksys::act::acc::PlayerBase player;
        player.getPlayerFromPlayerInfo();
        x = player.x_33();
    }
    if (x)
        return false;
    if (getPlayerPosition().y - mActor->getMtx().m[1][3] > 0.0f)
        return false;
    return RemainElectricCannonRootBase::m35();
}

f32 RemainElectricCannonRoot::m41() {
    bool is_battle = false;
    if (auto* gdm = ksys::gdt::Manager::instance())
        gdm->getParam().get().getBool(&is_battle, "Electric_Relic_Battle");
    if (is_battle)
        return RemainElectricCannonRootBase::m41();
    return *mSearchMaxDistLoiter_s;
}

}  // namespace uking::ai
