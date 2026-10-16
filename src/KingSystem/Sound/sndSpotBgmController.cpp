#include <aal/aalGroupMgr.h>
#include <aal/aalSystemAccessor.h>
#include <math/seadVector.h>
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Sound/sndBgmMgr.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/Utils/InitTimeInfo.h"

// The TU statics (static initialiser 0x7100ffc100).
namespace {
ksys::util::InitConstants sInitConstants;
ksys::util::InitTimeInfo sInitTimeInfo;
sead::Vector2f sUnk_710260F1F0{860.0f, 480.0f};
}  // namespace

namespace ksys::snd {

Unk_710260f198::Unk_710260f198() = default;

Unk_710260f198::~Unk_710260f198() {
    if (auto* bgm = sub_7100FFE14C())
        bgm->sub_71010255D0();
    if (mBossBgms) {
        delete mBossBgms;
        mBossBgms = nullptr;
    }
}

void Unk_710260f198::m4(sead::Heap* heap) {
    mBossBgms = new (heap, 8) Unk_71024fe958();
    if (mBossBgms)
        mBossBgms->init(heap);
    _8.sub_7100FF75DC(32, heap);
    _8._30 = &_f0;
    _8._38 = &_110;
    _8.sub_7100FF7920(0, heap);
    _8.sub_7100FF7920(1, heap);
    _8.sub_7100FF7920(4, heap);
    _8.sub_7100FF7920(2, heap);
    _8.sub_7100FF7920(5, heap);
    if (auto* group_mgr = aal::SystemAccessor::getGroupMgr())
        mGroup = group_mgr->findGroup("Bgm");
}

// NON_MATCHING: the original passes a 64-bit zero to Unk_SoundMgr30::sub_7100FF8780 (its parameter type is probably
// not s32).
void Unk_710260f198::m5() {
    if (_ec & 4) {
        SoundMgr::instance()->_30->sub_7100FF8780(0);
        _ec &= ~4;
    }
    sub_7100FFB5B0();
    if (!(_ec & 1))
        return;
    if (mBossBgms)
        mBossBgms->sub_710100D694();
    _8.sub_7100FF7698();
    sub_7100FFB7E8();
}

void Unk_710260f198::m6(f32 fade_sec) {
    if (!(_ec & 1)) {
        if (mBossBgms)
            mBossBgms->_8 = true;
        _8.sub_7100FF7830(fade_sec);
        _ec |= 1;
    }
    _ec &= ~4;
}

void Unk_710260f198::m7(f32 fade_sec) {
    if (!(_ec & 1))
        return;
    if (mBossBgms)
        mBossBgms->sub_710100D860();
    _8.sub_7100FF78A8(fade_sec);
    _ec &= ~1;
}

void Unk_710260f198::m9(const Unk_BgmControllerM8Arg& arg) {
    auto* boss_bgms = mBossBgms;
    if (!boss_bgms)
        return;
    boss_bgms->_c = arg._0;
    boss_bgms->_14 = arg._8;
    boss_bgms->_10 = arg._4;
    boss_bgms->_18 = arg._c;
}

void Unk_710260f198::m10() {
    auto* bgm = sead::DynamicCast<Unk_71024fe368>(_8.sub_7100FF7C74(3));
    if (bgm)
        bgm->_224 = true;
}

void Unk_710260f198::sub_7100FFBD44(s32 id, bool use_a0) {
    auto* heap = map::PlacementMgr::instance()->mDynamicHeap;
    if (use_a0) {
        _8.sub_7100FF7920(17, heap);
        if (_a0)
            _a0->sub_710100F798(id);
    } else {
        _8.sub_7100FF7920(16, heap);
        if (_98)
            _98->sub_71010121D8(id);
    }
}

void Unk_710260f198::sub_7100FFBDC0(s32 id, bool use_a0) {
    if (use_a0) {
        if (_a0)
            _a0->sub_710100F860(id);
        _8.sub_7100FF7BE0(17);
    } else {
        if (_98)
            _98->sub_71010122A0(id);
        _8.sub_7100FF7BE0(16);
    }
}

void Unk_710260f198::sub_7100FFBE0C(s32 a, bool b, s32 id, bool use_a0) {
    if (use_a0) {
        if (_a0)
            _a0->sub_710100F900(b, id);
    } else if (_98) {
        _98->sub_7101012340(a, b, id);
    }
}

void Unk_710260f198::sub_7100FFBE38(bool a, s32 id, bool use_a0) {
    if (use_a0) {
        if (_a0)
            _a0->sub_710100F8B0(a, id);
    } else if (_98) {
        _98->sub_71010122F0(a, id);
    }
    if (a && (_ec & 2)) {
        if (!(_ec & 1))
            _ec |= 4;
        _ec &= ~2;
    }
}

void Unk_710260f198::sub_7100FFBBE4(Unk_SpotBgmInstance* instance) {
    if (auto* bgm = sead::DynamicCast<Unk_710260f1a8>(_8.sub_7100FF7C74(5)))
        bgm->sub_71010252C0(instance, _ec & 1);
}

void Unk_710260f198::sub_7100FFBCA0(Unk_SpotBgmInstance* instance) {
    if (auto* bgm = sead::DynamicCast<Unk_710260f1a8>(_8.sub_7100FF7C74(5)))
        bgm->sub_7101025388(instance);
}

void Unk_710260f198::sub_7100FFBEA8(bool value) {
    if (auto* bgm = sead::DynamicCast<Unk_71024fd0a8>(_8.sub_7100FF7C74(4)))
        bgm->_20 = value;
}

}  // namespace ksys::snd
