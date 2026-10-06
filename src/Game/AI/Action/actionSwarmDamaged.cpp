#include "Game/AI/Action/actionSwarmDamaged.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_710072A944.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"

namespace uking::action {

SwarmDamaged::SwarmDamaged(const InitArg& arg) : SwarmDamagedBase(arg) {}

SwarmDamaged::~SwarmDamaged() = default;

bool SwarmDamaged::init_(sead::Heap* heap) {
    return SwarmDamagedBase::init_(heap);
}

void SwarmDamaged::enter_(ksys::act::ai::InlineParamPack* params) {
    SwarmDamagedBase::enter_(params);
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

void SwarmDamaged::m34(dmg::DamageManager* mgr, sead::Vector3f* pos, sead::Vector3f* dir) {
    mgr->getPosition(pos);
    sub_71005E2318(dir, mActor, mgr);
}

}  // namespace uking::action
