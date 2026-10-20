#include <aal/aalGroup.h>
#include <aal/aalGroupMgr.h>
#include <aal/aalSystemAccessor.h>
#include <new>
#include <cmath>
#include <limits>
#include <aal/aalListener.h>
#include "KingSystem/Sound/sndSound.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/Sound/Actor/Action/actionSpotBgmTriggerAction.h"
#include "KingSystem/Sound/sndBgmMgr.h"

// The kind 5 spot BGM (Unk_710260f1a8, 0x7101024a54..): a TU of its own in the original (the spot BGM instance
// functions it calls are not inlined).

namespace ksys::snd {

Unk_710260f1a8::~Unk_710260f1a8() {
    mInstances.freeBuffer();
    _60.freeBuffer();
}

void Unk_710260f1a8::m12(f32 fade_sec) {
    auto lock = sead::makeScopedLock(mLock);
    for (s32 i = 0; i < mInstances.size(); ++i) {
        if (auto* instance = mInstances[i])
            instance->sub_710102413C(fade_sec);
    }
}

void Unk_710260f1a8::m13(f32 fade_sec) {
    auto lock = sead::makeScopedLock(mLock);
    for (s32 i = 0; i < mInstances.size(); ++i) {
        if (auto* instance = mInstances[i])
            instance->sub_710102418C(fade_sec);
    }
    _28 = 0;
}

void Unk_710260f1a8::sub_71010252C0(Unk_SpotBgmInstance* instance, bool started) {
    if (!mInstances.isBufferReady())
        return;
    auto lock = sead::makeScopedLock(mLock);
    for (s32 i = 0; i < mInstances.size(); ++i) {
        if (!mInstances[i]) {
            instance->_368 = started ? instance->_368 | 1 : instance->_368 & ~1u;
            mInstances[i] = instance;
            break;
        }
    }
}

void Unk_710260f1a8::sub_7101025388(Unk_SpotBgmInstance* instance) {
    if (!mInstances.isBufferReady())
        return;
    auto lock = sead::makeScopedLock(mLock);
    for (s32 i = 0; i < mInstances.size(); ++i) {
        if (mInstances[i] == instance) {
            instance->sub_7101024280();
            mInstances[i] = nullptr;
            break;
        }
    }
}

void Unk_710260f1a8::sub_71010255D0() {
    _80 = 0;
    if (mGroup)
        mGroup->getParam().setVolume(1.0f);
}

}  // namespace ksys::snd

namespace ksys::snd {

// NON_MATCHING: instance traversal and control forwarding use different loop scheduling.
void Unk_710260f1a8::sub_710102544C(bool entering) {
    if (entering) {
        for (s32 i = 0; i < mInstances.size(); ++i) {
            if (mInstances[i])
                mInstances[i]->sub_7101023EC8();
        }
    } else {
        for (s32 i = 0; i < mInstances.size(); ++i) {
            if (mInstances[i])
                mInstances[i]->sub_71010242C8();
        }
    }
}

}  // namespace ksys::snd

namespace ksys::snd {

void Unk_710260f1a8::sub_7101024AD4(sead::Heap* heap) {
    mInstances.tryAllocBuffer(4, heap);
    mInstances.fill(nullptr);
    auto* positions = new (heap, 8, std::nothrow) PositionRequest[5];
    if (positions)
        _60.setBuffer(5, positions);
    if (auto* groups = aal::SystemAccessor::getGroupMgr())
        mGroup = groups->findGroup("EnvNoisy");
}

}  // namespace ksys::snd

namespace ksys::snd {

KSYS_VISIBILITY_HIDDEN bool sSpotGroupDuckingEnabled = true;
KSYS_VISIBILITY_HIDDEN f32 sSpotGroupVolumeFloor = 0.7f;
KSYS_VISIBILITY_HIDDEN s32 sSpotGroupDuckingCurve = 0;

Unk_710260f1a8::Unk_710260f1a8(const BgmInitArg& arg) : Bgm(arg.kind) {
    sub_7101024AD4(arg.heap);
}

// NON_MATCHING: request traversal, instance selection and volume calculation use different scheduling.
void Unk_710260f1a8::m5() {
    clearSubTrackDistancesMaybe();
    if (_84) {
        const sead::Vector3f listener = SoundMgr::instance()->sub_71011FC2D0()->getMatrix().getTranslation();
        if (_50 != 0) {
            setSubTrack0DistanceMaybe((_54 - listener).length());
            _50 = 0;
        }
        f32 nearest = 9999.0f;
        bool found = false;
        for (s32 i = 0; i < _60.size(); ++i) {
            auto& request = _60[i];
            if (request.mActive != 0) {
                const f32 distance = (request.mPosition - listener).length();
                if (distance < nearest)
                    nearest = distance;
                _60[i].mActive = 0;
                found = true;
            }
        }
        if (found)
            setSubTrack1DistanceMaybe(nearest);
        _84 = false;
    }
    const bool active = _40.isActive();
    for (s32 i = 0; i < mInstances.size(); ++i) {
        if (auto* instance = mInstances[i]) {
            if (active)
                instance->_368 |= 0x800;
            else
                instance->_368 &= ~0x800u;
            instance->sub_71010239A8();
            if ((instance->_368 & 0x32) == 2)
                instance->sub_71010241D0(true, false);
        }
    }
    f32 nearest = std::numeric_limits<f32>::max();
    Unk_SpotBgmInstance* selected = nullptr;
    Unk_SpotBgmInstance* allowed = nullptr;
    bool fading = false;
    for (s32 i = 0; i < mInstances.size(); ++i) {
        if (auto* instance = mInstances[i]) {
            if ((instance->_368 & 0x12) == 0x12) {
                if (instance->_368 & 0x20)
                    allowed = instance;
                if (instance->_264 < nearest) {
                    nearest = instance->_264;
                    selected = instance;
                }
                fading |= instance->_278.getValue() != instance->_278.getTarget();
            }
        }
    }
    if (_20 == 0.0f) {
        if (selected != allowed && !fading) {
            if (allowed)
                allowed->sub_71010241D0(false, false);
            if (selected)
                selected->sub_71010241D0(true, _28 != nullptr);
            _20 = 1.0f;
        }
    } else {
        _20 -= sub_710105E3A4();
        if (_20 < 0.0f)
            _20 = 0.0f;
    }
    _28 = selected;
    f32 gain = 0.0f;
    for (s32 i = 0; i < mInstances.size(); ++i) {
        if (auto* instance = mInstances[i]) {
            instance->sub_7101023F68(_70);
            if ((instance->_368 & 0x2000) && gain < instance->_268)
                gain = instance->_268;
        }
    }
    if (_80 != gain) {
        f32 volume = 1.0f;
        if (sSpotGroupDuckingEnabled) {
            f32 value = 1.0f - gain;
            if (value < 0.0f)
                value = 0.0f;
            else if (value > 1.0f)
                value = 1.0f;
            f32 curved = 0.0f;
            switch (sSpotGroupDuckingCurve) {
            case 0:
                curved = value;
                break;
            case 1:
                curved = value * value;
                break;
            case 2:
                curved = std::sqrt(value);
                break;
            case 3:
                curved = std::sin(value * 1.5707964f);
                break;
            }
            volume = sSpotGroupVolumeFloor + curved * (1.0f - sSpotGroupVolumeFloor);
        }
        if (mGroup)
            mGroup->getParam().setVolume(volume);
        _80 = gain;
    }
}

}  // namespace ksys::snd
