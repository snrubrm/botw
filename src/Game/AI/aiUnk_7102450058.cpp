#include "Game/AI/aiUnk_7102450058.h"
#include <prim/seadBitFlag.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actDropData.h"
#include "KingSystem/ActorSystem/actUnk_7100e4e084.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

// NON_MATCHING: scheduling only (the original materialises 10.0f / -1.0f after the stores to
// +0x20 / +0x2c)
CarriedData::CarriedData(ksys::act::Actor* actor) : mActor(actor) {}

CarriedData::~CarriedData() = default;

bool Unk_7102450298::init(sead::Heap* heap) {
    _30 = sub_7100F6D358(heap);
    return _30 != nullptr;
}

void Unk_7102450298::finalize() {
    if (_30) {
        ksys::phys::Constraint::destroy(_30);
        _30 = nullptr;
    }
}


void CarriedData::x_3(f32 a, f32 b) {
    auto* parent = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcParent());
    if (isPlayerProfile(parent) && b > 0.0f)
        _14 = sead::Mathf::clampMin(a / b, sead::Mathf::deg2rad(0.5f));
}

void CarriedData::x_19() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F62CA8(true);
        controller->sub_7100F62C14(_1c);
        controller->sub_7100F5F458(ksys::act::MotionType::_1);
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    } else if (auto* body = mActor->getMainBody()) {
        body->clearEntityMotionFlag4(true);
        body->setMaxImpulse(_1c);
        body->setLinearVelocity(sead::Vector3f::zero);
        body->setAngularVelocity(sead::Vector3f::zero);
        if (_2c & 0x80)
            body->disableContactLayer(ksys::phys::ContactLayer::EntitySmallObject);
    }
}

void CarriedData::x_16() {
    if (auto* data = mActor->m100()) {
        if (data->sub_7100E4F1D0(_14, _18))
            _2c |= 0x10;
    }
}

void CarriedData::x_6() {
    if (auto* data = mActor->m100()) {
        if (sead::BitFlagUtil::countOnBit(data->_1d0) >= 1)
            data->sub_7100E504C0();
    }
}

void CarriedData::x_8() {
    auto* data = mActor->m100();
    if (!data || !(data->_1d8 & 4))
        return;
    u8 flags = data->_1d0;
    if (flags & 1) {
        if ((_2c & 1) || data->_100 == 2) {
            flags &= ~1;
            data->_1d0 = flags;
        }
    }
    if (sead::BitFlagUtil::countOnBit(flags) <= 0)
        x_12();
}

void CarriedData::x_12() {
    if (auto* data = mActor->m100()) {
        if (data->_1d8 & 4)
            data->sub_7100E5052C();
    }
}

void CarriedData::updateIsDroppedFlag() {
    _2c &= 0x7f;
    auto* drop_data = mActor->getDropData();
    if (drop_data && drop_data->isFlag1Set())
        return;
    if (mActor->isWaitRevivalForDrop())
        return;
    _2c |= 0x80;
}
