#include "KingSystem/Sound/sndBgmMgr.h"
#include <math/seadMathCalcCommon.h>
#include <prim/seadScopedLock.h>
#include <xlink2/xlink2Event.h>
#include <xlink2/xlink2ResourceAccessorSLink.h>
#include <xlink2/xlink2UserInstanceSLink.h>
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/Sound/sndFxMgr.h"
#include "KingSystem/Sound/sndMusicInfo.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/World/worldEnvMgr.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/Utils/InitTimeInfo.h"

// The Ganon BGM (Unk_71024fed48): TU 0x7101010a68..0x7101011274 (static initialiser 0x7101011210) in the original.

namespace {
// The TU statics at 0x710260fc60 (static initialiser 0x7101011210).
ksys::util::InitConstants sInitConstants;
ksys::util::InitTimeInfo sInitTimeInfo;
sead::SafeString sStr_GanonBgm = "GanonBgm";
sead::SafeString sStr_GanonBgmFormer = "former";
sead::SafeString sStr_GanonBgmLatter = "latter";
}  // namespace

Unk_71024fed48::Unk_71024fed48(const ksys::snd::BgmInitArg& arg) : Unk_71025ce380(arg) {
    Unk_SpotBgmHandle::init(arg.heap, sStr_GanonBgm, nullptr);
}

Unk_71024fed48::~Unk_71024fed48() = default;

void Unk_71024fed48::sub_7101010B20() {
    if (mState == 1 || mState == 2)
        return;
    mState = 1;
    sub_710101D9D8();
    ksys::snd::ExpressionSoundCtrl::instance()->_294.start();
    if (auto* mgr = ksys::snd::SoundMgr::instance()) {
        if (mgr->_50)
            mgr->_50->_a8 = 1;
    }
}

void Unk_71024fed48::sub_7101010B84() {
    if (mState == 1 || mState == 2)
        return;
    mState = 2;
    sub_710101D9D8();
}

void Unk_71024fed48::sub_7101010C58(f32 fade_sec) {
    sub_710101D9F4(fade_sec);
    mState = mState == 1 ? 3 : mState == 2 ? 4 : 0;
    ksys::snd::ExpressionSoundCtrl::instance()->_294.stop(true);
    if (auto* mgr = ksys::snd::SoundMgr::instance()) {
        if (mgr->_50)
            mgr->_50->_a8 = 0;
    }
}

// 0x710260fbb8: debug flag (never written).
KSYS_VISIBILITY_HIDDEN bool sUnk_710260FBB8;

void Unk_71024fed48::m14(sead::TextWriter& writer) {
    if (!sUnk_710260FBB8)
        return;
    writer.printf("---- 不完全体ガノン戦BGM ----\n");
    writer.printf("処理             :%s\n", mActive ? "有効" : "無効");
    if (State::text(mState))
        writer.printf("状態             :%s\n", State::text(mState));
}

void Unk_71024fed48::hm14() {
    if (mState == 1)
        mEntry = sub_71010209FC(sStr_GanonBgmFormer);
    else if (mState == 2)
        mEntry = sub_71010209FC(sStr_GanonBgmLatter);
}

bool Unk_71024fed48::m10() {
    return mState != 0;
}

void Unk_71024fed48::m12(f32 fade_sec) {
    if (mState == 4)
        mState = 2;
    else if (mState == 3)
        mState = 1;
    else
        return;
    sub_710101D9D8();
}

void Unk_71024fed48::m13(f32 fade_sec) {
    sub_710101D9F4(fade_sec);
    mState = mState == 1 ? 3 : mState == 2 ? 4 : 0;
}

