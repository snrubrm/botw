#include "KingSystem/ActorSystem/actReaction.h"
#include "KingSystem/ActorSystem/actActorUnk6b8.h"
#include <basis/seadNew.h>
#include <hostio/seadHostIOCurve.h>
#include <math/seadMathCalcCommon.h>
#include <xlink2/xlink2UserInstanceSLink.h>
#include "Game/Actor/aiXlinkHandle.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/XLink/xlinkXLink.h"

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

ActorReactions::ActorReactions() = default;

ActorReactions::~ActorReactions() {
    for (s32 i = 0; i < mComponents.size(); ++i) {
        if (auto* component = mComponents[i]) {
            delete component;
            mComponents[i] = nullptr;
        }
    }
    mComponents.freeBuffer();
}

bool ActorReactions::init(Actor* actor, sead::Heap* heap) {
    mComponents.tryAllocBuffer(1, heap);
    for (s32 i = 0; i < mComponents.size(); ++i)
        mComponents[i] = nullptr;

    Unk_71024efd58::InitArg arg{actor, 0};
    for (s32 i = 0; i < mComponents.size(); ++i) {
        auto* component = new (heap, 8) ActorUnk6b8(arg);
        actor->set6b8(component);
        mComponents[i] = component;
        if (!mComponents[i])
            return false;
    }

    for (s32 i = 0; i < mComponents.size(); ++i)
        mComponents[i]->sub_7100EBF8C4(heap);

    _10 = false;
    return true;
}

void ActorReactions::calc() {
    for (s32 i = 0; i < mComponents.size(); ++i)
        mComponents[i]->m5();
}

void ActorReactions::sub_7101287410() {
    for (s32 i = 0; i < mComponents.size(); ++i)
        mComponents[i]->m9();
}

void ActorReactions::sub_7101287480() {
    if (_10)
        return;
    for (s32 i = 0; i < mComponents.size(); ++i) {
        if (auto* component = mComponents[i])
            component->m10();
    }
    _10 = true;
}

ActorReactionQueue::ActorReactionQueue() = default;

void ActorReactionQueue::init(sead::Heap* heap, const sead::SafeString& name) {
    const s32 num_cores = sead::CoreInfo::getNumCores();
    auto& core_queues = mCoreQueues;
    if (num_cores > 0)
        core_queues.allocBuffer(num_cores, heap);
    for (u32 i = 0; i < u32(num_cores); ++i) {
        core_queues.emplaceBack();
        core_queues[i]->allocBuffer(8, heap);
    }
    mActors.allocBuffer(num_cores * 8, heap);
    mHandles.allocBuffer(4, heap);
    for (s32 i = 0; i < 4; ++i)
        mHandles.emplaceBack();
    mName.copy(name);
}

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
