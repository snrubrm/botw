#include "Game/Actor/aiUnk_710072A944.h"
#include "Game/Actor/aiUnk_71007292A0.h"
#include <random/seadGlobalRandom.h>
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actSwarm.h"
#include "Game/Actor/aiUnk_71007368A4.h"
#include "Game/Actor/aiUnk_710073fa90.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/Resource/Actor/resResourceDamageParam.h"
#include "KingSystem/Resource/Actor/resResourceDrop.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

// 0x7100728f14: inferred free scope; operates on the Swarm's animation lists.
void sub_7100728F14(uking::act::Swarm* swarm, const sead::SafeString& name, bool a3, bool a4,
                    int slot, int bank);

void sub_71007292A0(ksys::act::Actor* actor, const sead::SafeString& name, bool a3, bool a4,
                    int slot, int bank) {
    if (auto* swarm = sead::DynamicCast<uking::act::Swarm>(actor))
        sub_7100728F14(swarm, name, a3, a4, slot, bank);
}

// NON_MATCHING: normalized direction components stay in FP registers instead of GP registers.
void sub_7100729370(uking::act::Swarm* swarm, sead::Vector3f* direction, s32* count) {
    sead::Vector3f sum = sead::Vector3f::zero;
    s32 num_contacts = 0;
    for (const auto& body : swarm->_14f8) {
        if (!body.sub_71002D481C())
            continue;
        sead::Vector3f normal = body._c;
        normal.normalize();
        sum -= normal;
        ++num_contacts;
    }
    if (direction)
        *direction = sum;
    if (count)
        *count = num_contacts;
}

bool sub_7100729494(uking::act::Swarm* swarm) {
    return swarm->sub_71002D47D8(0) || swarm->sub_71002D47D8(1) ||
           swarm->sub_71002D47D8(2) || swarm->sub_71002D47D8(3);
}

// NON_MATCHING: the third boolean count is added with swapped integer operands.
s32 sub_71007294F4(uking::act::Swarm* swarm) {
    s32 count = swarm->sub_71002D47D8(0);
    count += swarm->sub_71002D47D8(1);
    count += swarm->sub_71002D47D8(2);
    count += swarm->sub_71002D47D8(3);
    return count;
}

void sub_7100729DA0(uking::act::Swarm* swarm, f32 scale) {
    for (s32 i = 0, count = swarm->_14c8.size(); i < count; ++i) {
        if (auto* unit = swarm->_14c8[i]) {
            const f32 x = sead::GlobalRandom::instance()->getF32() * scale;
            const f32 y = sead::GlobalRandom::instance()->getF32() * scale;
            const f32 z = sead::GlobalRandom::instance()->getF32() * scale;
            unit->_6c.set(unit->_60.x + x, unit->_60.y + y, unit->_60.z + z);
        }
    }
}

void sub_710072A944(uking::act::Swarm* swarm, f32 min, f32 max) {
    for (s32 i = 0; i < swarm->_14c8.size(); ++i) {
        if (auto* unit = swarm->_14c8[i])
            unit->_5c = sead::GlobalRandom::instance()->getF32Range(min, max);
    }
    for (s32 i = 0; i < swarm->_15e8.size(); ++i) {
        if (auto* unit = swarm->_15e8[i]._8._10)
            unit->_5c = max;
    }
}

void sub_7100729EA8(uking::act::Swarm* swarm) {
    for (s32 i = 0, n = swarm->_15e8.size(); i < n; ++i) {
        const auto& body = swarm->_15e8[i];
        if (auto* unit = body._8._10)
            sub_71007A2B64(body._8._18, &unit->_8);
        else
            sub_71007A2B64(body._8._18, &swarm->getMtx());
    }
}

void sub_7100729F34(uking::act::Swarm* swarm) {
    for (s32 i = 0, n = swarm->_15e8.size(); i < n; ++i)
        sub_71007A2D34(swarm->_15e8[i]._8._18);
}

