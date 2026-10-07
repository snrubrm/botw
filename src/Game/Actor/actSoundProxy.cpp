#include "Game/Actor/actSoundProxy.h"
#include <prim/seadScopedLock.h>
#include <aal/aalHandle.h>
#include <aal/aalSoundSource.h>
#include <aal/aalSpatialCalculator.h>
#include <xlink2/xlink2HandleSLink.h>
#include "KingSystem/XLink/xlinkActorUtil.h"
#include <xlink2/xlink2UserInstanceSLink.h>
#include "KingSystem/XLink/xlinkXLink.h"

namespace uking::act {

void SoundProxy::sub_710105A0D0(aal::Shape* shape) {
    mShape = shape;
}

void SoundProxy::sub_710105A510() {
    auto lock = sead::makeScopedLock(mLock);
    mSourceMapObject = nullptr;
}

bool SoundProxy::prepareInit_(sead::Heap* heap, PrepareArg& arg) {
    return true;
}

void SoundProxy::onPreDeleteStart_(PrepareArg& arg) {}

void SoundProxy::sub_710105A0D8(const sead::Vector3f& a, const sead::Vector3f& b) {
    _854 = a;
    _860 = b;
}

// NON_MATCHING: the zero-countdown branch uses cbnz instead of reusing the decrement flags.
void SoundProxy::calcMaybe() {
    if (_8b8) {
        const s32 remaining = _8bc - 1;
        if (remaining >= 0) {
            _8bc = remaining;
            if (remaining == 0 && getXLink() && getXLink()->_50)
                getXLink()->_50->fadeIfLoopSound();
        }
        m107();
    }
}

void SoundProxy::sub_710105A4FC() {
    _8bc = 3;
    m107();
}

}  // namespace uking::act

namespace uking::act {

// NON_MATCHING: sound-count loop induction width and saved register choices differ.
void SoundProxy::sub_710105A10C(const sead::SafeString& name, xlink2::HandleSLink* handle) {
    auto lock = sead::makeScopedLock(mLock);
    if (!mSourceMapObject)
        return;
    xlink2::HandleSLink local_handle;
    if (!handle)
        handle = &local_handle;
    *handle = ksys::eft::searchAndEmitSLink(this, name.cstr(), false);
    if (!handle->isActive())
        return;
    handle->getEvent()->resetFlagBit(1);
    if (!mShape)
        return;
    sead::FixedPtrArray<aal::Handle, 8> sounds;
    const s32 count = handle->isActive() ?
        static_cast<xlink2::EventSLink*>(handle->getEvent())->getSoundHandle(&sounds) : 0;
    for (s32 i = 0; i != count; ++i) {
        if (auto* source = sounds[i]->getSoundSource())
            source->mSpatialSetting.setShape(mShape);
    }
}

// NON_MATCHING: sound-count loop induction width and saved register choices differ.
void SoundProxy::sub_710105A254(xlink2::HandleSLink* handle, s32 fade_frames) {
    auto lock = sead::makeScopedLock(mLock);
    if (!handle || !mSourceMapObject || !handle->isActive())
        return;
    sead::FixedPtrArray<aal::Handle, 8> sounds;
    const s32 count = handle->isActive() ?
        static_cast<xlink2::EventSLink*>(handle->getEvent())->getSoundHandle(&sounds) : 0;
    for (s32 i = 0; i != count; ++i) {
        auto* source = sounds[i]->getSoundSource();
        if (source && source->mSpatialCalculator)
            source->mSpatialCalculator->detachShape(true);
    }
    handle->fade(fade_frames);
}

// NON_MATCHING: sound-count loop induction width and saved register choices differ.
void SoundProxy::sub_710105A3F8() {
    if (getXLink() && getXLink()->_50) {
        auto* user = getXLink()->_50;
        for (const auto& event : *user->getEventList()) {
            sead::FixedPtrArray<aal::Handle, 8> sounds;
            const s32 count = static_cast<const xlink2::EventSLink&>(event).getSoundHandle(&sounds);
            for (s32 i = 0; i != count; ++i) {
                auto* source = sounds[i]->getSoundSource();
                if (source && source->mSpatialCalculator)
                    source->mSpatialCalculator->detachShape(true);
            }
        }
        user->stopAllEvent(-1);
    }
}

}  // namespace uking::act
