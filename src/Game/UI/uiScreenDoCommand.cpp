#include <container/seadBuffer.h>
#include <prim/seadSafeString.h>
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiTUStatics.h"
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiMessageString.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::ui {

// The TU's statics; the original merges them into the block at 0x71025ed2e0 (after the uiTUStatics.h
// objects), except the message label table, which sits in a block of its own at 0x71025ece48.

// The message label of each do command and a value.
struct CommandMessage {
    sead::SafeString label;
    s32 value;
};

// The button pane and its guide text pane.
struct CommandButton {
    sead::SafeString pane;
    sead::SafeString text;
    u32 _20;
    s32 _24;
};

static sead::SafeString sUnk_71025ED428 = "DoCommand_00";

static CommandButton sUnk_71025ED478[] = {
    {"Pa_A_00", "T_GuideA_00", 0, 0},
    {"Pa_B_00", "T_GuideB_00", 1, 1},
    {"Pa_X_00", "T_GuideX_00", 2, 2},
    {"Pa_Y_00", "T_GuideY_00", 3, 3},
    {"Pa_L_00", "T_GuideL_00", 6, 4},
    {"Pa_X_00", "T_GuideX_00", 2, 2},
    {"Pa_B_00", "T_GuideB_00", 1, 1},
    {"Pa_A_00", "T_GuideA_00", 0, 0},
};
static sead::Buffer<CommandButton> sUnk_71025ED438(sUnk_71025ED478);

static CommandMessage sUnk_71025ECE50[] = {
    {"0008", 8},
    {"0009", 0},
    {"0011", 0},
    {"0017", 0},
    {"0018", 0},
    {"0018", 7},
    {"0019", 0},
    {"0021", 0},
    {"0020", 0},
    {"0027", 0},
    {"0028", 0},
    {"0036", 0},
    {"0039", 4},
    {"0042", 0},
    {"0043", 0},
    {"0044", 0},
    {"0045", 10},
    {"0046", 0},
    {"0047", 0},
    {"0048", 3},
    {"0049", 0},
    {"0049", 7},
    {"0050", 0},
    {"0051", 0},
    {"0053", 0},
    {"0052", 0},
    {"0054", 0},
    {"0055", 0},
    {"0056", 0},
    {"0057", 0},
    {"0058", 0},
    {"0059", 0},
    {"0060", 3},
    {"0061", 0},
    {"0064", 0},
    {"0062", 0},
    {"0063", 0},
    {"0065", 0},
    {"0066", 0},
    {"0068", 0},
    {"0069", 0},
    {"0070", 0},
    {"0071", 0},
    {"0072", 3},
    {"0073", 0},
    {"0074", 0},
    {"0075", 0},
    {"0053", 0},
};
static sead::Buffer<CommandMessage> sUnk_71025ED448(sUnk_71025ECE50);

static sead::SafeString sUnk_71025ED458 = "mc_DoDefault";

struct CommandInfo {
    s32 command;
    s32 state;
    sead::SafeString animation;
};

static CommandInfo sUnk_71025ED5B8[] = {
    {66, 2, ""},
    {68, 16, ""},
    {17, 1, ""},
    {38, 10, "mc_DoDefault"},
    {22, 6, ""},
    {21, 7, ""},
    {26, 6, ""},
    {27, 8, ""},
    {28, 24, ""},
    {29, 25, ""},
    {16, 3, "mc_DoDefault"},
    {36, 9, ""},
    {18, 4, "mc_DoDefault"},
    {39, 11, "mc_DoDefault"},
    {11, 12, ""},
    {9, 0, ""},
    {42, 11, "mc_DoDefault"},
    {43, 11, "mc_DoDefault"},
    {25, 8, ""},
    {44, 13, "mc_DoDefault"},
    {45, 14, ""},
    {47, 15, "mc_DoDefault"},
    {48, 15, ""},
    {49, 17, ""},
    {50, 17, ""},
    {51, 4, "mc_DoDefault"},
    {52, 18, "mc_DoDefault"},
    {78, 19, ""},
    {56, 20, "mc_DoDefault"},
    {53, 22, ""},
    {54, 22, ""},
    {55, 22, ""},
    {41, 23, "mc_DoDefault"},
    {57, 24, ""},
    {58, 25, "mc_DoDefault"},
    {14, 26, ""},
    {40, 27, "mc_DoDefault"},
    {79, 28, ""},
    {80, 29, ""},
    {81, 30, ""},
    {82, 31, ""},
    {15, 32, ""},
    {60, 33, ""},
    {59, 34, ""},
    {83, 35, ""},
    {61, 36, "mc_DoDefault"},
    {62, 37, ""},
    {63, 38, ""},
    {24, 39, ""},
    {23, 40, ""},
    {30, 40, ""},
    {19, 41, "mc_DoDefault"},
    {46, 42, ""},
    {84, 43, ""},
    {64, 44, "mc_DoDefault"},
    {65, 45, ""},
    {85, 46, ""},
    {86, 47, "mc_DoDefault"},
};
static sead::Buffer<CommandInfo> sUnk_71025ED468(sUnk_71025ED5B8);

// inline-only in the original; name is a guess: the jump and the dash buttons (message values 8 to 10) swap with the
// JumpButtonChange option. Repeats in sub_7100A07990 and m94.
inline s32 getCommandButton(s32 value) {
    if (value >= 8 && value <= 10) {
        const bool changed = ksys::gdt::getFlag_JumpButtonChange();
        switch (value) {
        case 8:
            return changed ? 1 : 2;
        case 9:
            return changed ? 2 : 1;
        case 10:
            return changed ? 6 : 5;
        }
    }
    return value;
}

// 0x7100a07658
const char* ScreenDoCommand::getLayoutName_() const {
    return sUnk_71025ED428.cstr();
}

// 0x7100a0768c
// NON_MATCHING: the original tests _3658 before setting up the false return (block layout); the table walk matches.
bool ScreenDoCommand::setCommand(s32 command) {
    if (sub_7100AA8F10() && command != 14)
        return false;
    if (_3658 != -1)
        return false;
    for (u32 i = 0; i < u32(sUnk_71025ED468.size()); ++i) {
        if (sUnk_71025ED468(i).command == command) {
            if (sUnk_71025ED468(i).state == -1)
                return false;
            _3658 = sUnk_71025ED468(i).state;
            return true;
        }
    }
    return false;
}


// 0x7100a0772c
void ScreenDoCommand::sub_7100A0772C(s32 a1) {
    _365c = a1;
}


// inline-only in the original; name is a guess: the index of a command in the table, or -1.
inline s32 findCommandIndex(s32 command) {
    for (u32 i = 0; i < u32(sUnk_71025ED468.size()); ++i) {
        if (sUnk_71025ED468[i].command == command)
            return i;
    }
    return -1;
}

// inline-only in the original; name is a guess (see the declaration).
inline bool ScreenDoCommand::isSameCommandState(s32 command, s32 state) const {
    if (command < 0)
        return false;
    const s32 index = findCommandIndex(command);
    if (index < 0)
        return false;
    if (_3660 == 5)
        return command == 18;
    if (_3660 == 21)
        return command == 56;
    return sUnk_71025ED468[index].state == state;
}

// 0x7100a07734
// NON_MATCHING: the table walk keeps a separate 64-bit index (the original reuses the element address of the walk).
bool ScreenDoCommand::sub_7100A07734() {
    if (isClosed())
        return false;
    if (_3658 == -1)
        return true;
    if (isSameCommandState(_365c, _3658))
        return false;
    if (isClosedOrClosing())
        return true;
    return _3658 != _3660;
}

// 0x7100a0789c
// NON_MATCHING: the table walk keeps a separate 64-bit index (the original reuses the element address of the walk).
void ScreenDoCommand::sub_7100A0789C() {
    if (_3658 == -1)
        return;
    if (_3658 != _3660 && isSameCommandState(_365c, _3658)) {
        sub_7100A07990(_3658);
        Screen::open(3);
    } else if (isClosed()) {
        sub_7100A07990(_3658);
        Screen::open(1);
    }
    _3664 = _365c;
}
// 0x7100a07990
// NON_MATCHING: the original loads the animator vtable once before the 19 / 12 test and loads the 0x3630 frame
// inside the 26 branch.
void ScreenDoCommand::sub_7100A07990(s32 command) {
    if (command == -1)
        return;
    _3660 = command;

    const s32 button = getCommandButton(sUnk_71025ED448[command].value);

    s32 direction = (_3660 == 5 || _3660 == 21) ? 1 : -1;
    if (_3660 == 16)
        direction = 0;

    eui::LayoutEx* layout = sub_7100BEAFB0(sUnk_71025ED438[button].pane.cstr());
    if (!layout)
        return;

    eui::MessageString message;
    getMessage("LayoutMsg/DoCommand_00", sUnk_71025ED448[_3660].label, &message);
    setWidgetString(layout, sUnk_71025ED438[button].text, message);
    sub_7100BEB6F8(layout);

    if (_3618)
        _3618->Stop(static_cast<f32>(sUnk_71025ED438[button]._20));

    if (direction != -1) {
        if (_3610 && _3610->mFrame != static_cast<f32>(_3610->GetFrameSize()))
            _3610->StopAtMax();
        if (_3620)
            _3620->Stop(static_cast<f32>(direction));
    } else if (_3610 && _3610->mFrame != 0.0f) {
        _3610->StopAtMin();
    }

    if (sUnk_71025ED438[button]._24 != -1) {
        if (auto* animator = _3648.at(sUnk_71025ED438[button]._24)) {
            if (_3660 == 19 || _3660 == 12)
                animator->StopAtMax();
            else
                animator->StopAtMin();
        }
    }

    if (sUnk_71025ED438[button]._24 != -1) {
        if (auto* animator = _3638.at(sUnk_71025ED438[button]._24)) {
            if (animator->mFrame != 0.0f)
                animator->StopAtMin();
            if (_3628 && _3628->mFrame != 0.0f)
                _3628->StopAtMin();
        }
    }

    if (_3630) {
        if (_3660 == 26) {
            if (_3630->mFrame != static_cast<f32>(_3630->GetFrameSize()))
                _3630->StopAtMax();
        } else if (_3630->mFrame != 0.0f) {
            _3630->StopAtMin();
        }
    }

    x_2();
}

// 0x7100a07d68
// NON_MATCHING: loop rotation of the button walk (the original tests the size once before the outer loop).
void ScreenDoCommand::m93(sead::Heap* heap) {
    _3610 = mLayout->createAnimatorAuto("GuideNum", false);
    _3618 = mLayout->createAnimatorAuto("BtnTexPattern", false);
    _3620 = mLayout->createAnimatorAuto("BtnTexPattern2", false);
    _3628 = mLayout->createAnimatorAuto("DecideL", true);
    if (_3628)
        _3628->StopAtMin();
    _3630 = mLayout->createAnimatorAuto("MasterSword", true);
    if (_3630)
        _3630->StopAtMin();

    _3638.allocBuffer(5, heap);
    _3648.allocBuffer(5, heap);
    for (s32 i = 0; i < 5; ++i) {
        for (s32 j = 0; j < sUnk_71025ED438.size(); ++j) {
            const auto& button = sUnk_71025ED438[j];
            if (button._24 != i)
                continue;
            eui::LayoutEx* layout = sub_7100BEAFB0(button.pane.cstr());
            if (!layout) {
                _3648.insert(i, nullptr);
                _3638.insert(i, nullptr);
                break;
            }
            if (layout->GetAnimResourceData("Decide"))
                _3638.insert(i, layout->createAnimatorAuto("Decide", false));
            else
                _3638.insert(i, nullptr);
            if (layout->GetAnimResourceData("Attention"))
                _3648.insert(i, layout->createAnimatorAuto("Attention", false));
            else
                _3648.insert(i, nullptr);
            break;
        }
    }
}

// 0x7100a07fb0
// NON_MATCHING: the table walk keeps a separate 64-bit index (the original reuses the element address of the walk).
void ScreenDoCommand::m94() {
    if (isSameCommandState(_3664, _3660)) {
        const s32 button = getCommandButton(sUnk_71025ED448[_3660].value);
        const s32 slot = sUnk_71025ED438[button]._24;
        if (slot != -1) {
            if (auto* animator = _3638.at(slot)) {
                animator->PlayAuto(1.0f);
                if (_3628 && (button == 5 || button == 6 || button == 7 || button == 10))
                    _3628->PlayAuto(1.0f);
            }
        }
        const auto& info = sUnk_71025ED468[findCommandIndex(_3664)];
        if (!info.animation.isEmpty()) {
            const char* name = info.animation.cstr();
            invokeSoundLink2Event_(name);
        }
    }
    _3664 = -1;
}

// 0x7100a07d24
void ScreenDoCommand::sub_7100A07D24() {
    if (_3660 == -1)
        return;
    const s32 value = sUnk_71025ED448[_3660].value;
    if (value >= 8 && value <= 10)
        sub_7100A07990(_3660);
}
}  // namespace uking::ui
