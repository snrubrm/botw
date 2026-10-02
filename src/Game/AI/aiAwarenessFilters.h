#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"

namespace ksys::act {
class Actor;
}

namespace uking::act {
class Unk_71002dccbc;
}

// Awareness filters shared by many AI classes (their m2 and D0 live in the AI utility TU
// 0x7100744bb8-0x7100747a00). AI code builds them on the stack and iterates with
// ksys::act::sub_7100D7EEE8(&actor->getAwareness()->_8, &filter); the base dtor unlinks them.
// Placeholder names are the vtable addresses. Members are the ones each m2 reads (types from the
// load widths: pointer / bool / f32 / u32); the initial values written by the callers are not
// verified yet. m2 bodies are in aiAwarenessFilters.cpp (TODO: the ones calling unnamed helpers).

// vtable 0x7102451358 (m2 0x7100744bb8, D0 0x7100744c78)
class Unk_7102451358 : public ksys::act::Unk_71024dccf8 {
public:
    bool m2(ksys::act::Unk_71024dc978* entry) override;
};

// vtable 0x7102451380 (m2 0x7100744c9c, D0 0x7100744de8)
class Unk_7102451380 : public ksys::act::Unk_71024dccf8 {
public:
    bool m2(ksys::act::Unk_71024dc978* entry) override;

    /* 0x28 */ ksys::act::Actor* _28 = nullptr;  // the eater (sub_7100739E24)
};

// vtable 0x71024513d0 (m2 0x7100745034, D0 0x71007450c8)
class Unk_71024513d0 : public ksys::act::Unk_71024dccf8 {
public:
    bool m2(ksys::act::Unk_71024dc978* entry) override;
};

// vtable 0x71024513f8 (m2 0x71007450ec, D0 0x7100745218)
class Unk_71024513f8 : public ksys::act::Unk_71024dccf8 {
public:
    bool m2(ksys::act::Unk_71024dc978* entry) override;
};

// vtable 0x7102451420 (m2 0x710074523c, D0 0x7100745314)
class Unk_7102451420 : public ksys::act::Unk_71024dccf8 {
public:
    bool m2(ksys::act::Unk_71024dc978* entry) override;

    /* 0x28 */ ksys::act::Actor* _28 = nullptr;  // the eater (sub_7100739E24)
};

// vtable 0x7102451448 (m2 0x7100745338, D0 0x71007453ec)
class Unk_7102451448 : public ksys::act::Unk_71024dccf8 {
public:
    bool m2(ksys::act::Unk_71024dc978* entry) override;
};


// vtable 0x7102451498 (m2 0x7100746070, D0 0x71007462a0)
class Unk_7102451498 : public ksys::act::Unk_71024dccf8 {
public:
    bool m2(ksys::act::Unk_71024dc978* entry) override;

    /* 0x28 */ void* _28 = nullptr;
    /* 0x30 */ bool _30 = false;
    /* 0x31 */ bool _31 = false;
};

// vtable 0x71024514c0 (m2 0x71007454e4, D0 0x7100746234)
// Enemy target filter: _28 is the searching enemy, _30 a set of flag bits (1, 2, 4).
class Unk_71024514c0 : public ksys::act::Unk_71024dccf8 {
public:
    bool m2(ksys::act::Unk_71024dc978* entry) override;

    /* 0x28 */ ksys::act::Actor* _28 = nullptr;
    /* 0x30 */ u8 _30 = 0;
};

// vtable 0x7102451470 (m2 0x7100745410, D0 0x71007454c0); m2 tail-calls Unk_71024514c0::m2.
class Unk_7102451470 : public Unk_71024514c0 {
public:
    bool m2(ksys::act::Unk_71024dc978* entry) override;
};

// vtable 0x71024514e8 (m2 0x71007456fc, D0 0x7100746258); m2 calls Unk_71024514c0::m2.
class Unk_71024514e8 : public Unk_71024514c0 {
public:
    bool m2(ksys::act::Unk_71024dc978* entry) override;

    /* 0x38 */ void* _38 = nullptr;
};

// vtable 0x7102451510 (m2 0x7100745b14, D0 0x710074627c); m2 calls Unk_71024514c0::m2.
class Unk_7102451510 : public Unk_71024514c0 {
public:
    bool m2(ksys::act::Unk_71024dc978* entry) override;
};

// vtable 0x7102451538 (m2 0x71007462c4, D0 0x7100746360)
class Unk_7102451538 : public ksys::act::Unk_71024dccf8 {
public:
    bool m2(ksys::act::Unk_71024dc978* entry) override;
};

// vtable 0x7102451560 (m2 0x7100746384, D0 0x710074648c)
class Unk_7102451560 : public ksys::act::Unk_71024dccf8 {
public:
    bool m2(ksys::act::Unk_71024dc978* entry) override;

