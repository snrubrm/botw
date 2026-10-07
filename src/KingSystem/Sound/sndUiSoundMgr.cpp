#include <xlink2/xlink2HandleSLink.h>
#include <xlink2/xlink2UserInstanceSLink.h>
#include "KingSystem/Sound/sndMgr.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/StageInfo.h"

namespace ksys::snd {

// 0x710105d5ac: stops the previous HeartUp sound and emits mc_HeartUp. Non-zero `mode` keeps the
// sound in _38 muted while _28 plays; mode 0 fades _28 and reuses it for the new sound.
// NON_MATCHING: the original keeps &_38 in a register across the searchAndEmit call (one extra `add`
// and x20-relative addressing); with this source clang folds the address into the stores instead.
// Everything else, including both tails and the fade path, is identical.
bool UiSoundMgr::sub_710105D5AC(const s32* mode) {
    if (*mode != 0) {
        bool active = false;
        if (_20) {
            xlink2::HandleSLink h = _20->searchAndEmit("mc_HeartUp");
            _38 = h;
            active = h.isActive();
        }
        if (_28.isActive())
            _38.setVolumeScale(0.0f);
        return active;
    }
    _38.setVolumeScale(0.0f);
    _28.fade();
    if (!_20)
        return false;
    xlink2::HandleSLink h = _20->searchAndEmit("mc_HeartUp");
    _28 = h;
    return h.isActive();
}

// 0x710105d7b0: mutes _38 and emits mc_ExtraHeartUp (mode 0 only).
bool UiSoundMgr::sub_710105D7B0(const s32* mode) {
    if (*mode != 0)
        return false;
    _38.setVolumeScale(0.0f);
    if (!_20)
        return false;
    xlink2::HandleSLink h = _20->searchAndEmit("mc_ExtraHeartUp");
    return h.isActive();
}

void UiSoundMgr::sub_710105D844(const s32* mode) {
    if (*mode == 0) {
        _28.fade();
        _38.setVolumeScale(1.0f);
    } else {
        _38.fade();
    }
}

void UiSoundMgr::sub_710105D0E4(sead::Heap* heap) {}

// NON_MATCHING: the two flag selections allocate their temporary values in a different order.
void UiSoundMgr::sub_710105D0E8() {
    if (_8.isAllocatedOrFailed() && _8.isProcReady()) {
        _18 = static_cast<act::Actor*>(_8.getProc());
        _18->getActorFlags2().set(act::Actor::ActorFlag2::NoDistanceCheck);
        _8.releaseAndWakeProc();
    }
    if ((_80 & 0x10) && !_48.isActive()) {
        _58.moveTo(1.0f, 1.0f);
        _80 &= ~0x10;
    }
    _58.calc();
    if (auto* user = _20) {
        user->preCalc();
        user->postCalc();
    }
    if (_80 & 1)
        _80 |= 2;
    else
        _80 &= ~2;
    if (_80 & 4)
        _80 |= 8;
    else
        _80 &= ~0xd;
    _80 &= ~5;
}

UiSoundMgr::UiSoundMgr() : _88("UiSoundMgr") {}

UiSoundMgr::~UiSoundMgr() {
    if (_20) {
        _20->destroy();
        _20 = nullptr;
    }
}

void UiSoundMgr::sub_710105D23C(sead::Heap* heap, act::ActorCreator* creator) {
    if (!creator)
        return;
    if (StageInfo::getCurrentMapType() != "TitleMenu")
        creator->requestCreateActor("GetItemSound", heap, &_8, nullptr, nullptr, 1);
}

void UiSoundMgr::sub_710105D308() {
    _8.deleteProc();
    _18 = nullptr;
}

void UiSoundMgr::sub_710105D9F8(aal::SoundSource* source) {
    _48.attachSoundSource(source);
    _58.moveTo(0.0f, 0.2f);
    _80 |= 0x10;
}

bool UiSoundMgr::playSound(const sead::SafeString& label, xlink2::HandleSLink* handle) {
    if (_20) {
        xlink2::HandleSLink h = _20->searchAndEmit(label.cstr());
        if (handle)
            *handle = h;
        return h.isActive();
    }
    return false;
}

bool UiSoundMgr::emitGetItemSound(const sead::SafeString& label) {
    if (!_18)
        return false;
    if (_84 & 1)
        _88.log("[GetItemSound] %s", label.cstr());
    auto handle = eft::searchAndEmitSLink(_18, label.cstr(), true);
    if (handle.isActive())
        return true;
    if (label.findIndex("Rupee") != -1) {
        handle = eft::searchAndEmitSLink(_18, "Rupee", true);
        if (handle.isActive())
            return true;
    }
    if (label.findIndex("Weapon") != -1) {
        handle = eft::searchAndEmitSLink(_18, "Weapon", true);
        if (handle.isActive())
            return true;
    }
    handle = eft::searchAndEmitSLink(_18, "Default", true);
    return handle.isActive();
}

}  // namespace ksys::snd
