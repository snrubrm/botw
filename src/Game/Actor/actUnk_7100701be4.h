#pragma once

#include <gsys/gsysModelAccessKey.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actBoneHandle.h"

namespace ksys::act {
class Actor;
}

namespace uking::act {

// Placeholder name (first method 0x7100701be4; no CSV names in this TU 0x7100701be4-0x7100702160):
// the eyelid controller embedded in Enemy at 0xf60 (the EyeBlink / CloseEye / DieEye behaviors drive
// it through `Enemy::_f60`). Two bone handles (left / right eyelid) that are moved by `_184` while
// `_190` is set; `_17c` is the mode (0 = blink `_180` times, 2 = die, 3 = close).
class Unk_7100701be4 {
public:
    explicit Unk_7100701be4(ksys::act::Actor* actor) : mActor(actor) {}

    // Looks up the two eyelid bones (false if either is missing).
    bool sub_7100701BE4(const sead::SafeString& left, const sead::SafeString& right,
                        const sead::Vector3f& offset);
    // Adds the bone handles to the actor (once).
    void sub_7100701CE8();
    // Removes the bone handles and resets the offsets.
    void sub_7100701D4C();
    // Starts blinking `count` times.
    void sub_7100701DBC(s32 count);
    // Starts the dying eyes (mode 2; DieEye).
    void sub_7100701DD8();
    // Starts closing the eyes (mode 3; CloseEye).
    void sub_7100701DF0();
    // inline-only in the original; name is a guess. The same inlined sequence (`this` = Enemy + 0xf60
    // computed before the branch, tail call to sub_7100701D4C) ends EyeBlink::m9, CloseEye::m9 and
    // DieEye::m9: remove the bone handles now, or flag the removal while `_178` is positive.
    void removeOrDefer() {
        if (_178 <= 0)
            sub_7100701D4C();
        else
            _192 = true;
    }

    /* 0x000 */ ksys::act::Actor* mActor;
    /* 0x008 */ ksys::act::BoneHandle _8;
    /* 0x0b0 */ ksys::act::BoneHandle _b0;
    /* 0x158 */ gsys::BoneAccessKey _158;
    /* 0x15c */ gsys::BoneAccessKey _15c;
    /* 0x160 */ sead::Vector3f _160 = {0, 0, 0};
    /* 0x16c */ sead::Vector3f _16c = {0, 0, 0};
    /* 0x178 */ f32 _178 = 0;
    /* 0x17c */ s32 _17c = 0;
    /* 0x180 */ s32 _180 = 0;
    /* 0x184 */ sead::Vector3f _184 = {0, 0, 0};
    /* 0x190 */ bool _190 = false;
    /* 0x191 */ bool _191 = false;
    /* 0x192 */ bool _192 = false;
    /* 0x193 */ bool _193 = false;
    /* 0x194 */ u32 _194;
};
KSYS_CHECK_SIZE_NX150(Unk_7100701be4, 0x198);

}  // namespace uking::act
