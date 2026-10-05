#include "Game/AI/Action/actionFreezedInIce.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace uking::action {

FreezedInIce::FreezedInIce(const InitArg& arg) : ksys::act::ai::Action(arg) {}

bool FreezedInIce::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void FreezedInIce::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->x_8(false);
    if (mActor->getASList()->sub_710115AA68("FreezedInIce"))
        playAS("FreezedInIce", false, 0, 0, -1.0f);
    if (auto* physics = mActor->getPhysics())
        physics->getFlags().set(ksys::phys::InstanceSet::Flag::_20000);
    if (auto* xlink = mActor->getXLink())
        xlink->_cc.set(0x800);
    if (auto* unit = mActor->get548())
        unit->_18._50 = true;
}

void FreezedInIce::leave_() {
    auto* actor = mActor;
    if (auto* physics = actor->getPhysics()) {
        physics->getFlags().reset(ksys::phys::InstanceSet::Flag::_20000);
        physics->sub_7100FBA9BC();
    }
    if (auto* nav = actor->m45())
        ksys::phys::HavokAI::instance()->sub_7100F82BCC(nav);
    ksys::act::sub_7100EE544C(actor);
    if (auto* xlink = mActor->getXLink())
        xlink->_cc.reset(0x800);
    if (auto* unit = mActor->get548())
        unit->_18._50 = false;
}

void FreezedInIce::loadParams_() {}

void FreezedInIce::calc_() {
    if (!mActor->checkFreezeSignal())
        setFinished();
}

}  // namespace uking::action
