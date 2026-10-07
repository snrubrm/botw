#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>

namespace sead {
class Heap;
}

namespace ksys::act {
class Actor;
class AITerror;
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
    // 0x6e1de0: AITerror::sub_7100D786D8 of the terror (false without one).
    virtual bool m5();
    // 0x6e2078 (700 B)
    virtual void m6(bool a1);

    // 0x6e2420: removes the terror from the actor's AITerror list (Actor::_548).
    void sub_71006E2420();
    // lane1 s47 (declaration only, placeholder names): 0x6e24b0 sets the offset of the terror (a position),
    // 0x6e2440 a mode flag, 0x6e24d4 returns a scale (the terror's radius), 0x6e2024 / 0x6e1fd0 the tagged / untagged update.
    void sub_71006E24B0(const sead::Vector3f& offset);
    void sub_71006E2440(bool value);
    f32 sub_71006E24D4();
    void sub_71006E2024();
    void sub_71006E1FD0();

    // 2026-10-07: constructor 0x71006e1cc0 and cleanup 0x71006e1d94 establish these fields.
    ksys::act::Actor* _8 = nullptr;
    ksys::act::AITerror* _10 = nullptr;
    s32 _18 = 0;
    bool _1c = false;
};

}  // namespace uking::act
