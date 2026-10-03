#include "Game/AI/Action/actionCameraEventMove.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"

namespace uking::action {

CameraEventMove::CameraEventMove(const InitArg& arg) : CameraEvent(arg) {}

CameraEventMove::~CameraEventMove() = default;

void CameraEventMove::m45() {
    if (*mCancelDrawOther_d) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_108, &accessor);
        sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x3000002), nullptr);
    }
}

void CameraEventMove::m46() {
    getStaticParam(&mTargetActor_s, "TargetActor");
    getStaticParam(&mFrontBoneAxis_s, "FrontBoneAxis");
    getStaticParam(&mReviseModeRunning_s, "ReviseModeRunning");
    getStaticParam(&mReviseModeEnd_s, "ReviseModeEnd");
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mFovy_s, "Fovy");
    getStaticParam(&mFrontBoneAxisReverse_s, "FrontBoneAxisReverse");
    getStaticParam(&mCollisionInterpolateSkip_s, "CollisionInterpolateSkip");
    getStaticParam(&mFrontBoneName_s, "FrontBoneName");
    getDynamicParam_2(&mLat_d, "Lat");
    getDynamicParam_2(&mLng_d, "Lng");
    getDynamicParam_2(&mCount_d, "Count");
    getDynamicParam_2(&mPlayerRelative_d, "PlayerRelative");
    getDynamicParam_2(&mStartCalcOnly_d, "StartCalcOnly");
    getDynamicParam_2(&mUseImaginaryLineAngle_d, "UseImaginaryLineAngle");
    getDynamicParam_2(&mCancelDrawOther_d, "CancelDrawOther");
    getDynamicParam_2(&mLatReverse_d, "LatReverse");
    getDynamicParam_2(&mLngReverse_d, "LngReverse");
    getDynamicParam_2(&mNearSide_d, "NearSide");
    getDynamicParam_2(&mOffset_d, "Offset");
}

}  // namespace uking::action
