#pragma once

#include <math/seadVector.h>
#include <xlink2/xlink2HandleELink.h>
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/Chemical/chmElement.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
}

namespace ksys::phys {
class ContactPointInfo;
}

// The request ElementWater::create copies (WaterEmitter::calc_ and WaterExplode fill it on the stack).
struct ElementWaterCreateArg {
    ksys::act::Actor* actor = nullptr;
    sead::Vector3f position = sead::Vector3f::zero;
    // Normalised by the constructor.
    sead::Vector3f direction = sead::Vector3f::ex;
    f32 _20 = 1.0f;
    f32 _24 = 10.0f;
    f32 _28 = 30.0f;
    u8 flags = 1;
};
KSYS_CHECK_SIZE_NX150(ElementWaterCreateArg, 0x30);

// vtable 0x710250cfd8 (39 slots): the water element (emitted with the element name "water").
// Functions 0x71010e863c .. 0x71010e9fe4, next to wm::WeatherMgr.
class ElementWater : public Unk_7102518688 {
    SEAD_RTTI_OVERRIDE(ElementWater, Unk_7102518688)
public:
    // 0x71010e863c: through the world manager's chemical element holder (null without one).
    static ElementWater* create(const ElementWaterCreateArg* arg);

    // 0x71010e8668
    ElementWater(const ElementWaterCreateArg& arg, sead::Heap* heap);
    ~ElementWater() override;
    f32 m17(ksys::act::Chemical* chemical) override;
    f32 m20(ksys::act::Chemical* chemical) override;
    bool m29(const ElementName& name, sead::Heap* heap) override;
    void m33(bool a, bool fixed) override;
    void m35() override;
    void m36() override {}
    bool m37() override { return true; }
    void m38() override {}

    /* 0x48 */ u64 _48 = 0;
    /* 0x50 */ ksys::phys::RigidBody* _50 = nullptr;
    /* 0x58 */ ksys::phys::RigidBody* _58 = nullptr;
    /* 0x60 */ ksys::phys::ContactPointInfo* _60 = nullptr;
    /* 0x68 */ xlink2::HandleELink _68;
    /* 0x78 */ xlink2::HandleELink _78;
    /* 0x88 */ ElementWaterCreateArg mArg;
    /* 0xb8 */ ksys::act::BaseProcHandle mHandle;
    /* 0xc8 */ ksys::act::InstParamPack mParamPack;
    /* 0x1a0 */ bool _1a0 = false;
    /* 0x1a4 */ f32 _1a4 = 0.0f;
    /* 0x1a8 */ f32 _1a8 = 10.0f;
    /* 0x1ac */ f32 _1ac = 0.75f;
};
KSYS_CHECK_SIZE_NX150(ElementWater, 0x1b0);
