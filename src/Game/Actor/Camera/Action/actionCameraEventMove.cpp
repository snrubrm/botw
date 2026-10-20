#include <algorithm>
#include "Game/Actor/Camera/Action/actionCameraEventMove.h"
#include <random/seadGlobalRandom.h>
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/gameUnk_71024739d0.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actBaseProcAccessor.h"
#include "KingSystem/Event/evtEventSystem.h"
#include "KingSystem/Event/evtUnk_7100dc816c.h"
#include "KingSystem/System/Timer.h"

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

// NON_MATCHING: everything matches except the camera view-mode block after the two position updates.
// The original loads _2a5 / _2a4 before the getCamera() call and tests the mode against 2 before 0;
// ours loads the mode after the call and tests 0 first (the same stores and the same result).
// NON_MATCHING: the body matches instruction for instruction, but the compiler keeps four fewer
// float values live than the original (d8-d11 instead of d8-d15), so the frame is 0x50 instead of
// 0x70 and the register names in the whole function differ. The elevation guard also compares z
// before x and y in the original.
void CameraEventMove::sub_710075DCC4() {
    if (*mStartCalcOnly_d && (_2a1 & 2))
        return;

    if (mActor)
        sendMessage(*mActor->getMesTransceiverId(), ksys::MessageType(0x8800006), nullptr);

    if (!(_2a0 & 1))
        return;

    const s32 axis = _1b4;
    const sead::Vector3f dir(_184.m[0][axis] * _1b8, _184.m[1][axis] * _1b8,
                             _184.m[2][axis] * _1b8);

    f32 elevation = 0.0f;
    if (dir.x != 0.0f || dir.y != 0.0f || dir.z != 0.0f) {
        const f32 xz = std::sqrt(dir.x * dir.x + dir.z * dir.z);
        elevation = sub_7100924CAC(std::atan2(dir.y, xz) * (180.0f / sead::Mathf::pi()));
    }

    f32 azimuth = 0.0f;
    if (*mUseImaginaryLineAngle_d) {
        const sead::Vector3f delta = _148.getTranslation() - _118.getTranslation();
        if (delta.x != 0.0f || delta.z != 0.0f)
            azimuth = std::atan2(delta.x, delta.z) * (180.0f / sead::Mathf::pi());
    } else if (dir.x != 0.0f || dir.z != 0.0f) {
        azimuth = std::atan2(dir.x, dir.z) * (180.0f / sead::Mathf::pi());
    }

    act::Unk_7100922700 polar(std::max(*mRadius_s, 0.01f), elevation, azimuth);

    _84._c = _178;
    _84._c.y = _178.y + mOffset_d->y;

    const sead::Vector3f vector = polar.sub_7100923254();

    f32 lat;
    if (_2a2 != 0) {
        const f32 value = sead::Mathf::abs(mOffset_d->x);
        lat = _2a2 == 1 ? value : -value;
    } else {
        lat = mOffset_d->x * (*mLngReverse_d ? -1.0f : 1.0f);
    }

    sead::Vector3f side(vector.z, 0.0f, -vector.x);
    const f32 side_len = std::sqrt(vector.x * vector.x + vector.z * vector.z);
    if (side_len > 0.0f)
        side *= lat / side_len;
    _84._c += side;

    sead::Vector3f forward(vector.x, 0.0f, vector.z);
    const f32 forward_len = std::sqrt(vector.x * vector.x + vector.z * vector.z);
    if (forward_len > 0.0f)
        forward *= mOffset_d->z / forward_len;
    _84._c += forward;

    polar._4 = angleStuff(_1c8._4 + polar._4);
    polar._8 = angleStuff(_1c8._8 + polar._8);
    polar._4 = angleStuff(sub_7100924CAC(polar._4));

    _84._0 = _84._c + polar.sub_7100923254();
    _2a1 |= 2;
}

