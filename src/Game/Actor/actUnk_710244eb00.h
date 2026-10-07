#pragma once

#include <basis/seadTypes.h>

namespace sead {
class Heap;
}

namespace ksys::act {
class Actor;
}

namespace uking::act {

// Placeholder name (vtable 0x710244eb00, no RTTI; functions 0x7100 6e1cc0 - 0x7100 6e2564): the AITerror owner of an
// actor whose body moves (an actor-speed terror handler: its update uses the main body's velocity and the GlobalParameter
// TerrorRegistSpeed / TerrorUnregistSpeed / SpeedTerrorLevel values). Used by LumberjackFallenTree (+0xf8) and
// DynamicActor::prepareInit_. Everything is declared only (lane1 s47); layout: {vptr, Actor* _8, AITerror* _10,
// s32 _18, bool _1c}.
class Unk_710244eb00 {
public:
    // 0x6e1cc0
    Unk_710244eb00();
    // D1 0x6e1cdc / D0 0x6e1d38
    virtual ~Unk_710244eb00();
    // 0x6e1df0: creates the AITerror of `actor` (a DummyUserTag object) and initialises its sensor body.
    virtual bool init(sead::Heap* heap, ksys::act::Actor* actor);
    // 0x6e1ed0
    virtual void m3();
    // 0x6e1d94: unlinks the actor and destroys the AITerror.
    virtual void clear();
    // 0x6e1de0: AITerror::sub_7100D786D8 of the terror (true without one).
    virtual bool m5();
    // 0x6e2078 (700 B)
    virtual void m6(bool a1);

    // 0x6e2420: removes the terror from the actor's AITerror list (Actor::_548).
    void sub_71006E2420();

    u8 _8[0x20 - 0x8];
};

}  // namespace uking::act
