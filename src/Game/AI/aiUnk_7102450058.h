#pragma once

#include <basis/seadTypes.h>
#include <math/seadMathCalcCommon.h>
#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actActorBind.h"

namespace ksys::act {
class Actor;
}

// Unnamed carried-actor helper objects embedded in the AddCarriedBase family. Layouts come from the
// constructors (the classes have ~30 virtual / helper functions that are not decompiled).

// CSV: CarriedData (CarriedData::ctor 0x71006f3e40; vtable 0x7102450058).
class CarriedData {
public:
    explicit CarriedData(ksys::act::Actor* actor);
    virtual ~CarriedData();

    ksys::act::Actor* mActor;
    u32 _10 = 0;
    f32 _14 = sead::Mathf::pi() / 6;  // 0x3f060a92 (30 degrees)
    f32 _18 = 10.0f;
    f32 _1c = -1.0f;
    void* _20 = nullptr;
    f32 _28 = 1.0f;
    bool _2c = false;
};
KSYS_CHECK_SIZE_NX150(CarriedData, 0x30);

// vtable 0x7102450298 (ctor 0x71006f8a08). Embedded in AddCarriedBase (+0x68).
class Unk_7102450298 : public CarriedData {
public:
    explicit Unk_7102450298(ksys::act::Actor* actor);
    ~Unk_7102450298() override;

    void* _30 = nullptr;
    f32 _38 = 1.0f;
    f32 _3c = 1.0f;
    f32 _40 = 1.0f;
    f32 _44 = 0.0f;
    f32 _48 = 1.0f;
    f32 _4c = 1.0f;
    f32 _50 = 1.0f;
    bool _54 = false;
};
KSYS_CHECK_SIZE_NX150(Unk_7102450298, 0x58);

// vtable 0x710244ed58 (ctor 0x71006e80f8): an ActorBind variant. Embedded in AddNodeNodeCarried (+0xc0).
class Unk_710244ed58 : public ksys::act::ActorBind {
public:
    Unk_710244ed58();
    // Inline in the original (embedded users' D1 / D0 inline it; no out-of-line copy).
    ~Unk_710244ed58() override = default;

    bool m4(ksys::act::BaseProc* proc) override;

    /* 0x28 */ const char* _28 = nullptr;
    /* 0x30 */ const char* _30 = nullptr;
    /* 0x38 */ s64 _38 = -1;
    /* 0x40 */ sead::Matrix34f _40 = sead::Matrix34f::ident;
    /* 0x70 */ u32 _70 = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_710244ed58, 0x78);
