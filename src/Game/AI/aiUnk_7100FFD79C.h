#pragma once

#include <basis/seadTypes.h>

// Placeholder class (type unknown): the object that sub_7100FFD79C returns. Only virtual slot 10 (vtable
// offset 0x50) is known: BattleBgmRequestFinishTag::calc_ calls it when the signal turns on.
class Unk_7100ffd79c {
public:
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
};

// 0x7100ffd79c (declared only): `sUnk_2652610 ? sUnk_2652610->_30 ? _30->_48 : nullptr : nullptr` (the global
// at 0x7102652610 is reached through GOT 0x25799e8; also used by HorseRiddenAI's helper 0x7100ffdd38,
// CreateBgm::m6 and XLink::calc). Placeholder name.
Unk_7100ffd79c* sub_7100FFD79C();
