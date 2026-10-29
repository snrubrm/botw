#include "Game/UI/uiNormalMap.h"
#include "Game/UI/uiManager.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUtils.h"
#include "Game/UI/euiScreen.h"
#include <math/seadMathCalcCommon.h>
#include <nn/ui2d/Pane.h>
#include <nn/ui2d/Material.h>
#include <gfx/seadGraphics.h>
#include "KingSystem/Resource/resHandle.h"

namespace uking::ui {

// 0x71009a4d24
Unk_7102479bb0::~Unk_7102479bb0() = default;

// 0x71009a4d2c
Unk_7102479bd0::~Unk_7102479bd0() {
    if (mHandle->requestedLoad())
        mHandle->requestUnload2();
    if (mHandle) {
        delete mHandle;
        mHandle = nullptr;
    }
}

// 0x71009a50a4
Unk_7102479bf0::~Unk_7102479bf0() = default;

// 0x71009a524c (placeholder name): fades the tile's pane in or out depending on its texture state
void Unk_7102479bf0::sub_71009A524C() {
    auto* pane = mPane;
    if (!pane || mType == 1)
        return;
    _89 = _88;
    _8b = _8a;
    if (mType != 0) {
        _8c = 1;
    } else if (!mMapEntry->_20) {
        _8c = 3;
    } else {
        switch (mTexture.mState) {
        case 0:
        case 1:
        case 2:
        case 3:
            _8c = 2;
            break;
        case 4:
            _8c = 0;
            break;
        case 6:
            _8c = 3;
            break;
        default:
            break;
        }
    }
    switch (_8c) {
    case 0:
        if (pane->GetAlpha() != 0xff)
            pane->SetAlpha(u8(sead::Mathi::min(pane->GetAlpha() + 30, 0xff)));
        break;
    case 1:
        pane->SetAlpha(0xff);
        break;
    case 2:
        if (pane->GetAlpha() != 0)
            pane->SetAlpha(u8(sead::Mathi::max(pane->GetAlpha() - 30, 0)));
        break;
    case 3:
        pane->SetAlpha(0);
        break;
    }
    const u8 alpha = mPane->GetAlpha();
    _8a = alpha == 0;
    _88 = alpha == 0xff;
}

// 0x71009a5bc8
Unk_7102479c10::~Unk_7102479c10() = default;

// 0x71009a829c
bool Unk_7102479c10::sub_71009A829C() const {
    return _a8e9;
}

// 0x71009a82a8
bool Unk_7102479c10::sub_71009A82A8() const {
    return _a8ea;
}

// 0x71009a61dc
// NON_MATCHING: the store of value.x is scheduled after the second division in the original
void Unk_7102479c10::sub_71009A61DC() {
    if (!_a9f0 || !_10)
        return;
    auto* pane = _a9f0[0];
    if (!pane)
        return;
    const f32 width = pane->GetSize().width;
    const f32 height = pane->GetSize().height;
    _10->set68(width, height);
    sead::Vector2f value(width * 12.0f, height * 10.0f);
    _10->set50(value);
    value.x = width * 10.0f;
    value.y = height * 8.0f;
    _10->set58(value);
    _10->sub_7100950408();
    value.set(0.0f, 0.0f);
    const sead::Vector2f range = *_10->get58();
    value.x = range.x / 10000.0f;
    value.y = range.y / 8000.0f;
    _10->set60(value);
}

// 0x71009a63f4 (placeholder name): keeps each entry's previous flag, then re-parents the visible
// entries' two panes
void Unk_7102479c10::sub_71009A63F4() {
    sub_71009A64E0();
    for (s32 i = 0; i < 120; ++i)
        mEntries[i]._21 = mEntries[i]._20;
    sub_71009A6FF4();
    sub_71009A75AC();
    for (s32 i = 0; i < 120; ++i) {
        if (!mEntries[i]._20)
            continue;
        auto* child = _a9f0 ? _a9f0[i] : nullptr;
        if (_a9e0)
            _a9e0->AppendChild(child);
        child = _a9f0 ? _a9f0[i + 120] : nullptr;
        if (_a9e8)
            _a9e8->AppendChild(child);
    }
}

// 0x71009a6f34
void Unk_7102479c10::sub_71009A6F34() {
    for (s32 i = 0; i < 240; ++i) {
        auto& tile = mTiles[i];
        auto& texture = tile.mTexture;
        if (texture.mMaterial) {
            sead::Graphics::instance()->lockDrawContext();
            texture.mMaterial->GetTexMapArray()[0].ReplaceTextureInfo(&_a8f0);
            sead::Graphics::instance()->unlockDrawContext();
            if (texture.mHandle) {
                if (texture.mHandle->requestedLoad())
                    texture.mHandle->requestUnload2();
                texture.mIndex = -1;
            }
            texture.mPath.clear();
            texture.mState = 6;
        }
        tile.sub_71009A524C();
    }
}

// 0x71009a55a0
// NON_MATCHING: conditional path-level selection uses csel instead of the original branches.
void Unk_7102479bf0::sub_71009A55A0(u32 level) {
    if (mTexture.mHandle) {
        if (mTexture.mHandle->getResource()) {
            mTexture.mState = 3;
            return;
        }
        if (mTexture.mHandle && !mTexture.mHandle->checkLoadStatus())
            return;
    }
    mTexture.mState = 1;
    sead::FixedSafeString<64> path;
    sub_71009A5670(mMapEntry, mType != 0 ? 3 : level, &path);
}

// 0x71009a64e0, 660 B. Receiver already proven by current member declaration.
void Unk_7102479c10::sub_71009A64E0() {
    u32 seen[4]{};
    for (s32 i = 0; i < 15; ++i) {
        MainFieldArea area = Manager::instance()->sub_7100A7F2B0(i);
        for (const auto& tile : area) {
            if (u32(tile.mIndex) < 120)
                seen[u32(tile.mIndex) >> 5] |= 1u << (u32(tile.mIndex) & 31);
        }
    }
    for (s32 i = 0; i < 120; ++i) {
        if (seen[i >> 5] & (1u << (i & 31)))
            mTiles[i].mTexture.mState = 0;
    }
}

// 0x71009a7cf0
// NON_MATCHING: register allocation differs in the two-bank texture state loop.
void Unk_7102479c10::sub_71009A7CF0() {
    u32 seen[4]{};
    for (s32 i = 0; i < 15; ++i) {
        MainFieldArea area = Manager::instance()->sub_7100A7F2B0(i);
        for (const auto& tile : area) {
            if (u32(tile.mIndex) < 120)
                seen[u32(tile.mIndex) >> 5] |= 1u << (u32(tile.mIndex) & 31);
        }
    }
    for (s32 i = 0; i < 120; ++i) {
        if (seen[i >> 5] & (1u << (i & 31))) {
            mTiles[i].mTexture.mState = 0;
            mTiles[i + 120].mTexture.mState = 1;
        }
    }
    _a9a0.reset();
}

// 0x71009a80d0
// NON_MATCHING: mode branches and the second-bank bounds check are arranged differently.
void Unk_7102479c10::sub_71009A80D0(s32 mode, s32 area_index) {
    MainFieldArea area = Manager::instance()->sub_7100A7F2B0(area_index);
    if (mode == 0) {
        for (const auto& tile : area) {
            if (u32(tile.mIndex) < 120)
                mTiles[tile.mIndex].mTexture.mState = 0;
        }
    } else if (mode == 1) {
        for (const auto& tile : area) {
            if (u32(tile.mIndex) < 120)
                mTiles[tile.mIndex + 120].mTexture.mState = 1;
        }
        _a9a0.reset();
    }
}

// 0x71009a82b4 (placeholder name): draws `bounds` on the map screen, insetting the box by one unit
// after each of `count` draws. The coordinates are clamped to the map extent and scaled to UI units.
// NON_MATCHING: ours scales max.y before storing the min pair; the original stores min first and
// scales max.y after (same instructions and size, only that pair is scheduled the other way round).
void Unk_7102479c10::sub_71009A82B4(const sead::BoundBox2f& bounds, const sead::Color4f& color,
                                    s32 count, bool a4, bool a5, bool a6) {
    sead::BoundBox2f box;
    box.set(clampMapPosition(bounds.getMin()), clampMapPosition(bounds.getMax()));
    for (s32 i = count; i != 0; --i) {
        sub_7100AA9A40(box, eui::ScreenMgr::instance()->getScreen(ScreenId::AppMap), color, a4, a5,
                       a6);
        box.set(box.getMin().x + 1.0f, box.getMin().y + 1.0f, box.getMax().x - 1.0f,
                box.getMax().y - 1.0f);
    }
}

// 0x71009a8460 (placeholder name): draws a quad's four corners on the map screen after clamping and
// scaling them like sub_71009A82B4. `a7` is never read (see the header).
void Unk_7102479c10::sub_71009A8460(f32 size, const sead::Vector2f& corner0,
                                    const sead::Vector2f& corner1, const sead::Vector2f& corner2,
                                    const sead::Vector2f& corner3, const sead::Color4f& color,
                                    bool a7, bool show_corners, bool show_center, bool flag,
                                    const sead::Vector2f& offset) {
    const sead::Vector2f p0 = clampMapPosition(corner0);
    const sead::Vector2f p1 = clampMapPosition(corner1);
    const sead::Vector2f p2 = clampMapPosition(corner2);
    const sead::Vector2f p3 = clampMapPosition(corner3);
    sub_7100AA9878(size, p0, p1, p2, p3, eui::ScreenMgr::instance()->getScreen(ScreenId::AppMap),
                   color, show_corners, show_center, flag, offset);
}

}  // namespace uking::ui
