#include "Game/Actor/actRemains.h"
#include <basis/seadNew.h>
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71024f15c0.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::act {

Remains::Remains(const CreateArg& arg) : DynamicActor(arg) {}

Remains::~Remains() = default;

ksys::act::BaseProc* Remains::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) Remains(arg);
}

bool Remains::prepareInit_(sead::Heap* heap, PrepareArg& arg) {
    if (!DynamicActor::prepareInit_(heap, arg))
        return false;
    _b90 = new (heap) Unk_71024f15c0;
    return _b90 != nullptr;
}

void Remains::preDelete2_(const PreDeleteArg& arg) {
    if (_b90) {
        delete _b90;
        _b90 = nullptr;
    }
    DynamicActor::preDelete2_(arg);
}

void Remains::m63() {
    DynamicActor::m63();
    if (_b90) {
        _b90->m2();
        getHomeMtx(&mMtx);
        nullsub_4648();
    }
    _bb8 = false;
    _bb9 = true;
}

void Remains::initMaybe() {
    DynamicActor::initMaybe();
}

void Remains::updateLodStuff(ksys::act::Actor* other) {
    if (!other)
        return;
    auto* remains = static_cast<Remains*>(other);
    if (!_b90 || !remains->_b90)
        return;
    _b90->sub_7100EEBDB8(remains->_b90);
    mMtx = remains->mMtx;
    nullsub_4648();
}

void Remains::calcMaybe() {
    DynamicActor::calcMaybe();
    if (_bb8)
        sub_71002CA3EC();
}

void Remains::updatePositionMaybe() {
    DynamicActor::updatePositionMaybe();
}

// NON_MATCHING: scheduling/regalloc (the original selects both coordinate addresses before
// loading them)
void Remains::sub_71002CA3EC() {
    auto* aslist = mASList;
    if (!aslist || !aslist->_14.isValid())
        return;

    sead::Matrix34f mtx;
    mtx = aslist->_80;
    const f32 x = mMapObject ? mMapObject->getTranslate().x : mMtx.m[0][3];
    const f32 z = mMapObject ? mMapObject->getTranslate().z : mMtx.m[2][3];
    // Move to the centre of the 1000-unit grid cell that contains the actor's position.
    const sead::Vector3f offset{
        (x >= 0.0f ? 1.0f : -1.0f) *
            (sead::Mathf::floor(sead::Mathf::abs(x) / 1000.0f) * 1000.0f + 500.0f),
        0.0f,
        (z >= 0.0f ? 1.0f : -1.0f) *
            (sead::Mathf::floor(sead::Mathf::abs(z) / 1000.0f) * 1000.0f + 500.0f)};
    mtx.m[0][3] += offset.x;
    mtx.m[1][3] += offset.y;
    mtx.m[2][3] += offset.z;

    if (_bb9) {
        _bb9 = false;
        actorPhysicsSetFlag2();
        if (auto* controller = getCharacterController())
            controller->sub_7100F60500(mtx);
        else if (auto* body = getMainBody())
            body->setTransform(mtx, ksys::phys::PropagateToLinkedMotions{true});
        else
            sub_71011C88C0(mtx);
    } else {
        if (auto* controller = getCharacterController())
            controller->sub_7100F5F938(mtx);
        else if (auto* body = getMainBody())
            body->changePositionAndRotation(mtx, std::numeric_limits<f32>::epsilon());
        else
            sub_71011C88C0(mtx);
    }
}

Unk_7100d3cd74* Remains::m101() {
    return &_b98;
}

}  // namespace uking::act
