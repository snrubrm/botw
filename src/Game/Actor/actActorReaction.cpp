#include "Game/Actor/actActorReaction.h"
#include <basis/seadNew.h>
#include "KingSystem/ActorSystem/actActorUnk6b8.h"
#include <math/seadMathCalcCommon.h>
#include <xlink2/xlink2Locator.h>
#include <xlink2/xlink2UserInstanceSLink.h>
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/ActorSystem/actReaction.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include <xlink2/xlink2UserInstanceELink.h>
#include "KingSystem/XLink/xlinkXLink.h"
#include "Game/Actor/aiXlinkHandle.h"
#include "KingSystem/Sound/sndSound.h"
#include <hostio/seadHostIOCurve.h>

namespace uking::act {

ActorReaction::ActorReaction(const CreateArg& arg) : Actor(arg) {
    _1c0 = 2;
    getJobHandler(ksys::act::JobType::PreCalc) = nullptr;
    getJobHandler(ksys::act::JobType::Calc1) = nullptr;
    getJobHandler(ksys::act::JobType::Calc2) = nullptr;
}

ActorReaction::~ActorReaction() = default;

ksys::act::BaseProc* ActorReaction::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) ActorReaction(arg);
}

}  // namespace uking::act

Unk_71024efd58::Unk_71024efd58(const InitArg& arg) : _8(arg.actor), _10(arg._8) {}

Unk_71024efd58::~Unk_71024efd58() = default;

namespace ksys::act {

void ActorUnk6b8::sub_7100EBBCB8(bool fixed) {
    if (fixed) {
        _88 |= 0x4000;
        _8e = 3;
    } else {
        _88 &= ~0x4000;
    }
}

void ActorUnk6b8::sub_7100EBBCE4(bool on) {
    _88 = on ? (_88 | 0x100) : (_88 & ~0x100);
}

// NON_MATCHING: the original calls the base constructor 0x7100ebf8a0 (ours inlines it; it is defined above) and
// stores _84 before _7c.
ActorUnk6b8::ActorUnk6b8(const InitArg& arg) : Unk_71024efd58(arg) {
    if (auto* xlink = _8->getXLink()) {
        if (auto* user = xlink->_48) {
            xlink2::Locator locator;
            user->searchAsset(&locator, "ReactionEffect");
            if (locator.getAssetCallTable())
                _88 |= 0x800;
        }
    }
    _88 |= 2;
    if (_8->getName().findIndex("Tree") != -1 && _8->getName().findIndex("Trunk") != -1)
        _88 |= 4;
    if (_8->getName().findIndex("_Trunk") != -1)
        _88 |= 0x200;
    _7c = 0;
    _80 = 0;
    _84 = 0;
    _8a |= 3;
}

// Keep the native vptr store, following GameDataFlagSelector (upstream commit 96101229).
ActorUnk6b8::~ActorUnk6b8() { ; }

// NON_MATCHING: the _8e decrement is cmp / b.le / sub in the original (ours: subs / b.lt like the other
// counters), and the fade target address is kept in a register.
void ActorUnk6b8::m5() {
    if (BaseProcMgr::instance()->getMode() != BaseProcMgr::Mode::_0)
        return;
    auto* body = _8->getPhysicsMainBody();
    if (!body)
        return;

    auto* reaction = Reaction::instance()->_a8;
    const f32 rate = reaction ? reaction->sub_7100EC877C() : 0.0f;
    if (!(_88 & 0x4000)) {
        if (_74 > 0.0f) {
            _74 *= rate;
            if (_74 <= sead::Mathf::epsilon())
                _74 = 0.0f;
        }
        _7c = (_7c & 3) != 0 ? _7c - 1 : 0;
        _80 = (_80 & 3) != 0 ? _80 - 1 : 0;
        _84 = (_84 & 3) != 0 ? _84 - 1 : 0;
        if (_8e > 0)
            --_8e;
        if (_8c > 0)
            --_8c;
        if (_90 > 0)
            --_90;
        if (_8f > 0)
            --_8f;
        if (_8b > 0)
            --_8b;
        _4c = _40;
        body->getLinearVelocity(&_40);
    }

    if (_8d > 0 && --_8d <= 0) {
        _20.fade(reaction ? reaction->sub_7100EC87A4() : 0);
        _58 = phys::MaterialMask();
    }

    if (_8->getLife() && *_8->getLife() <= 0 && !_8->sub_71011CEA90())
        _20.fade(-1);

    if (_8->sub_71011CEA90()) {
        if (!(_88 & 0x400)) {
            if (reaction)
                _8c = reaction->sub_7100EC89BC();
            _88 |= 0x400;
        }
    } else {
        _88 &= ~0x400;
    }
    _88 &= 0xef07;

    if (auto* xlink = _8->getXLink()) {
        if (auto* user = xlink->_50) {
            if (xlink->_cc.isOnBit(1))
                user->setPropertyValue(0x18, _88 >> 8 & 1);
            if (xlink->_cc.isOnBit(22)) {
                user->setPropertyValue(0x19, _a0 / 30.0f);
                user->setPropertyValue(0x1a, _a4 / 30.0f);
            }
        }
    }
    _88 &= ~0x100;
    _a0 = 0.0f;
    _a4 = 0.0f;
    ++_7a;
}

void ActorUnk6b8::m8() {}

void ActorUnk6b8::m9() {
    _20.fade(-1);
    _8d = 0;
}

void ActorUnk6b8::m10() {
    const u16 flags = _88;
    _88 = flags | 0x2000;
    if (flags & 1)
        _20.fade(-1);
}

void ActorUnk6b8::SoundHandles::fade(s32 frame) {
    _0.fade(frame);
    _10.fade(frame);
}

}  // namespace ksys::act

