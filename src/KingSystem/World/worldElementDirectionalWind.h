#pragma once

#include <math/seadVector.h>
#include <xlink2/xlink2HandleELink.h>
#include <xlink2/xlink2HandleSLink.h>
#include "KingSystem/Chemical/chmElement.h"
#include "KingSystem/Utils/Types.h"

namespace aal {
class Shape;
}

namespace ksys::act {
class Actor;
}

// The request ElementDirectionalWindOrGust::create copies.
struct ElementDirectionalWindCreateArg {
    ksys::act::Actor* actor = nullptr;
    sead::Vector3f position = sead::Vector3f::zero;
    // Normalised by the constructor.
    sead::Vector3f direction = sead::Vector3f::ex;
    f32 _20 = 1.0f;
    f32 _24 = 0.0f;
    f32 _28 = 10.0f;
    f32 _2c = 0.0f;
    f32 _30 = 30.0f;
    f32 _34 = 5.0f;
    f32 _38 = 50.0f;
    // Bit 1: gust ("gust" instead of "directional_wind"); bit 2: sets _88.
    u8 flags = 1;
};
KSYS_CHECK_SIZE_NX150(ElementDirectionalWindCreateArg, 0x40);

// vtable 0x710250d2a0 (39 slots): directional wind / gust element. Functions 0x71010ef4dc .. 0x71010f1bb0,
// next to WindMgr.
class ElementDirectionalWindOrGust : public Unk_7102518688 {
    SEAD_RTTI_OVERRIDE(ElementDirectionalWindOrGust, Unk_7102518688)
public:
    // 0x71010ef4dc: through the world manager's chemical element holder (null without one).
    static ElementDirectionalWindOrGust* create(const ElementDirectionalWindCreateArg* arg);

    // 0x71010ef508
    ElementDirectionalWindOrGust(const ElementDirectionalWindCreateArg& arg, sead::Heap* heap);
    ~ElementDirectionalWindOrGust() override;
    bool m9() override { return true; }
    f32 m13(f32* out, const sead::Vector3f& pos, ksys::act::Chemical* chemical) override;
    f32 m14(sead::Vector3f* out, const sead::Vector3f& pos, ksys::act::Chemical* chemical) override;
    bool m18() override { return true; }
    f32 m20(ksys::act::Chemical* chemical) override;
    f32 m22() override;
    s32 m26() override;
    bool m29(const ElementName& name, sead::Heap* heap) override;
    void m33(bool a, bool fixed) override;
    void m35(f32 delta_frame) override;

    // 0x71010f0244 (CSV name; declared only): emits / fades the wind effect (ELink _58).
    void doEmitELink();
    // 0x71010efdb4 (CSV name): emits the windEmit sound (SLink _68) with the shape _80 and the position.
    void doEmitSLink();

    /* 0x48 */ ksys::phys::RigidBody* _48 = nullptr;
    /* 0x50 */ bool _50 = false;
    /* 0x58 */ xlink2::HandleELink _58;
    /* 0x68 */ xlink2::HandleSLink _68;
    /* 0x78 */ bool _78 = false;
    /* 0x80 */ aal::Shape* _80 = nullptr;
    /* 0x88 */ bool _88 = false;
    /* 0x90 */ ElementDirectionalWindCreateArg mArg;
    /* 0xd0 */ u64 _d0 = 0;
    /* 0xd8 */ u16 _d8 = 0;
    /* 0xda */ u16 _da = 0;
    /* 0xdc */ u16 _dc = 0;
    /* 0xe0 */ sead::Vector3f _e0 = sead::Vector3f::ex;
    /* 0xec */ sead::Vector3f _ec = sead::Vector3f::ey;
    // Not set by the constructor; the factory allocates 0x138 bytes.
    /* 0xf8 */ u8 _f8[0x138 - 0xf8];
};
KSYS_CHECK_SIZE_NX150(ElementDirectionalWindOrGust, 0x138);
