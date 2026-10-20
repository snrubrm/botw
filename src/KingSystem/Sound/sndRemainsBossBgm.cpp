#include <gfx/seadTextWriter.h>
#include "Game/gameUnkRttiPlaceholders.h"
#include "Game/Actor/aiUnk_7100FFDFDC.h"
#include "KingSystem/Sound/sndBgmMgr.h"
#include "KingSystem/Sound/sndFxMgr.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/System/StageInfo.h"
#include "KingSystem/Utils/InitTimeInfo.h"

// The Remains (Blight Ganon) boss BGM Unk_71024fd448: TU 0x7101000254..0x71010010a4 in the original (static
// initialisers 0x7101000228 before it and 0x71010010a4 at its end).

namespace {
// The TU statics at 0x710260f4a0 (static initialiser 0x71010010a4).
ksys::util::InitConstants sInitConstants;
ksys::util::InitTimeInfo sInitTimeInfo;
sead::SafeString sStr_Boss = "Boss";
sead::SafeString sStr_BossLatter = "Boss_latter";
const char* sRemainsBossBgmNames[] = {"RemainsWindBossBgm", "RemainsFireBossBgm", "RemainsElecBossBgm",
                                      "RemainsWaterBossBgm"};
}  // namespace

// NON_MATCHING: the original has one more (dead) reload of the spilled `type` after the store to mType.
Unk_71024fd448::Unk_71024fd448(const ksys::snd::BgmInitArg& arg) : Unk_71025ce380(arg) {
    auto* heap = arg.heap;
    ksys::snd::RemainsBossBgmType type;
    switch (arg.kind) {
    case ksys::snd::BgmKind::_27:
        type = ksys::snd::RemainsBossBgmType::Wind;
        break;
    case ksys::snd::BgmKind::_28:
        type = ksys::snd::RemainsBossBgmType::Elec;
        break;
    case ksys::snd::BgmKind::_29:
        type = ksys::snd::RemainsBossBgmType::Fire;
        break;
    case ksys::snd::BgmKind::_30:
        type = ksys::snd::RemainsBossBgmType::Water;
        break;
    default:
        return;
    }
    Unk_SpotBgmHandle::init(heap, sRemainsBossBgmNames[type], nullptr);
    mType = type;
}

Unk_71024fd448::~Unk_71024fd448() = default;

void Unk_71024fd448::hm14() {
    if (_190 == 1)
        _198 = sub_71010209FC(sStr_Boss);
    else if (_190 == 2)
        _198 = sub_71010209FC(sStr_BossLatter);
    if (_1a8 > 0.0f && _198 && _198->sub_7100FF6DF4(this))
        _198->mHandle.setLpfScale(_1a8);
}

void Unk_71024fd448::sub_7101000838(f32 value) {
    _1a8 = value;
    if (_198 && _198->sub_7100FF6DF4(this))
        _198->mHandle.setLpfScale(_1a8);
}

void Unk_71024fd448::m5() {
    if (_190)
        _1a0.calc();
}

bool Unk_71024fd448::m10() {
    return _190 != 0;
}

void Unk_71024fd448::m12(f32 fade_sec) {
    if (_190 == 4)
        _190 = 2;
    else if (_190 == 3)
        _190 = 1;
    else
        return;
    sub_710101D9D8();
}

void Unk_71024fd448::sub_71010007B4() {
    sub_710101D9F4(3.0f);
    _190 = _190 == 1 ? 3 : _190 == 2 ? 4 : 0;
    _1a0.~Unk_710103AB10();
    ksys::snd::ExpressionSoundCtrl::instance()->_294.stop(false);
    if (auto* mgr = ksys::snd::SoundMgr::instance()) {
        if (mgr->_50)
            mgr->_50->_a8 = 0;
    }
}

void Unk_71024fd448::sub_7101000514() {
    sub_710101D9F4(1.0f);
    _190 = _190 == 1 ? 3 : _190 == 2 ? 4 : 0;
    _1a0.~Unk_710103AB10();
    ksys::snd::ExpressionSoundCtrl::instance()->_294.stop(true);
    if (auto* mgr = ksys::snd::SoundMgr::instance()) {
        if (mgr->_50)
            mgr->_50->_a8 = 0;
    }
}

// NON_MATCHING: clang unrolls the four-type loop here; the original keeps the rotated loop.
void Unk_71024fd448::sub_71010003A4() {
    if (_190 - 1 < 2)
        return;

    for (s32 type = 0; type != 4; ++type) {
        if (mType.value() == type)
            continue;
        ksys::snd::RemainsBossBgmType bgm_type = ksys::snd::RemainsBossBgmType(type);
        auto* bgm = sub_7100FFE520(&bgm_type);
        if (!bgm)
            continue;
        bgm->sub_710101D9F4(1.0f);
        bgm->_190 = bgm->_190 == 1 ? 3 : bgm->_190 == 2 ? 4 : 0;
        bgm->_1a0.stop();
        ksys::snd::ExpressionSoundCtrl::instance()->_294.stop(true);
        if (auto* mgr = ksys::snd::SoundMgr::instance()) {
            if (mgr->_50)
                mgr->_50->_a8 = 0;
        }
    }

    _190 = 1;
    sub_710101D9D8();
    ksys::snd::ExpressionSoundCtrl::instance()->_294.start();
    if (auto* mgr = ksys::snd::SoundMgr::instance()) {
        if (auto* fx = mgr->_50) {
            s32 mode = 1;
            if (ksys::StageInfo::getCurrentMapName().findIndex("Remains") != -1 && mType.value() < 2)
                mode = 2;
            fx->_a8 = mode;
        }
    }
}

void Unk_71024fd448::sub_7101000598() {
    if (_190 == 1 || _190 == 2)
        return;
    _190 = 2;
    sub_710101D9D8();
    ksys::snd::ExpressionSoundCtrl::instance()->_294.start();
    if (auto* mgr = ksys::snd::SoundMgr::instance()) {
        if (auto* fx = mgr->_50) {
            s32 mode = 1;
            if (ksys::StageInfo::getCurrentMapName().findIndex("Remains") != -1) {
                switch (mType) {
                case ksys::snd::RemainsBossBgmType::Wind:
                case ksys::snd::RemainsBossBgmType::Fire:
                    mode = 2;
                    break;
                default:
                    break;
                }
            }
            fx->_a8 = mode;
        }
    }
}

// NON_MATCHING: the original tail-calls the destructor address 0x710103ab10 (ICF-folded with
// Unk_710103AB10::stop).
void Unk_71024fd448::m13(f32 fade_sec) {
    sub_710101D9F4(fade_sec);
    _190 = _190 == 1 ? 3 : _190 == 2 ? 4 : 0;
    _1a0.~Unk_710103AB10();
}

// 0x710260f3f8: debug flag (never written).
KSYS_VISIBILITY_HIDDEN bool sUnk_710260F3F8;

void Unk_71024fd448::m14(sead::TextWriter& writer) {
    if (!sUnk_710260F3F8)
        return;
    writer.printf("---- カースガノン戦BGM ----\n");
    writer.printf("処理             :%s\n", mActive ? "有効" : "無効");
    writer.printf("状態             :%s\n", State::text(_190) ? State::text(_190) : "不明");
}

