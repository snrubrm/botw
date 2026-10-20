#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/Sound/sndBgmMgr.h"
#include <aal/aalGroup.h>
#include <aal/aalSoundSource.h>
#include <aal/aalGroupMgr.h>
#include <aal/aalSystemAccessor.h>
#include "KingSystem/Event/evtEventFlow.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::snd {

struct Unk_7102610960 {
    u8 _0[0x28];
    Unk_710103b704::StartParam mParam;
};
static_assert(offsetof(Unk_7102610960, mParam) == 0x28);

// 0x7102610958 / 0x7102610960 (placeholder names): the custom ducking default start parameters. The
// byte selects the defaults instead of the caller's parameters.
KSYS_VISIBILITY_HIDDEN bool sUnk_7102610958;
KSYS_VISIBILITY_HIDDEN Unk_7102610960 sUnk_7102610960;

Unk_710103b704::Unk_710103b704(sead::Heap* heap)
    : _5c8(-1), _5cc(false), _5d0(6), _5d4(3), _5d8(false), _5d9(false), _5e0(heap), _620(0) {}

Unk_710103b76c::Unk_710103b76c() = default;

Unk_710103b704::~Unk_710103b704() = default;

void Unk_710103b704::sub_710103CEB0() {
    // Snapshot the control state before the external manager call, as in the original.
    const bool mixed = _5e0._39;
    auto* groups = aal::SystemAccessor::getGroupMgr();
    if (!mixed) {
        if (groups) {
            if (auto* group = groups->findGroup("Demo"))
                group->stopAllSound(-1.0f);
            if (auto* group = groups->findGroup("SystemAcrossScene"))
                group->stopAllSound(-1.0f);
        }
        if (_5c8 >= 0 && _8.getEntry(_5c8)._b0)
            _5e0.sub_710105BA88();
    } else if (groups) {
        if (auto* group = groups->findGroup("DemoMixed"))
            group->stopAllSound(-1.0f);
        if (auto* group = groups->findGroup("DemoDialog"))
            group->stopAllSound(-1.0f);
    }
}


void Unk_710103b704::sub_710103D0D8(UiSoundKind kind) {
    if (_5c8 < 0)
        return;
    auto& entry = _8.getEntry(_5c8);
    if (entry._0 == "GotoZoraVillage" && entry._58 == "ZoraArrival3") {
        auto* event = evt::Manager::instance()->getActiveEvent();
        if (!event || !(event->getFrameCount() > 300.0f))
            return;
        auto* group_mgr = aal::SystemAccessor::getGroupMgr();
        if (!group_mgr)
            return;
        auto* group = group_mgr->findGroup("NpcVoice");
        if (!group)
            return;
        group->allowEmit(sead::BitFlag8(0x20), false);
        return;
    }
    if (entry._0 == "Demo104_0" && kind.value == 4)
        SoundMgr::instance()->mDuckingMgr->sub_7101042024(DuckingMgr::DuckerType::cScreenFadeS);
}

void Unk_710103b704::sub_710103D324(UiSoundKind kind) {
    SoundMgr::instance()->mDuckingMgr->sub_7101042D6C(DuckingMgr::DuckerType::cEventSkip, _5d9);
    SoundMgr::instance()->mDuckingMgr->sub_7101042D6C(DuckingMgr::DuckerType::cEventSkipBeam, _5d9);
    _5d9 = false;
    if (_5c8 < 0)
        return;
    if (_8.getEntry(_5c8)._0 == "Demo346_4")
        _620 = kind.value == 1 ? 1.0f : 0.5f;
}

void Unk_710103b704::sub_710103BA44() {
    if (_5cc && --_5cc == 0)
        sub_710103BB00(_5d0, _5d4);
    _5e0.sub_710105ACEC();
    if (_620 > 0.0f) {
        _620 -= sub_710105E3A4();
        if (_620 <= 0.0f) {
            if (auto* mgr = aal::SystemAccessor::getGroupMgr()) {
                if (auto* group = mgr->findGroup("NpcVoice"))
                    group->allowEmit(sead::BitFlag8(0x20), true);
            }
            _620 = 0.0f;
        }
    }
}

