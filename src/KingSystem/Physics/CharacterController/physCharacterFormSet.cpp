#include "KingSystem/Physics/CharacterController/physCharacterFormSet.h"
#include <Havok/Physics2012/Collide/Shape/hkpShape.h>
#include <math/seadMathCalcCommon.h>
#include "KingSystem/Physics/RigidBody/Shape/physCapsuleShape.h"
#include "KingSystem/Physics/RigidBody/Shape/physCharacterPrismShape.h"
#include "KingSystem/Physics/RigidBody/Shape/physSphereShape.h"
#include "KingSystem/Physics/System/physCharacterControllerParam.h"

namespace ksys::phys {

CharacterFormSet::CharacterFormSet(f32 x) : _18(x) {}

CharacterFormSet::~CharacterFormSet() {
    for (s32 i = 0; i < mShapes.size(); ++i) {
        if (mShapes[i]._8) {
            delete mShapes[i]._8;
            mShapes[i]._8 = nullptr;
        }
    }
    mShapes.freeBuffer();
}

bool CharacterFormSet::m5() const {
    return mShapes[0]._0->getType() == hkcdShapeType::LIST;
}

void CharacterFormSet::allocShapes(s32 num, sead::Heap* heap) {
    mShapes.tryAllocBuffer(num, heap);
}

bool CharacterFormSet::init(ICharacterControllerParam* param, sead::Heap* heap) {
    allocShapes(param->getNumForms(), heap);
    bool ok = false;
    for (s32 i = 0; i < mShapes.size(); ++i) {
        auto& entry = mShapes[i];
        entry._8 = param->createShape(i, heap);
        if (entry._8) {
            entry._0 = entry._8->getHavokShapeConst();
            sub_7100F66D34(i);
            ok = true;
        }
    }
    return ok;
}

// NON_MATCHING: prism/sphere field loads and stores are scheduled differently.
void CharacterFormSet::sub_7100F66D34(s32 index) {
    auto& entry = mShapes[index];
    entry._10 = false;
    entry._11 = 0;
    entry._12 = false;
    entry._14 = 0;
    entry._18 = _18;
    entry._20.set(0, 0, 0);
    auto* shape = entry._8;
    if (shape->getType() == ShapeType::Capsule) {
        auto* capsule = sead::DynamicCast<CapsuleShape>(shape);
        if (!capsule)
            return;
        sead::Vector3f a, b;
        capsule->getVertices(&a, &b);
        if ((a.x - b.x) * (a.x - b.x) + (a.z - b.z) * (a.z - b.z) <
            sead::Mathf::epsilon()) {
            entry._10 = true;
            entry._14 = capsule->getRadius();
            entry._18 = capsule->getRadius();
            if (a.x == 0.0f && a.z == 0.0f && b.x == 0.0f && b.z == 0.0f)
                entry._11 = 1;
        }
        entry._12 = true;
        entry._20 = b.y < a.y ? b : a;
        entry._20.y -= capsule->getRadius();
    } else if (shape->getType() == ShapeType::Sphere) {
        auto* sphere = sead::DynamicCast<SphereShape>(shape);
        if (!sphere)
            return;
        entry._10 = true;
        entry._14 = sphere->mRadius;
        entry._18 = sphere->mRadius;
        if (sphere->mTranslate.x == 0.0f && sphere->mTranslate.z == 0.0f)
            entry._11 = 1;
        entry._12 = true;
        entry._20 = sphere->mTranslate;
        entry._20.y -= sphere->mRadius;
    } else {
        auto* prism = sead::DynamicCast<CharacterPrismShape>(shape);
        if (!prism)
            return;
        entry._10 = true;
        entry._14 = prism->mRadius;
        entry._18 = prism->mRing0Distance;
        entry._1c = prism->mRing1Distance;
        if (prism->mOffset.x == 0.0f && prism->mOffset.z == 0.0f)
            entry._11 = 1;
        entry._12 = true;
        entry._20 += prism->mOffset;
    }
}

const sead::Vector3f& CharacterFormSet::m7() const {
    return sead::Vector3f::zero;
}

}  // namespace ksys::phys
