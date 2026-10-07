#include "Game/AI/Action/actionForkEmitChmFieldByContact.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

bool sub_7100EEB19C(ksys::phys::RigidBody* body, sead::Vector3f* a2, sead::Vector3f* a3,
                    sead::Vector3f* a4, void* a5, void* a6, void* a7);

ForkEmitChmFieldByContact::ForkEmitChmFieldByContact(const InitArg& arg) : ForkEmitChmField(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
ForkEmitChmFieldByContact::~ForkEmitChmFieldByContact() {
    ;
}

bool ForkEmitChmFieldByContact::init_(sead::Heap* heap) {
    return ForkEmitChmField::init_(heap);
}

void ForkEmitChmFieldByContact::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkEmitChmField::enter_(params);
}

void ForkEmitChmFieldByContact::leave_() {
    ForkEmitChmField::leave_();
}

void ForkEmitChmFieldByContact::loadParams_() {
    ForkEmitChmField::loadParams_();
    getStaticParam(&mRigidBodyName_s, "RigidBodyName");
}

void ForkEmitChmFieldByContact::calc_() {
    ForkEmitChmField::calc_();
}

bool ForkEmitChmFieldByContact::m34(sead::Matrix34f* mtx) {
    if (!sub_71005DD7B0(mActor, nullptr, 0, 0))
        return false;
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
