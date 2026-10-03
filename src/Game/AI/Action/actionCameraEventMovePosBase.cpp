#include "Game/AI/Action/actionCameraEventMovePosBase.h"
#include <math/seadMathCalcCommon.h>
#include <prim/seadDelegate.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

CameraEventMovePosBase::CameraEventMovePosBase(const InitArg& arg) : CameraEvent(arg) {}

// NON_MATCHING: the original checks the message pointer for null (`cbz x1`); clang folds the check
// on a reference.
bool CameraEventMovePosBase::handleMessage_(const ksys::Message* message) {
    if (message == nullptr || message->getType() != 0x8800006)
        return false;

    {
        sead::Delegate1<CameraEventMovePosBase, ksys::act::ActorConstDataAccess*> on_actor(
            this, &CameraEventMovePosBase::sub_710076264C);
        sead::Delegate1<CameraEventMovePosBase, ksys::map::Object*> on_object(
            this, &CameraEventMovePosBase::sub_7100762698);
        sub_71007626AC(_164, mActorName1, mUniqueName1, &_168, &_357, 1, &on_actor, &on_object);
    }
    {
        sead::Delegate1<CameraEventMovePosBase, ksys::act::ActorConstDataAccess*> on_actor(
            this, &CameraEventMovePosBase::sub_710076294C);
        sead::Delegate1<CameraEventMovePosBase, ksys::map::Object*> on_object(
            this, &CameraEventMovePosBase::sub_7100762998);
        sub_71007626AC(_166, mActorName2, mUniqueName2, &_178, &_358, 4, &on_actor, &on_object);
    }
    sub_7100762C2C(&_168, &_188, &_1e8, 2);
    sub_7100762C2C(&_178, &_1b8, &_1f4, 8);
    return true;
}

void CameraEventMovePosBase::m43() {
    _356 = 0;
    _348 = sead::Mathf::clampMin(*mLatShiftRange_d, 0.0f);
    _34c = sead::Mathf::clampMin(*mLngShiftRange_d, 0.0f);
    const s32 ignoring_collision = *mActorIgnoringCollision_d;
    _350 = ignoring_collision >= -1 && ignoring_collision <= 1 ? ignoring_collision : -1;

    const s32 target1 = *mTargetActor1;
    if (target1 >= -1 && target1 <= 3)
        _164 = target1;
    const s32 target2 = *mTargetActor2;
    if (target2 >= -1 && target2 <= 3)
        _166 = target2;

    _168.reset();
    _357 = 2;
    _178.reset();
    _358 = 2;

    const u32 at_append_mode = *mAtAppendMode;
    _359 = at_append_mode < 4 ? at_append_mode : 1;
    const u32 pos_append_mode = *mPosAppendMode;
    _35a = pos_append_mode < 4 ? pos_append_mode : 1;
    if (_359 == 2) {
        if (_164 == -1)
            _359 = 1;
    } else if (_359 == 3) {
        if (_166 == -1)
            _359 = 1;
    }
    if (_35a == 2) {
        if (_164 == -1)
            _35a = 1;
    } else if (_35a == 3) {
        if (_166 == -1)
            _35a = 1;
    }

    const u32 fovy_append_mode = *mFovyAppendMode;
    if (fovy_append_mode < 2)
        _35b = fovy_append_mode;
    else
        _35b = 1;
    const u32 base_mode = *mBaseMode;
    _35c = base_mode < 2 ? base_mode : 0;
    const u32 motion_mode = *mMotionMode;
    _35d = motion_mode < 2 ? motion_mode : 0;
    const u32 revise_mode_end = *mReviseModeEnd_d;
    _200 = 0;
    _35f = revise_mode_end < 3 ? revise_mode_end : 1;

    _208.sub_710079C384(*mCount, 0.0f);
    _228 = _22c = sub_7100924D80(*mCushion);
    _354 = 0;

    if (!m48()) {
        {
            sead::Delegate1<CameraEventMovePosBase, ksys::act::ActorConstDataAccess*> on_actor(
                this, &CameraEventMovePosBase::sub_710076264C);
            sead::Delegate1<CameraEventMovePosBase, ksys::map::Object*> on_object(
                this, &CameraEventMovePosBase::sub_7100762698);
            sub_71007626AC(_164, mActorName1, mUniqueName1, &_168, &_357, 1, &on_actor,
                           &on_object);
        }
        {
            sead::Delegate1<CameraEventMovePosBase, ksys::act::ActorConstDataAccess*> on_actor(
                this, &CameraEventMovePosBase::sub_710076294C);
            sead::Delegate1<CameraEventMovePosBase, ksys::map::Object*> on_object(
                this, &CameraEventMovePosBase::sub_7100762998);
            sub_71007626AC(_166, mActorName2, mUniqueName2, &_178, &_358, 4, &on_actor,
                           &on_object);
        }
        sub_7100762C2C(&_168, &_188, &_1e8, 2);
        sub_7100762C2C(&_178, &_1b8, &_1f4, 8);
    }

    auto* camera = getCamera();
    if ((_348 != 0.0f || _34c != 0.0f) && _164 == -1 && _166 == -1) {
        sead::FixedSafeString<128> flow;
        sead::FixedSafeString<128> entry;
        getActiveEventFlowPath_0(camera, &flow, &entry);
        sead::FixedSafeString<128> path;
        getActiveEventFlowPath(camera, &path);
    }

    if (!camera)
        return;

    auto& data = camera->_860;
    data._0 = data._38 = data._70 = data._a8 = data._e0;
    _4c = data._0;
    sub_7100760DF8();
    if (*mCount <= 0.0f)
        camera->sub_71007929E0();
}

