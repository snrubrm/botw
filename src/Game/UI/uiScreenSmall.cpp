#include "Game/UI/uiScreenControlCreators.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/uiScreens.h"
#include <container/seadBuffer.h>
#include "Game/UI/uiUtils.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"

// Small leaf screen methods (named after their CSV address).
namespace uking::ui {

PouchCategory sub_7100A82D08(s32 tab);

// NON_MATCHING: the compiler outlines the SafeArray member constructor.
Unk_7100A341D0::Unk_7100A341D0() = default;
// NON_MATCHING: the compiler outlines the SafeArray member destructor.
Unk_7100A341D0::~Unk_7100A341D0() = default;

// NON_MATCHING: the loop induction variable is widened in category comparisons.
void ScreenPauseMenu::sub_7100A379BC(s32 tab) {
    mSelectedCategory = s32(sub_7100A82D08(tab));
    for (s32 i = 0; i < mTabControls.mEntries.size(); ++i) {
        auto& entry = mTabControls.mEntries[i];
        entry.mButton.sub_7100988060(entry.mFirstItemIndex < 0);
        entry.mButton.sub_710098802C(i == mSelectedCategory);
        entry.mPage.sub_7100936A28(sub_7100A82DB8(i));
        if (i == mSelectedCategory)
            entry.mPage.sub_7100936A7C(tab - entry.mFirstItemIndex);
        else
            entry.mPage.sub_7100936AD8();
    }
}

// 0x7100a34a04
void ScreenPauseMenu::sub_7100A34A04() {
    _3bb4 = 1;
}

// 0x7100a38994
void ScreenPauseMenu::adjstBoxCursor(sead::BoundBox2<f32>* box, const eui::BoxCursorNode*) const {
    if (!_3674)
        return;
    if (_3664.isUndef())
        return;
    if (_3664.isInside(box->getMin()) && _3664.isInside(box->getMax()))
        return;
    if (auto* screen = eui::ScreenMgr::instance()->getScreen(ScreenId::BoxCursorTV))
        screen->close(-4);
}

// 0x71009b0224
void ScreenPauseMenuUnk3a00::sub_71009B0224(bool enabled) {
    if (_130 == -1)
        return;
    for (auto& button : mButtons)
        button.sub_7100989968(enabled);
}

// 0x71009b0618
ScreenChildEx::ScreenChildEx(eui::LayoutEx* layout) : ScreenChild(layout) {
    _128 = nullptr;
}

// 0x71009b5fc8
void ScreenPauseMenuUnk3b98::sub_71009B5FC8(bool active) {
    if (active) {
        // Pointer virtual form retains the original state descriptor getId call.
        if (mStateMachine.getState()->getId() != (&sUnk_710261ee00)->getId())
            return;
        mStateMachine.changeState(&sUnk_71025d98a0);
    } else {
        mStateMachine.changeState(&sUnk_710261ee00);
    }
}

// 0x71009b9f94
bool ScreenPauseMenuUnk3b90::sub_71009B9F94(bool active) {
    if (active) {
        // Pointer virtual form retains the original state descriptor getId call.
        if (mStateMachine.getState()->getId() != (&sUnk_710261ee00)->getId())
            return false;
        mStateMachine.changeState(&sUnk_71025d9e00);
    } else {
        mStateMachine.changeState(&sUnk_710261ee00);
    }
    return true;
}

bool sub_7100AA8DD4();

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

// NON_MATCHING: independent Buffer offsets and table iteration differ.
bool ScreenDoCommand::setCommand(s32 command) {
    if (sub_7100AA8F10() && command != 14)
        return false;
    if (_3658 != -1)
        return false;
    for (const auto& entry : sUnk_71025ED468) {
        if (entry.command == command) {
            if (entry.state == -1)
                return false;
            _3658 = entry.state;
            return true;
        }
    }
    return false;
}


// 0x7100a0772c
void ScreenDoCommand::sub_7100A0772C(s32 a1) {
    _365c = a1;
}

// 0x7100a349f4
bool ScreenPauseMenu::sub_7100A349F4() {
    return _3bb4 == 3;
}

// 0x7100a34a10
bool ScreenPauseMenu::sub_7100A34A10() {
    return _3bb4 != 0;
}

s32 sUnk_710249ad74;

// 0x7100a6814c (CSV ScreenSystemWindow01::m100)
void ScreenSystemWindow01::m100() {
    if (_4b5c && u32(sUnk_710249ad74 - 1) <= 1)
        invokeSoundLink2Event_("mc_CloseOnlyLoad");
}

// 0x7100a663d8 (CSV ScreenSystemWindow01::m129)
void ScreenSystemWindow01::m129() {
    if (sUnk_710249ad74)
        _4b60 = !sub_7100A6641C();
}

// 0x7100a3f3f4
void ScreenPickUp::setItemAndOpen(const sead::SafeString& item, bool show) {
    open(3);
    if (show)
        sub_7100A3F450(item, 5.0f);
}

struct RuntimeTip {
    sead::SafeString message;
    sead::SafeString flag;
};

static RuntimeTip sUnk_71025EFC18[] = {
    {"0000", "GuideSPlus_GurdJust"},
    {"0001", "GuideSPlus_KaihiJust"},
    {"0003", "GuideS_HeadShoot"},
    {"0002", "GuideSPlus_Surfing"},
    {"0004", "GuideS_WarningGanbari"},
    {"0005", "GuideS_WarningCold"},
    {"0006", "GuideS_WarningHot"},
    {"0007", "GuideS_StealthAttack"},
    {"0008", "GuideS_WeaponDestruction"},
    {"0009", "GuideS_WeaponThrowAttack"},
    {"0010", "GuideS_WarningBurn"},
    {"0013", "GuideS_ClimbSlip"},
    {"0014", "GuideS_WeaponBurning"},
    {"0015", "GuideSPlus_Squat"},
    {"0017", "GuideS_WolfLead"},
    {"0016", "GuideS_SandSealError"},
    {"0018", "GuideS_Recipe"},
    {"0019", "GuideS_ElectricDamage"},
    {"0020", "GuideS_WarningColdLv2"},
    {"0021", "GuideS_WarningHotLv2"},
    {"0022", "GuideS_WarningBurnLv2"},
    {"0023", "GuideS_RelicControl"},
    {"0024", "GuideS_MotorcycleGasOff"},
};
static sead::Buffer<RuntimeTip> sUnk_71025EFC08(sUnk_71025EFC18);

// NON_MATCHING: the independent Buffer produces different global field offsets.
bool getRuntimeTipFlag(s32 index) {
    if (u32(index) > 22)
        return false;
    return ksys::gdt::getBoolByKey(sUnk_71025EFC08[index].flag, false);
}

// NON_MATCHING: the independent Buffer produces different global field offsets.
void ScreenMessageTipsRunTime::sub_7100A268AC(s32 index, s32 force) {
    _3618.lock();
    if (u32(index) <= 22 && _3660 != index &&
        !ksys::gdt::getBoolByKey(sUnk_71025EFC08[index].flag, false) &&
        ((force & 1) || (!sub_7100AA8F10() && !sub_7100AA8DD4()))) {
        _3658 = index;
        _365c = force & 1;
    }
    _3618.unlock();
}

// 0x7100a26be8
void ScreenMessageTipsRunTime::m93(sead::Heap*) {
    _3610 = mLayout->createAnimatorAuto("GuideOn", false);
    _3668.init(6.0f);
}

// 0x7100a26db8
void ScreenMessageTipsRunTime::m101() {
    if (_3684 == -1)
        _3660 = -1;
}


// ScreenPauseMenu creator; native getter/D0 precede its screen constructor.
static const ChildControlCreatorEntry sUnk_71024934b0[] = {
    {"Pa_Save_00", sub_7100A32F3C, 0},
    {"Pa_Quest_00", sub_7100A33038, 0},
    {"Pa_PagePorch_", sub_7100A33134, 1},
};
static const sead::Buffer<const ChildControlCreatorEntry> sUnk_71024934a0(sUnk_71024934b0);
// 0x7100a32f0c
// NON_MATCHING: adjacent owner-TU statics are merged, adding an address offset instruction.
const sead::Buffer<const ChildControlCreatorEntry>* Unk_71024934f8::getEntries() const {
    return &sUnk_71024934a0;
}
// 0x7100a32f18
Unk_71024934f8::~Unk_71024934f8() = default;

}  // namespace uking::ui
