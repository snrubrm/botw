#include "Game/gameUnk_71024739d0.h"

namespace uking {

Unk_71024739d0::Unk_71024739d0(ksys::phys::GroundHit ground_hit) : mQuery(nullptr, ground_hit) {}

Unk_71024739d0::~Unk_71024739d0() = default;

bool Unk_71024739d0::worldRayCast() {
    return mQuery.worldRayCast(ksys::phys::ContactLayerType::Entity);
}

void Unk_71024739d0::setStart(const sead::Vector3f& start) {
    mQuery.setStart(start);
    mStart = start;
}

void Unk_71024739d0::setEnd(const sead::Vector3f& end) {
    mQuery.setEnd(end);
    mEnd = end;
}

void Unk_71024739d0::getHitPosition(sead::Vector3f* position) const {
    mQuery.getHitPosition(position);
}

void Unk_71024739d0::getHitNormal(sead::Vector3f* normal) const {
    mQuery.getHitNormal(normal);
}

void Unk_71024739d0::sub_710090D73C() {
    mQuery.enableLayer(ksys::phys::ContactLayer::EntityGround);
    mQuery.enableLayer(ksys::phys::ContactLayer::EntityGroundRough);
    mQuery.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
    mQuery.enableLayer(ksys::phys::ContactLayer::EntityTree);
}

void Unk_71024739d0::sub_710090D784() {
    mQuery.enableLayer(ksys::phys::ContactLayer::EntityWater);
}

void Unk_71024739d0::sub_710090D790() {
    mQuery.enableLayer(ksys::phys::ContactLayer::EntityNPC);
    mQuery.enableLayer(ksys::phys::ContactLayer::EntityObject);
    mQuery.enableLayer(ksys::phys::ContactLayer::EntitySmallObject);
    mQuery.enableLayer(ksys::phys::ContactLayer::EntityRope);
    mQuery.enableLayer(ksys::phys::ContactLayer::EntityGround);
    mQuery.enableLayer(ksys::phys::ContactLayer::EntityGroundRough);
    mQuery.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
    mQuery.enableLayer(ksys::phys::ContactLayer::EntityTree);
}

void Unk_71024739d0::sub_710090D808() {
    mQuery.enableLayer(ksys::phys::ContactLayer::EntityPlayer);
    mQuery.enableLayer(ksys::phys::ContactLayer::EntityNPC);
    mQuery.enableLayer(ksys::phys::ContactLayer::EntityObject);
    mQuery.enableLayer(ksys::phys::ContactLayer::EntitySmallObject);
}

void Unk_71024739d0::sub_710090D850() {
    mQuery.enableLayer(ksys::phys::ContactLayer::EntityGround);
    mQuery.enableLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
    mQuery.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
    mQuery.enableLayer(ksys::phys::ContactLayer::EntityTree);
    mQuery.enableLayer(ksys::phys::ContactLayer::EntityObject);
}

void Unk_71024739d0::sub_710090D8A4() {
    mQuery.enableLayer(ksys::phys::ContactLayer::EntityGround);
    mQuery.enableLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
    mQuery.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
    mQuery.enableLayer(ksys::phys::ContactLayer::EntityTree);
    mQuery.enableLayer(ksys::phys::ContactLayer::EntityObject);
    mQuery.enableLayer(ksys::phys::ContactLayer::EntityWater);
}

}  // namespace uking
