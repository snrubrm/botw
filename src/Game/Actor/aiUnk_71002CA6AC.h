#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>

#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
}

namespace ksys::map {
class Rail;
}

namespace uking {
// 0x71025b6c50: the block of cached pointers that GameScene::initSomePointers clears (the original
// reaches it through the GOT). The same bytes are the per-remains-type position table, five 12-byte
// vectors; GameScene only ever clears the block.
struct Unk_71025b6c50 {
    struct Words {
        u64 _0;
        u64 _8;
        u64 _10;
        u64 _18;
        u64 _20;
        u64 _28;
        u64 _30;
        u32 _38;
    };
    union {
        Words words;
        sead::Vector3f mPositions[5];
    };
    Unk_71025b6c50() : words() {}
};
KSYS_CHECK_SIZE_NX150(Unk_71025b6c50, 0x40);
extern Unk_71025b6c50 sUnk_71025b6c50;
}  // namespace uking

// Remains-actor helpers (declared only; lane2 s21, placeholder names; the RemainsRoot AI is their only user).
// 0x71002ca6ac: stores `pos` in the position table entry of the remains type `id` (12-byte entries).
void sub_71002CA6AC(s32 id, const sead::Vector3f& pos);
// 0x71002ca808: the rail of the remains type `id` (aiRailMoveRemainsBGCamera's enter_).
ksys::map::Rail* sub_71002CA808(s32 id);
// 0x71002ca954 (1.1 KB): registers the remains actor of type `id` with its rail (RemainsRoot::m34).
bool sub_71002CA954(ksys::act::Actor* actor, s32 id, ksys::map::Rail* rail, bool allow_rot_axis_x);
