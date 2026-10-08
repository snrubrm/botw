#include "KingSystem/System/UIGlue.h"
#include <prim/seadSafeString.h>

// Glue between the ksys layer and the UI code: every function forwards to a handler (a function pointer set
// during the app initialisation by uking::ui) and does nothing / returns 0 while no handler is installed. The
// handlers are one contiguous table of pointers (0x7102606990 - 0x7102606af8). Placeholder names (sub_<addr>,
// `a<N>` arguments) are used where the function is not named yet; only the number of arguments is known.
namespace ksys::ui {

// 0x7102606a90: set by uiManager::init (0x7100a94460); called directly by ksys::sub_7100F3ED50 (no wrapper).
SUnk_7102606a90HandlerFn sUnk_7102606a90Handler;

using SSub_7100EDC2E4HandlerFn = bool (*)(bool);
SSub_7100EDC2E4HandlerFn sSub_7100EDC2E4Handler;

// 0x7100edc2e4
bool sub_7100EDC2E4(bool a1) {
    if (sSub_7100EDC2E4Handler)
        return sSub_7100EDC2E4Handler(a1);
    return false;
}

using SInitRupeeCounterHandlerFn = void (*)();
SInitRupeeCounterHandlerFn sInitRupeeCounterHandler;

// 0x7100edc304
void initRupeeCounter() {
    if (sInitRupeeCounterHandler)
        sInitRupeeCounterHandler();
}

using SIsRupeeCounterActiveHandlerFn = bool (*)();
SIsRupeeCounterActiveHandlerFn sIsRupeeCounterActiveHandler;

// 0x7100edc31c
bool isRupeeCounterActive() {
    if (sIsRupeeCounterActiveHandler)
        return sIsRupeeCounterActiveHandler();
    return false;
}

using SSub_7100EDC334HandlerFn = void (*)();
SSub_7100EDC334HandlerFn sSub_7100EDC334Handler;

// 0x7100edc334
void sub_7100EDC334() {
    if (sSub_7100EDC334Handler)
        sSub_7100EDC334Handler();
}

using SCallCheckWeaponFreeSlotHandlerMaybeHandlerFn = s32 (*)(void*, void*);
SCallCheckWeaponFreeSlotHandlerMaybeHandlerFn sCallCheckWeaponFreeSlotHandlerMaybeHandler;

// 0x7100edc34c
s32 callCheckWeaponFreeSlotHandlerMaybe(void* a1, void* a2) {
    if (sCallCheckWeaponFreeSlotHandlerMaybeHandler)
        return sCallCheckWeaponFreeSlotHandlerMaybeHandler(a1, a2);
    return 0;
}

using SCallIncreasePouchNumHandlerFn = void (*)(void*, void*);
SCallIncreasePouchNumHandlerFn sCallIncreasePouchNumHandler;

// 0x7100edc368
void callIncreasePouchNum(void* a1, void* a2) {
    if (sCallIncreasePouchNumHandler)
        sCallIncreasePouchNumHandler(a1, a2);
}

using SCheckVacancyItemHandlerFn = int (*)();
SCheckVacancyItemHandlerFn sCheckVacancyItemHandler;

// 0x7100edc380
int checkVacancyItem() {
    if (sCheckVacancyItemHandler)
        return sCheckVacancyItemHandler();
    return 0;
}

using SGetPorchNumHandlerFn = s32 (*)(const sead::SafeString&);
SGetPorchNumHandlerFn sGetPorchNumHandler;

// 0x7100edc3b4
s32 getPorchNum(const sead::SafeString& name) {
    if (sGetPorchNumHandler)
        return sGetPorchNumHandler(name);
    return 0;
}

using SSub_7100EDC3D0HandlerFn = s32 (*)(void*);
SSub_7100EDC3D0HandlerFn sSub_7100EDC3D0Handler;

// 0x7100edc3d0
s32 sub_7100EDC3D0(void* a1) {
    if (sSub_7100EDC3D0Handler)
        return sSub_7100EDC3D0Handler(a1);
    return 0;
}

using SSub_7100EDC3ECHandlerFn = s32 (*)(void*);
SSub_7100EDC3ECHandlerFn sSub_7100EDC3ECHandler;

// 0x7100edc3ec
s32 sub_7100EDC3EC(void* a1) {
    if (sSub_7100EDC3ECHandler)
        return sSub_7100EDC3ECHandler(a1);
    return 0;
}

using SSub_7100EDC408HandlerFn = s32 (*)(void*);
SSub_7100EDC408HandlerFn sSub_7100EDC408Handler;

// 0x7100edc408
s32 sub_7100EDC408(void* a1) {
    if (sSub_7100EDC408Handler)
        return sSub_7100EDC408Handler(a1);
    return 0;
}

using SSub_7100EDC424HandlerFn = void (*)();
SSub_7100EDC424HandlerFn sSub_7100EDC424Handler;

// 0x7100edc424
void sub_7100EDC424() {
    if (sSub_7100EDC424Handler)
        sSub_7100EDC424Handler();
}

using SCallFindDungeonNameForPositionHandlerFn = s32 (*)(void*, void*);
SCallFindDungeonNameForPositionHandlerFn sCallFindDungeonNameForPositionHandler;

// 0x7100edc43c
s32 callFindDungeonNameForPosition(void* a1, void* a2) {
    if (sCallFindDungeonNameForPositionHandler)
        return sCallFindDungeonNameForPositionHandler(a1, a2);
    return 0;
}

using SSub_7100EDC458HandlerFn = void (*)();
SSub_7100EDC458HandlerFn sSub_7100EDC458Handler;

// 0x7100edc458
void sub_7100EDC458() {
    if (sSub_7100EDC458Handler)
        sSub_7100EDC458Handler();
}

using SSub_7100EDC470HandlerFn = void (*)();
SSub_7100EDC470HandlerFn sSub_7100EDC470Handler;

// 0x7100edc470
void sub_7100EDC470() {
    if (sSub_7100EDC470Handler)
        sSub_7100EDC470Handler();
}

using SSub_7100EDC488HandlerFn = void (*)();
SSub_7100EDC488HandlerFn sSub_7100EDC488Handler;

// 0x7100edc488
void sub_7100EDC488() {
    if (sSub_7100EDC488Handler)
        sSub_7100EDC488Handler();
}

using SSub_7100EDC4A0HandlerFn = bool (*)();
SSub_7100EDC4A0HandlerFn sSub_7100EDC4A0Handler;

// 0x7100edc4a0 (lane4 s31: returns bool: Actor::isSpecialJobType_ negates it)
bool sub_7100EDC4A0() {
    if (sSub_7100EDC4A0Handler)
        return sSub_7100EDC4A0Handler();
    return false;
}

using SSub_7100EDC4B8HandlerFn = bool (*)();
SSub_7100EDC4B8HandlerFn sSub_7100EDC4B8Handler;

// 0x7100edc4b8 (lane1 s39: returns bool: GameSceneSubsys12's update tests it)
bool sub_7100EDC4B8() {
    if (sSub_7100EDC4B8Handler)
        return sSub_7100EDC4B8Handler();
    return false;
}

using SSub_7100EDC4D0HandlerFn = void (*)();
SSub_7100EDC4D0HandlerFn sSub_7100EDC4D0Handler;

// 0x7100edc4d0
void sub_7100EDC4D0() {
    if (sSub_7100EDC4D0Handler)
        sSub_7100EDC4D0Handler();
}

using SSub_7100EDC4E8HandlerFn = void (*)();
SSub_7100EDC4E8HandlerFn sSub_7100EDC4E8Handler;

// 0x7100edc4e8
void sub_7100EDC4E8() {
    if (sSub_7100EDC4E8Handler)
        sSub_7100EDC4E8Handler();
}

using SSub_7100EDC500HandlerFn = void (*)();
SSub_7100EDC500HandlerFn sSub_7100EDC500Handler;

// 0x7100edc500
void sub_7100EDC500() {
    if (sSub_7100EDC500Handler)
        sSub_7100EDC500Handler();
}

using SSub_7100EDC518HandlerFn = void (*)();
SSub_7100EDC518HandlerFn sSub_7100EDC518Handler;

// 0x7100edc518
void sub_7100EDC518() {
    if (sSub_7100EDC518Handler)
        sSub_7100EDC518Handler();
}

using SSub_7100EDC530HandlerFn = void (*)(s32, void*);
SSub_7100EDC530HandlerFn sSub_7100EDC530Handler;

// 0x7100edc530
void sub_7100EDC530(s32 id, void* a2) {
    if (sSub_7100EDC530Handler)
        sSub_7100EDC530Handler(id, a2);
}


using SSub_7100EDC548HandlerFn = bool (*)(s32);
SSub_7100EDC548HandlerFn sSub_7100EDC548Handler;

// 0x7100edc548
bool sub_7100EDC548(s32 a1) {
    if (sSub_7100EDC548Handler)
        return sSub_7100EDC548Handler(a1);
    return 0;
}


using SSub_7100EDC564HandlerFn = bool (*)(s32);
SSub_7100EDC564HandlerFn sSub_7100EDC564Handler;

// 0x7100edc564
bool sub_7100EDC564(s32 a1) {
    if (sSub_7100EDC564Handler)
        return sSub_7100EDC564Handler(a1);
    return 0;
}

using SSub_7100EDC5B8HandlerFn = s32 (*)(void*, void*, void*);
SSub_7100EDC5B8HandlerFn sSub_7100EDC5B8Handler;

// 0x7100edc5b8
s32 sub_7100EDC5B8(void* a1, void* a2, void* a3) {
    if (sSub_7100EDC5B8Handler)
        return sSub_7100EDC5B8Handler(a1, a2, a3);
    return 0;
}

using SSub_7100EDC5F0HandlerFn = void (*)();
SSub_7100EDC5F0HandlerFn sSub_7100EDC5F0Handler;

// 0x7100edc5f0
void sub_7100EDC5F0() {
    if (sSub_7100EDC5F0Handler)
        sSub_7100EDC5F0Handler();
}

using SSub_7100EDC608HandlerFn = void (*)(void*);
SSub_7100EDC608HandlerFn sSub_7100EDC608Handler;

// 0x7100edc608
void sub_7100EDC608(void* a1) {
    if (sSub_7100EDC608Handler)
        sSub_7100EDC608Handler(a1);
}

using SCallCloseFadeStatusScreenHandlerFn = void (*)();
SCallCloseFadeStatusScreenHandlerFn sCallCloseFadeStatusScreenHandler;

// 0x7100edc620
void callCloseFadeStatusScreen() {
    if (sCallCloseFadeStatusScreenHandler)
        sCallCloseFadeStatusScreenHandler();
}

using SSub_7100EDC654HandlerFn = s32 (*)(void*);
SSub_7100EDC654HandlerFn sSub_7100EDC654Handler;

// 0x7100edc654
s32 sub_7100EDC654(void* a1) {
    if (sSub_7100EDC654Handler)
        return sSub_7100EDC654Handler(a1);
    return 0;
}

using SSub_7100EDC670HandlerFn = void (*)(void*);
SSub_7100EDC670HandlerFn sSub_7100EDC670Handler;

// 0x7100edc670
void sub_7100EDC670(void* a1) {
    if (sSub_7100EDC670Handler)
        sSub_7100EDC670Handler(a1);
}

using SLoadHorseLayoutResHandlerFn = void (*)();
SLoadHorseLayoutResHandlerFn sLoadHorseLayoutResHandler;

// 0x7100edc688
void loadHorseLayoutRes() {
    if (sLoadHorseLayoutResHandler)
        sLoadHorseLayoutResHandler();
}

using SSub_7100EDC6A0HandlerFn = void (*)();
SSub_7100EDC6A0HandlerFn sSub_7100EDC6A0Handler;

// 0x7100edc6a0
void sub_7100EDC6A0() {
    if (sSub_7100EDC6A0Handler)
        sSub_7100EDC6A0Handler();
}

using SSub_7100EDC6B8HandlerFn = void (*)();
SSub_7100EDC6B8HandlerFn sSub_7100EDC6B8Handler;

// 0x7100edc6b8
void sub_7100EDC6B8() {
    if (sSub_7100EDC6B8Handler)
        sSub_7100EDC6B8Handler();
}

using SSub_7100EDC6D0HandlerFn = void (*)();
SSub_7100EDC6D0HandlerFn sSub_7100EDC6D0Handler;

// 0x7100edc6d0
void sub_7100EDC6D0() {
    if (sSub_7100EDC6D0Handler)
        sSub_7100EDC6D0Handler();
}

using SSub_7100EDC6E8HandlerFn = void (*)();
SSub_7100EDC6E8HandlerFn sSub_7100EDC6E8Handler;

// 0x7100edc6e8
void sub_7100EDC6E8() {
    if (sSub_7100EDC6E8Handler)
        sSub_7100EDC6E8Handler();
}


using SSub_7100EDC580HandlerFn = bool (*)();
SSub_7100EDC580HandlerFn sSub_7100EDC580Handler;

// 0x7100edc580
bool sub_7100EDC580() {
    if (sSub_7100EDC580Handler)
        return sSub_7100EDC580Handler();
    return true;
}

using SSub_7100EDC5D4HandlerFn = bool (*)();
SSub_7100EDC5D4HandlerFn sSub_7100EDC5D4Handler;

// 0x7100edc5d4
bool sub_7100EDC5D4() {
    if (sSub_7100EDC5D4Handler)
        return sSub_7100EDC5D4Handler();
    return true;
}

using SSub_7100EDC59CHandlerFn = void (*)(bool);
SSub_7100EDC59CHandlerFn sSub_7100EDC59CHandler;

// 0x7100edc59c
void sub_7100EDC59C(bool a1) {
    if (sSub_7100EDC59CHandler)
        sSub_7100EDC59CHandler(a1);
}

using SSub_7100EDC638HandlerFn = void (*)(bool);
SSub_7100EDC638HandlerFn sSub_7100EDC638Handler;

// 0x7100edc638
void sub_7100EDC638(bool a1) {
    if (sSub_7100EDC638Handler)
        sSub_7100EDC638Handler(a1);
}

using SSub_7100EDC700HandlerFn = void (*)(bool);
SSub_7100EDC700HandlerFn sSub_7100EDC700Handler;

// 0x7100edc700
void sub_7100EDC700(bool a1) {
    if (sSub_7100EDC700Handler)
        sSub_7100EDC700Handler(a1);
}

}  // namespace ksys::ui

namespace uking::ui {

using SGetItemValueHandlerFn = s32 (*)(const sead::SafeString&);
SGetItemValueHandlerFn sGetItemValueHandler;

// 0x7100edc398
s32 getItemValue(const sead::SafeString& name) {
    if (sGetItemValueHandler)
        return sGetItemValueHandler(name);
    return 0;
}

}  // namespace uking::ui
