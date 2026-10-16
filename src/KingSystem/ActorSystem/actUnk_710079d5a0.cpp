// Unk_7102459df8::Unk_710079d5a0 (TU from 0x79f600, separate from Unk_7102459df8: not inlined into it).
#include "KingSystem/ActorSystem/actUnk_7102459df8.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actPhysicsUserTag.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physCollisionInfo.h"

namespace ksys::act {

Unk_7102459df8::Unk_710079d5a0::Unk1::Unk1() = default;

void Unk_7102459df8::Unk_710079d5a0::sub_710079F600() {
    for (int i = 0; i < mNum; ++i) {
        mEntries[i].resetFlags();
        mEntries[i]._50.reset();
    }
    mNum = 0;
    _582 = 0;
}

// NON_MATCHING: the original takes the first list node before locking the collision info; regalloc.
void Unk_7102459df8::Unk_710079d5a0::sub_710079F9C0(sead::Buffer<phys::CollisionInfo*>* buffer,
                                                    Actor* actor) {
    for (auto* info : *buffer) {
        if (info->getCollidingBodies().size() == 0)
            continue;
        info->lock();
        for (auto& bodies : info->getCollidingBodies()) {
            auto* tag_b = sead::DynamicCast<PhysicsUserTag>(bodies.bodies[1]->getUserTag());
            if (!tag_b)
                continue;
            auto* tag_a = sead::DynamicCast<PhysicsUserTag>(bodies.bodies[0]->getUserTag());
            if (!tag_a)
                continue;
            auto* other = tag_a->getActor(nullptr, actor);
            if (!other)
                continue;
            ActorLinkConstDataAccess accessor;
            tag_b->acquireActor(&accessor);
            if (!accessor.hasProc(other)) {
                _582 = true;
                if (_588)
                    _588(other, &accessor, bodies.bodies[0], bodies.bodies[1]);
            }
        }
        info->unlock();
    }
}

}  // namespace ksys::act
