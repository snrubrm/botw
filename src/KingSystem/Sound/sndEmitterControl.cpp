#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/Sound/sndBgmMgr.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/AOC/aocManager.h"
#include "KingSystem/ActorSystem/actReaction.h"
#include <aal/aalArbiter.h>
#include <aal/aalEmitter.h>
#include <aal/aalSystemAccessor.h>
#include "KingSystem/Event/evtInfoData.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Event/evtEventFlow.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace ksys::snd {

// The TU's static initialiser is 0x710105ce74 (`_GLOBAL__sub_I_sndEmitterControl.cpp`).
static util::InitTimeInfoEx sInitTimeInfo;

Unk_710105abc0::Unk_710105abc0(sead::Heap* heap)
    : _8(nullptr), _38(0), _39(false), _3c(0.891f) {
    if (auto* arbiter = aal::SystemAccessor::getArbiter()) {
        _8 = arbiter->allocEmitter(nullptr, "Emitter");
        if (_8)
            _8->mSpatialSetting.setPositioned(false);
    }
}


Unk_710105abc0::~Unk_710105abc0() {
    if (_8) {
        if (auto* arbiter = aal::SystemAccessor::getArbiter()) {
            arbiter->freeEmitter(_8);
            _8 = nullptr;
        }
    }
}

// NON_MATCHING: the original keeps the sample rate as an integer until the division (lib aal::AssetInfo::getSampleRate
// converts it to f32 first)
f32 Unk_710105abc0::sub_710105AE80() const {
    if (_10.isActive() && _10.getAssetInfo()) {
        const f32 rate = _10.getAssetInfo()->getSampleRate();
        if (rate != 0.0f)
            return static_cast<f32>(s32(_10.getPlaySamplePosition())) * 30.0f / rate;
    }
    return -1.0f;
}

// NON_MATCHING: the comparison result is materialized after the string loop instead of before it,
// and the original uses full-width moves when forwarding that Boolean fade choice.
void Unk_710105abc0::sub_710105AF00(const sead::SafeString& name, bool skip_event_info) {
    if (_38.isOn(1) || _39)
        return;
    const char* stop_type = "StopWithFade";
    if (!skip_event_info) {
        al::ByamlIter iter;
        if (evt::InfoData::instance()->getEntry(&iter, name, name))
            iter.tryGetStringByKey(&stop_type, "bgm_stop");
    }
    const sead::SafeString type(stop_type);
    if (type == "NotStop")
        return;
    const bool fade_type = type != "StopNotFade";
    auto* bgm = SoundMgr::instance()->_30;
    if (bgm->_88 & 3) {
        bgm->sub_7100FF8684(fade_type);
        _38.set(1);
    }
    if (bgm->_78->sub_7101007C14() || (bgm->_88 & 4)) {
        bgm->sub_7100FF8AC4(fade_type);
        _38.set(2);
    }
}

// NON_MATCHING: the original keeps the sample rate as an integer until the division (lib
// aal::AssetInfo::getSampleRate converts it first) and spills the SoundMgr state to the stack.
void Unk_710105abc0::sub_710105ACEC() {
    if (_20.getValue() != _20.getTarget())
        _20.calc();

    if (!_10.isActive())
        return;

    if (auto* mgr = SoundMgr::instance()) {
        f32 volume = _20.getValue();
        if (mgr->_ec != 2)
            volume *= _3c;
        _10.setVolume(volume);
        _10.setTrackVolume(4, mgr->sub_71011FC31C());
    }

    auto* eventMgr = evt::Manager::instance();
    if (!eventMgr)
        return;
    auto* event = eventMgr->getActiveEvent();
    if (!event)
        return;
    if (event->getEventFlowType() != 2 || !event->isPlaying())
        return;

    const f32 event_frame = event->getFrameCount();

    const f32 position = sub_710105AE80();

    if (position - event_frame >= 4.0f)
        _10.pause(sead::BitFlag8(0x40), true, 0.0f);
    else
        _10.pause(sead::BitFlag8(0x40), false, 0.0f);
}

void Unk_710105abc0::sub_710105B37C() {
    SoundMgr::instance()->mDuckingMgr->sub_7101042024(DuckingMgr::DuckerType::cTmlnMovie);
}

