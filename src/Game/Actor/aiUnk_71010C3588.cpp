#include "Game/Actor/aiUnk_71010C3588.h"
#include <aal/aalShape.h>
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "Game/gameUnkRttiPlaceholders.h"

Unk_710250c260::Unk_710250c260() = default;

Unk_710250c260::~Unk_710250c260() {
    if (mBody) {
        if (mBody->isAddedToWorld())
            mBody->removeFromWorldImmediately(nullptr);
        delete mBody;
        mBody = nullptr;
    }
}

Unk_710250c3c8::Unk_710250c3c8() = default;

Unk_710250c3c8::~Unk_710250c3c8() {
    destroy(true);
    if (mBody) {
        if (mBody->isAddedToWorld())
            mBody->removeFromWorldImmediately(nullptr);
        delete mBody;
        mBody = nullptr;
    }
    if (mShape) {
        mShape->destroy();
        mShape = nullptr;
    }
}

bool Unk_710250c3c8::sub_71010C4284() const {
    return !mBody || !mBody->isAddedToWorld();
}


Unk_710250c118::~Unk_710250c118() = default;

Unk_710250c280::~Unk_710250c280() = default;

Unk_710250c3e8::~Unk_710250c3e8() = default;

Unk_710250c550::~Unk_710250c550() = default;

Unk_710250c6d8::~Unk_710250c6d8() = default;

bool Unk_710250c118::m29(const ElementName& name, sead::Heap* heap) {
    if (mHolder)
        mHolder->_1a = u8(mArg._4);
    setRigidBody(mArg.body, true);
    return true;
}

void Unk_710250c118::m33(bool a, bool fixed) {
    if (mArg.body)
        mArg.body->setFixed(ksys::phys::Fixed(fixed), ksys::phys::PreserveVelocities(true));
}

bool Unk_710250c280::m29(const ElementName& name, sead::Heap* heap) {
    if (mHolder) {
        mHolder->_3c = mArg._0;
        mHolder->_1c = mArg._4;
    }
    setRigidBody(mArg.body, true);
    return true;
}

void Unk_710250c280::m35(f32 delta_frame) {
    if (mHolder) {
        mHolder->_3c = mArg._0;
        mHolder->_1c = mArg._4;
    }
}

void Unk_710250c280::m33(bool a, bool fixed) {
    if (mArg.body)
        mArg.body->setFixed(ksys::phys::Fixed(fixed), ksys::phys::PreserveVelocities(true));
}

bool Unk_710250c550::m29(const ElementName& name, sead::Heap* heap) {
    if (mHolder)
        mHolder->_18 |= 0x100;
    setRigidBody(_50, true);
    return true;
}

void Unk_710250c550::m33(bool a, bool fixed) {
    if (_50)
        _50->setFixed(ksys::phys::Fixed(fixed), ksys::phys::PreserveVelocities(true));
}

bool Unk_710250c6d8::m29(const ElementName& name, sead::Heap* heap) {
    if (mHolder)
        mHolder->_1a = 2;
    setRigidBody(_50, true);
    return true;
}

void Unk_710250c6d8::m33(bool a, bool fixed) {
    if (_50)
        _50->setFixed(ksys::phys::Fixed(fixed), ksys::phys::PreserveVelocities(true));
}
