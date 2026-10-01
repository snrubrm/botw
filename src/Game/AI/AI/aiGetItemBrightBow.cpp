#include "Game/AI/AI/aiGetItemBrightBow.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"

namespace uking::ai {

GetItemBrightBow::GetItemBrightBow(const InitArg& arg) : GetItemNormal(arg) {}

GetItemBrightBow::~GetItemBrightBow() = default;

bool GetItemBrightBow::init_(sead::Heap* heap) {
    return GetItemNormal::init_(heap);
}

void GetItemBrightBow::enter_(ksys::act::ai::InlineParamPack* params) {
    GetItemNormal::enter_(params);
}

void GetItemBrightBow::calc_() {
    GetItemNormal::calc_();
}

void GetItemBrightBow::leave_() {
    GetItemNormal::leave_();
}

void GetItemBrightBow::loadParams_() {
    GetItemNormal::loadParams_();
    getStaticParam(&mGetRadius_s, "GetRadius");
}

bool GetItemBrightBow::m34() {
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    return (pos - getPlayerPosition()).squaredLength() < sead::Mathf::square(*mGetRadius_s);
}

// NON_MATCHING: the original negates the m270() result with mvn+and in its own return block
bool GetItemBrightBow::m35() {
    auto* player = ksys::act::PlayerInfo::instance()->getPlayer();
    if (!player)
        return true;
    return !player->m270();
}

}  // namespace uking::ai