void sub_710072A778(uking::act::Swarm* swarm, const sead::SafeString& name, f32 frame) {
    for (s32 i = 0, n = swarm->_14c8.size(); i < n; ++i) {
        if (auto* unit = swarm->_14c8[i])
            unit->sub_71002DA3A0(frame, name);
    }
}

bool sub_7100729D18(ksys::act::Actor* actor, sead::Vector3f* out, const sead::Vector3f& dir,
                    f32 speed, s32* b, bool flag) {
    SwarmUnitVectorGetter getter(sub_7100729558);
    return sub_7100729568(actor, out, &dir, b, getter, flag, speed);
}

bool sub_7100729D5C(f32 speed, uking::act::Swarm* swarm, void* a, const sead::Vector3f* pos,
                    void* b, bool flag) {
    SwarmUnitVectorGetter getter(sub_7100729560);
    return sub_7100729568(swarm, static_cast<sead::Vector3f*>(a), pos, static_cast<s32*>(b), getter,
                          flag, speed);
}

void sub_710072ABB4(ksys::act::Actor* actor) {
    if (auto* swarm = sead::DynamicCast<uking::act::Swarm>(actor)) {
        for (s32 i = 0; i < swarm->_15f8.size(); ++i) {
            if (auto* body = swarm->_15f8[i]._8._18)
                body->addToWorld();
        }
    }
}

void sub_710072AAE4(ksys::act::Actor* actor) {
    if (auto* swarm = sead::DynamicCast<uking::act::Swarm>(actor)) {
        for (s32 i = 0; i < swarm->_15f8.size(); ++i) {
            if (auto* body = swarm->_15f8[i]._8._18)
                body->removeFromWorld();
        }
    }
}

uking::act::Swarm::Unit* sub_710072A6DC(uking::act::Swarm* swarm, const sead::Vector3f& pos) {
    uking::act::Swarm::Unit* nearest = nullptr;
    f32 min_distance = sead::Mathf::infinity();
    for (s32 i = 0, count = swarm->_14c8.size(); i < count; ++i) {
        auto* unit = swarm->_14c8[i];
        if (!unit || (unit->_b8 & 1))
            continue;
        const f32 distance = (pos - unit->_8.getTranslation()).squaredLength();
        if (distance < min_distance) {
            min_distance = distance;
            nearest = unit;
        }
    }
    return nearest;
}

// NON_MATCHING: the local mask stack slot differs.
s32 sub_710072AA48(ksys::act::Actor* actor, s32 type) {
    auto* param = actor->getParam()->getRes().mDamageParam;
    if (!param)
        return 0;
    // Complete 18-word native lookup at 1E7B690; types outside the table use Sword (bit 0).
    static constexpr u32 sources[] = {1, 2, 4, 8, 0x10, 0x2000, 1, 0x8000, 1,
                                      1, 1, 1, 1, 1, 1, 1, 0x1000, 0x10000};
    sead::SafeString name;
    u32 source = u32(type) < 18 ? sources[type] : 1;
    sub_7100736C18(&source, &name);
    return sead::Mathf::round(param->getDamageRate(name));
}

// NON_MATCHING: the DropTable key construction is scheduled differently.
void swarmDropTableStuff(ksys::act::Actor* actor) {
    auto* root = actor->getRootAi();
    if (!root)
        return;
    auto* drop = actor->getParam()->getRes().mDropTable;
    const sead::SafeString table = "Swarm";
    if (!drop || drop->findTableIndex(table) == -1)
        return;
    root->getMapUnitParams().setString(table, "DropTable");
}