// NON_MATCHING: stack slot order (the original's delegates are allocated below `prev`, as if they came
// from an inlined helper), the second target-ready check is evaluated without branches in the
// original, and float register allocation.
void CameraEventMovePosBase::m44() {
    auto* camera = getCamera();
    if (!camera)
        return;

    auto& state = camera->_860._0;
    const act::Unk_71009214b8 prev = state;

    if (m48()) {
        const bool found1 = sub_71007624A8(_164, &_168, &_188, &_1e8, &_357, 1, 2);
        const bool found2 = sub_71007624A8(_166, &_178, &_1b8, &_1f4, &_358, 4, 8);
        if ((found1 || found2) && mActor) {
            sendMessage(*mActor->getMesTransceiverId(), ksys::MessageType(0x8800006), nullptr);
        }
    } else {
        {
            sead::Delegate1<CameraEventMovePosBase, ksys::act::ActorConstDataAccess*> on_actor(
                this, &CameraEventMovePosBase::sub_710076264C);
            sead::Delegate1<CameraEventMovePosBase, ksys::map::Object*> on_object(
                this, &CameraEventMovePosBase::sub_7100762698);
            sub_71007626AC(_164, mActorName1, mUniqueName1, &_168, &_357, 1, &on_actor,
                           &on_object);
        }
        {
            sead::Delegate1<CameraEventMovePosBase, ksys::act::ActorConstDataAccess*> on_actor(
                this, &CameraEventMovePosBase::sub_710076294C);
            sead::Delegate1<CameraEventMovePosBase, ksys::map::Object*> on_object(
                this, &CameraEventMovePosBase::sub_7100762998);
            sub_71007626AC(_166, mActorName2, mUniqueName2, &_178, &_358, 4, &on_actor,
                           &on_object);
        }
        sub_7100762C2C(&_168, &_188, &_1e8, 2);
        sub_7100762C2C(&_178, &_1b8, &_1f4, 8);
    }

    sub_7100761338();

    if (!(*mStartCalcOnly && (_356 & 0x20)) && !(_164 != -1 && (~_356 & 3) != 0)) {
        if ((_356 & 0x10) && !(_166 != -1 && (~_356 & 0xc) != 0)) {
            sub_7100762D14(&_bc, &_f4);
            _356 |= 0x20;
        }
    }

    if (auto* cam = getCamera())
        _12c = cam->_860._0;

    if (_356 & 0x20) {
        ksys::Timer::update(&_200, 1.0f);
        if (*mCount <= _200)
            setFinished();

        _208.sub_710079C408();
        _228 = _22c + (1.0f - _22c) * _208._18;
        if (_208._18 < 1.0f) {
            if (_35d == 1)
                sub_710076353C(&state);
            else
                sub_71007633A4(&state);

            if (*mCollisionInterpolateSkip && sub_7100761F84(prev, &state)) {
                _200 = sead::Mathf::max(sead::Mathf::clampMin(*mCount, 0.0f), _200);
                _208.sub_710079C510(1.0f);
                camera->sub_71007929E0();
            }
        }
        if (_208._18 >= 1.0f) {
            if (_35d == 1)
                sub_710076353C(&state);
            else
                sub_71007633A4(&state);
        }
    }

    sub_710076203C();
    sub_7100762144();
}

