#pragma once

#include <container/seadBuffer.h>
#include <math/seadVector.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/Utils/Types.h"

class hkpShape;

namespace sead {
class Heap;
}

namespace ksys::phys {

class Shape;
struct ICharacterControllerParam;

// Placeholder: 0x30 byte entry of a CharacterFormSet (one per form).
struct CharacterControllerShape {
    // The capsule form set's factory stores newly constructed Havok capsule shapes
    // here; controller initialization passes the second pointer to RigidBodyFromShape.
    /* 0x00 */ const hkpShape* _0 = nullptr;
    /* 0x08 */ Shape* _8 = nullptr;
    /* 0x10 */ bool _10 = false;
    /* 0x11 */ u8 _11 = 0;
    /* 0x12 */ bool _12 = false;
    /* 0x13 */ u8 _13;
    /* 0x14 */ f32 _14 = 0;
    /* 0x18 */ f32 _18 = 0;
    /* 0x1c */ f32 _1c = 1.0f;
    /* 0x20 */ sead::Vector3f _20 = sead::Vector3f::zero;
    /* 0x2c */ u8 _2c[4];
};
KSYS_CHECK_SIZE_NX150(CharacterControllerShape, 0x30);

// The shapes of a character controller's forms (CharacterController::_30); vtable 0x71024f5e40.
// CharacterControllerParam::createFormSet builds one from the param's forms.
class CharacterFormSet {
    SEAD_RTTI_BASE(CharacterFormSet)
public:
    explicit CharacterFormSet(f32 x);
    virtual ~CharacterFormSet();
    virtual void m4() {}
    virtual bool m5() const;
    virtual void m6(const sead::Vector3f& offset) {}
    virtual const sead::Vector3f& m7() const;

    void allocShapes(s32 num, sead::Heap* heap);
    bool init(ICharacterControllerParam* param, sead::Heap* heap);
    void sub_7100F66D34(s32 index);

    /* 0x08 */ sead::Buffer<CharacterControllerShape> mShapes;
    // createFormSet passes the param's height_enable_hitting_wall; the default for each form's _18.
    /* 0x18 */ f32 _18;
};
KSYS_CHECK_SIZE_NX150(CharacterFormSet, 0x20);

// vtable 0x71024f5e90: a CharacterFormSet with two capsule forms.
class Unk_71024f5e90 : public CharacterFormSet {
    SEAD_RTTI_OVERRIDE(Unk_71024f5e90, CharacterFormSet)
public:
    struct Param {
        struct Form {
            f32 height;
            f32 radius;
        };
        Form forms[2];
        sead::Vector3f offset;
    };

    Unk_71024f5e90() : CharacterFormSet(0.1f) {}
    ~Unk_71024f5e90() override;

    static Unk_71024f5e90* make(const Param& param, sead::Heap* heap);
    void m4() override;
    // m6 (0x7100f67444, sets mOffset and moves both capsules' vertices) is not declared yet:
    // it needs hkpCapsuleShape::setVertex, which lib/hkStubs does not define.
    const sead::Vector3f& m7() const override;

    /* 0x1c */ f32 mRadius[2] = {1.0f, 1.0f};
    /* 0x24 */ f32 mHeight[2] = {2.0f, 1.0f};
    // (0, capsule top vertex height, 0) per form.
    /* 0x2c */ sead::Vector3f _2c[2];
    // (0, radius, 0) per form.
    /* 0x44 */ sead::Vector3f _44[2];
    /* 0x5c */ sead::Vector3f mOffset;
};
KSYS_CHECK_SIZE_NX150(Unk_71024f5e90, 0x68);

}  // namespace ksys::phys
