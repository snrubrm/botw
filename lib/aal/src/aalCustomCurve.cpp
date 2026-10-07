#include "aal/aalCustomCurve.h"

namespace aal {

// NON_MATCHING: the original stores the zero count of the segment list right after the name copy.
// 0x7100ba2868
CustomCurve::CustomCurve(const sead::SafeString& name) : Curve(name) {
    mSegments.initOffset(0x10);
}

}  // namespace aal
