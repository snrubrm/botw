#pragma once

#include "KingSystem/Utils/Types.h"
#include <basis/seadTypes.h>

namespace eui {

// Base class of the eui buttons (placeholder: only vtable slot 30 and the state at 0x40 are known).
class ButtonBase {
public:
    virtual ~ButtonBase() = default;
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void m12();
    virtual void m13();
    virtual void m14();
    virtual void m15();
    virtual void m16();
    virtual void m17();
    virtual void m18();
    virtual void m19();
    virtual void m20();
    virtual void m21();
    virtual void m22();
    virtual void m23();
    virtual void m24();
    virtual void m25();
    virtual void m26();
    virtual void m27();
    virtual void m28();
    virtual void m29();
    // slot 30
    virtual void setState(s32 state) = 0;

    // 0x7100bd73ec / 0x7100bd7400 / 0x7100bd7414
    void ForceOff();
    void ForceOn();
    void ForceDown();

    u8 _8[0x40 - 0x8];
    /* 0x40 */ s32 _40;
};

}  // namespace eui
