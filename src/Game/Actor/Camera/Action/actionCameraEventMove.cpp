#include "Game/Actor/Camera/Action/actionCameraEventMove.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actBaseProcAccessor.h"
#include "KingSystem/Event/evtEventSystem.h"
#include "KingSystem/Event/evtUnk_7100dc816c.h"

namespace uking::action {

CameraEventMove::CameraEventMove(const InitArg& arg) : CameraEvent(arg) {}

CameraEventMove::~CameraEventMove() = default;

void CameraEventMove::m45() {
    if (*mCancelDrawOther_d) {
        ksys::act::ActorLinkConstDataAccess accessor;
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
    ksys::act::ActorLinkConstDataAccess accessor;
    sub_7100924BE4(&accessor);
    accessor.linkAcquire(link);
}

// NON_MATCHING: same as sub_710075D338 (the tail call to BaseProcLink::operator=).
void CameraEventMove::sub_710075D3CC(ksys::act::BaseProcLink* link) {
    if (*mPlayerRelative_d) {
        *link = _2a3 ? ksys::evt::sub_7100DC85D4(mActor) : ksys::evt::EventSystem::instance()->mSpeaker.mLink;
        return;
    }
    ksys::act::ActorLinkConstDataAccess accessor;
    sub_7100924BE4(&accessor);
    accessor.linkAcquire(link);
}

bool CameraEventMove::handleMessage_(const ksys::Message* message) {
    if (!message)
        return false;
    if (message->getType() != ksys::MessageType(0x8800006))
        return false;

    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(&_f8, &accessor);
    const sead::Matrix34f mtx = accessor.getActorMtx();
    _118 = mtx;

    sead::Matrix34f bone_mtx = sead::Matrix34f::ident;
    if (mFrontBoneName_s.isEmpty()) {
        _184 = mtx;
        _1b4 = 2;
        _1b8 = 1.0f;
    } else if (accessor.sub_7100D12944(&bone_mtx, mFrontBoneName_s)) {
        _184 = bone_mtx;
        _1b4 = *mFrontBoneAxis_s;
        _1b8 = *mFrontBoneAxisReverse_s ? -1.0f : 1.0f;
    } else {
        _184 = mtx;
        _1b4 = 2;
        _1b8 = 1.0f;
    }

    if (sub_7100EE1D34(accessor)) {
        _178 = _118.getTranslation();
    } else if (accessor.isPlayerProfile()) {
        ksys::act::acc::PlayerBase player;
        ksys::act::acquireActor(&_f8, &player);
        _178 = player.getLookAtPosForCamera();
    } else {
        _178 = accessor.getPreviousPos2();
    }

    {
        ksys::act::acc::PlayerBase player;
        ksys::act::acquireActor(&_108, &player);
        _148 = player.getActorMtx();
        _2a0 |= 1;
    }
    return true;
}

void CameraEventMove::sub_710075E014() {
    auto* camera = getCamera();
    if (!camera)
        return;

    const sead::Vector3f diff = _84._0 - _84._c;
    const act::Unk_7100922700 polar(diff);
    act::Unk_7100922700 out;
    out._0 = _1bc._0 + (polar._0 - _1bc._0) * _1d8._18;
    out._4 = angleStuff(angleStuff(angleStuff(polar._4 - _1bc._4) * _1d8._18) + _1bc._4);
    out._8 = angleStuff(angleStuff(angleStuff(polar._8 - _1bc._8) * _1d8._18) + _1bc._8);

    camera->_860._0._c = _4c._c + (_84._c - _4c._c) * _1d8._18;
    const sead::Vector3f offset = out.sub_7100923254();
    camera->_860._0._0 = camera->_860._0._c + offset;
    camera->_860._0._24 = _4c._24 + (_84._24 - _4c._24) * _1d8._18;
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