void Unk_710105abc0::sub_710105B8EC() {
    if (_10.isPaused(0x40))
        _10.pause(0x40, false, 0.0f);
    _10.attachSoundSource(nullptr);
}

bool Unk_710105abc0::sub_710105B090() {
    if (_38.isOn(1) && SoundMgr::instance()->_30->_60.getValue() !=
                           SoundMgr::instance()->_30->_60.getTarget())
        return false;
    return true;
}

Unk_SoundMgr60_828::Unk_SoundMgr60_828() = default;
Unk_SoundMgr60_828::~Unk_SoundMgr60_828() = default;

// NON_MATCHING: path string construction and asset-name loads are scheduled differently.
bool Unk_SoundMgr60_828::StreamPathResolver::sub_7100BA1AEC(sead::BufferedSafeString* path,
                                                         aal::AssetInfo* info) {
    if (!path || !info)
        return false;
    if (!aoc::Manager::instance())
        return true;
    sead::FixedSafeString<128> root("aoc:/");
    path->format("%s/Sound/Resource/Stream/%s%s", root.cstr(), info->getAssetName(), ".bfstm");
    return true;
}

// NON_MATCHING: list search and new-entry initialization use different register schedules.
void Unk_SoundMgr60_828::sub_710105C3D0(const sead::SafeString& name, res::Handle* pack) {
    for (auto& entry : mEntries) {
        if (entry.mName == name) {
            entry._a0 = false;
            return;
        }
    }
    auto* entry = mEntries.emplaceBack();
    entry->mName.copy(name);
    sead::FixedSafeString<64> path;
    path.format("M_%s.bars", name.cstr());
    SoundMgr::instance()->_60->requestLoadBars(&entry->mHandle, path, false, false, 0, pack);
}

// NON_MATCHING: list and resource-cast branches use different schedules.
bool Unk_SoundMgr60_828::sub_710105C70C(const sead::SafeString& name) {
    for (auto& entry : mEntries) {
        if (entry.mName != name)
            continue;
        if (entry.mHandle.isReady())
            return true;
        if (!entry.mHandle.isReadyOrNeedsParse() || !entry.mHandle.parseResource(nullptr))
            return false;
        auto* bars = sead::DynamicCast<Unk_7102502978>(entry.mHandle.getResource());
        if (entry.mHandle.isSuccess() && bars) {
            sead::FixedSafeString<64> path;
            path.format("M_%s.bars", entry.mName.cstr());
            bars->sub_7101057588(path);
        }
        return true;
    }
    return true;
}

// NON_MATCHING: sound handle stores and the final list-search branch are scheduled differently.
void Unk_SoundMgr60_828::sub_710105CD4C(const sead::SafeString& name, aal::Handle handle) {
    for (auto& entry : mEntries) {
        if (entry.mName == name) {
            entry.mSoundHandle = handle;
            return;
        }
    }
}

// NON_MATCHING: soundtrack format selection and list-search branches differ.
bool Unk_SoundMgr60_828::sub_710105CA84(aal::AssetInfo* info, const sead::SafeString& name,
                                      bool use_barefoot) {
    for (auto& entry : mEntries) {
        if (entry.mName != name)
            continue;
        if (!entry.mHandle.isSuccess())
            return false;
        auto* bars = sead::DynamicCast<Unk_7102502978>(entry.mHandle.getResource());
        if (!bars)
            return false;
        sead::FixedSafeString<128> asset;
        const bool barefoot = use_barefoot && act::Reaction::instance()->_a8 &&
                              act::Reaction::instance()->_a8->mIsPlayerBarefoot;
        asset.format(barefoot ? "%s_SoundTrack_bf" : "%s_SoundTrack", entry.mName.cstr());
        if (!aal::Emitter::searchAssetInfo(info, bars, asset, false))
            return false;
        if (name.startsWith("Demo6"))
            info->_18 = &mStreamPathResolver;
        return true;
    }
    return false;
}

// NON_MATCHING: the original walks the list by entry pointers (node - 0xa8) and null-checks the result.
void Unk_SoundMgr60_828::sub_710105C96C(const sead::SafeString& name) {
    Entry* found = nullptr;
    for (auto& entry : mEntries) {
        if (entry.mName == name) {
            found = &entry;
            break;
        }
    }
    if (found)
        found->_a0 = true;
}

}  // namespace ksys::snd
