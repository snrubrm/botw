#include "KingSystem/Physics/physConversions.h"
#include <Havok/Physics2012/Collide/Shape/Convex/Capsule/hkpCapsuleShape.h>
#include <algorithm>
#include "KingSystem/Physics/CharacterController/physCharacterFormSet.h"

namespace ksys::phys {

// NON_MATCHING: the two vertex temporaries swap stack slots and vector registers.
Unk_71024f5e90* Unk_71024f5e90::make(const Param& param, sead::Heap* heap) {
    auto* set = new (heap) Unk_71024f5e90();
    set->allocShapes(2, heap);
    for (s32 i = 0; i < 2; ++i) {
        const f32 height = param.forms[i].height;
        const f32 radius = param.forms[i].radius;
        const f32 top = std::max(height - radius, radius + 0.01f);
        const hkVector4f a(param.offset.x, radius + param.offset.y, param.offset.z);
        const hkVector4f b(param.offset.x, param.offset.y + top, param.offset.z);
        auto* shape = new hkpCapsuleShape(a, b, radius);
        set->_2c[i] = {0, top, 0};
        set->_44[i] = {0, radius, 0};
        set->mRadius[i] = radius;
        set->mHeight[i] = height;
        set->mShapes[i]._0 = shape;
    }
    set->mOffset = param.offset;
    return set;
}

void Unk_71024f5e90::m4() {
    for (s32 i = 0; i < mShapes.size(); ++i) {
        delete mShapes[i]._0;
        mShapes[i]._0 = nullptr;
    }
}

Unk_71024f5e90::~Unk_71024f5e90() = default;

// NON_MATCHING: instruction scheduling (the y sums and the offset.z load are ordered differently).
void Unk_71024f5e90::m6(const sead::Vector3f& offset) {
    mOffset = offset;
    for (s32 i = 0; i < 2; ++i) {
        const hkVector4f top = toHkVec4(_2c[i] + offset);
        const hkVector4f bottom = toHkVec4(offset + _44[i]);
        // mShapes holds const shape pointers; the capsules were created by make().
        auto* shape = const_cast<hkpCapsuleShape*>(static_cast<const hkpCapsuleShape*>(mShapes[i]._0));
        shape->setVertex(0, bottom);
        shape->setVertex(1, top);
    }
}

const sead::Vector3f& Unk_71024f5e90::m7() const {
    return mOffset;
}

}  // namespace ksys::phys