// NON_MATCHING: native zero fade-kind arguments use full-register moves.
void Unk_710103b704::sub_710103BB00(BgmCtrlType bgm_type, SeCtrlType se_type) {
    switch (bgm_type) {
    case BgmCtrlType::_1:
        SoundMgr::instance()->_30->sub_7100FF8780(0);
        SoundMgr::instance()->_30->sub_7100FF88A8(0);
        break;
    case BgmCtrlType::_2:
        SoundMgr::instance()->_30->sub_7100FF8780(1);
        SoundMgr::instance()->_30->sub_7100FF88A8(1);
        break;
    case BgmCtrlType::_3:
        SoundMgr::instance()->_30->sub_7100FF8684(0);
        SoundMgr::instance()->_30->sub_7100FF8AC4(0);
        break;
    case BgmCtrlType::_4:
        SoundMgr::instance()->_30->sub_7100FF8684(1);
        SoundMgr::instance()->_30->sub_7100FF8AC4(1);
        break;
    case BgmCtrlType::_5:
        SoundMgr::instance()->_30->sub_7100FF8684(2);
        SoundMgr::instance()->_30->sub_7100FF8AC4(2);
        break;
    case BgmCtrlType::_6:
        SoundMgr::instance()->mDuckingMgr->sub_7101042024(DuckingMgr::DuckerType::cEvtBgmReduce);
        break;
    case BgmCtrlType::_7:
        SoundMgr::instance()->mDuckingMgr->sub_7101042D6C(DuckingMgr::DuckerType::cEvtBgmReduce, false);
        break;
    case BgmCtrlType::_8:
        SoundMgr::instance()->mDuckingMgr->sub_7101042024(DuckingMgr::DuckerType::cEvtBgmMute);
        break;
    case BgmCtrlType::_9:
        SoundMgr::instance()->mDuckingMgr->sub_7101042D6C(DuckingMgr::DuckerType::cEvtBgmMute, false);
        break;
    default:
        break;
    }
    switch (se_type) {
    case SeCtrlType::_1:
        SoundMgr::instance()->mDuckingMgr->sub_7101042024(DuckingMgr::DuckerType::cEvtWorldMute);
        break;
    case SeCtrlType::_2:
        SoundMgr::instance()->mDuckingMgr->sub_7101042D6C(DuckingMgr::DuckerType::cEvtWorldMute, false);
        break;
    case SeCtrlType::_3:
        SoundMgr::instance()->mDuckingMgr->sub_7101042024(DuckingMgr::DuckerType::cEvtEnvReduce);
        break;
    case SeCtrlType::_4:
        SoundMgr::instance()->mDuckingMgr->sub_7101042D6C(DuckingMgr::DuckerType::cEvtEnvReduce, false);
        break;
    case SeCtrlType::_5:
        SoundMgr::instance()->mDuckingMgr->sub_7101042024(DuckingMgr::DuckerType::cTitleMute);
        break;
    default:
        break;
    }
}

void Unk_710103b704::sub_710103BD88(const sead::SafeString& name, bool skip_event_info) {
    if (_5cc) {
        sub_710103BB00(_5d0, _5d4);
        _5cc = 0;
    }
    _5e0.sub_710105AF00(name, skip_event_info);
}

bool Unk_710103b704::isBgmReady() {
    return _5e0.sub_710105B090();
}

void Unk_710103b704::setWorldMuteType(bool movie, const sead::SafeString& type) {
    if (movie)
        _5e0.sub_710105B37C();
    else
        _5e0.sub_710105B394(type);
    _5e0.sub_710105B8EC();
}

