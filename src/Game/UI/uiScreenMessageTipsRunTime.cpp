#include <container/seadBuffer.h>
#include <prim/seadSafeString.h>
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiTUStatics.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"
#include "Game/UI/euiMessageString.h"

namespace uking::ui {

// The TU's statics are merged into one block at 0x71025efab0 (after the uiTUStatics.h objects).
static sead::SafeString sUnk_71025EFBF8 = "MessageTipsRunTime_00";

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

// inline-only in the original; name is a guess: the same bit test (0x200b >> index) repeats in sub_7100A26A5C
// and m94. Tips 0, 1, 3 and 13 explain an action.
inline bool isGuideActionTip(s32 index) {
    switch (index) {
    case 0:
    case 1:
    case 3:
    case 13:
        return true;
    default:
        return false;
    }
}

// 0x7100a26878
const char* ScreenMessageTipsRunTime::getLayoutName_() const {
    return sUnk_71025EFBF8.cstr();
}

// 0x7100a26a5c
void ScreenMessageTipsRunTime::sub_7100A26A5C(s32 index) {
    eui::MessageString message;
    getMessage("LayoutMsg/MessageTipsRunTime_00", sUnk_71025EFC08[index].message, &message);
    setWidgetString(mLayout, "T_Text_00", message);

    const bool is_action_tip = isGuideActionTip(index);
    if (is_action_tip) {
        sub_7100A99188();
        if (_3610)
            _3610->StopAtMax();
    } else if (_3610) {
        _3610->StopAtMin();
    }
    _3668.reset();

    switch (index) {
    case 0:
        ksys::gdt::setFlag_Guide_GurdJust(true);
        break;
    case 1:
        ksys::gdt::setFlag_Guide_BackStep(true);
        ksys::gdt::setFlag_Guide_SideStep(true);
        break;
    case 3:
        ksys::gdt::setFlag_Guide_Surfing(true);
        break;
    case 13:
        ksys::gdt::setFlag_Guide_Squat(true);
        break;
    }
}

// 0x7100a26bac
bool getRuntimeTipFlag(s32 index) {
    if (u32(index) > 22)
        return false;
    return ksys::gdt::getBoolByKey(sUnk_71025EFC08[index].flag, false);
}

// 0x7100a26954
void ScreenMessageTipsRunTime::sub_7100A26954() {
    if (_3658 != -1) {
        if (_3658 != _3660) {
            _3660 = _3658;
            _3664 = _365c;
            _3684 = 0;
        }
        _3658 = -1;
        _365c = false;
    }
    if (_3664 && sub_7100AA8F10())
        return;
    if (!(_292 & 2) || _3684 == -1)
        return;
    if (++_3684 != 15)
        return;
    _3684 = -1;
    _3680 = 0;
    if (sub_7100AA8F10()) {
        _3660 = -1;
    } else {
        sub_7100A26A5C(_3660);
        if (mState == 1 || mState == 2)
            open(2);
        else
            open(1);
    }
    _3664 = false;
}

// 0x7100a268ac
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

// 0x7100a26c2c
void ScreenMessageTipsRunTime::m94() {
    if (_3660 != -1 && sub_7100AA8F10()) {
        close(-4);
        _3660 = -1;
    } else if (_3660 != -1 && isOpened()) {
        if (_3668.updateAndCheckEnded())
            close(-1);
        if (!_3680 && _3668.getProgress() >= 0.6666667f) {
            ksys::gdt::setBoolByKey(true, sUnk_71025EFC08[_3660].flag);
            // The level 2 warnings also mark the level 1 tip as seen.
            switch (_3660) {
            case 18:
                ksys::gdt::setBoolByKey(true, sUnk_71025EFC08[5].flag);
                break;
            case 19:
                ksys::gdt::setBoolByKey(true, sUnk_71025EFC08[6].flag);
                break;
            case 20:
                ksys::gdt::setBoolByKey(true, sUnk_71025EFC08[10].flag);
                break;
            }
            _3680 = 1;
        }
    }
    if (isGuideActionTip(_3660))
        sub_7100A99188();
}

// 0x7100a26db8
void ScreenMessageTipsRunTime::m101() {
    if (_3684 == -1)
        _3660 = -1;
}


}  // namespace uking::ui
