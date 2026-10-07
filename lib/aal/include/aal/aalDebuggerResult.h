#pragma once

#include <basis/seadTypes.h>

namespace aal {

/// Why a sound was changed by the audio system (the reason that is shown by the debug tools): a code of 32 bits. The
/// meanings of the codes are not known (the limiters use 0x20000 | n, the spatial calculation 0x10000 | n).
struct DebuggerResult {
    u32 code;
};

}  // namespace aal
