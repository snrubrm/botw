#include "Game/Actor/AI/aiRemainsWindBatteryAttack.h"
#include "Game/Actor/actBeamBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"

namespace uking::ai {

RemainsWindBatteryAttack::RemainsWindBatteryAttack(const InitArg& arg)
    : GuardianCommonBeamAttack(arg) {}

RemainsWindBatteryAttack::~RemainsWindBatteryAttack() {
    for (s32 i = 0; i < 5; ++i) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_38[i], &accessor);
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
}

bool RemainsWindBatteryAttack::init_(sead::Heap* heap) {
    if (!GuardianCommonBeamAttack::init_(heap))
        return false;
    auto* actor = mActor;
    ksys::act::InstParamPack pack;
    ksys::act::ActorCreator::setCreatePriorityState1(pack, actor);
    for (s32 i = 0; i < 5; ++i) {
        auto* created = ksys::act::ActorCreator::instance()->createActor(
            "GuardianBeam_RemainsWind", ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(),
            &pack, true, false);
        if (!created)
            continue;
        if (auto* beam = sead::DynamicCast<act::Beam>(created)) {
            beam->sub_7100002DA8(actor);
            beam->sub_7100003804(actor, "Head");
        }
        _38[i].acquire(created, false);
    }
    if (actor->getModel())
        _88.search(actor->getModel(), "Head");
    return true;
}

void RemainsWindBatteryAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianCommonBeamAttack::enter_(params);
    changeChild("待機");
}

void RemainsWindBatteryAttack::leave_() {
    GuardianCommonBeamAttack::leave_();
}

void RemainsWindBatteryAttack::loadParams_() {
    GuardianCommonBeamAttack::loadParams_();
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
