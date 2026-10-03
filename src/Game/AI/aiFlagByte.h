#pragma once

#include <basis/seadTypes.h>

namespace uking::ai {

// Inline-only in the original; name and form are guesses. A byte of flags whose bit index is a SEAD_ENUM
// that is passed by value (the by-value / named enum copy shares its stack slot with earlier scoped objects
// and the mask is a `u8` local: `flags op mask` with the mask computed before the load).
// Evidence (lane1 s26): HorseLoopTargetAndWaitAI::{enter_,calc_,leave_} and HorseFollow::{enter_,leave_}
// repeat exactly this sequence; `sead::BitFlag8::setBit(int)` / `isOnBit(int)` give `mask op flags`
// and a different stack layout.
template <typename Enum>
class FlagByte {
public:
    static u8 makeMask(Enum bit) { return 1 << int(bit); }

    void makeAllZero() { mBits = 0; }
    void setBit(Enum bit) {
        const u8 mask = makeMask(bit);
        mBits |= mask;
    }
    void resetBit(Enum bit) {
        const u8 mask = makeMask(bit);
        mBits &= ~mask;
    }
    bool isOnBit(Enum bit) const {
        const u8 mask = makeMask(bit);
        return (mBits & mask) != 0;
    }

private:
    u8 mBits = 0;
};

}  // namespace uking::ai