void sub_710072A514(uking::act::Swarm* swarm, const sead::Vector3f& front,
                   const sead::Vector3f& up) {
    sead::Matrix34f transform;
    ksys::util::sub_71011F00EC(&transform, front, up, sead::Vector3f::zero, true);
    for (s32 i = 0, count = swarm->_14c8.size(); i < count; ++i) {
        if (auto* unit = swarm->_14c8[i]) {
            sead::Matrix33f rotation;
            sub_7100741118(&rotation, unit->_8);
            sub_710074191C(&rotation, front, up, true, sead::Mathf::deg2rad(30.0f));
            unit->sub_71002D93E8(rotation);
        }
    }
}

void sub_710072A5F8(uking::act::Swarm* swarm, const sead::Vector3f& front,
                   const sead::Vector3f& up) {
    sead::Matrix34f transform;
    ksys::util::sub_71011F0260(&transform, front, up, sead::Vector3f::zero, false);
    for (s32 i = 0, count = swarm->_14c8.size(); i < count; ++i) {
        if (auto* unit = swarm->_14c8[i]) {
            sead::Matrix33f rotation;
            sub_7100741118(&rotation, unit->_8);
            sub_710074191C(&rotation, front, up, false, sead::Mathf::deg2rad(30.0f));
            unit->sub_71002D93E8(rotation);
        }
    }
}

// NON_MATCHING: direction component stores and matrix address allocation differ.
void sub_710072A264(uking::act::Swarm* swarm, const sead::Vector3f& target,
                   const sead::Vector3f& up) {
    for (s32 i = 0, count = swarm->_14c8.size(); i < count; ++i) {
        if (auto* unit = swarm->_14c8[i]) {
            sead::Vector3f direction = target - unit->_8.getTranslation();
            direction.normalize();
            sead::Matrix33f rotation;
            sub_7100741118(&rotation, unit->_8);
            sub_710074191C(&rotation, direction, up, true, sead::Mathf::deg2rad(30.0f));
            unit->sub_71002D93E8(rotation);
        }
    }
}

// NON_MATCHING: direction component stores and matrix address allocation differ.
void sub_710072A3BC(uking::act::Swarm* swarm, const sead::Vector3f& target,
                   const sead::Vector3f& up) {
    for (s32 i = 0, count = swarm->_14c8.size(); i < count; ++i) {
        if (auto* unit = swarm->_14c8[i]) {
            sead::Vector3f direction = target - unit->_8.getTranslation();
            direction.normalize();
            sead::Matrix33f rotation;
            sub_7100741118(&rotation, unit->_8);
            sub_710074191C(&rotation, direction, up, false, sead::Mathf::deg2rad(30.0f));
            unit->sub_71002D93E8(rotation);
        }
    }
}

// NON_MATCHING: direction and rotation use opposite stack slots.
void sub_7100729FAC(uking::act::Swarm* swarm, const sead::Vector3f& up) {
    for (s32 i = 0, count = swarm->_14c8.size(); i < count; ++i) {
        if (auto* unit = swarm->_14c8[i]) {
            sead::Vector3f direction = unit->_38.mean;
            direction.normalize();
            if (direction == sead::Vector3f(0.0f, 0.0f, 0.0f))
                continue;
            sead::Matrix33f rotation;
            sub_7100741118(&rotation, unit->_8);
            sub_710074191C(&rotation, direction, up, true, sead::Mathf::deg2rad(30.0f));
            unit->sub_71002D93E8(rotation);
        }
    }
}

// NON_MATCHING: direction and rotation use opposite stack slots.
void sub_710072A108(uking::act::Swarm* swarm, const sead::Vector3f& up) {
    for (s32 i = 0, count = swarm->_14c8.size(); i < count; ++i) {
        if (auto* unit = swarm->_14c8[i]) {
            sead::Vector3f direction = unit->_38.mean;
            direction.normalize();
            if (direction == sead::Vector3f(0.0f, 0.0f, 0.0f))
                continue;
            sead::Matrix33f rotation;
            sub_7100741118(&rotation, unit->_8);
            sub_710074191C(&rotation, direction, up, false, sead::Mathf::deg2rad(30.0f));
            unit->sub_71002D93E8(rotation);
        }
    }
}