namespace ksys::act {

// The speed curves that scale the pitch and volume of a reaction event. Both objects are
// namespace-scope (the original reaches them through the GOT); their curve data are the float
// tables at 0x7102519018 / 0x7102519030.
f32 sReactionPitchCurveData[] = {0.06f, 1.0f, -0.00965478178f, 0.19f, 1.18f, 0.317206114f};
f32 sReactionVolumeCurveData[] = {0.0f, 0.41f, 0.05f, 0.5f, 0.075f, 0.675f, 0.1f, 0.85f, 0.18f, 1.0f};

struct ReactionPitchCurve {
    sead::hostio::Curve<f32> curve;
    ReactionPitchCurve() {
        curve.mFloats = sReactionPitchCurveData;
        curve.mInfo = {10, 4, 6, 6};
    }
};
struct ReactionVolumeCurve {
    sead::hostio::Curve<f32> curve;
    ReactionVolumeCurve() {
        curve.mFloats = sReactionVolumeCurveData;
        curve.mInfo = {6, 4, 10, 10};
    }
};
ReactionPitchCurve sReactionPitchCurve;
ReactionVolumeCurve sReactionVolumeCurve;

void ActorReactionHandle::update() {
    if (!mActive) {
        uking::xlink::fade(mHandle, -1);
        mActive = false;
    }
    mActive = false;
}

// NON_MATCHING: everything but one instruction; our clang keeps the two clampMin 0.0f bounds in a
// callee-saved register, the original materialises 0.0f again for the second clamp.
bool ActorReactionHandle::emit(Actor* actor, Actor* source, const sead::SafeString& name) {
    if (mActive)
        return false;
    if (!actor || !source)
        return false;
    uking::xlink::fade(mHandle, 0);
    mActor = actor;
    xlink::XLink* xlink = source->getXLink();
    if (!xlink)
        return false;
    if (xlink2::UserInstanceSLink* user = xlink->_50)
        user->searchAndEmit(name.cstr(), &mHandle);
    if (!mHandle.isActive())
        return false;
    const f32 speed = mActor->getVelocity().length();
    mHandle.setPosition(mActor->getMtx().getTranslation());
    mHandle.setPitchScale(
        sead::Mathf::clampMin(sReactionPitchCurve.curve.interpolateToF32(speed), 0.0f));
    mHandle.setVolumeScale(
        sead::Mathf::clampMin(sReactionVolumeCurve.curve.interpolateToF32(speed) * 0.15f, 0.0f));
    mActive = true;
    return true;
}

// NON_MATCHING: as emit, the second clampMin 0.0f bound is not rematerialised.
bool ActorReactionHandle::resume(Actor* actor, Actor* source, const sead::SafeString& name) {
    if (!mHandle.isActive() || mHandle.getEvent()->getBitFlag().isOnBit(4)) {
        if (xlink2::UserInstanceSLink* user = source->getXLink()->_50)
            user->searchAndEmit(name.cstr(), &mHandle);
    }
    bool active;
    if (mHandle.isActive()) {
        const f32 speed = mActor->getVelocity().length();
        mHandle.setPosition(mActor->getMtx().getTranslation());
        mHandle.setPitchScale(
            sead::Mathf::clampMin(sReactionPitchCurve.curve.interpolateToF32(speed), 0.0f));
        mHandle.setVolumeScale(
            sead::Mathf::clampMin(sReactionVolumeCurve.curve.interpolateToF32(speed) * 0.15f,
                                  0.0f));
        active = true;
    } else {
        active = false;
    }
    mActive = active;
    return active;
}

ActorReactionQueue::ActorReactionQueue() = default;

// Both destructors of the queue only call the teardown member.
ActorReactionQueue::~ActorReactionQueue() {
    sub_7101287B10();
}

// Fades the held events out and releases both container arrays.
// NON_MATCHING: the bodies are instruction-identical; the original computes the two loop
// preheader end pointers as a byte count (lsl #3 + cbz), ours tests the element count.
void ActorReactionQueue::sub_7101287B10() {
    for (auto& handle : mHandles) {
        uking::xlink::fade(handle.mHandle, -1);
        handle.mActive = false;
    }
    mHandles.freeBuffer();
    for (auto& queue : mCoreQueues)
        queue.freeBuffer();
    mCoreQueues.freeBuffer();
    mActor = nullptr;
}

void ActorReactionQueue::setActor(Actor* actor) {
    mActor = actor;
}

bool ActorReactionQueue::queue(Actor* actor, const sead::CoreId& core) {
    const s32 index = sead::CoreInfo::getPlatformCoreId(core);
    if (mCoreQueues[index]->isFull())
        return false;
    mCoreQueues[index]->pushBack(actor);
    return true;
}

// NON_MATCHING: same body and instruction order; the original keeps &mActors (x9) and &mActors.mPtrs
// (x8) in registers for the inlined pushBack, ours addresses both through `this`.
void ActorReactionQueue::merge() {
    for (auto& queue : mCoreQueues) {
        for (auto& actor : queue)
            mActors.pushBack(&actor);
    }
    mActors.sort(&compareDistance);
}

void ActorReactionQueue::calc() {
    merge();
    for (auto it = mActors.begin(); it != mActors.end(); ++it)
        emit(&*it);
    for (auto it = mHandles.begin(); it != mHandles.end(); ++it)
        it->update();
    for (auto it = mCoreQueues.begin(); it != mCoreQueues.end(); ++it)
        it->clear();
    mActors.clear();
}

// The queued actors are walked one by one; the reaction of `actor` is emitted into the first free
// handle, or resumed when it already has one. Stops when no free handle could emit the reaction.
void ActorReactionQueue::emit(Actor* actor) {
    for (auto it = mActors.begin(); it != mActors.end(); ++it) {
        ActorReactionHandle* handle = nullptr;
        for (auto jt = mHandles.begin(); jt != mHandles.end(); ++jt) {
            if (jt->mHandle.isActive() && jt->mActor == actor) {
                handle = jt.operator->();
                break;
            }
        }
        if (handle && handle->resume(actor, mActor, mName))
            continue;
        bool emitted = false;
        for (auto jt = mHandles.begin(); jt != mHandles.end(); ++jt) {
            if (jt->mHandle.isActive())
                continue;
            emitted = jt->emit(actor, mActor, mName);
            break;
        }
        if (!emitted)
            return;
    }
}

s32 ActorReactionQueue::compareDistance(const Actor* a, const Actor* b) {
    const sead::Vector3f listener =
        ksys::snd::SoundMgr::instance()->_58->mListener->getMatrix().getTranslation();
    const f32 da = (a->getMtx().getTranslation() - listener).length();
    const f32 db = (b->getMtx().getTranslation() - listener).length();
    if (da < db)
        return -1;
    if (da > db)
        return 1;
    return 0;
}

}  // namespace ksys::act
