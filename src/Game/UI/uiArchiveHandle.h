#pragma once

#include "Game/UI/uiUnkTiny.h"

namespace nn::ui2d {

// The constructor and shortcut-button composite prove these four owned UI
// controllers and the 0xa8-byte extent.
class ArchiveHandle {
public:
    ArchiveHandle();
    virtual ~ArchiveHandle();
    void sub_71009C3570(s32 state);
    void sub_71009C3578(s32 state, f32 frame);
    void sub_71009C36B8(f32 frame);
    void sub_71009C36C0();
    void sub_71009C36C8(s32 category, s32 value, s32 number);
    void sub_71009C36D0();
    Material* sub_71009C3780() const;
    f32 sub_71009C37A8() const;

    u64 _8 = 0;
    u64 _10 = 0;
    u64 _18 = 0;
    u64 _20 = 0;
    u64 _28 = 0;
    /* 0x30 */ uking::ui::Unk_710247aa30 mBreak;
    /* 0x50 */ uking::ui::Unk_71024774c8 mTexture;
    /* 0x68 */ uking::ui::Unk_7102477508 mNumber;
    /* 0x90 */ uking::ui::Unk_7102474b38 mSwitch;
};
static_assert(sizeof(ArchiveHandle) == 0xa8);

}  // namespace nn::ui2d
