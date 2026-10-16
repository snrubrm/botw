#include "KingSystem/Chemical/chmElement.h"
#include <cmath>
#include <math/seadBoundBox.h>
#include <math/seadMathCalcCommon.h>
#include <thread/seadThread.h>
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Chemical/chmChemical.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/World/worldManager.h"

void Unk_7102518620::onMaxPositionExceeded(ksys::phys::RigidBody* body) {
    if (auto* element = mElement) {
        if (element->mHolder)
            element->mHolder->sub_7100D8CF88();
        element->m30();
    }
}

void Unk_7102518620::onBodyShapeChanged(ksys::phys::RigidBody* body) {
    if (mElement)
        mElement->updateRadius();
}

Unk_7102518688::Unk_7102518688(const ElementName& name, sead::Heap* heap, bool flag8)
    : Element(name, heap) {
    if (flag8)
        mFlags = 8;
    mTag.mElement = this;
}

Unk_7102518688::~Unk_7102518688() {
    if (mFlags & 8 && mHolder) {
        ksys::act::Chemical::sub_7100D8CD24(mHolder, true);
        unlinkHolderMaybe();
    }
    if (mRigidBody) {
        mRigidBody->setUserTag(nullptr);
        mRigidBody = nullptr;
    }
    mTag.mElement = nullptr;
}

void Unk_7102518688::m4(const sead::Matrix34f& mtx) {
    if (mRigidBody)
        mRigidBody->changePositionAndRotation(mtx);
}

void Unk_7102518688::m5(sead::Matrix34f* mtx) const {
    if (mHolder && mRigidBody)
        mRigidBody->getTransform(mtx);
}

bool Unk_7102518688::m9() {
    if (mHolder && mHolder->_78 == 1)
        return true;
    return false;
}

bool Unk_7102518688::m10() {
    if (mRigidBody && mRigidBody->isAddedToWorld() && mHolder)
        return true;
    return false;
}

void Unk_7102518688::m12() {}

f32 Unk_7102518688::m16() {
    if (!mRigidBody)
        return 0.0f;
    return Element::m16();
}

f32 Unk_7102518688::m22() {
    if (!mRigidBody)
        return 1.0f;
    return mRigidBody->getVolume();
}

f32 Unk_7102518688::m23() {
    if (!mRigidBody)
        return 1.0f;
    const f32 four_pi = 4.0f * sead::Mathf::pi();
    const f32 r2 = std::pow(mRigidBody->getVolume() * 3.0f / four_pi, 2.0f / 3.0f);
    return r2 * four_pi * 0.25f;
}

void Unk_7102518688::m30() {
    if (mRigidBody)
        mRigidBody->removeFromWorld();
}

void Unk_7102518688::x() {
    ksys::act::Chemical::sub_7100D8CD24(mHolder, true);
}

void Unk_7102518688::m34() {
    if (mHolder && mFlags & 8)
        mHolder->_18 |= 0x10;
}

// NON_MATCHING: the original tests the combined result with cbz; we compare it with 1.
bool Unk_7102518688::m31() {
    notifyChemicalMaybe();
    mFlags |= 1;
    mTag.mElement = nullptr;
    bool removed = true;
    if (mRigidBody) {
        mRigidBody->removeFromWorldAndResetLinks();
        if (mRigidBody->isAddedToWorld() || mRigidBody->isAddingBodyToWorld())
            removed = false;
    }
    const bool result = m37() && removed;
    if (result)
        mFlags |= 4;
    return result;
}

void Unk_7102518688::m32() {
    notifyChemicalMaybe();
    mFlags |= 3;
    mTag.mElement = nullptr;
    if (mRigidBody)
        mRigidBody->removeFromWorldImmediatelyAndResetLinks();
    m38();
}

void Unk_7102518688::m3() {
    if (!(mFlags & 1))
        m35();
}

f32 Unk_7102518688::m7() {
    if (!mRigidBody)
        return 0.0f;
    sead::BoundBox3f box;
    mRigidBody->getAabbInWorld(&box);
    return box.getMin().y;
}

void Unk_7102518688::m8() {
    if (!(mFlags & 1))
        m36();
}

void Unk_7102518688::setRigidBody(ksys::phys::RigidBody* body, bool add_to_world) {
    if (mFlags & 1)
        return;

    mRigidBody = body;
    body->setContactLayer(ksys::phys::ContactLayer::SensorChemicalElement);
    mRigidBody->setUserTag(&mTag);

    if (mHolder->_8->type.ref() == 1) {
        body->setContactPointInfo(ksys::world::Manager::instance()->getChemicalMgrUnchecked()->_b00);
    } else if (mHolder->_80 && mHolder->_80->_c & 0x10000000) {
        body->setCollisionInfo(ksys::world::Manager::instance()->getChemicalMgrUnchecked()->_b08);
    } else {
        body->setContactPointInfo(ksys::world::Manager::instance()->getChemicalMgrUnchecked()->_af8);
    }

    ksys::act::sub_7100E3F3AC(mRigidBody, mHolder);

    if (add_to_world && !mRigidBody->isAddedToWorld() && !mRigidBody->isAddingBodyToWorld()) {
        mRigidBody->addToWorld();
        notifyChemicalMaybe();
    }

    m8();
    updateRadius();
}
