#include "Game/Actor/Action/actionSwarmDamaged.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_710072A944.h"
#include "Game/Actor/aiUnk_710072BA90.h"
#include "Game/Actor/Damage/dmgDamageManager.h"

namespace uking::action {

SwarmDamaged::SwarmDamaged(const InitArg& arg) : SwarmDamagedBase(arg) {}

SwarmDamaged::~SwarmDamaged() = default;

bool SwarmDamaged::init_(sead::Heap* heap) {
    return SwarmDamagedBase::init_(heap);
}

// NON_MATCHING: contact/count guards and unit velocity loads are scheduled differently.
void SwarmDamaged::enter_(ksys::act::ai::InlineParamPack* params) {
    SwarmDamagedBase::enter_(params);
    if (isFinished() || isFailed())
        return;
    auto* swarm = static_cast<act::Swarm*>(mActor);
    m33(swarm);
    sead::Vector3f direction;
    s32 count = 0;
    sub_7100729370(swarm, &direction, &count);
    if (count == 0) {
        for (s32 i = 0; i < swarm->_14c8.size(); ++i) {
            if (auto* unit = swarm->_14c8[i]) {
                const f32 x = unit->_60.x * 5.0f;
                const f32 spread = x + (x >= 0.0f ? 0.5f : -0.5f);
                const f32 lift = sead::Mathf::clamp((unit->_60.y + 2.0f) * 0.25f, 0.0f, 1.0f);
                unit->_6c.x = spread + (2.0f - (lift + lift));
                unit->_6c.y = unit->_60.y + (lift + lift);
                unit->_6c.z = unit->_60.z;
            }
        }
    } else {
        for (s32 i = 0; i < swarm->_14c8.size(); ++i) {
            if (auto* unit = swarm->_14c8[i]) {
                f32 x = unit->_60.x * 5.0f;
                x += x >= 0.0f ? 0.5f : -0.5f;
                f32 y = unit->_60.y;
                if (direction.x < -0.1f)
                    x = -sead::Mathf::abs(x);
                else if (direction.x > 0.1f)
                    x = sead::Mathf::abs(x);
                if (direction.y > -0.1f) {
                    const f32 lift = sead::Mathf::clamp((y + 2.0f) * 0.25f, 0.0f, 1.0f);
                    y += lift + lift;
                    x += 2.0f - (lift + lift);
                }
                unit->_6c.set(x, y, unit->_60.z);
            }
        }
    }
}

void SwarmDamaged::leave_() {
    SwarmDamagedBase::leave_();
}

void SwarmDamaged::loadParams_() {
    SwarmDamagedBase::loadParams_();
    getStaticParam(&mDeadSubActorMax_s, "DeadSubActorMax");
}

void SwarmDamaged::calc_() {
    SwarmDamagedBase::calc_();
}

void SwarmDamaged::m33(act::Swarm* swarm) {
    auto* mgr = sub_710072BA90(swarm);
    if (!mgr || mgr->getField54() == -1)
        return;

    sead::Vector3f pos;
    sead::Vector3f step;
    m34(mgr, &pos, &step);
    for (s32 i = 0; i < *mDeadSubActorMax_s; i++) {
        if (auto* unit = sub_710072A6DC(swarm, pos))
            swarmStuff(unit, -1);
        pos += step;
    }
}

void SwarmDamaged::m34(act::DamageManager* mgr, sead::Vector3f* pos, sead::Vector3f* dir) {
    mgr->getPosition(pos);
    sub_71005E2318(dir, mActor, mgr);
}

}  // namespace uking::action
