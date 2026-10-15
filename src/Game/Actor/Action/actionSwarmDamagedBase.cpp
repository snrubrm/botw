#include "Game/Actor/Action/actionSwarmDamagedBase.h"
#include <random/seadGlobalRandom.h>
#include "Game/Actor/aiUnk_710072A944.h"
#include "Game/Actor/aiUnk_710072A80C.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "Game/Actor/actSwarm.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

SwarmDamagedBase::SwarmDamagedBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SwarmDamagedBase::~SwarmDamagedBase() = default;

bool SwarmDamagedBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SwarmDamagedBase::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* swarm = sead::DynamicCast<act::Swarm>(mActor);
    if (!swarm) {
        setFailed();
        return;
    }
    if (auto* controller = swarm->getCharacterController()) {
        sead::Vector3f velocity;
        controller->sub_7100F5F598(&velocity);
        const f32 min_speed = *mRiseSpeedMin_s * 30.0f;
        if (velocity.y < min_speed)
            velocity.y = min_speed;
        controller->sub_7100F5F6FC(velocity);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    }
    for (int i = 0; i < swarm->_14c8.size(); ++i) {
        if (auto* unit = swarm->_14c8[i])
            unit->_5c = sead::GlobalRandom::instance()->getF32Range(*mSubAccRateMin_s,
                                                                    *mSubAccRateMax_s);
    }
    _68 = ksys::Timer(0.0f, 0.0f, 1.0f);
}

void SwarmDamagedBase::leave_() {
    ksys::act::ai::Action::leave_();
}

bool SwarmDamagedBase::sub_7100284D00(void* ptr) const {
    for (const Entry& entry : _78) {
        if (entry.mPtr == ptr)
            return true;
    }
    return false;
}

void SwarmDamagedBase::loadParams_() {
    getStaticParam(&mIgnoreHitGroundTime_s, "IgnoreHitGroundTime");
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mRiseSpeedMin_s, "RiseSpeedMin");
    getStaticParam(&mSubAccRateMin_s, "SubAccRateMin");
    getStaticParam(&mSubAccRateMax_s, "SubAccRateMax");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mIsCreateDeadActor_s, "IsCreateDeadActor");
    getMapUnitParam(&mSubUnitNum_m, "SubUnitNum");
    getMapUnitParam(&mPatternID_m, "PatternID");
}

// NON_MATCHING: the compiler merges the repeated failure cleanup loops.
void SwarmDamagedBase::calc_() {
    sub_71002844D0();
    if (isFinished() || isFailed())
        return;
    auto* swarm = static_cast<act::Swarm*>(mActor);
    if (swarm->_1610 == 0) {
        setFinished();
        return;
    }
    m32(swarm);
    if (_68.value > static_cast<f32>(*mTime_s)) {
        sub_71002844D0();
        for (Entry& entry : _78) {
            if (entry.mHandle.isAllocatedOrFailed()) {
                entry.mHandle.deleteProc();
                if (entry.mPtr) {
                    sub_71002847E0(&entry);
                    entry.mPtr->m10();
                }
            }
        }
        setFinished();
    } else {
        _68.update();
    }
    if (sub_7100729494(swarm) &&
        (_68.value > static_cast<f32>(*mIgnoreHitGroundTime_s) || sub_71007294F4(swarm) == 4)) {
        sub_71002844D0();
        for (Entry& entry : _78) {
            if (entry.mHandle.isAllocatedOrFailed()) {
                entry.mHandle.deleteProc();
                if (entry.mPtr) {
                    sub_71002847E0(&entry);
                    entry.mPtr->m10();
                }
            }
        }
        setFailed();
    }
}

void SwarmDamagedBase::sub_71002844D0() {
    for (Entry& entry : _78) {
        if (entry.mHandle.isProcReady()) {
            auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(entry.mHandle.releaseAndWakeProc());
            auto* unit = entry.mPtr;
            if (!actor || !unit)
                continue;
            sead::Matrix34f matrix(unit->_8);
            sead::Vector3f position = matrix.getTranslation();
            f32 height;
            if (sub_710072C21C(&height, &position) == 2 && position.y < height + 0.1f) {
                position.y = height + 0.1f;
                matrix.setTranslation(position);
            }
            actor->setMatrix(matrix, nullptr);
            actor->setVelocity(&unit->_38.mean, nullptr);
            swarmDropTableStuff(actor);
            unit->m10();
        } else if (entry.mHandle.hasProcCreationFailed()) {
            entry.mHandle.deleteProcIfFailed();
        }
    }
}

// NON_MATCHING: rotation temporaries use different stack slots and the shared angle branch is duplicated.
void SwarmDamagedBase::sub_71002847E0(Entry* entry) {
    sead::Vector3f position = entry->mPtr->_8.getTranslation();
    f32 height;
    if (sub_710072C21C(&height, &position) == 2 && height + 0.1f > position.y)
        position.y = height + 0.1f;
    const sead::Vector3f rotation = entry->mPtr->_8.getRotation();
    ksys::act::InstParamPack params;
    params->addPosition(position);
    params->addRotation(rotation);
    params->add(10, "@I");
    ksys::act::ActorCreator::addAITreeParam(params, entry->mIdx, "CreateDeadConditionType");
    params->add(sead::SafeString("Swarm"), "DropTable");
    sub_710072A80C(mActor, nullptr, &params);
}

// NON_MATCHING: the free-slot search retains a loop instead of the native fully unrolled selection.
void SwarmDamagedBase::swarmStuff(act::Swarm::Unit* unit, s32 deadConditionType) {
    if (!unit)
        return;
    if (!*mIsCreateDeadActor_s) {
        unit->m10();
        return;
    }
    s32 index = 0;
    for (; index < 10; ++index) {
        if (!_78[index].mHandle.isAllocatedOrFailed())
            break;
    }
    if (index == 10)
        return;
    Entry* entry = &_78[index];
    ksys::act::InstParamPack params;
    params->add(10, "@I");
    ksys::act::ActorCreator::addAITreeParam(params, deadConditionType, "CreateDeadConditionType");
    params->add(sead::SafeString("Swarm"), "DropTable");
    sub_710072A80C(mActor, &entry->mHandle, &params);
    if (entry->mHandle.isAllocatedOrFailed()) {
        entry->mPtr = unit;
        entry->mIdx = deadConditionType;
    } else {
        unit->m10();
    }
}

void SwarmDamagedBase::m32(act::Swarm* swarm) {
    // The result is discarded.
    sub_7100729D5C(*mSpeed_s, swarm, nullptr, nullptr, nullptr, false);
    sub_710072A108(swarm, sead::Vector3f::ey);
}

}  // namespace uking::action
