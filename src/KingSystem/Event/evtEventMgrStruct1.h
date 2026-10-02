#pragma once

#include <basis/seadTypes.h>
#include <container/seadSafeArray.h>
#include <math/seadVector.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::evt {

// Name from the CSV (EventMgrStruct1::ctor 0x71012730a0; created by EventMgr::init and stored at
// Manager+0x1d2d0). 16 clocks (one is taken by each evt::EventFlowTimeline, 0x71012731d8) and 0x400
// entries that refer to a clock by index (registered by 0x7100da70a8; read by timeline actions
// through Manager). Member meanings are not confirmed; placeholder names.
class EventMgrStruct1 {
public:
    struct Clock {
        f32 _0 = 0;
        s32 _4 = 0;  // index in _0
        bool _8 = false;  // in use
    };

    struct Entry {
        f32 _0 = 0;
        f32 _4 = 0;
        s32 _8 = -1;  // clock index (-1: free)
    };

    EventMgrStruct1();

    // 0x71012731d8: takes the first free clock (null if all are in use).
    Clock* sub_71012731D8();
    // 0x7101273334: frees every entry that refers to `clock`; also frees the clock if `release`.
    void sub_7101273334(Clock* clock, bool release);
    // 0x7101273370: registers an entry {value.x, value.y} for `clock`; returns its index or -1.
    int sub_7101273370(Clock* clock, const sead::Vector2f& value);
    // 0x71012733d8: frees entry `idx`.
    void sub_71012733D8(int idx);
    // 0x7101273400: clock value minus _0 of entry `idx` (-1 if the entry is free).
    f32 sub_7101273400(int idx) const;
    // 0x7101273448: _4 of entry `idx` (0 if the entry is free).
    f32 sub_7101273448(int idx) const;

    sead::SafeArray<Clock, 16> _0;
    sead::SafeArray<Entry, 0x400> _c0;
};
KSYS_CHECK_SIZE_NX150(EventMgrStruct1, 0x30c0);

}  // namespace ksys::evt
