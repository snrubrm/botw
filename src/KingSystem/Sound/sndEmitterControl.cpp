#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/Sound/sndBgmMgr.h"
#include <aal/aalArbiter.h>
#include <aal/aalEmitter.h>
#include <aal/aalSystemAccessor.h>
#include "KingSystem/Event/evtInfoData.h"
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

}  // namespace ksys::snd
