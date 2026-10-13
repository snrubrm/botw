#include "Game/AI/aiUnk_710072A944.h"
#include <random/seadGlobalRandom.h>
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actSwarm.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/Resource/Actor/resResourceDamageParam.h"
#include "KingSystem/Resource/Actor/resResourceDrop.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

void sub_710072A944(uking::act::Swarm* swarm, f32 min, f32 max) {
    for (s32 i = 0; i < swarm->_14c8.size(); ++i) {
        if (auto* unit = swarm->_14c8[i])
            unit->_5c = sead::GlobalRandom::instance()->getF32Range(min, max);
    }
    for (s32 i = 0; i < swarm->_15e8.size(); ++i) {
        if (auto* unit = swarm->_15e8[i]._18)
            unit->_5c = max;
    }
}

void sub_7100729EA8(uking::act::Swarm* swarm) {
    for (s32 i = 0, n = swarm->_15e8.size(); i < n; ++i) {
        const auto& body = swarm->_15e8[i];
        if (auto* unit = body._18)
            sub_71007A2B64(body._20, &unit->_8);
        else
            sub_71007A2B64(body._20, &swarm->getMtx());
    }
}

void sub_7100729F34(uking::act::Swarm* swarm) {
    for (s32 i = 0, n = swarm->_15e8.size(); i < n; ++i)
        sub_71007A2D34(swarm->_15e8[i]._20);
}

void sub_710072A778(uking::act::Swarm* swarm, const sead::SafeString& name, f32 frame) {
    for (s32 i = 0, n = swarm->_14c8.size(); i < n; ++i) {
        if (auto* unit = swarm->_14c8[i])
            unit->sub_71002DA3A0(frame, name);
    }
}

void sub_710072ABB4(ksys::act::Actor* actor) {
    if (auto* swarm = sead::DynamicCast<uking::act::Swarm>(actor)) {
        for (s32 i = 0; i < swarm->_15f8.size(); ++i) {
            if (auto* body = swarm->_15f8[i]._20)
                body->addToWorld();
        }
    }
}

void sub_710072AAE4(ksys::act::Actor* actor) {
    if (auto* swarm = sead::DynamicCast<uking::act::Swarm>(actor)) {
        for (s32 i = 0; i < swarm->_15f8.size(); ++i) {
            if (auto* body = swarm->_15f8[i]._20)
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
