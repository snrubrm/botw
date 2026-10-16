#pragma once

#include <math/seadVector.h>
#include "KingSystem/Chemical/chmElement.h"
#include "KingSystem/Utils/Types.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace ksys::act {
class Actor;
}


// Constructor 0x71010c3114 copies this request (0x1c bytes), including the Actor pointer at offset 0.
struct ElementSparkCreateArg {
    ksys::act::Actor* actor = nullptr;
    sead::Vector3f position = sead::Vector3f::zero;
    f32 radius = 1.0f;
    f32 life = 15.0f;
};
KSYS_CHECK_SIZE_NX150(ElementSparkCreateArg, 0x20);

// vtable 0x710250bfd0 (39 slots): the spark element ("spark"). Functions 0x71010c3114 .. 0x71010c3538.
class ElementSpark : public Unk_7102518688 {
    SEAD_RTTI_OVERRIDE(ElementSpark, Unk_7102518688)
public:
    // 0x71010c3114
    ElementSpark(const ElementSparkCreateArg& arg, sead::Heap* heap);
    ~ElementSpark() override;
    bool m29(const ElementName& name, sead::Heap* heap) override;
    void m33(bool a, bool fixed) override;
    // Counts the life down by the frame delta and releases the element at 0.
    void m35(f32 delta_frame) override;

    /* 0x48 */ ksys::phys::RigidBody* _48 = nullptr;
    /* 0x50 */ Unk_71012419b4 mXLink;
    /* 0x70 */ ElementSparkCreateArg mArg;
};
KSYS_CHECK_SIZE_NX150(ElementSpark, 0x90);

namespace ksys::world {

// Null-safe request dispatch through the world manager's chemical element holder.
ElementSpark* sub_71010C30E8(const ElementSparkCreateArg* arg);

}  // namespace ksys::world
