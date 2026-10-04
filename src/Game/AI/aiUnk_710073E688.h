#pragma once

#include <container/seadBuffer.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
}
struct Unk_7100d3d3a8;

// Placeholder name = constructor address. Vacuum state embedded in the tornado actions.
class Unk_710073e688 {
public:
    Unk_710073e688();
    ~Unk_710073e688();
    bool sub_710073E730(sead::Heap* heap, s32 count, ksys::act::Actor* actor);

    /* 0x00 */ ksys::act::Actor* _0 = nullptr;
    /* 0x08 */ f32 _8 = 1.0f;
    /* 0x0c */ f32 _c = 1.0f;
    /* 0x10 */ f32 _10 = 20.0f;
    /* 0x18 */ sead::Buffer<Unk_7100d3d3a8*> _18;
    /* 0x28 */ s32 _28 = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_710073e688, 0x30);
