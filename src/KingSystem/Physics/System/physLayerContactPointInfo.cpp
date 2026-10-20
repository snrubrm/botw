#include "KingSystem/Physics/System/physLayerContactPointInfo.h"
#include <Havok/Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <Havok/Physics2012/Dynamics/Collide/ContactListener/hkpContactPointEvent.h>
#include <Havok/Physics2012/Dynamics/Constraint/Contact/hkpContactPointProperties.h>
#include <Havok/Physics2012/Utilities/CharacterControl/CharacterRigidBody/hkpCharacterRigidBody.h>
#include <limits>
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/physConversions.h"
#include "KingSystem/Physics/System/physContactMgr.h"
#include "KingSystem/Physics/System/physUtil.h"
#include "KingSystem/Physics/System/physSystem.h"

namespace ksys::phys {

LayerContactPointInfo* LayerContactPointInfo::make(sead::Heap* heap, int num, int num2,
                                                   const sead::SafeString& name, int a, int b,
                                                   int c) {
    return System::instance()->allocLayerContactPointInfo(heap, num, num2, name, a, b, c);
}

void LayerContactPointInfo::free(LayerContactPointInfo* instance) {
    System::instance()->freeLayerContactPointInfo(instance);
}

bool LayerContactPointInfo::registerLayerPair(ContactLayer layer1, ContactLayer layer2,
                                              bool enabled) {
    if (mLayerType == ContactLayerType::Invalid)
        mLayerType = getContactLayerType(layer1);

    if (!isPairUnknown(layer1, layer2))
        return false;

    // Add a new one.
    auto* entry = mLayerEntries.emplaceBack();
    if (entry == nullptr)
        return false;

    entry->layer1 = layer1;
    entry->layer2 = layer2;
    entry->enabled = enabled;
    [&] { System::instance()->registerContactPointLayerPair(this, layer1, layer2, enabled); }();
    return true;
}

bool LayerContactPointInfo::isPairUnknown(ContactLayer layer1, ContactLayer layer2) const {
    for (int i = 0; i < mLayerEntries.size(); ++i) {
        const auto* entry = mLayerEntries[i];
        if (int(layer1) == entry->layer1 && int(layer2) == entry->layer2)
            return false;
        if (int(layer1) == entry->layer2 && int(layer2) == entry->layer1)
            return false;
    }
    return true;
}

LayerContactPointInfo::LayerContactPointInfo(const sead::SafeString& name, int a, int b, int c)
    : ContactPointInfoBase(name, a, b, c) {}

LayerContactPointInfo::~LayerContactPointInfo() = default;

void LayerContactPointInfo::allocPoints(sead::Heap* heap, int num, int num2) {
    mPoints.allocBufferAssert(num, heap);
    mLayerEntries.allocBuffer(num2, heap);
}

void LayerContactPointInfo::freePoints() {
    mPoints.freeBuffer();
    mLayerEntries.freeBuffer();
}

void LayerContactPointInfo::Iterator::getPointPosition(sead::Vector3f* out, Point point) const {
    const float separating_distance = getPoint()->separating_distance;
    out->e = getPoint()->position.e;

    switch (point) {
    case Point::BodyA: {
        if (getPoint()->flags.isOn(ContactPoint::Flag::Penetrating))
            return;
        *out += getPoint()->separating_normal * -separating_distance;
        break;
    }

    case Point::BodyB: {
        if (!getPoint()->flags.isOn(ContactPoint::Flag::Penetrating))
            return;
        *out += getPoint()->separating_normal * separating_distance;
        break;
    }

    case Point::Midpoint:
    default: {
        *out += getPoint()->separating_normal * separating_distance * 0.5f;
        break;
    }
    }
}

sead::Vector3f LayerContactPointInfo::Iterator::getPointPosition(Point point) const {
    sead::Vector3f out;
    getPointPosition(&out, point);
    return out;
}

LayerContactPointInfo::Iterator::Iterator(const LayerContactPointInfo::Points& points, int count)
    : mPoints(points.getBufferPtr()), mPointsNum(count), mPointsStart(points.getBufferPtr()) {
    for (int i = 0; i != count; ++i) {
        if (!mPoints[i]->flags.isOn(ContactPoint::Flag::Invalid))
            break;
        ++mIdx;
    }
}

LayerContactPointInfo::Iterator::Iterator(const LayerContactPointInfo::Points& points, int count,
                                          IsEnd is_end)
    : mIdx(count), mPoints(points.getBufferPtr()), mPointsNum(count),
      mPointsStart(points.getBufferPtr()) {}

Unk_71024f9510* Unk_71024f9510::make(sead::Heap* heap, RigidBody* body,
                                     CharacterController* controller, bool enabled) {
    auto* listener = new (heap, 8) Unk_71024f9510(body, controller, enabled);
    body->getHkBody()->addContactListener(listener);
    return listener;
}

// NON_MATCHING: vector calculations are scheduled differently, and the contact-layer argument
// lacks the original zero-extension at the call boundary.
void Unk_71024f9510::contactPointCallback(const hkpContactPointEvent& event) {
    if (event.m_contactPoint->getPosition().getInt24W() == hkpCharacterRigidBody::m_magicNumber)
        return;
    if (event.m_contactPointProperties->m_flags & hkContactPointMaterial::CONTACT_IS_DISABLED)
        return;

    RigidBody* other_body = getRigidBody(*event.getBody(1));
    f32 sign = 1.0f;
    if (other_body == mBody) {
        other_body = getRigidBody(*event.getBody(0));
        sign = -1.0f;
    }
    if (!xxx_3(other_body->getContactLayer().value()))
        return;

    const sead::Vector3f normal = toVec3(event.m_contactPoint->getSeparatingNormal());
    sead::Vector3f direction(sign * normal.x, 0.0f, sign * normal.z);
    if (direction.normalize() >= std::numeric_limits<f32>::epsilon()) {
        sead::Vector3f shape_position;
        if (!mController->sub_7100F62EFC(&shape_position, mController->_224))
            return;
        sead::Matrix34f transform;
        mController->physicsXXXGetMtx_1(&transform);
        const sead::Vector3f world_position = transform * shape_position;
        const sead::Vector3f contact_position = toVec3(event.m_contactPoint->getPosition());
        const sead::Vector3f offset(contact_position.x - world_position.x, 0.0f,
                                   contact_position.z - world_position.z);
        if (!(direction.dot(offset) > 0.0f)) {
            if (mEnabled)
                return;
            sead::Vector3f velocity;
            mController->sub_7100F5F598(&velocity);
            velocity.y = 0.0f;
            if (velocity.normalize() < std::numeric_limits<f32>::epsilon())
                return;
            if (!(direction.dot(velocity) < 0.0f))
                return;
            event.m_contactPoint->setNormalOnly(toHkVec4(direction * sign));
            return;
        }
    } else if (mEnabled) {
        return;
    }
    event.m_contactPointProperties->m_flags |= hkContactPointMaterial::CONTACT_IS_DISABLED;
}

void sub_7100FCFEB8(Unk_71024f9510* listener) {
    listener->mBody->getHkBody()->removeContactListener(listener);
    delete listener;
}

}  // namespace ksys::phys
