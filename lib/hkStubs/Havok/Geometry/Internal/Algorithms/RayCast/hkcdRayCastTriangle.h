#pragma once

#include <Havok/Geometry/Internal/Types/hkcdRay.h>

namespace hkcdRayCastTriangle {

// Native 15A096C takes an in/out SIMD fraction and writes the hit normal.
// The result is a front/back hit mask, filtered by the supplied flags.
hkUint32 safeUsingDynamicTolerance(const hkcdRay& ray, hkVector4Parameter a,
                                  hkVector4Parameter b, hkVector4Parameter c,
                                  hkUint32 flags, hkSimdReal& fractionInOut,
                                  hkVector4& normalOut);

}  // namespace hkcdRayCastTriangle
