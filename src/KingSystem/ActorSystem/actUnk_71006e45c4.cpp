#include "KingSystem/ActorSystem/actUnk_71006e45c4.h"
#include "Game/gameSceneSubsysMisc.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace ksys::act {

Unk_71006e45c4::Unk_71006e45c4() {
    mFlags |= 1;
}

Unk_71006e45c4::~Unk_71006e45c4() {
    releaseFromScene();
}

void Unk_71006e45c4::releaseFromScene() {
    auto* subsys = GameSceneSubsys5::instance();
    if (!subsys)
        return;
    if (subsys->_318 == this)
        sub_71006E4DF0(&subsys->_150, false);
    else if (subsys->_c8.hasProcById(mActor))
        subsys->sub_7100905C70();
}

bool Unk_71006e45c4::m2() {
    if (mFlags & 4) {
        if (auto* subsys = GameSceneSubsys5::instance())
            return subsys->sub_71009059D4();
    }
    return false;
}

void Unk_71006e45c4::m12() {
    if (m2()) {
        GameSceneSubsys5::instance()->sub_7100905C70();
        if (auto* body = mActor->getMainBody())
            body->setMotionFlag(phys::RigidBody::MotionFlag::_20000);
    }
}

void Unk_71006e45c4::m13() {
    releaseFromScene();
}

void Unk_71006e45c4::m14() {
    releaseFromScene();
}

void Unk_71006e45c4::m3(bool enable) {
    if ((mFlags & 1) && !enable) {
        if (mFlags & 2) {
            mActor->sub_71011D0228(3);
            mFlags &= ~0x80u;
        }
    } else if (!(mFlags & 1) && enable) {
        if (mFlags & 2)
            mActor->sub_71011D0204(1);
    }
    if (enable)
        mFlags |= 1;
    else
        mFlags &= ~1u;
}

bool Unk_71006e45c4::m4() {
    return mFlags & 1;
}

bool Unk_71006e45c4::m9() {
    if (mFlags & 0x100)
        return true;
    return mActor->getActorFlags2().isOn(Actor::ActorFlag2::_40);
}

bool Unk_71006e45c4::m15() {
    return mFlags >> 1 & 1;
}

bool Unk_71006e45c4::m16() {
    return mFlags >> 9 & 1;
}

}  // namespace ksys::act
