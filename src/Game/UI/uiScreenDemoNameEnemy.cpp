#include <container/seadBuffer.h>
#include <prim/seadSafeString.h>
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiTUStatics.h"

namespace uking::ui {

// The TU's statics (static initializer 0x7100a03570), merged into the block at 0x71025ec880 after the
// uiTUStatics.h objects.
static sead::SafeString sLayoutName = "DemoNameEnemy_00";

// The boss gauge parts pane shown for each boss actor.
struct DemoNameEnemyGauge {
    sead::SafeString actor;
    sead::SafeString pane;
};

static DemoNameEnemyGauge sUnk_71025EC9E8[] = {
    {"Enemy_GanonBeast", "Pa_BossGauge_GanonBeast_00"},
    {"Enemy_Ganon", "Pa_BossGauge_Ganon_00"},
    {"Enemy_SiteBoss_Bow", "Pa_BossGauge_FantomGanonWind_00"},
    {"Enemy_SiteBoss_Sword", "Pa_BossGauge_FantomGanonElectric_00"},
    {"Enemy_SiteBoss_Spear", "Pa_BossGauge_FantomGanonWater_00"},
    {"Enemy_SiteBoss_Lsword", "Pa_BossGauge_FantomGanonFire_00"},
    {"Enemy_SiteBoss_Bow_R", "Pa_BossGauge_FantomGanonWind_00_R"},
    {"Enemy_SiteBoss_Sword_R", "Pa_BossGauge_FantomGanonElectric_00_R"},
    {"Enemy_SiteBoss_Spear_R", "Pa_BossGauge_FantomGanonWater_00_R"},
    {"Enemy_SiteBoss_Lsword_R", "Pa_BossGauge_FantomGanonFire_00_R"},
};
static sead::Buffer<DemoNameEnemyGauge> sUnk_71025EC9D8(sUnk_71025EC9E8);

// 0x7100a03cfc
const char* ScreenDemoNameEnemy::getLayoutName_() const {
    return sLayoutName.cstr();
}

}  // namespace uking::ui