void Unk_710103b704::sub_710103BD3C() {
    _5e0._10.stop(1.0f, 0.0f);
    SoundMgr::instance()->mDuckingMgr->sub_7101042D6C(DuckingMgr::DuckerType::cTmlnLoading, false);
    _5d9 = false;
}

// NON_MATCHING: boolean setup differs; zero fade arguments use w1 instead of x1.
void Unk_710103b704::sub_710103C5F4(bool defer_bgm) {
    if (_5d8 || (SoundMgr::instance()->_e4 & ~1) == 2)
        return;
    auto* ducking = SoundMgr::instance()->mDuckingMgr;
    const bool dialog = ducking->mDuckers[DuckingMgr::DuckerType(DuckingMgr::DuckerType::cTalk)].isOnDucking() ||
                        ducking->mDuckers[DuckingMgr::DuckerType(DuckingMgr::DuckerType::cDialog)].isOnDucking();
    auto* bgm = SoundMgr::instance()->_30;
    const bool suspend_bgm = !(bgm->_88 & 1) & !bgm->_78->sub_7101007C14();
    ducking->sub_7101042D6C(DuckingMgr::DuckerType::cEvtBgmMute, suspend_bgm);
    ducking->sub_7101042D6C(DuckingMgr::DuckerType::cEvtBgmReduce, dialog || suspend_bgm);
    ducking->sub_7101042D6C(DuckingMgr::DuckerType::cEvtEnvReduce, dialog);
    ducking->sub_7101042D6C(DuckingMgr::DuckerType::cEvtWorldMute, false);
    ducking->sub_7101042D6C(DuckingMgr::DuckerType::cTitleMute, false);
    ducking->sub_7101042D6C(DuckingMgr::DuckerType::cCustomEvt, false);
    ducking->sub_7101042D6C(DuckingMgr::DuckerType::cCustomEvt2, false);
    ExpressionSoundCtrl::instance()->sub_710104F904();
    ExpressionSoundCtrl::instance()->sub_710104F8C4(false);
    ExpressionSoundCtrl::instance()->sub_710104F920(false);
    if (!bgm->_78->sub_7101007C90()) {
        if (defer_bgm)
            bgm->_88 |= 2;
        else
            bgm->sub_7100FF8780(0);
    }
    if (defer_bgm)
        bgm->_88 |= 4;
    else
        bgm->sub_7100FF88A8(0);
}

bool Unk_710103b704::sub_710103CE1C() {
    return !SoundMgr::instance()->mDuckingMgr->mDuckers[
                DuckingMgr::DuckerType(DuckingMgr::DuckerType::cEventSkip)].sub_710103E368() &&
           !SoundMgr::instance()->mDuckingMgr->mDuckers[
                DuckingMgr::DuckerType(DuckingMgr::DuckerType::cEventSkipBeam)].sub_710103E368();
}

void Unk_710103b704::sub_710103CFE8(int bgm_type, int se_type) {
    _5d0 = bgm_type;
    _5d4 = se_type;
}

void Unk_710103b704::sub_710103CFF4(StartParam& param) {
    StartParam& start = sUnk_7102610958 ? sUnk_7102610960.mParam : param;
    auto* mgr = SoundMgr::instance()->mDuckingMgr;
    if (!mgr->getDucker(DuckingMgr::DuckerType(0x30)).mDucker.isInitialized()) {
        mgr->sub_71010421F0(DuckingMgr::DuckerType(0x30), start);
        return;
    }
    if (!mgr->getDucker(DuckingMgr::DuckerType(0x31)).mDucker.isInitialized())
        mgr->sub_71010421F0(DuckingMgr::DuckerType(0x31), start);
}

}  // namespace ksys::snd

