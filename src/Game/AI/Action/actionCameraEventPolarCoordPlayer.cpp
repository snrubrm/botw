#include "Game/AI/Action/actionCameraEventPolarCoordPlayer.h"
#include <prim/seadDelegate.h>
#include "Game/Actor/actCameraUtil.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Event/evtEventSystem.h"
#include "KingSystem/Event/evtUnk_7100dc816c.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

CameraEventPolarCoordPlayer::CameraEventPolarCoordPlayer(const InitArg& arg)
    : CameraEventPolarCoord(arg), _100(), _10c(), _118(), _148(), _1d8() {}

void CameraEventPolarCoordPlayer::m47() {
    for (int i = 0; i < 3; ++i) {
        const int kind = m62(i);
        _94[i] = kind >= -1 && kind <= 3 ? kind : -1;
    }

    for (int i = 0; i < 3; ++i) {
        _10c[i] = _100[i] = _94[i] != -1;
        _118[i].reset();
    }
}

bool CameraEventPolarCoordPlayer::m48() {
    sub_7100768208();
    if (_10c[0] == 1)
        return false;
    if (_10c[1] == 1)
        return false;
    return _10c[2] != 1;
}

void CameraEventPolarCoordPlayer::m49() {
    sub_71007685C0(0);
    sub_71007685C0(1);
    sub_71007685C0(2);
}

// NON_MATCHING: regalloc (w8/w9 swapped in the second and third iterations)
void CameraEventPolarCoordPlayer::sub_7100768208() {
    for (int i = 0; i < 3; ++i) {
        if (_10c[i] == 0)
            continue;

        if (_100[i] == 2 && _10c[i] == 1 && !_118[i].hasProc())
            _100[i] = 1;

        if (_100[i] == 1) {
            sub_7100768474(i);
            if (_100[i] == 1)
                continue;
        }

        sub_71007685C0(i);
    }
}

// NON_MATCHING: the compiler shares the link assignment between reference kinds 0 and 2.
void CameraEventPolarCoordPlayer::sub_7100768474(int idx) {
    switch (_94[idx]) {
    case 0:
        _118[idx] = ksys::evt::sub_7100DC85D4(mActor);
        break;
    case 1: {
        ksys::act::ActorConstDataAccess accessor;
        sub_7100924BE4(&accessor);
        accessor.linkAcquire(&_118[idx]);
        break;
    }
    case 2:
        if (auto* event = ksys::evt::EventSystem::instance())
            _118[idx] = event->mSpeaker.mLink;
        break;
    case 3: {
        _1d8 = idx;
        sead::Delegate1<CameraEventPolarCoordPlayer, ksys::act::ActorConstDataAccess*> on_actor(
            this, &CameraEventPolarCoordPlayer::sub_71007686A8);
        sead::Delegate1<CameraEventPolarCoordPlayer, ksys::map::Object*> on_object(
            this, &CameraEventPolarCoordPlayer::sub_71007686D8);
        act::sub_71009248D4(mActor, _a0[idx], _d0[idx], &on_actor, &on_object);
        break;
    }
    }
    if (_118[idx].hasProc())
        _100[idx] = 2;
}

void CameraEventPolarCoordPlayer::m56(act::Unk_7100922700* out) {
    sead::Vector3f from = sead::Vector3f::zero;
    sead::Vector3f to = sead::Vector3f::zero;
    m60(&from);
    m61(&to);
    out->set(to - from);
}

const ksys::act::BaseProcLink* CameraEventPolarCoordPlayer::m59() {
    const int idx = m63();
    if (u32(idx) < 3)
        return &_118[idx];
    return &ksys::act::sUnk_71026505e0;
}

void CameraEventPolarCoordPlayer::sub_71007685C0(int idx) {
    if (_10c[idx] == 2 && !m64())
        return;
    if (_100[idx] != 2 || !_118[idx].hasProc())
        return;

    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&_118[idx], &accessor);
    const auto& mtx = accessor.getActorMtx();
    if (!ksys::util::sub_71011F10F4(mtx)) {
        _148[idx] = mtx;
        _10c[idx] = 2;
    }
}

void CameraEventPolarCoordPlayer::sub_71007686A8(ksys::act::ActorConstDataAccess* accessor) {
    if (accessor && accessor->hasProc())
        accessor->linkAcquire(&_118[_1d8]);
}

void CameraEventPolarCoordPlayer::sub_71007686D8(ksys::map::Object* object) {
    if (!object)
        return;

    const sead::Vector3f rotate = object->getRotate();
    const sead::Vector3f translate = object->getTranslate();
    sead::Matrix34f mtx;
    mtx.makeRT(rotate, translate);
    if (ksys::util::sub_71011F10F4(mtx))
        return;

    _148[_1d8] = mtx;
    _100[_1d8] = 3;
    _10c[_1d8] = 2;
}

void CameraEventPolarCoordPlayer::m60(sead::Vector3f* out) {}

void CameraEventPolarCoordPlayer::m61(sead::Vector3f* out) {}

int CameraEventPolarCoordPlayer::m62(int idx) {
    return -1;
}

int CameraEventPolarCoordPlayer::m63() {
    return -1;
}

bool CameraEventPolarCoordPlayer::m64() {
    return false;
}

}  // namespace uking::action
