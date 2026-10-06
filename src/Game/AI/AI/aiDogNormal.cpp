#include "Game/AI/AI/aiDogNormal.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"

namespace uking::ai {

DogNormal::DogNormal(const InitArg& arg) : DomesticNormal(arg) {}

DogNormal::~DogNormal() = default;

bool DogNormal::init_(sead::Heap* heap) {
    if (!DomesticNormal::init_(heap))
        return false;

    auto* object = mActor->getMapObject();
    if (!object)
        return true;
    auto* link_data = object->getLinkData();
    if (!link_data || link_data->mLinksOther.links.size() < 1)
        return true;
    auto* other = link_data->mLinksOther.links(0).other_obj;
    if (!other)
        return true;
    link_data = other->getLinkData();
    if (!link_data || link_data->mLinksOther.links.size() < 1)
        return true;
    auto* target = link_data->mLinksOther.links(0).other_obj;
    if (!target)
        return true;

    if (target->isRevivalGameDataFlagOn())
        return true;

    _464.setBit(Flag(Flag::_0));
    const sead::Vector3f translate = target->getTranslate();
    _44c = translate;
    _458 = target->getRotate().y;
    return true;
}

void DogNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    DomesticNormal::enter_(params);
    _428.previous_value = _428.value = *mFriendTickRate_s;
}

void DogNormal::leave_() {
    DomesticNormal::leave_();
}

bool DogNormal::m40() {
    return (isCurrentChild("徘徊") || isCurrentChild("なつき")) && _464.isOffBit(Flag(Flag::_4));
}

bool DogNormal::m41() {
    if (isCurrentChild("興味対象発見") && getCurrentChild()->isFinished()) {
        sub_7100364460();
        if (_464.isOnBit(Flag(Flag::_4)))
            return true;
    }
    return PreyNormal::m41();
}

bool DogNormal::m44() {
    return DomesticNormal::m44() || isCurrentChild("宝まで誘導") || isCurrentChild("なつき") ||
           isCurrentChild("ふり向き");
}

void DogNormal::loadParams_() {
    DomesticNormal::loadParams_();
    getStaticParam(&mNumFriendlyFoodForLeadTreasure_s, "NumFriendlyFoodForLeadTreasure");
    getStaticParam(&mMaxFollowDist_s, "MaxFollowDist");
    getStaticParam(&mMaxFollowFriendDecayRate_s, "MaxFollowFriendDecayRate");
    getStaticParam(&mFoodFriendRate_s, "FoodFriendRate");
    getStaticParam(&mFoodFriendDist_s, "FoodFriendDist");
    getStaticParam(&mNearFriendRate_s, "NearFriendRate");
    getStaticParam(&mNearFriendDist_s, "NearFriendDist");
    getStaticParam(&mFarFriendDecayRate_s, "FarFriendDecayRate");
    getStaticParam(&mFarFriendDist_s, "FarFriendDist");
    getStaticParam(&mFarFriendFriendlyDist_s, "FarFriendFriendlyDist");
    getStaticParam(&mAttackFriendDecayRate_s, "AttackFriendDecayRate");
    getStaticParam(&mFriendTickRate_s, "FriendTickRate");
    getStaticParam(&mNoMoveFriendDecayRate_s, "NoMoveFriendDecayRate");
    getStaticParam(&mNoMoveThreshold_s, "NoMoveThreshold");
    getStaticParam(&mFramesKeepMaxFriendly_s, "FramesKeepMaxFriendly");
    getStaticParam(&mFramesStayAfterLead_s, "FramesStayAfterLead");
    getStaticParam(&mAngleTurnToPlayer_s, "AngleTurnToPlayer");
}

}  // namespace uking::ai
