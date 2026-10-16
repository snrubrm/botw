#include "Game/UI/uiShortcutIconButton.h"
#include "Game/UI/euiButton.h"
#include "Game/UI/euiScreen.h"
#include "Game/UI/uiUtils.h"

namespace uking::ui {

Unk_7102474c68::Unk_7102474c68() = default;
Unk_7102474c68::~Unk_7102474c68() = default;

// 0x7100936db8
void Unk_7102474c68::m4(sead::Heap* heap) {
    mTextures.sub_7100A814D8(heap, 0, 1, "ShortCutIconContent");
    if (!_8)
        return;
    mArchive.sub_71009C33F8(_8);
    mTextures.setMaterial(0, mArchive.sub_71009C3780(), true);
    mTextures.setAnimator(0, mArchive.mBreak.mLayout, "PicLoad");
}

void Unk_7102474c68::m6() {
    mTextures.sub_7100A816D8();
    if (_10) {
        if (sub_7100939CA0()) {
            if ((_10->mFlags & 0x10) && !mActive) {
                mActive = true;
                _10->On();
            }
        } else if (mActive) {
            mActive = false;
            _10->Off();
        }
    }
}
void Unk_7102474c68::m7() { sub_7100936EEC(); }
void Unk_7102474c68::sub_7100936EEC() {
    if (!_8)
        return;
    auto* screen = sead::DynamicCast<ScreenMainShortCut>(eui::ScreenMgr::instance()->getScreen(ScreenId::MainShortCut));
    if (!screen)
        return;
    ShortcutIconInfo info;
    const bool valid = screen->sub_7100A20E5C(sub_7100939C78(), &info);
    if (info.mEquipOnly) {
        if (valid)
            mArchive.sub_71009C3580(info.mEquipped);
        return;
    }
    if (valid) {
        mArchive.sub_71009C3578(info.mBreakState, info.mBreakFrame);
        if (info.mName.isEmpty()) {
            mTextures.unload(0);
        } else {
            sub_7100AA9838();
            mTextures.sub_7100A81B1C(info.mName, 0);
            sub_7100AA9848();
        }
        if (info.mBowCount >= 0)
            mArchive.sub_71009C35A4(info.mBowCount);
        else
            mArchive.sub_71009C3694();
        mArchive.sub_71009C3580(info.mEquipped);
        mArchive.sub_71009C36B8(info.mTextureFrame);
        if (info.mPlayBombLoop)
            mArchive.sub_71009C372C(true, info.mBombFrame);
        else
            mArchive.sub_71009C36E4(false);
        mArchive.sub_71009C36C8(info.mCategory, info.mValue, info.mNumber);
        mArchive.sub_71009C3764(info.mIconCategory);
    } else {
        mTextures.unload(0);
        mArchive.sub_71009C3570(-1);
        mArchive.sub_71009C3580(false);
        mArchive.sub_71009C3694();
        mArchive.sub_71009C36C0();
        mArchive.sub_71009C36D0();
        mArchive.sub_71009C36E4(false);
        mArchive.sub_71009C3764(info.mIconCategory);
    }
    if (!valid || info.mEffect == 2)
        mArchive.mSwitch.sub_71009330E4();
    else
        mArchive.mSwitch.sub_7100932FA8(info.mEffect, info.mEffectLayout, false);
}

void Unk_7102474c68::m8() { mTextures.unload(0); }
void Unk_7102474c68::m12() { mArchive.mSwitch.sub_71009330E4(); }
void Unk_7102474c68::m13() {
    sub_7100936EEC();
    _10->ForceOff();
    mActive = false;
}
void Unk_7102474c68::m14() { mTextures.unload(0); }

// 0x7100937210
Unk_7102474d30::Unk_7102474d30() = default;

// 0x710093724c
Unk_7102474d30::~Unk_7102474d30() = default;

// 0x71009372c4
void Unk_7102474d30::sub_71009372C4(nn::ui2d::Pane* pane) {
    _3c8 = pane;
    if (pane) {
        _3d0 = pane->GetPosition().x;
        _3d4 = pane->GetPosition().x;
    }
}

// 0x71009372e0
void Unk_7102474d30::sub_71009372E0(eui::LayoutEx* layout) {
    _3e0.sub_7100936B18(layout);
}

// 0x71009372e8
void Unk_7102474d30::sub_71009372E8(s32 index, s32 count) {
    sub_710093F278(count, 0);
    sub_710093E42C(index, 1);
    _3c8->SetPosition(nn::util::Float3{_3d0, _3d4, 0.0f});
    _3e0.sub_7100936B7C(index > 0, index < count - 1);
}

// NON_MATCHING: the arrow layout address (_3e0) is computed in a different place
// 0x7100937790
void Unk_7102474d30::m7() {
    if (!(_2c & 1))
        return;
    if (_28 & 0x30) {
        const s32 index = _2dc;
        auto* screen =
            sead::DynamicCast<ScreenMainShortCut>(eui::ScreenMgr::instance()->getScreen(ScreenId::MainShortCut));
        if (screen)
            screen->sub_7100A21604(index);
        _3e0.sub_7100936B7C(index > 0, _2ac - 1 > index);
    }
    sub_7100937894();
}

// NON_MATCHING: the original multiplies by 15 and -15 and then selects (ours selects the factor)
// 0x7100937894
void Unk_7102474d30::sub_7100937894() {
    if (!_3c8)
        return;
    const sead::Vector2f& offset = sub_710093F160(_2dc);
    const f32 rate = sead::Mathf::clamp(sead::Mathf::abs(offset.x) / 20.0f, 0.0f, 1.0f);
    _3d8 = _3d0 + (offset.x < 0 ? rate * -15.0f : rate * 15.0f);
    const f32 current = _3c8->GetPosition().x;
    if (!sead::Mathf::equalsEpsilon(_3d8, current, 0.01f)) {
        const f32 diff = _3d8 - current;
        f32 value = diff;
        sub_7100AA2350(mScreen, &value, 0.0f, 0.5f, 3.0f, 1.0f);
        const nn::util::Float3 position{current + (diff - value), _3d4, 0.0f};
        _3c8->SetPosition(position);
    }
}

}  // namespace uking::ui
