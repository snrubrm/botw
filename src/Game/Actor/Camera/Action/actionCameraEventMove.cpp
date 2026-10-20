#include "Game/Actor/Camera/Action/actionCameraEventMove.h"
#include <random/seadGlobalRandom.h>
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/gameUnk_71024739d0.h"
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

    const act::Unk_7100922700 polar(_84._0 - _84._c);
    act::Unk_7100922700 out = _1bc;
    out._0 += (polar._0 - _1bc._0) * _1d8._18;
    out._4 = angleStuff(angleStuff(angleStuff(out._4 - _1bc._4) * _1d8._18) + out._4);
    out._8 = angleStuff(angleStuff(angleStuff(out._8 - _1bc._8) * _1d8._18) + out._8);

    camera->_860._0._c = _4c._c + (_84._c - _4c._c) * _1d8._18;
    const sead::Vector3f offset = out.sub_7100923254();
    camera->_860._0._0 = camera->_860._0._c + offset;
    camera->_860._0._24 = _4c._24 + (_84._24 - _4c._24) * _1d8._18;
}

void CameraEventMove::m43() {
    _84._24 = *mFovy_s;
    _2a3 = *mTargetActor_s < 2 ? *mTargetActor_s : 1;
    sub_710075D338(&_f8);
    sub_710075D3CC(&_108);
    _2a4 = *mReviseModeRunning_s < 3 ? *mReviseModeRunning_s : 1;
    _2a5 = *mReviseModeEnd_s < 3 ? *mReviseModeEnd_s : 1;
    _1d4 = 0.0f;
    _1d8.sub_710079C384(*mCount_d, 0.0f);
    _2a0 = 0;
    _2a1 = 0;
    _2a2 = 0;

    auto* camera = getCamera();
    if (!camera)
        return;

    camera->_860._a8 = camera->_860._e0;
    camera->_860._70 = camera->_860._e0;
    camera->_860._38 = camera->_860._e0;
    camera->_860._0 = camera->_860._e0;
    _bc = camera->_860._0;
    _4c = camera->_860._0;
    const sead::Vector3f diff = camera->_860._0._0 - camera->_860._0._c;
    _1bc.set(diff);

    if (*mCount_d == 0.0f)
        camera->sub_71007929E0();
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

// 0x710075e810 (unnamed): whether `pos` is visible from `target`. A ray from `target` to `pos` on the
// ground layers blocks; then two rays from `pos` to `target` on the object layers decide, the one with
// normal checking losing when it hits closer to `target`.
bool CameraEventMove::sub_710075E810(const sead::Vector3f& pos, const sead::Vector3f& target) {
    uking::Unk_71024739d0 ground(ksys::phys::GroundHit::HitAll);
    ground.sub_710090D73C();
    ground.setStart(target);
    ground.setEnd(pos);
    // called through a pointer in the original (not devirtualised)
    if ((&ground)->worldRayCast())
        return true;

    uking::Unk_71024739d0 normal(ksys::phys::GroundHit::HitAll);
    normal.sub_710090D808();
    normal.mQuery.setNormalCheckingMode(ksys::phys::RayCast::NormalCheckingMode::_1);
    normal.setStart(pos);
    normal.setEnd(target);
    // called through a pointer in the original (not devirtualised)
    if (!(&normal)->worldRayCast())
        return false;

    uking::Unk_71024739d0 plain(ksys::phys::GroundHit::HitAll);
    plain.sub_710090D808();
    plain.mQuery.setNormalCheckingMode(ksys::phys::RayCast::NormalCheckingMode::_0);
    plain.setStart(pos);
    plain.setEnd(target);
    // called through a pointer in the original (not devirtualised)
    if (!(&plain)->worldRayCast())
        return true;

    sead::Vector3f plain_hit;
    sead::Vector3f normal_hit;
    plain.getHitPosition(&plain_hit);
    normal.getHitPosition(&normal_hit);
    const f32 plain_distance = (plain_hit - target).squaredLength();
    const f32 normal_distance = (normal_hit - target).squaredLength();
    return normal_distance < plain_distance;
}

// NON_MATCHING: the original peels the first iteration's copy of the polar offset into the loop
// preheader and re-copies only the elevation at the loop head; ours keeps the whole copy at the loop
// head, so the function is 24 bytes shorter. Everything else matches.
bool CameraEventMove::sub_710075E9B4(sead::Vector3f* pos, const sead::Vector3f& target, s32 count) {
    if (count < 0)
        return false;
    if (!sub_710075E810(*pos, target))
        return false;

    sead::Vector3f point = *pos;
    act::Unk_7100922700 dir(*pos - target);
    dir._4 = angleStuff(sub_7100924CAC(dir._4));

    for (s32 i = 0; i < count; ++i) {
        act::Unk_7100922700 polar = dir;
        const f32 sign = s32(sead::GlobalRandom::instance()->getU32()) >= 0 ? 1.0f : -1.0f;
        const f32 angle = f32(i) * sign * 2.5f;

        polar._4 = angleStuff(angle);
        polar._4 = angleStuff(sub_7100924CAC(polar._4));
        point = target + polar.sub_7100923254();
        if (!sub_710075E810(point, target)) {
            *pos = point;
            return false;
        }

        polar._4 = angleStuff(-angle);
        polar._4 = angleStuff(sub_7100924CAC(polar._4));
        point = target + polar.sub_7100923254();
        if (!sub_710075E810(point, target)) {
            *pos = point;
            return false;
        }
    }
    return true;
}

// NON_MATCHING: same loop rotation as sub_710075E9B4 (the polar offset copy is not peeled).
bool CameraEventMove::sub_710075EB98(sead::Vector3f* pos, const sead::Vector3f& target, s32 count) {
    if (count < 0)
        return false;
    if (!sub_710075E810(*pos, target))
        return false;

    sead::Vector3f point = *pos;
    const act::Unk_7100922700 dir(*pos - target);

    for (s32 i = 0; i < count; ++i) {
        act::Unk_7100922700 polar = dir;
        const f32 sign = s32(sead::GlobalRandom::instance()->getU32()) >= 0 ? 1.0f : -1.0f;
        const f32 angle = f32(i) * sign * 2.5f;

        polar._4 = angleStuff(angle);
        point = target + polar.sub_7100923254();
        if (!sub_710075E810(point, target)) {
            *pos = point;
            return false;
        }

        polar._4 = angleStuff(-angle);
        point = target + polar.sub_7100923254();
        if (!sub_710075E810(point, target)) {
            *pos = point;
            return false;
        }
    }
    return true;
}

}  // namespace uking::action
