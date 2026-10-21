// The TU at 0x71012c1fa0 .. 0x71012c2850 (after sndSoundMgr38_60.cpp): the attenuation ducking entries and their
// owner (SoundMgr::_88), with the static initialiser 0x71012c2850.
#include <algorithm>
#include <aal/aalSoundSource.h>
#include <prim/seadScopedLock.h>
#include "KingSystem/Sound/sndSoundAttenuationMgr.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace ksys::snd {

namespace {
util::InitTimeInfo sInitTimeInfo;
}  // namespace

void Unk_710251aef0::add(const aal::Handle& handle, f32 value) {
    auto lock = sead::makeScopedLock(mCS);
    if (auto* item = mItems.emplaceBack()) {
        item->handle = handle;
        item->value = value;
        mActive = true;
    }
}

// NON_MATCHING: the loudest volume is kept with a select (the original branches) and the blocks that set `apply`
// are laid out differently.
void Unk_710251aef0::calc() {
    const auto* param = mDucker->mAttenuationParam;
    bool any = false;
    bool found = false;
    f32 max_volume = 0.0f;

    for (auto it = mItems.robustBegin(), end = mItems.robustEnd(); it != end; ++it) {
        if (!it->handle.isActive()) {
            mItems.erase(&*it);
            continue;
        }

        if (it->done) {
            any = true;
            continue;
        }

        f32 volume = 1.0f;
        if (param->_2)
            volume = it->value;
        if (param->_1 && it->handle.getSoundSource()->mSpatialSetting.isPositioned()) {
            const auto* result = it->handle.getSoundSource()->getSpatialCalcResult(0);
            if (!result) {
                any = true;
                continue;
            }
            volume *= result->volume;
        }
        found = true;
        any = true;
        it->done = true;
        if (max_volume < volume)
            max_volume = volume;
    }

    f32 volume = 1.0f;
    bool apply = false;
    if (found) {
        apply = true;
        if (param->_1 || param->_2) {
            if (param->_4 > param->_8) {
                volume = std::min((max_volume - param->_8) / (param->_4 - param->_8), 1.0f);
                if (volume <= 0.0f)
                    apply = false;
            } else {
                apply = false;
            }
        }
        if (mDucker->isOnDucking() && !param->_0)
            apply = false;
    }

    if (!any) {
        if (mDucker->isOnDucking())
            mDucker->deactivateMaybe(false);
        mActive = false;
        return;
    }

    if (apply) {
        const bool on = mDucker->isOnDucking();
        const bool use_volume = param->_1 || param->_2;
        if (on) {
            if (use_volume)
                mDucker->sub_710103E2DC(volume);
            else
                mDucker->activateAndResetMaybe();
        } else {
            if (use_volume)
                mDucker->sub_710103E020(volume);
            else
                mDucker->activateMaybe();
        }
    }
    mActive = true;
}

Unk_710251aef0::~Unk_710251aef0() = default;

Unk_710251af10::Unk_710251af10() {
    auto* mgr = SoundMgr::instance()->mDuckingMgr;
    for (s32 i = 0; i < mEntries.size(); ++i)
        mEntries[i].mDucker = &mgr->getDucker(DuckingMgr::DuckerType::ValueType(DuckingMgr::DuckerType::cExplosion + i));
}

void Unk_710251af10::calc() {
    for (s32 i = 0; i < mEntries.size(); ++i) {
        if (mEntries[i].mActive)
            mEntries[i].calc();
    }
}

}  // namespace ksys::snd