    /* 0x28 */ uking::act::Unk_71002dccbc* _28 = nullptr;
};

// vtable 0x7102451588 (m2 0x71007464d4, D0 0x7100746604)
class Unk_7102451588 : public ksys::act::Unk_71024dccf8 {
public:
    bool m2(ksys::act::Unk_71024dc978* entry) override;
};

// vtable 0x71024515b0 (m2 0x7100746628, D0 0x71007466e8)
class Unk_71024515b0 : public ksys::act::Unk_71024dccf8 {
public:
    bool m2(ksys::act::Unk_71024dc978* entry) override;
};

// vtable 0x71024515d8 (m2 0x710074670c, D0 0x71007467a0)
class Unk_71024515d8 : public ksys::act::Unk_71024dccf8 {
public:
    bool m2(ksys::act::Unk_71024dc978* entry) override;
};

// vtable 0x7102451600 (m2 0x71007467c4, D0 0x7100746918)
class Unk_7102451600 : public ksys::act::Unk_71024dccf8 {
public:
    bool m2(ksys::act::Unk_71024dc978* entry) override;

    /* 0x28 */ bool _28 = false;
    /* 0x29 */ bool _29 = false;
};

// vtable 0x7102451628 (m2 0x710074693c, D0 0x71007469e8)
class Unk_7102451628 : public ksys::act::Unk_71024dccf8 {
public:
    bool m2(ksys::act::Unk_71024dc978* entry) override;
};

// vtable 0x7102451678 (m2 0x7100746b58, D0 0x7100746bec)
class Unk_7102451678 : public ksys::act::Unk_71024dccf8 {
public:
    bool m2(ksys::act::Unk_71024dc978* entry) override;
};

// vtable 0x71024516a0 (m2 0x7100746c10, D0 0x7100746cac)
class Unk_71024516a0 : public ksys::act::Unk_71024dccf8 {
public:
    bool m2(ksys::act::Unk_71024dc978* entry) override;
};

// vtable 0x71024516c8 (m2 0x7100746cd0, D0 0x7100746f2c)
class Unk_71024516c8 : public ksys::act::Unk_71024dccf8 {
public:
    bool m2(ksys::act::Unk_71024dc978* entry) override;

    /* 0x28 */ ksys::act::Actor* _28 = nullptr;
    /* 0x30 */ bool _30 = false;
};

// vtable 0x71024516f0 (m2 0x7100746f50, D0 0x710074712c)
class Unk_71024516f0 : public ksys::act::Unk_71024dccf8 {
public:
    bool m2(ksys::act::Unk_71024dc978* entry) override;

    // m2: Stalfos parts within XZ distance sqrt(_28) of _34 and sqrt(_2c) of _40, and within
    // height difference _30 of _34.
    /* 0x28 */ f32 _28 = 0;
    /* 0x2c */ f32 _2c = 0;
    /* 0x30 */ f32 _30 = 0;
    /* 0x34 */ sead::Vector3f _34 = sead::Vector3f::zero;
    /* 0x40 */ sead::Vector3f _40 = sead::Vector3f::zero;
};

// vtable 0x7102451768 (m2 0x71007472ec, D0 0x7100747418)
class Unk_7102451768 : public ksys::act::Unk_71024dccf8 {
public:
    bool m2(ksys::act::Unk_71024dc978* entry) override;

    /* 0x28 */ u32 _28 = 0;
};

// vtable 0x71024517b8 (m2 0x7100747560, D0 0x7100747714)
class Unk_71024517b8 : public ksys::act::Unk_71024dccf8 {
public:
    bool m2(ksys::act::Unk_71024dc978* entry) override;

    /* 0x28 */ ksys::act::BaseProc* _28 = nullptr;
    /* 0x30 */ bool _30 = false;
    /* 0x31 */ bool _31 = false;
};

// vtable 0x71024517e0 (m2 0x7100747738, D0 0x71007478dc)
class Unk_71024517e0 : public ksys::act::Unk_71024dccf8 {
public:
    bool m2(ksys::act::Unk_71024dc978* entry) override;
};

// vtable 0x7102451808 (m2 0x7100747834, D0 0x7100747900); m2 tail-calls Unk_71024517e0::m2.
class Unk_7102451808 : public Unk_71024517e0 {
public:
    bool m2(ksys::act::Unk_71024dc978* entry) override;
};

// vtable 0x7102451830 (m2 0x7100747924, D0 0x71007479e8)
class Unk_7102451830 : public ksys::act::Unk_71024dccf8 {
public:
    bool m2(ksys::act::Unk_71024dc978* entry) override;
};
