#pragma once

#include <basis/seadTypes.h>

namespace uking::ai {

// Inline-only in the original; name and form are guesses. A byte of flags whose bit index is a SEAD_ENUM
// that is passed by value (the by-value / named enum copy shares its stack slot with earlier scoped objects
// and the mask is a `u8` local: `flags op mask` with the mask computed before the load).
// Evidence (lane1 s26): HorseLoopTargetAndWaitAI::{enter_,calc_,leave_} and HorseFollow::{enter_,leave_}
// repeat exactly this sequence; `sead::BitFlag8::setBit(int)` / `isOnBit(int)` give `mask op flags`
// and a different stack layout.
template <typename Enum, typename T = u8>
class FlagBits {
public:
    static T makeMask(Enum bit) { return 1 << int(bit); }

    void makeAllZero() { mBits = 0; }
    void setBit(Enum bit) {
        const T mask = makeMask(bit);
        mBits |= mask;
    }
    void resetBit(Enum bit) {
        const T mask = makeMask(bit);
        mBits &= ~mask;
    }
    bool isOnBit(Enum bit) const {
        const T mask = makeMask(bit);
        return (mBits & mask) != 0;
    }

    void changeBit(Enum bit, bool on) {
        const T mask = makeMask(bit);
        mBits = on ? mBits | mask : mBits & ~mask;
    }
    bool isOffBit(Enum bit) const { return !isOnBit(bit); }

private:
    T mBits = 0;
};

template <typename Enum>
using FlagByte = FlagBits<Enum, u8>;

}  // namespace uking::ai
