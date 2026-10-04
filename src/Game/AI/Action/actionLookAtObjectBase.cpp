#include "Game/AI/Action/actionLookAtObjectBase.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

LookAtObjectBase::LookAtObjectBase(const InitArg& arg) : PlayerAction(arg) {}

LookAtObjectBase::~LookAtObjectBase() = default;

bool LookAtObjectBase::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void LookAtObjectBase::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void LookAtObjectBase::leave_() {}

void LookAtObjectBase::loadParams_() {
    getDynamicParam(&mObjectId_d, "ObjectId");
    getDynamicParam(&mFaceId_d, "FaceId");
    getDynamicParam(&mTurnDirection_d, "TurnDirection");
    getDynamicParam(&mIsValid_d, "IsValid");
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mUniqueName_d, "UniqueName");
    getDynamicParam(&mPosOffset_d, "PosOffset");
    getDynamicParam(&mTurnPosition_d, "TurnPosition");
}

void LookAtObjectBase::calc_() {}

void LookAtObjectBase::m33() {
    _30 = *mObjectId_d;
    _34 = *mFaceId_d;
    _38.set(sead::Vector3f::zero);
    _68.set(sead::Vector3f::zero);
    _44 = false;
    _45 = *mIsValid_d;
    _48 = mActorName_d;
    _58 = mUniqueName_d;
}

bool LookAtObjectBase::m35(ksys::act::BaseProcLink* link, sead::Vector3f* pos,
                           const sead::SafeString& name1, const sead::SafeString& name2) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::findLinkedActor(&accessor, mActor, name1);
    auto* obj = ksys::act::findLinkReferenceObj(mActor, name1, "", nullptr);
    if (accessor.hasProc()) {
        accessor.linkAcquire(link);
        return true;
    }
    if (!obj)
        return false;
    *pos = sead::Vector3f(obj->getTranslate());
    return true;
}

}  // namespace uking::action