// 0x710075d6d8 (placeholder name): the first orbit update, run at the start of m44. It builds the
// orbit polar from the front-bone axis (or the camera state for the imaginary line), decides the near
// side, then searches the 2.5 degree ring around the look-at point for a visible two-step orbit.
// NON_MATCHING: the same body, but clang keeps the radius and the elevation in registers instead of
// the two stack spills the original has, so every local slot is 0x10 higher and the register names
// differ throughout. The near-side check, the two offset additions and the four ring searches match
// instruction for instruction.
void CameraEventMove::sub_710075D6D8() {
    if (_2a1 & 1)
        return;
    if (!(_2a0 & 1))
        return;

    const s32 axis = _1b4;
    const sead::Vector3f dir(_184.m[0][axis] * _1b8, _184.m[1][axis] * _1b8,
                             _184.m[2][axis] * _1b8);

    f32 elevation = 0.0f;
    if (dir.x != 0.0f || dir.y != 0.0f || dir.z != 0.0f) {
        const f32 xz = std::sqrt(dir.x * dir.x + dir.z * dir.z);
        elevation = sub_7100924CAC(std::atan2(dir.y, xz) * (180.0f / sead::Mathf::pi()));
    }

    f32 azimuth = 0.0f;
    if (*mUseImaginaryLineAngle_d) {
        const sead::Vector3f delta = _148.getTranslation() - _118.getTranslation();
        if (delta.x != 0.0f || delta.z != 0.0f)
            azimuth = std::atan2(delta.x, delta.z) * (180.0f / sead::Mathf::pi());
    } else if (dir.x != 0.0f || dir.z != 0.0f) {
        azimuth = std::atan2(dir.x, dir.z) * (180.0f / sead::Mathf::pi());
    }

    const sead::Vector3f side(dir.z, 0.0f, -dir.x);

    if (*mNearSide_d) {
        if (auto* camera = getCamera()) {
            const sead::Vector3f delta(camera->_860._0._0.x - _178.x, 0.0f,
                                       camera->_860._0._0.z - _178.z);
            _2a2 = side.dot(delta) > 0.0f ? 1 : 2;
        } else {
            _2a2 = 0;
        }
    } else {
        _2a2 = 0;
    }

    const f32 radius = std::max(*mRadius_s, 0.01f);
    const act::Unk_7100922700 base(radius, elevation, azimuth);

    sead::Vector3f point = _178;
    point.y = _178.y + mOffset_d->y;

    const sead::Vector3f vector = base.sub_7100923254();

    f32 lat;
    if (_2a2 != 0) {
        const f32 value = mOffset_d->x > 0.0f ? mOffset_d->x : -mOffset_d->x;
        lat = _2a2 == 1 ? value : -value;
    } else {
        lat = (*mLngReverse_d ? -1.0f : 1.0f) * mOffset_d->x;
    }

    sead::Vector3f side_offset(vector.z, 0.0f, -vector.x);
    const f32 side_len = std::sqrt(vector.x * vector.x + vector.z * vector.z);
    if (side_len > 0.0f)
        side_offset *= lat / side_len;
    point += side_offset;

    sead::Vector3f forward(vector.x, 0.0f, vector.z);
    const f32 forward_len = std::sqrt(vector.x * vector.x + vector.z * vector.z);
    if (forward_len > 0.0f)
        forward *= mOffset_d->z / forward_len;
    point += forward;

    f32 lat_angle;
    if (_2a2 != 0) {
        const f32 value = *mLat_d > 0.0f ? *mLat_d : -*mLat_d;
        lat_angle = _2a2 == 1 ? value : -value;
    } else {
        lat_angle = (*mLatReverse_d ? -1.0f : 1.0f) * *mLat_d;
    }

    f32 lng_angle;
    if (_2a2 != 0) {
        const f32 value = *mLng_d > 0.0f ? *mLng_d : -*mLng_d;
        lng_angle = _2a2 == 1 ? value : -value;
    } else {
        lng_angle = (*mLngReverse_d ? -1.0f : 1.0f) * *mLng_d;
    }

    const act::Unk_7100922700 adjusted(radius, sub_7100924CAC(elevation + lat_angle),
                                       azimuth + lng_angle);
    sead::Vector3f candidate = point + adjusted.sub_7100923254();

    if (sub_710075E810(candidate, point)) {
        for (s32 i = 0; i < 2; ++i) {
            const f32 sign1 =
                s32(sead::GlobalRandom::instance()->getU32()) >= 0 ? 1.0f : -1.0f;
            const f32 step1 = f32(i + 1) * sign1 * 2.5f;

            act::Unk_7100922700 polar = base;
            polar._8 = angleStuff(polar._8 + step1);
            candidate = point + polar.sub_7100923254();
            if (!sub_710075E9B4(&candidate, point, i + 1))
                break;

            polar = base;
            polar._8 = angleStuff(polar._8 - step1);
            candidate = point + polar.sub_7100923254();
            if (!sub_710075E9B4(&candidate, point, i + 1))
                break;

            const f32 sign2 =
                s32(sead::GlobalRandom::instance()->getU32()) >= 0 ? 1.0f : -1.0f;
            const f32 step2 = f32(i + 1) * sign2 * 2.5f;

            polar = base;
            polar._4 = angleStuff(polar._4 + step2);
            polar._4 = angleStuff(sub_7100924CAC(polar._4));
            candidate = point + polar.sub_7100923254();
            if (!sub_710075EB98(&candidate, point, i))
                break;

            polar = base;
            polar._4 = angleStuff(polar._4 - step2);
            polar._4 = angleStuff(sub_7100924CAC(polar._4));
            candidate = point + polar.sub_7100923254();
            if (!sub_710075EB98(&candidate, point, i))
                break;
        }
    }

    _1c8._0 = radius;
    _1c8._4 = angleStuff(adjusted._4 - base._4);
    _1c8._8 = angleStuff(adjusted._8 - base._8);
    _2a1 |= 1;
}

void CameraEventMove::m44() {
    auto* camera = getCamera();
    if (!camera)
        return;

    camera->sub_71007953C8();

    if (*mCancelDrawOther_d) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_108, &accessor);
        sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x3000001), nullptr);
    }

    sub_710075D6D8();
    sub_710075DCC4();

    if (_2a1 & 2) {
        ksys::Timer::update(&_1d4, 1.0f);
        if (*mCount_d <= _1d4)
            setFinished();
        _1d8.sub_710079C408();
        _bc = camera->_860._0;
        sub_710075E014();
        if (*mCollisionInterpolateSkip_s) {
            if (auto* camera_actor = getCameraActor()) {
                if (sub_7100925654(&camera_actor->_860._0, _bc, nullptr)) {
                    _1d8.sub_710079C510(1.0f);
                    sub_710075E014();
                    setFinished();
                }
            }
        }
    }

    if (isFinishedOrFailed()) {
        if (auto* cam = getCamera()) {
            cam->_860._818 = 0;
            if (_2a5 == 2)
                cam->_860._818 = 1;
            else if (_2a5 == 0)
                cam->_860._818 = 2;
        }
    } else {
        if (auto* cam = getCamera()) {
            cam->_860._818 = 0;
            if (_2a4 == 2)
                cam->_860._818 = 1;
            else if (_2a4 == 0)
                cam->_860._818 = 2;
        }
    }

    _2a0 = 0;
    auto* link = *mPlayerRelative_d != 0 ? &_108 : &_f8;
    if (!link->hasProc())
        return;

    camera->_860._7c0[camera->_860._81a] = *link;
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