// NON_MATCHING: the original computes the _7c0 link address before selecting the source link (C++14
// operand order of the overloaded BaseProcLink assignment) and tail-calls the assignment.
void CameraEventMovePosBase::sub_710076203C() {
    if (*mCollisionInterpolateSkip && !(_208._18 >= 1.0f)) {
        if (auto* camera = getCamera())
            camera->_860._818 = 2;
        return;
    }

    const u8 revise_mode_end = _35f;
    if (auto* camera = getCamera()) {
        camera->_860._818 = 0;
        switch (revise_mode_end) {
        case 2:
            camera->_860._818 = 1;
            break;
        case 0:
            camera->_860._818 = 2;
            break;
        }
    }

    auto* camera = getCamera();
    if (!camera)
        return;

    ksys::act::BaseProcLink* link = nullptr;
    if (_350 == 0)
        link = &_168;
    else if (_350 == 1)
        link = &_178;
    if (!link || !link->hasProc())
        link = &ksys::act::sUnk_71026505e0;
    camera->_860._7c0[camera->_860._81a] = *link;
}

void CameraEventMovePosBase::sub_7100762144() {
    if ((_164 != -1 && (~_356 & 3) != 0) || (_166 != -1 && (~_356 & 0xc) != 0)) {
        const s32 max = sub_7100922088();
        if (_354 < max) {
            if (max <= ++_354) {
                sead::FixedSafeString<256> message;
                sub_71007629AC(&message);
                setFailed();
            }
        }
    }
}

void CameraEventMovePosBase::m46() {
    getDynamicParam_2(&mReviseModeEnd_d, "ReviseModeEnd");
    getDynamicParam_2(&mLatShiftRange_d, "LatShiftRange");
    getDynamicParam_2(&mLngShiftRange_d, "LngShiftRange");
    getDynamicParam_2(&mActorIgnoringCollision_d, "ActorIgnoringCollision");
}

bool CameraEventMovePosBase::sub_71007624A8(s16 target, ksys::act::BaseProcLink* link,
                                            sead::Matrix34f* mtx, sead::Vector3f* pos, u8* state,
                                            u8 link_flag, u8 mtx_flag) {
    if (target == -1)
        return false;

    if (target == 1) {
        *state = 0;
        if (!(_356 & link_flag)) {
            ksys::act::ActorConstDataAccess accessor;
            sub_7100924BE4(&accessor);
            accessor.linkAcquire(link);
            if (link->hasProc())
                _356 |= link_flag;
        }

        if (link->hasProc() && (!(_356 & mtx_flag) || !*mStartCalcOnly)) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(link, &accessor);
            const auto& actor_mtx = accessor.getActorMtx();
            if (!ksys::util::sub_71011F10F4(actor_mtx)) {
                sead::Vector3f actor_pos = sead::Vector3f::zero;
                if (sub_7100926210(accessor, &actor_pos)) {
                    *mtx = actor_mtx;
                    *pos = actor_pos;
                    _356 |= mtx_flag;
                }
            }
        }
        return false;
    }

    if (_356 & mtx_flag)
        return !*mStartCalcOnly;
    return true;
}

