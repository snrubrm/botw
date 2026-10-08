#include "Game/AI/Action/actionCameraEventMove.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Event/evtEventSystem.h"
#include "KingSystem/Event/evtUnk_7100dc816c.h"

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

// NON_MATCHING: the original tail-calls BaseProcLink::operator= from the non-accessor path (`b`) and keeps a separate
// epilogue in the accessor path; ours calls it and shares the epilogue. Tried: accessor path first or last, if / else,
// ternary and early returns; clang 4 does not mark the call as a tail call here.
void CameraEventMove::sub_710075D338(ksys::act::BaseProcLink* link) {
    if (!*mPlayerRelative_d) {
        *link = _2a3 ? ksys::evt::sub_7100DC85D4(mActor) : ksys::evt::EventSystem::instance()->mSpeaker.mLink;
        return;
    }
    ksys::act::ActorConstDataAccess accessor;
    sub_7100924BE4(&accessor);
    accessor.linkAcquire(link);
}

// NON_MATCHING: same as sub_710075D338 (the tail call to BaseProcLink::operator=).
void CameraEventMove::sub_710075D3CC(ksys::act::BaseProcLink* link) {
    if (*mPlayerRelative_d) {
        *link = _2a3 ? ksys::evt::sub_7100DC85D4(mActor) : ksys::evt::EventSystem::instance()->mSpeaker.mLink;
        return;
    }
    ksys::act::ActorConstDataAccess accessor;
    sub_7100924BE4(&accessor);
    accessor.linkAcquire(link);
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
