#include "Game/gameSceneSubsys15.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/Sound/sndBgmMgr.h"

SEAD_SINGLETON_DISPOSER_IMPL(GameSceneSubsys15)

// TU static at 0x71025ce518 (set by the TU initialiser 0x7100895018).
static sead::SafeString sRemainsFireBattleBgm = "RemainsFireBattleBgm";

// 0x7100894740
GameSceneSubsys15::~GameSceneSubsys15() {
    ksys::snd::SoundMgr::instance()->_c8 = nullptr;
}

// 0x7100894aac
void GameSceneSubsys15::m2() {
    _28 = 0;
}

// 0x7100894ab4
// NON_MATCHING: the original addresses the string as 0x71025ce3c0 + 0x158 (merged with the TU's other statics,
// which this file does not have yet).
void GameSceneSubsys15::m3() {
    if (!ksys::snd::sub_7100FFD7CC())
        return;
    if (ksys::gdt::getFlag_Fire_Relic_Battle() && !ksys::gdt::getFlag_Fire_Relic_BattlePlaying()) {
        auto* bgm = sead::DynamicCast<ksys::snd::Unk_71025ce390>(
            ksys::snd::sub_7100FFD784()->find(sRemainsFireBattleBgm));
        if (bgm)
            bgm->mStarted = true;
    }
    _28 |= 8;
}

// 0x7100894b80
// NON_MATCHING: the original tail-calls the counter getter in the first branch (ours converts it to bool).
s32 GameSceneSubsys15::m4() {
    if (ksys::snd::sub_7100FFDBD4())
        return ksys::gdt::getFlag_Counter_TerminalFinalTrial();
    auto* controller = ksys::snd::sub_7100FFD878();
    if (!controller)
        return false;
    const auto type = controller->_94;
    switch (type) {
    case 0:
        return ksys::gdt::getFlag_Counter_TerminalWind();
    case 1:
        return ksys::gdt::getFlag_Counter_TerminalFire();
    case 2:
        return ksys::gdt::getFlag_Counter_TerminalElectric();
    case 3:
        return ksys::gdt::getFlag_Counter_TerminalWater();
    default:
        return false;
    }
}

// 0x7100894c14
bool GameSceneSubsys15::m5() {
    if (ksys::snd::sub_7100FFDBD4())
        return false;
    auto* controller = ksys::snd::sub_7100FFD878();
    if (!controller)
        return false;
    const auto type = controller->_94;
    switch (type) {
    case 0:
        return ksys::gdt::getFlag_Die_PGanonWind();
    case 1:
        return ksys::gdt::getFlag_Die_PGanonFire();
    case 2:
        return ksys::gdt::getFlag_Die_PGanonElectric();
    case 3:
        return ksys::gdt::getFlag_Die_PGanonWater();
    default:
        return false;
    }
}

// 0x7100894c9c
bool GameSceneSubsys15::m6() {
    if (ksys::snd::sub_7100FFDBD4())
        return true;
    auto* controller = ksys::snd::sub_7100FFD878();
    if (!controller)
        return false;
    const auto type = controller->_94;
    switch (type) {
    case 0:
        return ksys::gdt::getFlag_IsPlayed_Demo704_0();
    case 1:
        return ksys::gdt::getFlag_IsPlayed_Demo705_0();
    case 2:
        return ksys::gdt::getFlag_IsPlayed_Demo706_0();
    case 3:
        return ksys::gdt::getFlag_IsPlayed_Demo708_0();
    default:
        return false;
    }
}

// 0x7100894d2c
bool GameSceneSubsys15::m7() {
    if (!ksys::gdt::getFlag_NakedIsland_Activated() || ksys::gdt::getFlag_NakedIsland_Finish())
        return false;
    return ksys::gdt::getFlag_NakedIsland_InIsland();
}

// 0x7100894d64
s32 GameSceneSubsys15::m8() {
    if (ksys::gdt::getFlag_UMiiMini_MakeVillage_Marry())
        return 5;
    if (ksys::gdt::getFlag_UMiiMini_MakeVillage_Invite04())
        return 4;
    if (ksys::gdt::getFlag_UMiiMini_MakeVillage_Invite03())
        return 3;
    if (ksys::gdt::getFlag_UMiiMini_MakeVillage_Invite02())
        return 2;
    return ksys::gdt::getFlag_UMiiMini_MakeVillage_Invite01();
}

// 0x7100894de0
bool GameSceneSubsys15::m9() {
    return ksys::gdt::getFlag_FinalTrial_FirstMessage();
}