void CameraEventMovePosBase::sub_710076264C(ksys::act::ActorConstDataAccess* accessor) {
    if (!accessor)
        return;
    accessor->linkAcquire(&_168);
    if (_168.hasProc()) {
        _357 = 0;
        _356 |= 1;
    }
}

void CameraEventMovePosBase::sub_7100762698(ksys::map::Object* object) {
    sub_7100762AB8(object, &_188, &_357, 1, 2);
}

void CameraEventMovePosBase::sub_710076294C(ksys::act::ActorConstDataAccess* accessor) {
    if (!accessor)
        return;
    accessor->linkAcquire(&_178);
    if (_178.hasProc()) {
        _358 = 0;
        _356 |= 4;
    }
}

void CameraEventMovePosBase::sub_7100762998(ksys::map::Object* object) {
    sub_7100762AB8(object, &_1b8, &_358, 4, 8);
}

void CameraEventMovePosBase::sub_71007629AC(sead::BufferedSafeString* message) {
    auto* camera = getCameraActor();
    if (!camera)
        return;

    sead::FixedSafeString<128> flow;
    sead::FixedSafeString<128> entry;
    getActiveEventFlowPath_0(camera, &flow, &entry);
    message->appendWithFormat("%s<%s>で相対アクタが見つからなかったことに由来するエラー", flow.cstr(),
                              entry.cstr());
}

void CameraEventMovePosBase::sub_7100762AB8(ksys::map::Object* object, sead::Matrix34f* mtx,
                                            u8* state, u8 flag1, u8 flag2) {
    if (!object)
        return;

    const sead::Vector3f rotate = object->getRotate();
    const sead::Vector3f translate = object->getTranslate();
    sead::Matrix34f object_mtx;
    object_mtx.makeRT(rotate, translate);
    if (ksys::util::sub_71011F10F4(object_mtx))
        return;

    *mtx = object_mtx;
    *state = 1;
    _356 = _356 | flag1 | flag2;
}

void CameraEventMovePosBase::sub_7100762C2C(ksys::act::BaseProcLink* link, sead::Matrix34f* mtx,
                                            sead::Vector3f* pos, u8 flag) {
    if (!link->hasProc())
        return;

    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    const auto& actor_mtx = accessor.getActorMtx();
    if (ksys::util::sub_71011F10F4(actor_mtx))
        return;

    sead::Vector3f actor_pos = sead::Vector3f::zero;
    if (sub_7100926210(accessor, &actor_pos)) {
        *mtx = actor_mtx;
        *pos = actor_pos;
        _356 |= flag;
    }
}

// NON_MATCHING: the original checks _35b once after both switches; ours duplicates the check
void CameraEventMovePosBase::sub_7100762D14(act::Unk_71009214b8* from, act::Unk_71009214b8* to) {
    switch (_359) {
    case 0:
        to->_c = _84._c + from->_c;
        break;
    case 1:
        to->_c = from->_c;
        break;
    case 2:
        to->_c = from->_c;
        to->_c.setMul(_188, to->_c);
        break;
    case 3:
        to->_c = from->_c;
        to->_c.setMul(_1b8, to->_c);
        break;
    }

    switch (_35a) {
    case 0:
        to->_0 = _84._0 + from->_0;
        break;
    case 1:
        to->_0 = from->_0;
        break;
    case 2:
        to->_0 = from->_0;
        to->_0.setMul(_188, to->_0);
        break;
    case 3:
        to->_0 = from->_0;
        to->_0.setMul(_1b8, to->_0);
        break;
    }

    switch (_35b) {
    case 1:
        to->_24 = from->_24;
        break;
    case 0:
        to->_24 = _84._24 + from->_24;
        break;
    }

    to->_30 = sub_7100922058();
    if (auto* camera = getCameraActor())
        to->_30 = camera->_860.sub_710079ADA0();
    to->_34 = sub_7100922064();
    to->_28 = 0;
}

