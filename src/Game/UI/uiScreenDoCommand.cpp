#include <container/seadBuffer.h>
#include <prim/seadSafeString.h>
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiTUStatics.h"
#include "Game/UI/uiUtils.h"

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
    s32 _20;
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
    if (command < 0)
        return -1;
    for (u32 i = 0; i < u32(sUnk_71025ED468.size()); ++i) {
        if (sUnk_71025ED468[i].command == command)
            return i;
    }
    return -1;
}

// inline-only in the original; name is a guess (see the declaration).
inline bool ScreenDoCommand::isSameCommandState(s32 state) const {
    const s32 index = findCommandIndex(_365c);
    if (index < 0)
        return false;
    if (_3660 == 5)
        return _365c == 18;
    if (_3660 == 21)
        return _365c == 56;
    return sUnk_71025ED468[index].state == state;
}

// 0x7100a07734
// NON_MATCHING: the table walk keeps a separate 64-bit index (the original reuses the element address of the walk).
bool ScreenDoCommand::sub_7100A07734() {
    if (isClosed())
        return false;
    if (_3658 == -1)
        return true;
    if (isSameCommandState(_3658))
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
    if (_3658 != _3660 && isSameCommandState(_3658)) {
        sub_7100A07990(_3658);
        Screen::open(3);
    } else if (isClosed()) {
        sub_7100A07990(_3658);
        Screen::open(1);
    }
    _3664 = _365c;
}
}  // namespace uking::ui
