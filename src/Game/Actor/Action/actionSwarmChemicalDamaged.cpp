#include "Game/Actor/Action/actionSwarmChemicalDamaged.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_710072A944.h"
#include "Game/Actor/aiUnk_710072BA90.h"
#include "Game/Actor/actSwarm.h"
#include "Game/Actor/actUnk_71025ae680.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/Damage/dmgDamageManager.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include <random/seadGlobalRandom.h>

namespace uking::action {

SwarmChemicalDamaged::SwarmChemicalDamaged(const InitArg& arg) : SwarmDamaged(arg) {}

SwarmChemicalDamaged::~SwarmChemicalDamaged() = default;

bool SwarmChemicalDamaged::init_(sead::Heap* heap) {
    return SwarmDamaged::init_(heap);
}

void SwarmChemicalDamaged::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_7100283004(params);
    SwarmDamaged::enter_(params);
}

void SwarmChemicalDamaged::sub_7100283004(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    _1d4 = -1;
    _1d8 = -1;
    _1d0 = false;

    auto* manager = sub_710072BA90(actor);
    auto* unit = sead::DynamicCast<act::Unk_710244ff68>(static_cast<ksys::act::DynamicActor*>(actor)->m159());
    if (manager && unit) {
        if (manager->getField54() == 0x12) {
            _1d4 = 2;
            _1d8 = unit->_20;
        } else if (manager->getField54() == 3) {
            _1d4 = 3;
            _1d8 = unit->_1c;
        } else if (manager->getField54() == 4) {
            _1d4 = 4;
            _1d8 = unit->_24;
        }
    }
    if (_1d4 != -1)
        _1d0 = true;

    if (*mResetChemicalTimer_s > 0.0f)
        _1e0.mTimer.reset(*mResetChemicalTimer_s);
    else
        sub_71002831E4();
}

void SwarmChemicalDamaged::leave_() {
    SwarmDamaged::leave_();
    sub_71002831E4();
}

void SwarmChemicalDamaged::loadParams_() {
    SwarmDamaged::loadParams_();
    getStaticParam(&mResetChemicalTimer_s, "ResetChemicalTimer");
    getStaticParam(&mIsResetAllObject_s, "IsResetAllObject");
}

void SwarmChemicalDamaged::calc_() {
    if (!(_1e0.mTimer.value <= sead::Mathf::epsilon())) {
        _1e0.sub_7100D3BCE4();
        if (_1e0.mTimer.value <= sead::Mathf::epsilon())
            sub_71002831E4();
    }
    SwarmDamaged::calc_();
}

// NON_MATCHING: the three random offsets stay in d11/d12 in the original; our build keeps one fewer
// callee-saved float and places the pos/dir locals 0x10 higher.
void SwarmChemicalDamaged::m33(act::Swarm* swarm) {
    if (!swarm)
        return;

    const s32 state = _1d8;
    auto* mgr = sub_710072BA90(swarm);

    if (state == -1) {
        if (!mgr || mgr->getField54() == -1)
            return;

        const s32 count = swarm->_15f8.size();
        if (count < 1)
            return;

        const s32 max = *mDeadSubActorMax_s;
        if (max < 1)
            return;

        s32 per = max / count;
        if (per < 1)
            per = 1;

        sead::Vector3f dir;
        sub_71005E2318(&dir, mActor, mgr);

        s32 spawned = 0;
        for (s32 i = 0; i < count && spawned < max; ++i) {
            if (!swarm->_15f8[i]._8._18 || !swarm->_15f8[i]._8._18->isAddedToWorld())
                continue;

            sead::Vector3f pos;
            if (mActor && static_cast<act::Swarm*>(mActor)->_15f8[i]._8._18)
                static_cast<act::Swarm*>(mActor)->_15f8[i]._8._18->getPosition(&pos);
            else
                mgr->getPosition(&pos);

            for (s32 j = 1; j < per && spawned < max; ++j) {
                sead::Vector3f offset;
                offset.x = pos.x + sead::GlobalRandom::instance()->getF32() * 6.0f - 3.0f;
                offset.y = pos.y + sead::GlobalRandom::instance()->getF32() * 6.0f - 3.0f;
                offset.z = pos.z + sead::GlobalRandom::instance()->getF32() * 6.0f - 3.0f;
                if (auto* unit = sub_710072A6DC(swarm, offset)) {
                    if (!sub_7100284D00(unit)) {
                        swarmStuff(unit, _1d4);
                        ++spawned;
                    }
                }
                pos += dir;
            }
        }
    } else {
        if (!mgr || mgr->getField54() == -1)
            return;

        sead::Vector3f pos;
        sead::Vector3f dir;
        m34(mgr, &pos, &dir);

        if (*mDeadSubActorMax_s < 1)
            return;

        for (s32 i = 0; i < *mDeadSubActorMax_s; ++i) {
            if (auto* unit = sub_710072A6DC(swarm, pos)) {
                if (!sub_7100284D00(unit))
                    swarmStuff(unit, _1d4);
            }
            pos += dir;
        }
    }
}

void SwarmChemicalDamaged::m34(act::DamageManager* mgr, sead::Vector3f* pos, sead::Vector3f* dir) {
    if (_1d8 == -1) {
        SwarmDamaged::m34(mgr, pos, dir);
        return;
    }

    auto* swarm = static_cast<act::Swarm*>(mActor);
    if (swarm && swarm->_15f8[_1d8]._8._18)
        swarm->_15f8[_1d8]._8._18->getPosition(pos);
    else
        mgr->getPosition(pos);
    sub_71005E2318(dir, mActor, mgr);
}

void SwarmChemicalDamaged::sub_71002831E4() {
    if (_1d0) {
        _1d0 = false;
        if (auto* unk = sead::DynamicCast<act::Unk_710244ff68>(static_cast<ksys::act::DynamicActor*>(mActor)->m159())) {
            if (*mIsResetAllObject_s)
                unk->sub_71006EF05C(_1d4);
            else
                unk->sub_71006EEFB4(_1d4, _1d8);
        }
    }
}

}  // namespace uking::action