namespace ksys::snd {

// NON_MATCHING: string copies, group operations and the scene-state stores are scheduled differently.
void Unk_710103b704::sub_710103BE18(const sead::SafeString& name,
                                   const sead::SafeString& type, bool mixed, bool start_control,
                                   bool use_barefoot, bool flag) {
    const s32 previous = _5c8;
    ++_5c8;
    if (previous < -1 || _5c8 > 7) {
        _5c8 = previous;
        return;
    }
    _8.getEntry(_5c8)._0.copy(name);
    _8.getEntry(_5c8)._58.copy(type);
    _8.getEntry(_5c8)._b0 = mixed;
    if (mixed) {
        if (start_control)
            _5e0.sub_710105B5D4(name, use_barefoot, flag);
        SoundMgr::instance()->mDuckingMgr->sub_7101042D6C(DuckingMgr::DuckerType(0x1f), false);
    }
    if (_5c8 != 0)
        return;
    if (auto* bgm = sub_7100FFE14C())
        bgm->sub_710102544C(true);
    SoundMgr::instance()->_58->sub_7101055100();
    if (auto* groups = aal::SystemAccessor::getGroupMgr()) {
        if (auto* group = groups->findGroup("NpcVoice")) {
            if (name == "Demo344_1" && type == "Demo344_1") {
                if (auto* sound_group = sead::DynamicCast<aal::SoundGroup>(group)) {
                    for (auto& source : sound_group->getPlayingSoundSources()) {
                        if (source.mSpatialCalculator)
                            source.mSpatialCalculator->detachPositioningInfo();
                    }
                }
            } else {
                group->stopAllSound(0.5f);
            }
            if (name == "Demo346_4") {
                group->allowEmit(sead::BitFlag8(0x20), false);
                _620 = 0;
            }
        }
    }
    _5d0 = mixed ? 0 : 6;
    _5d4 = mixed ? 0 : 3;
    _5cc = 3;
    _5d8 = false;
}

void Unk_710103b704::sub_710103C334(const sead::SafeString& name,
                                   const sead::SafeString& type, bool defer_bgm) {
    if (_5c8 < 0)
        return;
    if (_8.getEntry(_5c8)._b0)
        _5e0.sub_710105B934(_8.getEntry(_5c8)._0, defer_bgm);
    if (auto* groups = aal::SystemAccessor::getGroupMgr()) {
        if (auto* group = groups->findGroup("NpcVoice")) {
            group->allowEmit(sead::BitFlag8(0x20), true);
            _620 = 0;
        }
    }
    if (_5e0._39) {
        if (_8.getEntry(_5c8)._0 != name)
            return;
        if (_8.getEntry(_5c8)._58 != type)
            return;
    }
    if (_5c8 == 0) {
        _5cc = 0;
        SoundMgr::instance()->_58->sub_71010554C8();
        if (auto* bgm = sub_7100FFE14C())
            bgm->sub_710102544C(false);
        sub_710103C5F4(defer_bgm);
    }
    auto& entry = _8.getEntry(_5c8);
    entry._0.clear();
    entry._58.clear();
    entry._b0 = false;
    --_5c8;
}

void Unk_710103b704::sub_710103C7D0() {
    if (_5e0._39) {
        SoundMgr::instance()->mDuckingMgr->sub_7101042024(DuckingMgr::DuckerType(0x22));
        return;
    }
    SoundMgr::instance()->mDuckingMgr->sub_7101042024(DuckingMgr::DuckerType(0x21));
    _5d9 = false;
    if (_5c8 >= 0) {
        const auto& entry = _8.getEntry(_5c8);
        if (entry._b0) {
            const auto& name = entry._0;
            if (name == "Demo155_0" || name == "Demo158_0" || name == "Demo160_0" ||
                name == "Demo162_0" || name == "Demo141_0" || name == "Demo141_1" ||
                name == "Demo141_2" || name == "Demo141_3" || name == "Demo670_0" ||
                name == "Demo670_1" || name == "Demo670_2" || name == "Demo670_3")
                _5d9 = true;
        }
    }
}

}  // namespace ksys::snd
