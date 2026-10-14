#pragma once

#include <math/seadVector.h>

namespace uking {

// Placeholder names (no names known): const Vector3f with external linkage in .rodata 0x7101ec1800 - 0x7101ec182c,
// read through the GOT by HorseSaddleDefaultAction::m32 / m33 and HorseSaddleBindAction::m32 / m33
// (the first pair is selected by the `IsZelda` dynamic param). The pairs look like a bind rotation (Z) and
// translation of the saddle.
extern const sead::Vector3f sUnk_7101ec1800;  // (0, 0, -1.1344640)
extern const sead::Vector3f sUnk_7101ec180c;  // (-0.055, 0.14, 0)
extern const sead::Vector3f sUnk_7101ec1818;  // (0, 0, -1.0122909)
extern const sead::Vector3f sUnk_7101ec1824;  // (-0.01, 0.14, 0)

}  // namespace uking
