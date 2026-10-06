#include "Game/AI/aiUnk_710072A944.h"
#include <random/seadGlobalRandom.h>
#include "Game/Actor/actSwarm.h"
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
