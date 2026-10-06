#pragma once

#include <basis/seadTypes.h>

namespace aal {

/// The result of starting a sound. TODO: only the values that are known are named.
enum class StartResult : s32 {
    Success = 0,
    /// The sound could not be started because there is no speaker balance unifier to play it with.
    NoUnifier = 9,
};

}  // namespace aal
