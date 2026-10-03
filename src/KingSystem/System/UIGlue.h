#pragma once

#include <prim/seadSafeString.h>

namespace ksys::ui {

int getPorchNum(const sead::SafeString& name);
void initRupeeCounter();
bool isRupeeCounterActive();

// Further handler wrappers (UIGlue.cpp)
void sub_7100EDC334();
s32 callCheckWeaponFreeSlotHandlerMaybe(void* a1, void* a2);
void callIncreasePouchNum(void* a1, void* a2);
void checkVacancyItem();
s32 sub_7100EDC3D0(void* a1);
s32 sub_7100EDC3EC(void* a1);
s32 sub_7100EDC408(void* a1);
void sub_7100EDC424();
s32 callFindDungeonNameForPosition(void* a1, void* a2);
void sub_7100EDC458();
void sub_7100EDC470();
void sub_7100EDC488();
void sub_7100EDC4A0();
void sub_7100EDC4B8();
void sub_7100EDC4D0();
void sub_7100EDC4E8();
void sub_7100EDC500();
void sub_7100EDC518();
void sub_7100EDC530(void* a1, void* a2);
s32 sub_7100EDC548(void* a1);
s32 sub_7100EDC564(void* a1);
s32 sub_7100EDC5B8(void* a1, void* a2, void* a3);
void sub_7100EDC5F0();
void sub_7100EDC608(void* a1);
void callCloseFadeStatusScreen();
s32 sub_7100EDC654(void* a1);
void sub_7100EDC670(void* a1);
void loadHorseLayoutRes();
void sub_7100EDC6A0();
void sub_7100EDC6B8();
void sub_7100EDC6D0();
void sub_7100EDC6E8();

}  // namespace ksys::ui
