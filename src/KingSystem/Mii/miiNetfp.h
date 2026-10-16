#pragma once

#include <container/seadSafeArray.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Mii/miiModelCreator.h"

namespace ksys::mii {

class UMii;

// Part name tables, filled by sinitUmiiStrings2 0x7100f5cc00 (the static initializer at the end of this
// TU; not decompiled, so they are only declared here). Placeholder names.
// 0x710260d1a0: one name per ModelCreator::Arg type (14 part types).
extern sead::SafeArray<sead::SafeString, 14> sUnk_710260D1A0;
// 0x710260d7a0: indexed by UMii::Personal::sex_age (6 values).
extern sead::SafeArray<sead::SafeString, 6> sUnk_710260D7A0;
// 0x710260db50: indexed by UMii::Body::type (5 values).
extern sead::SafeArray<sead::SafeString, 5> sUnk_710260DB50;
// 0x710260dc50: indexed by UMii::sub_7100F4BF0C() (mouth names).
extern sead::SafeArray<sead::SafeString, 3> sUnk_710260DC50;

// 0x710260d3a0: Korok part names, by ModelCreator::Arg type (6 entries; 0x7100f5ab68).
extern sead::SafeArray<sead::SafeString, 6> sUnk_710260D3A0;
// 0x710260d480: part names by Arg type (3 entries; 0x7100f5ada8).
extern sead::SafeArray<sead::SafeString, 3> sUnk_710260D480;
// 0x710260d510: a single part name (indexed by Arg type, which folds to entry 0; 0x7100f5af44).
extern sead::SafeArray<sead::SafeString, 1> sUnk_710260D510;

// 0x710260d610 / 0x710260d630: single part names like sUnk_710260D510 (races 5 and 6).
extern sead::SafeArray<sead::SafeString, 1> sUnk_710260D610;
extern sead::SafeArray<sead::SafeString, 1> sUnk_710260D630;

// 0x7100f5a550 (placeholder name): the model name of part `arg.type` for the race of `umii` (body.race).
void sub_7100F5A550(sead::BufferedSafeString* out, const ModelCreator::Arg& arg, const UMii& umii);
// 0x710260d530: Gerudo part names, by Arg type (6 entries; 0x7100f5b02c).
extern sead::SafeArray<sead::SafeString, 6> sUnk_710260D530;
// 0x7100f5b02c (placeholder name): race 4 (Gerudo parameters).
void sub_7100F5B02C(sead::BufferedSafeString* out, const ModelCreator::Arg& arg, const UMii& umii);

// 0x7100f5ab68 / 0x7100f5ada8 / 0x7100f5af44 (placeholder names): model names of other part sets (the
// first uses the Korok parameters). Same arguments as sub_7100F5A708.
void sub_7100F5AB68(sead::BufferedSafeString* out, const ModelCreator::Arg& arg, const UMii& umii);
void sub_7100F5ADA8(sead::BufferedSafeString* out, const ModelCreator::Arg& arg, const UMii& umii);
void sub_7100F5AF44(sead::BufferedSafeString* out, const ModelCreator::Arg& arg, const UMii& umii);
// 0x7100f5ba04 (placeholder name): part type 2 of sub_7100F5ADA8 (from the hat parameter).
void sub_7100F5BA04(sead::BufferedSafeString* out, const UMii& umii);

// 0x7100f5b5b8 / 0x7100f5b774 (placeholder names): the model names of part types 0 (body) and 8 (hat).
void sub_7100F5B5B8(sead::BufferedSafeString* out, const UMii& umii);
void sub_7100F5B774(sead::BufferedSafeString* out, const UMii& umii);

// 0x7100f5a708 (placeholder name): writes the model name of part `arg.type` of `umii` to `out` (empty
// when the Mii does not have that part).
void sub_7100F5A708(sead::BufferedSafeString* out, const ModelCreator::Arg& arg, const UMii& umii);

}  // namespace ksys::mii
