#include "Game/UI/uiScreens.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/uiScreenChildMessage.h"

// Default implementations of ScreenChild and ScreenChildEx virtual slots (0x7100931dd8 - 0x71009321c8, ...): empty or
// forwarding to another slot of the same object.
namespace uking::ui {

// NON_MATCHING: the state tests become one bit-mask test here; the original tests 0 separately and the odd / even
// ranges with sub + cmp + tbnz.
// 0x71010a8e30
bool ScreenChild::m5(bool a1) {
    if (!_110)
        return false;
    const s32 state = _104;
    if (state == 0 || state == 2 || state == 4 || state == 6) {
        _104 = a1 ? 1 : 3;
        return true;
    }
    if (state == 1 || state == 3 || state == 5)
        return false;
    return true;
}

// NON_MATCHING: as m5.
// 0x71010a8e80
bool ScreenChild::m6(bool a1) {
    if (!_110 && !_118)
        return false;
    const s32 state = _104;
    if (state == 7 || state == 1 || state == 3 || state == 5) {
        _104 = a1 ? 2 : 4;
        return true;
    }
    if (state == 2 || state == 4 || state == 6)
        return false;
    return true;
}

// 0x71010a8ee0
// NON_MATCHING: the direct state membership tests become a bit-mask test.
bool ScreenChild::m7(bool immediate) {
    if (!_110)
        return false;
    const s32 state = _104;
    if (state == 0 || state == 2 || state == 4 || state == 6) {
        mLayout->sub_7100BDDE7C(false, !immediate, true);
        _104 = 5;
        return true;
    }
    if (state == 1 || state == 3 || state == 5)
        return false;
    return true;
}

// 0x71010a8f68
// NON_MATCHING: the direct state membership tests become a bit-mask test.
bool ScreenChild::m8(bool immediate) {
    if (!_110 && !_118)
        return false;
    const s32 state = _104;
    if (state == 7 || state == 1 || state == 3 || state == 5) {
        mLayout->startAnimCloseImpl_(false, !immediate);
        _104 = 6;
        return true;
    }
    if (state == 2 || state == 4 || state == 6)
        return false;
    return true;
}

// 0x71010a8ff4
void ScreenChild::m9() {}

// 0x71010a8ff8
void ScreenChild::m10() {}

// 0x71010a8ffc
void ScreenChild::m11() {}

// 0x7100931f54
s32 ScreenChild::m12() { return 0; }

// 0x7100931f5c
void ScreenChild::m13() {}

// 0x7100931f60
void ScreenChild::m14() {}

// 0x7100931f64
void ScreenChild::m15() {}

// 0x7100931f68
void ScreenChild::m16() {}

// 0x7100931f6c
void ScreenChild::m17() {}

// 0x7100931f70
void ScreenChild::m18() {}

// 0x7100931f74
void ScreenChild::m19() {}

// 0x7100931f78
void ScreenChild::m20() {}

// 0x7100931f7c
void ScreenChild::m21() {}

// 0x7100931f80
void ScreenChild::m22() {}

// 0x7100931f84
void ScreenChild::m23(void* a1) {}

// 0x7100931f88
void ScreenChild::m24(sead::Heap*) {}

// 0x7100931f8c
void ScreenChild::m25() {}

// 0x7100931f90
void ScreenChild::m26() {}

// 0x7100931f94
void ScreenChild::m27() {}

// 0x7100931f98
void ScreenChild::m28() {}

// 0x7100931f9c
void ScreenChild::m29() {}

// 0x7100931fa0
void ScreenChild::m30() {}

// 0x7100931fa4
void ScreenChild::m31() {}

// 0x7100931fa8
void ScreenChild::m32() {}

// 0x7100931fac
void ScreenChild::m33() {}

// 0x7100931fb0
void ScreenChild::m34() {}

// 0x7100931fb4
void ScreenChild::m35(void* a1) {}

// 0x7100931fb8
void ScreenChild::m36(void* a1) {}

// 0x7100931fbc
void ScreenChild::m37(void* a1) {}

// 0x7100931fc0
void ScreenChild::m38(void* a1) {}

// 0x7100931fc4
void ScreenChild::m39(void* a1) {}

// 0x7100931fc8
void ScreenChild::m40(void* a1) {}

// 0x7100931fcc
void ScreenChild::m41(void* a1) {}

// 0x7100931fd0
void ScreenChild::m42(void* a1) {}

// 0x7100931fd4
void ScreenChild::m43() { m13(); }

// 0x7100931fe0
void ScreenChild::m44() { m14(); }

// 0x7100931fec
void ScreenChild::m45() { m15(); }

// 0x7100931ff8
void ScreenChild::m46() { m16(); }

// 0x7100932004
void ScreenChild::m47() { m17(); }

// 0x7100932010
void ScreenChild::m48() { m18(); }

// 0x710093201c
void ScreenChild::m49() { m19(); }

// 0x7100932028
void ScreenChild::m50() { m20(); }

// 0x7100932034
void ScreenChild::m51() { m21(); }

// 0x7100932040
void ScreenChild::m52() { m22(); }

// 0x710093204c
void ScreenChild::m53(void* a1) { m23(a1); }

// 0x7100932058
void ScreenChild::m56() { m26(); }

// 0x7100932064
void ScreenChild::m57() { m31(); }

// 0x7100932070
void ScreenChild::m58() { m32(); }

// 0x710093207c
void ScreenChild::m59() { m33(); }

// 0x7100932088
void ScreenChild::m60() { m34(); }

// 0x7100932094
void ScreenChild::m61(void* a1) { m35(a1); }

// 0x71009320a0
void ScreenChild::m62(void* a1) { m36(a1); }

// 0x71009320ac
void ScreenChild::m63(void* a1) { m37(a1); }

// 0x71009320b8
void ScreenChild::m64(void* a1) { m38(a1); }

// 0x71009320c4
void ScreenChild::m65(void* a1) { m39(a1); }

// 0x71009320d0
void ScreenChild::m66(void* a1) { m40(a1); }

// 0x71009320dc
void ScreenChild::m67(void* a1) { m41(a1); }

// 0x71009320e8
void ScreenChild::m68(void* a1) { m42(a1); }

// 0x71009320f4
void ScreenChild::m69() { m27(); }

// 0x7100932100
void ScreenChild::m70() { m28(); }

// 0x710093210c
void ScreenChild::m71() { m29(); }

// 0x7100932118
void ScreenChild::m72() { m30(); }

// 0x7100932124
void ScreenChildEx::m81() {}

// 0x7100932128
void ScreenChildEx::m82() {}

// 0x710093212c
void ScreenChildEx::m83() {}

// 0x7100932130
void ScreenChildEx::m84() {}

// 0x7100932134
void ScreenChildEx::m85(void* a1) {}

// 0x7100932138
void ScreenChildEx::m86(void* a1) {}

// 0x710093213c
void ScreenChildEx::m87(void* a1, void* a2) {}

// 0x7100932140
void ScreenChildEx::m88(void* a1, void* a2) {}

// 0x7100932144
void ScreenChildEx::m89(void* a1, void* a2) {}

// 0x7100932148
void ScreenChildEx::m90(void* a1, void* a2) {}

// 0x710093214c
void ScreenChildEx::m91(void* a1, void* a2) {}

// 0x7100932150
void ScreenChildEx::m92(void* a1, void* a2) {}

// 0x7100932154
void ScreenChildEx::m93(void* a1, void* a2) {}

// 0x7100932158
void ScreenChildEx::m94(void* a1, void* a2) {}

// 0x710093215c
void ScreenChildEx::m95(void* a1) { m85(a1); }

// 0x7100932168
void ScreenChildEx::m96(void* a1) { m86(a1); }

// 0x7100932174
void ScreenChildEx::m97(void* a1, void* a2) { m87(a1, a2); }

// 0x7100932180
void ScreenChildEx::m98(void* a1, void* a2) { m88(a1, a2); }

// 0x710093218c
void ScreenChildEx::m99(void* a1, void* a2) { m89(a1, a2); }

// 0x7100932198
void ScreenChildEx::m100(void* a1, void* a2) { m90(a1, a2); }

// 0x71009321a4
void ScreenChildEx::m101(void* a1, void* a2) { m91(a1, a2); }

// 0x71009321b0
void ScreenChildEx::m102(void* a1, void* a2) { m92(a1, a2); }

// 0x71009321bc
void ScreenChildEx::m103(void* a1, void* a2) { m93(a1, a2); }

// 0x71009321c8
void ScreenChildEx::m104(void* a1, void* a2) { m94(a1, a2); }


// NON_MATCHING: the state wrapper destructor remains out-of-line.
Unk_71025098d0::~Unk_71025098d0() = default;


void Unk_71025098d0::run() { mMachine.run(); }

// NON_MATCHING: the bool state callback result requires conversion to the receiver's int result.
int Unk_71025098d0::receive(const ksys::Message& message) {
    if (!mMachine.mCurrent)
        Unk_7102474a70::replaceState();
    if (mMachine.mCurrent && mMachine.mCurrent->reenter(const_cast<ksys::Message*>(&message)))
        return 1;
    if (mMachine.mCurrent)
        return mMachine.mCurrent->exec5(const_cast<ksys::Message*>(&message));
    return 0;
}

void Unk_71025098d0::receive(const ksys::MessageAck& ack) {
    if (mMachine.mCurrent)
        mMachine.mCurrent->exec6(const_cast<ksys::MessageAck*>(&ack));
}

}  // namespace uking::ui
