#include <aal/aalShape.h>
#include <aal/aalSoundSource.h>
#include <xlink2/xlink2AssetExecutorSLink.h>
#include "KingSystem/XLink/xlinkActorUtil.h"
#include <aal/aalSpeakerBalanceUnifier.h>
#include <aal/aalSpeakerBalanceUnifierMgr.h>
#include <aal/aalSystemAccessor.h>
#include <prim/seadBitFlag.h>
#include <prim/seadScopedLock.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/XLink/xlinkManager.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/World/worldEnvMgr.h"
#include "KingSystem/World/worldTimeMgr.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace {
// Set up by the TU's 52-byte static initialiser.
ksys::util::InitConstants sInitConstants;
ksys::util::InitTimeInfo sInitTimeInfo;
}  // namespace

namespace ksys::snd {

f32 SpeakerBalanceUnifierMgr::sSizeThresholds[3] = {2.0f, 5.0f, 40.0f};

// 0x7101027554
SpeakerBalanceUnifierMgr::SpeakerBalanceUnifierMgr() = default;

SpeakerBalanceUnifierMgr::~SpeakerBalanceUnifierMgr() {
    if (auto* mgr = aal::SystemAccessor::getSpeakerBalanceUnifierMgr()) {
        for (s32 i = 0; i < mUnifiers.size(); ++i) {
            if (auto* unifier = mUnifiers[i])
                mgr->freeSpeakerBalanceUnifier(unifier);
        }
    }
    mUnifiers.freeBuffer();
    mActor = nullptr;
}

// NON_MATCHING: the original reads the thresholds through a direct adrp of a file-local table that is not constant (it
// is written elsewhere in its translation unit); a never-written local table gets folded, so it is an external member here
// (GOT access).
void SpeakerBalanceUnifierMgr::sub_7101027BF4() {}

void SpeakerBalanceUnifierMgr::sub_7101027BBC() {}

void SpeakerBalanceUnifierMgr::sub_7101027BC0(sead::Heap* heap, act::ActorCreator* creator) {
    if (mActor)
        return;
    creator->requestCreateActor("BoxWaterSound", heap, &mHandle, nullptr, nullptr, 1);
}

void SpeakerBalanceUnifierMgr::sub_7101027D4C(f32 size, aal::Shape* shape) {
    if (!mUnifiers.isBufferReady())
        return;
    s32 idx;
    if (sSizeThresholds[0] >= size)
        idx = 0;
    else if (sSizeThresholds[1] >= size)
        idx = 1;
    else if (sSizeThresholds[2] >= size)
        idx = 2;
    else
        idx = 3;

    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    if (auto* unifier = mUnifiers.at(idx))
        unifier->addUnifiable(shape);
}

void SpeakerBalanceUnifierMgr::sub_7101027E0C(aal::Shape* shape) {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    for (s32 i = 0; i < mUnifiers.size(); ++i) {
        if (auto* unifier = mUnifiers.at(i))
            unifier->removeUnifiable(shape);
    }
}

void SpeakerBalanceUnifierMgr::sub_7101027CE8() {
    mHandle.deleteProc();
    for (s32 i = 0; i < mUnifiers.size(); ++i) {
        if (auto* unifier = mUnifiers.at(i))
            unifier->clearUnifiable();
    }
    mActor = nullptr;
}

// NON_MATCHING: original local label tables use direct access; the kind argument and label selection
// also have different scheduling. The original kind type remains unknown.
xlink2::HandleSLink SpeakerBalanceUnifierMgr::sub_7101027E90(f32 size, int type,
                                                           aal::Shape* shape) {
    xlink2::HandleSLink handle;
    if (!mActor)
        return handle;
    sead::SafeString* names;
    if (type == 1)
        names = sUnk_7102610618;
    else if (type == 2)
        names = sUnk_7102610658;
    else
        return handle;
    sead::SafeString label;
    s32 index;
    if (sSizeThresholds[0] >= size)
        index = 0;
    else if (sSizeThresholds[1] >= size)
        index = 1;
    else if (sSizeThresholds[2] >= size)
        index = 2;
    else
        index = 3;
    label = names[index];
    if (label.isEmpty())
        return handle;
    handle = eft::searchAndEmitSLink(mActor, label.cstr(), false);
    auto* event = static_cast<xlink2::EventSLink*>(handle.getEvent());
    if (event && event->getCreateId() == handle.getCreateId()) {
        event->resetFlagBit(1);
        if (auto* executor = event->getAliveAssetExecutor()) {
            if (auto* source = executor->getHandle()->getSoundSource()) {
                if (source->mState < 3)
                    source->mSpatialSetting.setShape(shape);
            }
        }
    }
    return handle;
}

// 0x71010289cc: empty in the release build (Unk_SoundMgr38::sub_710102AF84 calls it).
Unk_SoundMgr38_58::~Unk_SoundMgr38_58() = default;

void Unk_SoundMgr38_58::sub_7101028690() {
    for (auto& entry : mEntries) {
        // called through a pointer in the original (not devirtualised)
        (&entry)->sub_710104A0D4();
    }
    if (mInstances) {
        mInstances->sub_710104993C();
        delete mInstances;
        mInstances = nullptr;
    }
}

// NON_MATCHING: sub_710102880C is inlined here; the original calls it
void Unk_SoundMgr38_58::sub_7101028710() {
    auto lock = sead::makeScopedLock(mCS);
    sub_710102880C();

    if (auto* mgr = SoundMgr::instance()->_38) {
        if (mgr->_a0)
            sub_7101028954(45);
    }

    if (auto* env_mgr = world::Manager::instance()->getEnvMgr()) {
        if (env_mgr->getPaletteSet() == 7 && env_mgr->getPaletteSetTransition() > 0.0f)
            sub_7101028954(45);
    }

    if (mInstances)
        mInstances->sub_7101049C60();

    for (auto& entry : mEntries)
        entry.sub_710104A1B8();
}

// NON_MATCHING: the original loads and masks the bit field in each branch; ours shares one load at the end
void Unk_SoundMgr38_58::sub_710102880C() {
    auto* world = world::Manager::instance();
    if (!world)
        return;
    auto* time_mgr = world->getTimeMgr();
    if (!time_mgr)
        return;

    f32 time = time_mgr->getTime();
    if (auto* mgr = SoundMgr::instance()->_38) {
        if (mgr->_140 >= 0.0f)
            time = mgr->_140;
    }

    if (time >= 60.0f && time < 75.0f)
        mTimeZone = 5;
    else if (time >= 75.0f && time < 105.0f)
        mTimeZone = 1;
    else if (time >= 105.0f && time < 120.0f)
        mTimeZone = 3;
    else if (time >= 120.0f && time < 270.0f)
        mTimeZone = 2;
    else if (time >= 270.0f && time < 285.0f)
        mTimeZone = 3;
    else
        mTimeZone = 4;
}

void Unk_SoundMgr38_58::sub_7101028954(s32 arg) {
    for (auto& entry : mEntries) {
        if (auto* user_instance = entry.getUserInstance())
            user_instance->stopAllEvent(arg);
    }
}

namespace {
// 0x7102501200: the chirp names by climate type and time of day.
const char* const sBirdNames[4][3] = {
    {"EnvSeEmitPointBirdTemperate_Morning", "EnvSeEmitPointBirdTemperate_Noon",
     "EnvSeEmitPointBirdTemperate_Night"},
    {"EnvSeEmitPointBirdSubtropic_Morning", "EnvSeEmitPointBirdSubtropic_Noon",
     "EnvSeEmitPointBirdSubtropic_Night"},
    {"EnvSeEmitPointBirdTropical_Morning", "EnvSeEmitPointBirdTropical_Noon",
     "EnvSeEmitPointBirdTropical_Night"},
    {"EnvSeEmitPointBirdSubarctic_Morning", "EnvSeEmitPointBirdSubarctic_Noon",
     "EnvSeEmitPointBirdSubarctic_Night"},
};
}  // namespace

// 0x71010289d0: plays the chirp `type` at `pos` with property value `value`. The distance to the player picks
// the playback category (3 when the type matches the current climate, 2 when close, 1 when far); the time-of-day
// bit set picks the name variant.
// NON_MATCHING: the entry scan is an if / else chain in the original (it compares each entry's _a0 at fixed
// offsets); the range-for lowers to a csel chain, and the surrounding register allocation differs (592 B vs 660 B).
void Unk_SoundMgr38_58::sub_71010289D0(f32 value, s32 type, const sead::Vector3f* pos) {
    sead::Vector3f player_position = sead::Vector3f::zero;
    const s32 climate = xlink::Manager::instance()->getClimateMaybe();
    act::ActorSystem::instance()->getPlayerPosition(&player_position);

    s32 category;
    if (type == climate) {
        category = 3;
    } else {
        f32 distance = pos->y - player_position.y;
        distance = distance > 0.0f ? distance : -distance;
        category = distance <= 20.0f ? 2 : 1;
    }

    auto lock = sead::makeScopedLock(mCS);
    sub_7101028C64();

    const u32 num_zones = sead::BitFlagUtil::countOnBit(mTimeZone);
    if (num_zones == 0)
        return;

    const u32 target = sead::GlobalRandom::instance()->getU32(num_zones);
    s32 zone = -1;
    u32 seen = 0;
    for (s32 i = 0; i < 3; ++i) {
        if (!(mTimeZone & (1 << i)))
            continue;
        if (seen == target) {
            zone = i;
            break;
        }
        ++seen;
    }
    if (zone < 0)
        return;

    const char* name = sBirdNames[type][zone];
    Entry* entry = sub_7101028E7C(name, category);
    if (!entry) {
        for (auto& candidate : mEntries) {
            if (candidate._a0 == u32(category)) {
                entry = &candidate;
                break;
            }
        }
        if (!entry)
            return;
        entry->mPos = *pos;
        entry->mPropertyValue = value;
        entry->sub_710104A5E8();
    } else {
        entry->mPos = *pos;
        entry->mPropertyValue = value;
        entry->sub_710104A308(name);
    }
    entry->mZone = zone;
    entry->mType = type;
    entry->_a0 = category;
}

Unk_SoundMgr38_58::BirdChirpSoundEmitter::~BirdChirpSoundEmitter() = default;

void Unk_SoundMgr38_58::BirdChirpSoundEmitter::m4(xlink2::UserInstanceSLink* user_instance) {
    if (user_instance)
        user_instance->setPropertyValue(0, mPropertyValue);
}

void Unk_SoundMgr38_58::BirdChirpSoundEmitter::m5(xlink2::UserInstanceSLink* user_instance,
                                                  xlink2::HandleSLink* handle) {
    if (handle)
        handle->setPosition(mPos);
}

void Unk_SoundMgr38_58::sub_71010289CC() {}

}  // namespace ksys::snd
