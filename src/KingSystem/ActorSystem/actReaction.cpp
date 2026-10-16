#include "KingSystem/ActorSystem/actReaction.h"
#include <math/seadBoundBox.h>
#include <algorithm>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace ksys::act {
Reaction* Reaction::sInstance;

void Reaction::Unk1::sub_7100EC66FC(Actor* actor) {
    _110 = 2;
}

f32 Reaction::Unk1::sub_7100EC877C() const {
    return 0.7f;
}

s32 Reaction::Unk1::sub_7100EC87A4() const {
    return 7;
}

s8 Reaction::Unk1::sub_7100EC89BC() const {
    return 5;
}

// NON_MATCHING: min / max operand order, the 2 / 3 choice becomes a csel, and the size is returned as a
// 64-bit register move.
s32 Reaction::sub_7100EC2278(Actor* actor, bool* is_long) {
    if (auto* body = actor->getMainBody()) {
        sead::BoundBox3f aabb;
        body->getAabbInLocal(&aabb);
        const f32 x = aabb.getMax().x - aabb.getMin().x;
        const f32 y = aabb.getMax().y - aabb.getMin().y;
        const f32 z = aabb.getMax().z - aabb.getMin().z;
        const f32 min = std::min(std::min(x, y), z);
        const f32 max = std::max(std::max(x, y), z);

        s32 size;
        if (max < 0.4f)
            size = 0;
        else if (max < 0.75f)
            size = 1;
        else if (min > 3.0f)
            size = 4;
        else if (min > 1.5f)
            size = 3;
        else
            size = 2;

        if (is_long) {
            const bool is_large = max > 4.5f;
            const bool is_thin = min / max < 0.35f;
            const bool is_flat = (x + y + z - min - max) / max < 0.35f;
            *is_long = is_large && is_thin && is_flat;
        }
        return size;
    }

    s32 size = 2;
    if (auto* body = actor->getPhysicsMainBody()) {
        sead::BoundBox3f aabb;
        body->getAabbInLocal(&aabb);
        size = aabb.getMax().y - aabb.getMin().y < 2.2f ? 2 : 3;
    }
    if (is_long)
        *is_long = false;
    return size;
}
}  // namespace ksys::act
