#include "KingSystem/ActorSystem/actUnk_71006e45c4.h"
#include "Game/gameSceneSubsysMisc.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/System/StageInfo.h"

namespace ksys::act {

// 0x71006e4950: source scope is inferred; the only direct caller passes this object.
void sub_71006E4950(Unk_71006e45c4* object) {
    Actor* actor = object->mActor;
    if (auto* awareness = actor->get548()) {
        if (auto* entry = sead::DynamicCast<Unk_71024dc858>(awareness->m8())) {
            const auto& aabb = object->mActor->getAabb();
            const sead::Vector3f delta = aabb.getMin() - aabb.getMax();
            entry->_4c = delta.length() * 0.5f;
        }
    } else {
        // The native path evaluates cstr twice and discards both results; its purpose is unknown.
        const auto& profile = actor->getProfile();
        profile.cstr();
        profile.cstr();
    }
}

// NON_MATCHING: flag-address placement changes register allocation.
void Unk_71006e45c4::m5(Actor* actor) {
    mActor = actor;
    bool has_metal = false;
    if (actor) {
        if (auto* bodies = actor->getRigidBodyByName(sub_71007A24D0()->cstr())) {
            for (s32 i = 0, count = bodies->getRigidBodies().size(); i < count; ++i) {
                if (sub_71009059FC(bodies->getRigidBody(i))) {
                    has_metal = true;
                    break;
                }
            }
        }
    }
    if (has_metal)
        mFlags.setBitOn(1);
    else
        mFlags.setBitOff(1);
    if (mFlags & 2) {
        mActor->sub_71011D0204(1);
        sub_71006E4950(this);
    }
    mFlags &= ~8u;
}


// 0x71006e770c: free scope inferred from the native no-argument caller and body.
bool sub_71006E770C() {
    return ksys::StageInfo::getCurrentMapType() == "CDungeon" &&
           ksys::StageInfo::getCurrentMapName() == "Dungeon126";
}

Unk_71006e45c4::Unk_71006e45c4() {
    mFlags |= 1;
}

Unk_71006e45c4::~Unk_71006e45c4() {
    sub_71006E4668();
}

void Unk_71006e45c4::sub_71006E4668() {
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

void Unk_71006e45c4::m11() {
    sub_71006E6194();
}

void Unk_71006e45c4::m12() {
    if (m2()) {
        GameSceneSubsys5::instance()->sub_7100905C70();
        if (auto* body = mActor->getMainBody())
            body->setMotionFlag(phys::RigidBody::MotionFlag::_20000);
    }
}

void Unk_71006e45c4::m13() {
    sub_71006E4668();
}

void Unk_71006e45c4::m14() {
    sub_71006E4668();
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
