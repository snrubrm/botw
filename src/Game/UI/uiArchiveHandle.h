#pragma once

#include "Game/UI/uiUnkTiny.h"
#include "Game/UI/euiAnimator.h"

namespace nn::ui2d {

// The constructor and shortcut-button composite prove these four owned UI
// controllers and the 0xa8-byte extent.
class ArchiveHandle {
public:
    ArchiveHandle();
    virtual ~ArchiveHandle();
    void sub_71009C33F8(eui::LayoutEx* layout);
    void sub_71009C3580(bool off);
    void sub_71009C3694();
    void sub_71009C36E4(bool play);
    void sub_71009C3764(u32 category);
    f32 sub_71009C3788() const;
    void sub_71009C3570(s32 state);
    void sub_71009C3578(s32 state, f32 frame);
    void sub_71009C36B8(f32 frame);
    void sub_71009C36C0();
    void sub_71009C36C8(s32 category, s32 value, s32 number);
    void sub_71009C36D0();
    Material* sub_71009C3780() const;
    f32 sub_71009C37A8() const;

    eui::LayoutEx* mLayout = nullptr;
    eui::Animator* mEquipOff = nullptr;
    eui::Animator* mNumOff = nullptr;
    eui::Animator* mBombLoop = nullptr;
    eui::Animator* mCategoryIcon = nullptr;
    /* 0x30 */ uking::ui::Unk_710247aa30 mBreak;
    /* 0x50 */ uking::ui::Unk_71024774c8 mTexture;
    /* 0x68 */ uking::ui::Unk_7102477508 mNumber;
    /* 0x90 */ uking::ui::Unk_7102474b38 mSwitch;
};
static_assert(sizeof(ArchiveHandle) == 0xa8);

}  // namespace nn::ui2d
