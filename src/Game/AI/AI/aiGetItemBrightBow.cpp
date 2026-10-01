#include "Game/AI/AI/aiGetItemBrightBow.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

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

}  // namespace uking::ai
