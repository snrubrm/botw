#include "Game/UI/uiScreens.h"
#include <container/seadBuffer.h>
#include "Game/UI/uiUtils.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"

// Small leaf screen methods (named after their CSV address).
namespace uking::ui {

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

// 0x7100a26db8
void ScreenMessageTipsRunTime::m101() {
    if (_3684 == -1)
        _3660 = -1;
}

}  // namespace uking::ui
