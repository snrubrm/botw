#include "Game/AI/Action/actionForkEmitShockWaveByContact.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

bool sub_7100EEB19C(ksys::phys::RigidBody* body, sead::Vector3f* a2, sead::Vector3f* a3,
                    sead::Vector3f* a4, void* a5, void* a6, void* a7);

ForkEmitShockWaveByContact::ForkEmitShockWaveByContact(const InitArg& arg)
    : ForkASTrgEmitShockWave(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
ForkEmitShockWaveByContact::~ForkEmitShockWaveByContact() {
    ;
}

bool ForkEmitShockWaveByContact::init_(sead::Heap* heap) {
    return ForkASTrgEmitShockWave::init_(heap);
}

void ForkEmitShockWaveByContact::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkASTrgEmitShockWave::enter_(params);
}

void ForkEmitShockWaveByContact::leave_() {
    ForkASTrgEmitShockWave::leave_();
}

void ForkEmitShockWaveByContact::loadParams_() {
    ForkASTrgEmitShockWave::loadParams_();
    getStaticParam(&mRigidBodyName_s, "RigidBodyName");
}

void ForkEmitShockWaveByContact::calc_() {
    ForkASTrgEmitShockWave::calc_();
}

bool ForkEmitShockWaveByContact::m33(sead::Matrix34f* mtx) {
    auto* actor = mActor;
    const char* group = ksys::act::getStr_Body().cstr();
    auto* body = actor->findPhysicsBodyByName(group, mRigidBodyName_s.cstr());
    if (!body) {
        actor = mActor;
        group = ksys::act::getStr_EntitySensor().cstr();
        body = actor->findPhysicsBodyByName(group, mRigidBodyName_s.cstr());
        if (!body)
            return false;
    }
    sead::Vector3f position;
    sead::Vector3f normal;
    if (!sub_7100EEB19C(body, nullptr, &position, &normal, nullptr, nullptr, nullptr))
        return false;
    ksys::util::sub_71011F00EC(mtx, sead::Vector3f::ez, normal, position, false);
    return true;
}

}  // namespace uking::action
