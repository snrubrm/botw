#pragma once

#include <heap/seadDisposer.h>
#include "KingSystem/Utils/Types.h"

// Name from the CSV. The singleton at 0x71025d1720 holds title/demo and blood moon flags.
// The factory at 0x71008bf480 constructs its disposer at +0x8 and allocates 0x30 bytes.
class Struct30 {
    SEAD_SINGLETON_DISPOSER(Struct30)
    Struct30() = default;

public:
    virtual ~Struct30();

    bool isTitleMonitoringOrDemo() const { return mIsTitleMonitoringOrDemo; }
    void setIsTitleMonitoringOrDemo(bool value);
    void setField29(bool value);
    u8 getField2B() const;
    bool isPanicBloodMoon() const;
    void setIsPanicBloodMoon(bool value);

private:
    // The factory clears these two adjacent flags with a single halfword store.
    /* 0x28 */ bool mIsTitleMonitoringOrDemo = false;
    /* 0x29 */ bool _29 = false;
    /* 0x2a */ bool _2a = true;
    /* 0x2b */ u8 _2b = 0;
    /* 0x2c */ bool mIsPanicBloodMoon = false;
};
KSYS_CHECK_SIZE_NX150(Struct30, 0x30);
