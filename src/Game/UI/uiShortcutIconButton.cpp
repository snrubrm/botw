#include "Game/UI/uiShortcutIconButton.h"
#include "Game/UI/euiButton.h"
#include "Game/UI/euiScreen.h"
#include "Game/UI/uiUtils.h"

namespace uking::ui {

Unk_7102474c68::Unk_7102474c68() = default;
Unk_7102474c68::~Unk_7102474c68() = default;
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

}  // namespace uking::ui
