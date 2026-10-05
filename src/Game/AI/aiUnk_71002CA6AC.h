#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>

namespace ksys::act {
class Actor;
}

namespace ksys::map {
class Rail;
}

// Remains-actor helpers (declared only; lane2 s21, placeholder names; the RemainsRoot AI is their only user).
// 0x71002ca6ac: stores `pos` in the position table entry of the remains type `id` (12-byte entries).
void sub_71002CA6AC(s32 id, const sead::Vector3f& pos);
// 0x71002ca954 (1.1 KB): registers the remains actor of type `id` with its rail (RemainsRoot::m34).
bool sub_71002CA954(ksys::act::Actor* actor, s32 id, ksys::map::Rail* rail, bool allow_rot_axis_x);