// NON_MATCHING: the original keeps &_188 / &_1b8 in registers; _35b check as in sub_7100762D14
void CameraEventMovePosBase::sub_71007630E8(act::Unk_71009214b8* from, act::Unk_71009214b8* to) {
    switch (_359) {
    case 0:
        to->_c = from->_c - _84._c;
        break;
    case 1:
        to->_c = from->_c;
        break;
    case 2: {
        sead::Matrix34f mtx = _188;
        mtx.invert();
        to->_c = from->_c;
        to->_c.setMul(mtx, to->_c);
        break;
    }
    case 3: {
        sead::Matrix34f mtx = _1b8;
        mtx.invert();
        to->_c = from->_c;
        to->_c.setMul(mtx, to->_c);
        break;
    }
    }

    switch (_35a) {
    case 0:
        to->_0 = from->_0 - _84._0;
        break;
    case 1:
        to->_0 = from->_0;
        break;
    case 2: {
        sead::Matrix34f mtx = _188;
        mtx.invert();
        to->_0 = from->_0;
        to->_0.setMul(mtx, to->_0);
        break;
    }
    case 3: {
        sead::Matrix34f mtx = _1b8;
        mtx.invert();
        to->_0 = from->_0;
        to->_0.setMul(mtx, to->_0);
        break;
    }
    }

    switch (_35b) {
    case 1:
        to->_24 = from->_24;
        break;
    case 0:
        to->_24 = from->_24 - _84._24;
        break;
    }
}

bool CameraEventMovePosBase::sub_7100761F84(const act::Unk_71009214b8& prev,
                                            act::Unk_71009214b8* state) {
    ksys::act::BaseProcLink* link = nullptr;
    if (_350 == 0)
        link = &_168;
    else if (_350 == 1)
        link = &_178;
    if (!link || !link->hasProc())
        link = &ksys::act::sUnk_71026505e0;

    ksys::phys::SystemGroupHandler* handler = nullptr;
    if (link->hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(link, &accessor);
        handler = accessor.x(0);
    }
    return sub_7100925654(state, prev, handler);
}

// NON_MATCHING: load order of the first angle difference
void CameraEventMovePosBase::sub_71007633A4(act::Unk_71009214b8* state) {
    const act::Unk_7100922700 to(_f4._0 - _f4._c);
    act::Unk_7100922700 polar(_4c._0 - _4c._c);
    polar._0 += (to._0 - polar._0) * _208._18;
    polar._4 = angleStuff(angleStuff(angleStuff(to._4 - polar._4) * _208._18) + polar._4);
    polar._8 = angleStuff(angleStuff(angleStuff(to._8 - polar._8) * _208._18) + polar._8);
    state->_c = _4c._c + (_f4._c - _4c._c) * _208._18;
    state->_0 = state->_c + polar.sub_7100923254();
    state->_24 = _4c._24 + (_f4._24 - _4c._24) * _208._18;
    state->_28 = _4c._28 + (_f4._28 - _4c._28) * _208._18;
}

// NON_MATCHING: load order of the first angle difference
void CameraEventMovePosBase::sub_710076353C(act::Unk_71009214b8* state) {
    const act::Unk_7100922700 to(_f4._c - _f4._0);
    act::Unk_7100922700 polar(_4c._c - _4c._0);
    polar._0 += (to._0 - polar._0) * _208._18;
    polar._4 = angleStuff(angleStuff(angleStuff(to._4 - polar._4) * _208._18) + polar._4);
    polar._8 = angleStuff(angleStuff(angleStuff(to._8 - polar._8) * _208._18) + polar._8);
    state->_0 = _4c._0 + (_f4._0 - _4c._0) * _208._18;
    state->_c = state->_0 + polar.sub_7100923254();
    state->_24 = _4c._24 + (_f4._24 - _4c._24) * _208._18;
    state->_28 = _4c._28 + (_f4._28 - _4c._28) * _208._18;
}

float CameraEventMovePosBase::m47(const Pattern& pattern) {
    return 0.0f;
}

bool CameraEventMovePosBase::m48() {
    return true;
}

}  // namespace uking::action
