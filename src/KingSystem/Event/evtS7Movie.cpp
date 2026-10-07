#include "KingSystem/Event/evtS7.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/System/MoviePlayer.h"
#include "KingSystem/System/OverlayArenaSystem.h"

namespace ksys::evt {

// 0x71008b8edc
S7Movie::S7Movie(sead::Heap* heap, EventFlowBase* flow) : S7(heap, flow) {
    _1c = 0;
    _20 = 0;
    _1c0 = false;
}

// D1 0x71008b8fc0, D0 0x71008b8fd4
// Written as `{ ; }` (as upstream's GameDataFlagSelector::~GameDataFlagSelector() { ; }, user-approved): the original keeps
// the vtable store, which an empty destructor drops.
S7Movie::~S7Movie() {
    ;
}

// 0x71008b8f6c (CSV evt::S7Movie::m4)
void S7Movie::m4() {
    _1c = 0;
    _20 = 0;
    _1c0 = false;
    if (sub_71008AF3B8()->_12 && sub_71008AF3B8()->_11) {
        _1c = 4;
        _1c0 = true;
    }
    sub_71008AF278();
}

// 0x71008b9f10
bool S7Movie::sub_71008B9F10() {
    if (mFlow->mEventName == "Demo143_0") {
        if (gdt::getFlag_Clear_RemainsWater(false))
            return true;
        if (gdt::getFlag_Clear_RemainsFire(false))
            return true;
        if (gdt::getFlag_Clear_RemainsElectric(false))
            return true;
    }
    if (mFlow->mEventName == "Demo143_3") {
        if (gdt::getFlag_Clear_RemainsFire(false))
            return true;
        if (gdt::getFlag_Clear_RemainsElectric(false))
            return true;
    }
    if (mFlow->mEventName == "Demo143_1") {
        if (gdt::getFlag_Clear_RemainsElectric(false))
            return true;
    }
    return false;
}

// 0x71008b9e04
void S7Movie::x(bool a) {
    const bool started = sub_71008AF3B8()->_12;
    const bool condition = sub_71008B9F10();
    if (!started) {
        if (!condition)
            return;
        sub_71008AF3B8()->_12 = true;
        MoviePlayer::instance()->_3dc = true;
        if (a)
            sub_71008AF3B8()->_11 = true;
    } else if (!condition) {
        sub_71008AF3B8()->_12 = false;
        MoviePlayer::instance()->_3dc = false;
        if (sub_71008AF3B8()->_11)
            OverlayArenaSystem::instance()->sub_7100FDE9E4(nullptr);
        sub_71008AF3B8()->_11 = false;
    } else if (a) {
        sub_71008AF3B8()->_11 = true;
    }
}

// 0x71008ba28c (CSV evt::S7Movie::m10)
bool S7Movie::isPlaying() {
    return _1c == 2;
}

// 0x71008b9ee0 (CSV evt::S7Movie::m7)
const char* S7Movie::m7() {
    return _28.cstr();
}

}  // namespace ksys::evt
