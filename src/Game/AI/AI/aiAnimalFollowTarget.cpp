#include "Game/AI/AI/aiAnimalFollowTarget.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAnimalFollowOffset.h"

namespace uking::ai {

AnimalFollowTarget::AnimalFollowTarget(const InitArg& arg) : HorseFollow(arg) {}

AnimalFollowTarget::~AnimalFollowTarget() = default;

bool AnimalFollowTarget::init_(sead::Heap* heap) {
    return HorseFollow::init_(heap);
}

void AnimalFollowTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseFollow::enter_(params);
}

void AnimalFollowTarget::calc_() {
    HorseFollow::calc_();
}

void AnimalFollowTarget::leave_() {
    HorseFollow::leave_();
}

void AnimalFollowTarget::loadParams_() {
    HorseFollow::loadParams_();
    getStaticParam(&mUseLocalOffsetType_s, "UseLocalOffsetType");
}

const sead::Vector3f* AnimalFollowTarget::m38() {
    if (*mUseLocalOffsetType_s == 1) {
        if (const auto* offset =
                mActor->getParam()->getRes().mGParamList->getAnimalFollowOffset()) {
            return &offset->mEatLocalOffset.ref();
        }
    }
    return mSelfPositionOffsetLocal_s;
}

}  // namespace uking::ai
