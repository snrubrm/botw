#pragma once

#include <container/seadSafeArray.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Mii/miiModelCreator.h"

namespace ksys::mii {

class UMii;

// Part name tables defined (and filled by a static initializer) in another TU; placeholder names.
// 0x710260d1a0: one name per ModelCreator::Arg type (14 part types).
extern sead::SafeArray<sead::SafeString, 14> sUnk_710260D1A0;
// 0x710260d7a0: indexed by UMii::Personal::sex_age (6 values).
extern sead::SafeArray<sead::SafeString, 6> sUnk_710260D7A0;
// 0x710260db50: indexed by UMii::Body::type (5 values).
extern sead::SafeArray<sead::SafeString, 5> sUnk_710260DB50;
// 0x710260dc50: indexed by UMii::sub_7100F4BF0C() (mouth names).
extern sead::SafeArray<sead::SafeString, 3> sUnk_710260DC50;

// 0x7100f5b5b8 / 0x7100f5b774 (placeholder names): the model names of part types 0 (body) and 8 (hat).
void sub_7100F5B5B8(sead::BufferedSafeString* out, const UMii& umii);
void sub_7100F5B774(sead::BufferedSafeString* out, const UMii& umii);

// 0x7100f5a708 (placeholder name): writes the model name of part `arg.type` of `umii` to `out` (empty
// when the Mii does not have that part).
void sub_7100F5A708(sead::BufferedSafeString* out, const ModelCreator::Arg& arg, const UMii& umii);

}  // namespace ksys::mii
