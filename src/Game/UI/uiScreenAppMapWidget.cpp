#include "KingSystem/AOC/aocManager.h"
#include "Game/UI/uiManager.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/euiLayoutEx.h"
#include "KingSystem/System/Patrol.h"
#include "Game/UI/uiUnkSingletons.h"
#include "Game/Scene/gameStageInfo.h"
#include "Game/AOC/aocHardModeManager.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/GameData/gdtSaveMgr.h"
#include <filedevice/seadFileDeviceMgr.h>
#include "Game/UI/uiUtils.h"
#include <heap/seadExpHeap.h>
#include <math/seadMathCalcCommon.h>
#include <new>
#include <nn/ui2d/Pane.h>
#include <nn/ui2d/Util.h>

namespace uking::ui {

// inline-only in the original; name is a guess (see the declaration)
inline void ScreenAppMapWidget::refreshHomePage() {
    if (auto* home = sead::DynamicCast<ScreenAppHome>(eui::ScreenMgr::instance()->getScreen(ScreenId::AppHome))) {
        home->sub_71009DC99C(false);
        home->x_2();
    }
}

// 0x710260b150: the map footprint pass (see uiScreens.h); the tracker block count / total are at 0x19c / 0x1a0
Unk_710260b150* sUnk_710260b150;

// 0x71009af058
// NON_MATCHING: the only difference is the operand order of the commutative count + pending add.
void ScreenAppMapWidget::sub_71009AF058(s8 count) {
    if (count <= 0)
        return;
    const s32 value = (mFootPrint.mCount + mFootPrint.mPending) / count;
    _b4f8 = s16(value);
    if (sUnk_710260b150 && _b4ac == 3) {
        sUnk_710260b150->_19c = u32(value) & 0xffff;
        sUnk_710260b150->_1a0 = count;
    }
}

// The accessors below read the widget's zoom / cursor state (offsets 0xb4a0-0xb4ff).

// 0x71009a9388
void ScreenAppMapWidget::sub_71009A9388() {
    if (UiSubsys1::instance()->get38f8() == 2 && mFieldPane)
        mFieldPane->SetAlpha(0);
    UiSubsys1::instance()->set3904(false);
    mNormalMap._a8ea = false;
}

// 0x71009a93e0
void ScreenAppMapWidget::sub_71009A93E0() {
    if (UiSubsys1::instance()->get38f8() == 2 && mFieldPane)
        mFieldPane->SetAlpha(0);
    UiSubsys1::instance()->set3904(false);
    mNormalMap._a8ea = false;
}

// 0x71009a9438
bool ScreenAppMapWidget::sub_71009A9438() {
    return mNormalMap._a9a0.isDone() || mNormalMap._a8eb;
}

// NON_MATCHING: the original has two copies of the _850.get38() call (one per branch of the mode test); ours
// merges them.
// 0x71009a947c
void ScreenAppMapWidget::sub_71009A947C() {
    f32 target;
    if (mSubsys->sub_7100965EA8() == 2 && _b34c)
        target = sub_7100965EB0();
    else
        target = mSubsys->_850.get38();
    const f32 height = sub_7100966008()->y;
    f32 value = height / mSubsys->_850.get28();
    const f32 diff = height / target - value;
    sub_7100AA2350(_130, &value, height / target, 0.15f, diff > 0.0f ? diff : -diff, 1.0f);
    mSubsys->_850.set28(height / value);
}

// 0x71009ae1c0
void ScreenAppMapWidget::sub_71009AE1C0() {
    _b4ff |= 1;
    UiSubsys1::instance()->clear38c8();
    refreshHomePage();
}

// 0x71009ae29c
void ScreenAppMapWidget::sub_71009AE29C(bool up) {
    if (up) {
        _b4a4 = 6;
        if (++_b4fa >= 3) {
            _b4fa = 2;
            _b4a4 = 8;
        }
    } else {
        _b4a4 = 7;
        if (--_b4fa < 0) {
            _b4fa = 0;
            _b4a4 = 8;
        }
    }
    refreshHomePage();
}

// 0x71009ae3c8
// NON_MATCHING: same instruction set and size; clang lays the _b4a4 = 4 arm first (tbnz to the _b4a4 = 5
// arm), the original lays the _b4a4 = 5 arm first (tbz to the _b4a4 = 4 arm).
void ScreenAppMapWidget::sub_71009AE3C8() {
    const u8 old = _b4ff;
    _b4ff ^= 1;
    UiSubsys1::instance()->clear38c8();
    if (old & 1) {
        _b4a4 = 5;
        _b4fe = 0;
    } else {
        _b4a4 = 4;
        _b4ff = (_b4ff & 0xf) | 0x40;
        _b4a8 = 0;
        _b4fd = 0;
        sUnk_71025D9610.mUnkFlag = true;
    }
    if (auto* home = sead::DynamicCast<ScreenAppHome>(
            eui::ScreenMgr::instance()->getScreen(ScreenId::AppHome))) {
        home->sub_71009DC99C(false);
        home->x_2();
    }
}

// 0x71009af1ac
void ScreenAppMapWidget::sub_71009AF1AC() {
    _b4ff ^= 8;
    if (_b4ff & 8) {
        UiSubsys1::instance()->set6e4(19);
        refreshHomePage();
        _b4a4 = 17;
    } else {
        UiSubsys1::instance()->set6e4(0);
        refreshHomePage();
        _b4a4 = 16;
    }
}

// 0x71009a98a4: stores the map scale for `level`, saves it as the App_Map_Scale game data flag,
// updates the map view position and marks the end of the zoom-out animation.
void ScreenAppMapWidget::sub_71009A98A4(s32 level) {
    const f32 scale = sub_7100965960(level);
    mSubsys->_850.set38(scale);
    ksys::gdt::Manager::instance()->setF32(scale, sUnk_71025D9610.mAppMapScale);
    mSubsys->set898(level);
    sead::Vector2f position;
    UiSubsys1::instance()->sub_7100965EEC(scale, &position);
    mSubsys->_850.set40(position);
    mSubsys->set3884(false);
    if (mSubsys->is898Zero())
        _b528 = true;
}

// 0x71009a995c
void ScreenAppMapWidget::sub_71009A995C() {
    _b34c = 1;
}

// 0x71009a92c0 (slot 34): removes the child panes of every visible map entry and marks the widget ready.
void ScreenAppMapWidget::m34() {
    for (s32 i = 0; i < 120; ++i) {
        if (!mNormalMap.mEntries[i]._20)
            continue;
        nn::ui2d::Pane* pane = mNormalMap._a9f0 ? mNormalMap._a9f0[i] : nullptr;
        if (mNormalMap._a9e0)
            mNormalMap._a9e0->RemoveChild(pane);
        pane = mNormalMap._a9f0 ? mNormalMap._a9f0[i + 120] : nullptr;
        if (mNormalMap._a9e8)
            mNormalMap._a9e8->RemoveChild(pane);
    }
    _8e8 = true;
}

// 0x71009a8d20 (slot 25): tracks whether the map is at its minimum scale and steps the field pane's alpha.
void ScreenAppMapWidget::m25() {
    if (_b528) {
        const f32 scale = mSubsys->_850.get28();
        const s32 index = mSubsys->_850.get48();
        const f32 level = returnFalse();
        const bool scale_changed =
            scale != sub_7100965960(s32(level)) && f32(index) == level;
        if (!scale_changed)
            _b528 = false;
    }
    mNormalMap._a8e8 = !_b528;
    sub_71009A8E54();
    mNormalMap.sub_71009A6774();
    dlcHeroPathStuff(this);
    if (mNormalMap._a8ea)
        UiSubsys1::instance()->set3904(true);
    if (UiSubsys1::instance()->get3904()) {
        if (mFieldPane) {
            const u8 alpha = mFieldPane->GetAlpha();
            if (alpha != 0xff) {
                const u32 value = alpha + UiSubsys1::instance()->get3905();
                const u8 new_alpha = u8(value < 0xff ? value : 0xff);
                mFieldPane->SetAlpha(new_alpha);
            }
        }
    }
    _b33c = 0;
    _b34c = 0;
}

// 0x71009a99f0: applies the map widget's scale level to the map view parameters
void ScreenAppMapWidget::sub_71009A99F0(s32 level) {
    mSubsys->_850.get28();
    const f32 scale = sub_7100965960(level);
    mSubsys->_850.set38(scale);
    mSubsys->set898(level);
}

// 0x71009a9a38 (placeholder name): applies the scale level to both the map view scale and its raw value
void ScreenAppMapWidget::sub_71009A9A38(s32 level) {
    mSubsys->_850.get28();
    const f32 scale = sub_7100965960(level);
    mSubsys->_850.set28(scale);
    mSubsys->_850.set38(scale);
    mSubsys->set898(level);
}

// 0x71009af344 (placeholder name): queues the current area's first tile bank
void ScreenAppMapWidget::sub_71009AF344() {
    mNormalMap.sub_71009A80D0(0, mNormalMap._8->_128);
}

// 0x71009af35c
void ScreenAppMapWidget::sub_71009AF35C() {
    mNormalMap.sub_71009A7FA4();
}

// 0x71009af364 (placeholder name): queues the current area's second tile bank
void ScreenAppMapWidget::sub_71009AF364() {
    mNormalMap.sub_71009A80D0(1, mNormalMap._8->_128);
}

// 0x71009aef7c
s32 ScreenAppMapWidget::sub_71009AEF7C() const {
    return _b4a0;
}

// 0x71009aefec
sead::Vector2f ScreenAppMapWidget::sub_71009AEFEC() const {
    return {(_b4b8 + _b4b8) * _b4e8 + _b4e0, _b4bc * -2.0f * _b4e8 + _b4e4};
}

// 0x71009af0b4
bool ScreenAppMapWidget::sub_71009AF0B4() const {
    return (_b4ff >> 4) & 1;
}

// 0x71009af0c4
bool ScreenAppMapWidget::sub_71009AF0C4() const {
    return _b4a8 == 1;
}

// 0x71009af0d8
bool ScreenAppMapWidget::sub_71009AF0D8() const {
    return _b4a8 == 2;
}

// 0x71009af0ec
bool ScreenAppMapWidget::sub_71009AF0EC() const {
    return (_b4ff >> 5) & 1;
}

// 0x71009af0fc
bool ScreenAppMapWidget::sub_71009AF0FC() const {
    return _b4fe > 0;
}

// 0x71009af110
bool ScreenAppMapWidget::sub_71009AF110() const {
    return s8(_b4ff) < 0;
}

// 0x71009af124
void ScreenAppMapWidget::sub_71009AF124(sead::Vector2f* out) const {
    out->x = (_b4b0 + _b4b0) * _b4e8 + _b4e0;
    out->y = _b4b4 * -2.0f * _b4e8 + _b4e4;
}

// 0x71009af178
bool ScreenAppMapWidget::sub_71009AF178() const {
    if (!(_b4ff & 1))
        return 1;
    return (_b4ff >> 1) & 1;
}

// 0x71009af194
bool ScreenAppMapWidget::sub_71009AF194() const {
    return (_b4ff & 5) == 5;
}

// 0x71009a967c
// NON_MATCHING: the original loads _128 after getVec3870 (argument evaluation order)
void ScreenAppMapWidget::sub_71009A967C() {
    UiSubsys1::instance()->clear3864();
    if (_b350 == 1)
        sub_71009A9B8C();
    sead::Vector2f pos = *mSubsys->getVec3868();
    sub_7100AA21F4(_128, &pos, *mSubsys->getVec3870(), _b51c, _b520, _b524);
    mSubsys->sub_7100966D0C(pos);
}

// 0x71009a9cf8
// NON_MATCHING: see sub_71009A9DBC
void ScreenAppMapWidget::sub_71009A9CF8(const sead::Vector3f& position) {
    _b350 = 2;
    sub_71009A9DBC(position);
}

// 0x71009a9dbc
// NON_MATCHING: the original copies the target into a second stack slot (64-bit copy) after getVec3868
void ScreenAppMapWidget::sub_71009A9DBC(const sead::Vector3f& position) {
    sead::Vector2f target{0.0f, 0.0f};
    _8e0->sub_7100950464(position, &target);

    const sead::Vector2f center = *mSubsys->getVec3868();
    mSubsys->sub_7100966350(target);
    const f32 dx = center.x - target.x;
    const f32 dy = center.y - target.y;
    const f32 distance = sead::Mathf::sqrt(dx * dx + dy * dy);

    _b51c = 0.15f;
    _b520 = distance;
    _b524 = 5.0f;
    _b338 = true;
}

// 0x71009a970c
// NON_MATCHING: register allocation (the original keeps &mSubsys in a register for every access)
void ScreenAppMapWidget::sub_71009A970C() {
    UiSubsys1::instance()->clear3864();
    if (_b338) {
        UiSubsys1::instance()->sub_71009663D4();
        mSubsys->set3884(false);
    }
    if (mSubsys->get3884())
        return;

    sead::Vector2f pos = *mSubsys->_850.get30();
    const sead::Vector2f* target = mSubsys->_850.get40();
    const f32 dx = pos.x - target->x;
    const f32 dy = pos.y - target->y;
    const f32 distance = sead::Mathf::sqrt(dx * dx + dy * dy);
    const bool arrived = sub_7100AA21F4(_128, &pos, *target, 0.15f, distance, 1.0f);
    mSubsys->set3884(arrived);
    if (!arrived)
        mSubsys->set880(pos);
}

// 0x71009a9820
void ScreenAppMapWidget::sub_71009A9820() {
    const s32 level = mSubsys->_850.get48();
    if (mSubsys->is898EqualTo3()) {
        _128->invokeSoundLink2Event_("mc_mapZoom_in_limit");
    } else if (mSubsys->is898Below3()) {
        sub_71009A98A4(level + 1);
        _128->invokeSoundLink2Event_("mc_mapZoom_in");
    }
}

// 0x71009a996c
void ScreenAppMapWidget::sub_71009A996C() {
    const s32 level = mSubsys->_850.get48();
    if (mSubsys->is898Zero()) {
        _128->invokeSoundLink2Event_("mc_mapZoom_out_limit");
    } else if (mSubsys->is898Positive()) {
        sub_71009A98A4(level - 1);
        _128->invokeSoundLink2Event_("mc_mapZoom_out");
    }
}

// 0x71009a9a9c
void ScreenAppMapWidget::sub_71009A9A9C(s32 index) {
    const s32 level = sub_71009661BC(index);
    mSubsys->_850.get28();
    const f32 scale = sub_7100965960(level);
    mSubsys->_850.set28(scale);
    mSubsys->_850.set38(scale);
    mSubsys->set898(level);
}

// 0x71009a9b08 (placeholder name): sets the map view's scale and its second scale from `value`
void ScreenAppMapWidget::sub_71009A9B08(f32 value) {
    mSubsys->_850.set2c(value);
    mSubsys->_850.set3c(value);
}

// 0x71009a9b48
void ScreenAppMapWidget::sub_71009A9B48() {
    UiSubsys1::instance()->sub_7100966894();
    _b350 = 0;
}

// 0x71009a9b7c
void ScreenAppMapWidget::sub_71009A9B7C() {
    _b350 = 1;
    sub_71009A9B8C();
}

// 0x71009a9b8c (placeholder name): starts the map view move in mode 1. Picks the target position from the map
// marker (or the mode's own marker position), centres it, then stores the move rate / duration from the TU's
// static block and the distance from the centred position.
// NON_MATCHING: the mode tests are 5..6 / (7 or <= 4) in both, but clang canonicalises ours as `cmp #1; b.hi` and
// `ccmp #4, #4, ne; b.gt` where the original has `cmp #2; b.hs` and `ccmp #4, #0, ne; b.hi`; ours also keeps
// `&mSubsys` in x20, which shifts the two rate registers from w21/w20 to w22/w21 (everything else matches).
void ScreenAppMapWidget::sub_71009A9B8C() {
    if (ksys::Patrol::instance() && ksys::Patrol::instance()->mField0 &&
        UiSubsys1::instance()->is848Zero())
        return;
    if (!_b33a)
        return;

    sead::Vector3f position{0.0f, 0.0f, 0.0f};
    const s32 mode = Manager::instance()->_64c38;
    if (mode == 5 || mode == 6) {
        mSubsys->sub_7100961CD4(&position);
    } else if (mode == 7 || mode < 5) {
        position = *mSubsys->getMapMarkerPosition();
    }

    sead::Vector2f target{0.0f, 0.0f};
    const f32 rate = sUnk_71025D9610.mViewMoveRate;
    const f32 duration = sUnk_71025D9610.mViewMoveDuration;
    _8e0->sub_7100950464(position, &target);
    const sead::Vector2f center = *mSubsys->getVec3868();
    const sead::Vector2f clamped = target;
    mSubsys->sub_7100966350(clamped);
    const f32 dx = center.x - clamped.x;
    const f32 dy = center.y - clamped.y;
    const f32 distance = sead::Mathf::sqrt(dx * dx + dy * dy);
    _b51c = rate;
    _b520 = distance;
    _b524 = duration;
    _b338 = true;
}

// 0x71009a9e74
void ScreenAppMapWidget::sub_71009A9E74(const sead::Vector3f* pos) {
    _b350 = 2;
    UiSubsys1::instance()->sub_7100966684(pos);
}

// NON_MATCHING: register allocation only (the result is copied through the stack in the original; ours forwards
// the last two values to the output directly).
// 0x71009a9e90
void ScreenAppMapWidget::sub_71009A9E90(const sead::Vector3f& position, sead::Vector2f* result) {
    const sead::Vector2f* factor = _8e0->get60();
    sead::Vector2f pos = sead::Vector2f::zero;
    pos.x = factor->x * position.x;
    pos.y = -(factor->y * position.z);
    sub_7100AA0BB0(&pos, mSubsys->_850.get2c());
    const f32 scale = mSubsys->_850.get28();
    pos.x *= scale;
    pos.y *= scale;
    const sead::Vector2f* offset = mSubsys->_850.get20();
    pos.x += offset->x;
    pos.y += offset->y;
    *result = pos;
}

// NON_MATCHING: register allocation only (the offset and scale-factor registers are swapped and the y offset load
// is hoisted).
// 0x71009a9f4c
void ScreenAppMapWidget::sub_71009A9F4C(const sead::Vector2f& position, sead::Vector2f* result) {
    sead::Vector2f pos = position;
    sub_7100AA0BB0(&pos, -mSubsys->_850.get2c());
    const f32 scale = mSubsys->_850.get28();
    const sead::Vector2f offset = *mSubsys->_850.get30();
    pos.x -= scale * offset.x;
    pos.y -= scale * offset.y;
    const sead::Vector2f factor = *_8e0->get60();
    const f32 inv_scale = 1.0f / scale;
    result->set(inv_scale * (pos.x / factor.x), -((pos.y / factor.y) * inv_scale));
}

// 0x71009aa004
void ScreenAppMapWidget::sub_71009AA004() {
    if (ksys::aoc::Manager::instance()->getVersion() >= 0x200)
        sub_71009AA024();
}

// 0x71009aa024
// NON_MATCHING: same instructions, but clang tail-duplicates the manager/null/_b4ac epilogue into every arm
// (and hoists the manager's address into a callee-saved register); the original keeps one epilogue.
void ScreenAppMapWidget::sub_71009AA024() {
    if (ksys::aoc::Manager::instance()->getVersion() < 0x200)
        return;
    if (_b4fe > 0)
        --_b4fe;
    if (UiSubsys1::instance()->is848EqualTo1()) {
        if (_b4a0 == 0) {
            if (_b4ac == 3) {
                _b4ac = 4;
                _b4a0 = 1;
            } else if (_b4ff) {
                _b4ff = 0;
            }
        } else if (_b4a0 == 1) {
            sub_71009AA17C();
        } else if (_b4a0 == 2) {
            sub_71009AA344();
        } else if (_b4a0 == 3) {
            sub_71009ADEF0();
        }
    } else {
        if (_b4a0 == 0) {
            if (_b4ac == 3) {
                _b4ac = 4;
                _b4a0 = 1;
            } else if (_b4ff) {
                _b4ff = 0;
            }
        } else if (_b4a0 == 1) {
            sub_71009AA17C();
        } else {
            _b4a0 = 0;
        }
    }
    auto* mgr = ksys::aoc::Manager::instance();
    if (!mgr)
        return;
    if (_b4ac != 3)
        return;
    mgr->sub_7100F37864();
}

// 0x71009af034
f32 ScreenAppMapWidget::sub_71009AF034() const {
    static const sead::SafeArray<f32, 32> sTable{{0.0625f, 0.25f, 0.5625f, 1.0f, 1.5625f, 2.25f, 3.0625f, 4.0f, 5.0625f,
                                                  6.25f, 7.5625f, 9.0f, 10.5625f, 12.25f, 14.0625f, 16.0f, 17.9375f,
                                                  19.75f, 21.4375f, 23.0f, 24.4375f, 25.75f, 26.9375f, 28.0f,
                                                  28.9375f, 29.75f, 30.4375f, 31.0f, 31.4375f, 31.75f, 31.9375f,
                                                  32.0f}};
    return sTable[_b4fc];
}

// NON_MATCHING: the add operands are swapped (as in sub_71009AEF88) and the original keeps the redundant `last >= 0`
// test that ours folds into the clamp.
// 0x71009aeef0
void ScreenAppMapWidget::sub_71009AEEF0() {
    const s32 count = mFootPrint.mCount + mFootPrint.mPending;
    const s32 last = count - 1 < 0 ? 0 : count - 1;
    _b4ec = last;
    _b4f0 = last;
    if (last >= 0 && last < count) {
        const u32 packed = mFootPrint.mCells[last];
        s32 x = (packed >> 13) & 0x1fff;
        if (packed & 0x4000000)
            x = -x;
        s32 y = packed & 0xfff;
        if (packed & 0x1000)
            y = -y;
        _b4b8 = f32(x);
        _b4bc = f32(y);
    }
}

// NON_MATCHING: the original adds `_b388 + _b499` as `add w8, w8, w9`; ours emits the operands swapped (`add w8, w9, w8`)
// 0x71009aef88
void ScreenAppMapWidget::sub_71009AEF88() {
    _b4ec = 0;
    _b4f0 = 0;
    if (mFootPrint.mCount + mFootPrint.mPending >= 1) {
        const u32 packed = *mFootPrint.mCells.getBufferPtr();
        s32 x = (packed >> 13) & 0x1fff;
        if (packed & 0x4000000)
            x = -x;
        s32 y = packed & 0xfff;
        if (packed & 0x1000)
            y = -y;
        _b4b8 = f32(x);
        _b4bc = f32(y);
    }
}

// The TU's static block: the map display mode flag and the "App_Map_Scale" game data flag. The original
// TU also merges its remaining statics into this block; they are not modelled yet.
KSYS_VISIBILITY_HIDDEN Unk_71025D9610 sUnk_71025D9610 = {false, {}, 0.15f, 5.0f, {}, "App_Map_Scale", {}, {}};

// NON_MATCHING: same work; the original passes a copy of the target vector to sub_7100966350 (ours passes the local
// itself) and adds _b388 + _b499 in the other operand order.
// 0x71009adef0
void ScreenAppMapWidget::sub_71009ADEF0() {
    f32 x = 0.0f;
    f32 y = 0.0f;
    if (mFootPrint.mCount + mFootPrint.mPending >= 1) {
        const u32 packed = *mFootPrint.mCells.getBufferPtr();
        s32 px = (packed >> 13) & 0x1fff;
        if (packed & 0x4000000)
            px = -px;
        s32 py = packed & 0xfff;
        if (packed & 0x1000)
            py = -py;
        x = f32(px);
        y = f32(py);
    }

    const sead::Vector3f position(x, 0.0f, y);
    sub_71009A9CF8(position);
    if (_b4fc > 0) {
        --_b4fc;
    } else {
        _b4fc = 0x20;
        setMode(2);
    }
}

// 0x71009ae04c
void ScreenAppMapWidget::setMode(s32 mode) {
    _b4a0 = mode;

    if (auto* home = sead::DynamicCast<ScreenAppHome>(
            eui::ScreenMgr::instance()->getScreen(ScreenId::AppHome))) {
        home->sub_71009DC99C(false);
        home->x_2();
    }

    if (UiSubsys1::instance()->get38b8())
        return;

    switch (mode) {
    case 0:
        UiSubsys1::instance()->set38c8();
        _b4ff &= 0xf;
        _b4a8 = 0;
        _b4fd = 0;
        sUnk_71025D9610.mUnkFlag = true;
        break;
    case 1:
        UiSubsys1::instance()->clear38c8();
        _b4ff &= ~1;
        _b4ac = 0;
        break;
    case 2:
        UiSubsys1::instance()->clear38c8();
        _b4ff &= ~1;
        break;
    case 3:
        UiSubsys1::instance()->clear38c8();
        _b4ff &= ~1;
        break;
    }
}

// 0x71009a878c (slot 24): binds the map subsystem, creates the map animators and panes and the footprint data
// NON_MATCHING: the instructions agree except for (1) the last-cell clamp, where clang folds ours to
// `sub / bic / cmp / b.ge` but the original has `subs / csel / tbnz / cmp / b.le` (the redundant `last >= 0`
// test clang drops), (2) the commutative `count + pending` add operands, and (3) the old-version arm, which the
// original places after the epilogue and tail-calls while ours shares the epilogue.
void ScreenAppMapWidget::m24(sead::Heap* heap) {
    mSubsys = UiSubsys1::instance();
    _8e0 = mSubsys->sub_7100965E58();
    sub_71009A89C0();

    _8c8 = mLayout->createAnimatorAuto(sUnk_71025D9610.mAnimatorNames[0].cstr(), false);
    _8d0 = mLayout->createAnimatorAuto(sUnk_71025D9610.mAnimatorNames[1].cstr(), false);

    nn::ui2d::Pane* mapPane = mLayout->mPane->FindPaneByName("N_Map_00", true);
    nn::ui2d::Pane* bgPane = mLayout->mPane->FindPaneByName("N_MapBG_00", true);

    Unk_7102479fb0 arg;
    arg._8 = _138;
    arg._10 = mapPane;
    arg._18 = bgPane;
    arg._20 = mMapPanes;
    mNormalMap.sub_71009A5CFC(arg, heap);

    _130 = _128;
    if (ksys::aoc::Manager::instance()->getVersion() >= 0x200) {
        mFootPrint.init(heap);
        do {
            mFootPrint.step();
        } while (!mFootPrint.isIdle());

        _b4a0 = 0;
        const s32 count = mFootPrint.mCount + mFootPrint.mPending;
        const s32 last = count - 1 < 0 ? 0 : count - 1;
        _b4ec = last;
        _b4f0 = last;
        if (last >= 0 && last < count) {
            const u32 packed = mFootPrint.mCells[last];
            s32 x = (packed >> 13) & 0x1fff;
            if (packed & 0x4000000)
                x = -x;
            s32 y = packed & 0xfff;
            if (packed & 0x1000)
                y = -y;
            _b4b8 = f32(x);
            _b4bc = f32(y);
        }
    } else {
        mFootPrint.sub_7100A86960(heap);
    }
}

// 0x71009a8be4
Unk_7102479fb0::~Unk_7102479fb0() = default;

// 0x71009a8c20 (slot 17): re-initialises the footprint heap on the saved track data after a load, unless the save
// system has bit 0x20 of _1a50 set, and selects the last saved cell.
// NON_MATCHING: the last-cell clamp / add / index lowering is the same as m24 (sub/bic vs subs/csel, commutative
// count + pending operand order, uxtw vs sxtw).
void ScreenAppMapWidget::m17() {
    if (ksys::aoc::Manager::instance()->getVersion() < 0x200)
        return;
    if (SaveSystem::instance()->_1a50 & 0x20)
        return;

    mFootPrint.initHeap();
    do {
        mFootPrint.step();
    } while (!mFootPrint.isIdle());

    _b4a0 = 0;
    const s32 count = mFootPrint.mCount + mFootPrint.mPending;
    const s32 last = count - 1 < 0 ? 0 : count - 1;
    _b4ec = last;
    _b4f0 = last;
    if (last >= 0 && last < count) {
        const u32 packed = mFootPrint.mCells[last];
        s32 x = (packed >> 13) & 0x1fff;
        if (packed & 0x4000000)
            x = -x;
        s32 y = packed & 0xfff;
        if (packed & 0x1000)
            y = -y;
        _b4b8 = f32(x);
        _b4bc = f32(y);
    }
}

// 0x71009a8be8
void ScreenAppMapWidget::m14() {
    for (s32 i = 120; i < 240; ++i)
        mNormalMap.mTiles[i].mTexture.mState = 1;
    mNormalMap._a9a0.reset();
}

// 0x71009a9380
void ScreenAppMapWidget::m21() {
    mNormalMap.sub_71009A6F34();
}

// 0x71009a9280
void ScreenAppMapWidget::m31() {
    UiSubsys1::instance()->sub_710095B530();
    if (_8e8)
        mNormalMap.sub_71009A63F4();
    _8e8 = false;
}

// 0x71009af37c
u8 ScreenAppMapWidget::sub_71009AF37C() const {
    return mNormalMap._a8eb;
}

ScreenAppMapWidget::~ScreenAppMapWidget() = default;


// 0x71009aeccc
void ScreenAppMapWidget::sub_71009AECCC() {
    if (ksys::aoc::Manager::instance()->hasAoc2()) {
        if (uking::StageInfo::getCurrentMapType() == "MainField") {
            sead::Vector3f pos = {0.0f, 0.0f, 0.0f};
            sub_7100A9B800(&pos);
            mFootPrint.sub_7100A86468(pos.x, pos.z, false);
        } else if (uking::StageInfo::getCurrentMapType() == "MainFieldDungeon") {
            sead::Vector3f pos = {0.0f, 0.0f, 0.0f};
            mSubsys->sub_7100961CD4(&pos);
            mFootPrint.sub_7100A866BC(pos.x, pos.z, false);
        } else {
            sead::Vector3f pos = {0.0f, 0.0f, 0.0f};
            mSubsys->sub_7100961CD4(&pos);
            mFootPrint.sub_7100A86468(pos.x, pos.z, false);
        }
        _b4fb = 0;
        const s32 count = mFootPrint.mCount + mFootPrint.mPending;
        s32 idx = count - 1;
        if (idx < 0)
            idx = 0;
        _b4ec = u32(idx);
        _b4f0 = u32(idx);
        if (idx >= 0 && count > idx) {
            const u32 cell = mFootPrint.mCells[idx];
            s32 x = (cell >> 13) & 0x1fff;
            if (cell & 0x4000000)
                x = -x;
            s32 y = cell & 0xfff;
            if (cell & 0x1000)
                y = -y;
            _b4b8 = f32(x);
            _b4bc = f32(y);
        }
    }
    _b4a4 = -1;
}

}  // namespace uking::ui

namespace nn::font {

// 0x71009af838: the out-of-line DynamicCast<eui::PictureEx>(Pane*) instantiation of this TU.
template eui::PictureEx* DynamicCast<eui::PictureEx, nn::ui2d::Pane>(nn::ui2d::Pane*);

}  // namespace nn::font
