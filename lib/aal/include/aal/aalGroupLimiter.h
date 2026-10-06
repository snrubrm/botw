#pragma once

#include <basis/seadTypes.h>

namespace aal {

/// Limits the number of sounds of a group. TODO: only the members Group forwards to are declared.
class GroupLimiter {
public:
    /// 0x7100b8014c / 0x7100b80170 / 0x7100b80274 (declared only)
    void calc();
    void calcActiveSoundLimit();
    void calcRequestSoundLimit();
};

/// Ducks the volume of a group while other groups play. TODO: only calc is declared (0x7100b82ba0).
class GroupDucker {
public:
    void calc();
};

}  // namespace aal
