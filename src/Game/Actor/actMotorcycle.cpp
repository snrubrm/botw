#include "Game/Actor/actMotorcycle.h"
#include <basis/seadNew.h>

namespace uking::act {

ksys::act::BaseProc* Motorcycle::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) Motorcycle(arg);
}

// NON_MATCHING: the members are placeholders (ctor and dtor not decompiled)
Motorcycle::~Motorcycle() = default;

bool Motorcycle::x_6() const {
    return _f88.isOnBit(11);
}

f32 Motorcycle::x_8() const {
    if (_f10 == 5 || _f10 == 6)
        return _e00 / -35.0f;
    return 0.0f;
}

void Motorcycle::x_11() {
    _f88.set(0x40000);
}

void Motorcycle::x_5() {
    _f88.set(0x800000);
}

void Motorcycle::setAccelMaybe(f32 accel) {
    const f32 prev = _e3c;
    if (accel > 0.0f && prev == 0.0f)
        _10a4 = 1;
    else if (accel == 0.0f && prev == 1.0f)
        _10a4 = 2;
    _e3c = accel;
}

void Motorcycle::crashMaybe(bool crash) {
    _f88.reset(1);
    if (crash) {
        _f88.set(0x4000000);
        x_7();
    } else {
        _f88.reset(0x4000000);
    }
    _df0 = 0;
}

}  // namespace uking::act
