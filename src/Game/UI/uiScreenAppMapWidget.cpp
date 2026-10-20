#include "KingSystem/AOC/aocManager.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUnkSingletons.h"
#include "Game/UI/uiUtils.h"
#include <heap/seadExpHeap.h>
#include <math/seadMathCalcCommon.h>
#include <new>

namespace uking::ui {

// 0x710260b150: the save tracker's progress object (block count at +0x19c, block total at +0x1a0)
struct Unk_710260b150 {
    u8 _0[0x19c];
    /* 0x19c */ u32 _19c;
    /* 0x1a0 */ s32 _1a0;
};
KSYS_VISIBILITY_HIDDEN Unk_710260b150* sUnk_710260b150;

// 0x71009af058
// NON_MATCHING: the original loads the tracker global through its GOT entry (one extra indirection)
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

// 0x71009a9438
bool ScreenAppMapWidget::sub_71009A9438() {
    return mNormalMap._a9a0.isDone() || mNormalMap._a8eb;
}

// 0x71009a995c
void ScreenAppMapWidget::sub_71009A995C() {
    _b34c = 1;
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
// NON_MATCHING: same result; the original keeps the branch (`tbnz` / `ubfx`), ours selects with `csinc`
u8 ScreenAppMapWidget::sub_71009AF178() const {
    if (!(_b4ff & 1))
        return 1;
    return (_b4ff >> 1) & 1;
}

// 0x71009af194
bool ScreenAppMapWidget::sub_71009AF194() const {
    return (_b4ff & 5) == 5;
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

// 0x71009af034
f32 ScreenAppMapWidget::sub_71009AF034() const {
    static const sead::SafeArray<f32, 32> sTable{{0.0625f, 0.25f, 0.5625f, 1.0f, 1.5625f, 2.25f, 3.0625f, 4.0f, 5.0625f,
                                                  6.25f, 7.5625f, 9.0f, 10.5625f, 12.25f, 14.0625f, 16.0f, 17.9375f,
                                                  19.75f, 21.4375f, 23.0f, 24.4375f, 25.75f, 26.9375f, 28.0f,
                                                  28.9375f, 29.75f, 30.4375f, 31.0f, 31.4375f, 31.75f, 31.9375f,
                                                  32.0f}};
    return sTable[_b4fc];
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

KSYS_VISIBILITY_HIDDEN bool sUnk_71025D9610 = false;

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
    _b350 = 2;
    sead::Vector2f target{0.0f, 0.0f};
    _8e0->sub_7100950464(position, &target);

    const sead::Vector2f* center = mSubsys->getVec3868();
    mSubsys->sub_7100966350(target);
    const f32 dx = center->x - target.x;
    const f32 dy = center->y - target.y;
    const f32 distance = sead::Mathf::sqrt(dx * dx + dy * dy);

    _b51c = 0.15f;
    _b520 = distance;
    _b524 = 5.0f;
    _b338 = true;
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
        sUnk_71025D9610 = true;
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

// 0x7100a842e4
Unk_710249d330::~Unk_710249d330() {
    mCells.freeBuffer();
    mFlags.freeBuffer();
    if (mHeap) {
        mHeap->destroy();
        mHeap = nullptr;
    }
    mCount = 0;
}

// 0x7100a862a4
void Unk_710249d330::init(sead::Heap* heap) {
    if (mState != 0)
        return;
    if (mHeap) {
        mCells.freeBuffer();
        mFlags.freeBuffer();
        mHeap->destroy();
        mHeap = nullptr;
        mCount = 0;
    }
    if (auto* cells = new (heap, 4, std::nothrow) u32[0x38400])
        mCells.setBuffer(0x38400, cells);
    if (auto* flags = new (heap, 4, std::nothrow) u8[0x38400])
        mFlags.setBuffer(0x38400, flags);
    mHeap = sead::ExpHeap::create(0x227100, "FootPrintWorkHeap", heap, 8,
                                  sead::Heap::cHeapDirection_Reverse, false);
    mState = 1;
}

// 0x7100a863c4
void Unk_710249d330::initHeap() {
    if (mState != 0)
        return;
    if (mHeap) {
        mHeap->destroy();
        mHeap = nullptr;
        mCount = 0;
    }
    if (mCells.getBufferPtr() && mFlags.getBufferPtr()) {
        mHeap = sead::ExpHeap::create(0x227100, "FootPrintWorkHeap", getHeap(), 8,
                                      sead::Heap::cHeapDirection_Reverse, false);
        mState = 1;
    }
}

// 0x7100a843c0
void Unk_710249d330::step() {
    switch (mState) {
    case 1:
        mState = 2;
        break;
    case 2:
        sub_7100A843F4();
        break;
    case 3:
        mState = 0;
        break;
    default:
        break;
    }
}

// 0x7100a86950
bool Unk_710249d330::isIdle() const {
    return mState == 0;
}

// NON_MATCHING: the original decodes both cell coordinates before the compare and folds them into a ccmp
// pair (660 bytes); clang short-circuits the second decode (636 bytes).
// 0x7100a866bc
void Unk_710249d330::sub_7100A866BC(f32 x, f32 y, bool flag) {
    if (!ksys::aoc::Manager::instance()->hasAoc2())
        return;

    const s32 count = mCount;
    if (count > 0) {
        const u32 last = mCells[count - 1];
        s32 last_x = (last >> 13) & 0x1fff;
        if (last & 0x4000000)
            last_x = -last_x;
        s32 last_y = last & 0xfff;
        if (last & 0x1000)
            last_y = -last_y;
        if (s32(x) == s32(f32(last_x)) && s32(y) == s32(f32(last_y)))
            return;
    }

    const s32 x_i = s32(x);
    const s32 y_i = s32(y);
    if (x_i == 0 && y_i == 0)
        return;
    if (x_i == -0x60 && y_i == 0x140)
        return;

    const s32 x_abs = sead::Mathi::abs(x_i);
    const s32 y_abs = sead::Mathi::abs(y_i);
    const u32 packed_x = (u32(x_abs) & 0x1fff) | (x < 0.0f ? 0x2000 : 0);
    const u32 packed_y = (u32(y_abs) & 0xfff) | (y < 0.0f ? 0x1000 : 0);
    const s32 zone = (y_i + 4000) / 0x96 + ((x_i + 5000) / 0x96) * 0x36;
    if (zone & 0xf000)
        return;
    u32 packed = packed_y | (packed_x << 13);
    if (flag)
        packed |= 0x8000000;
    packed |= u32(zone) << 28;

    if ((u32(count) >> 10) < 0xe1) {
        mFlags[count] = u8(u32(zone) >> 4);
        mCells[mCount] = packed;
        if (mPending)
            return;
        mPending = true;
        return;
    }

    const s32 n = mCells.size() - 0x1c20;
    if (n > 0) {
        for (s32 i = 0; i < n; ++i) {
            mCells[i] = mCells[i + 0x1c20];
            mFlags[i] = mFlags[i + 0x1c20];
        }
    }
    mCount = count - 0x1c20;
    mFlags[mCount] = u8(u32(zone) >> 4);
    const s32 idx = mCount;
    mCount = idx + 1;
    mCells[idx] = packed;
    if (!mPending)
        return;
    mPending = false;
}

}  // namespace uking::ui
