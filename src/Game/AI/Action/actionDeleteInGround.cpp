#include "Game/AI/Action/actionDeleteInGround.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Actor/actRideable.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::action {

DeleteInGround::DeleteInGround(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DeleteInGround::~DeleteInGround() = default;

bool DeleteInGround::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the original hoists the load of mActor above the isEmpty() branch (shared by both arms)
void DeleteInGround::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710073DE08(mActor);
    if (auto* mgr = mActor->getDamageMgr())
        mgr->mField_34 = 1;
    sub_71007A397C(mActor);
    if (mASName_s.isEmpty()) {
        mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        setFinished();
    } else if (auto* rideable = mActor->m132()) {
        rideable->_18.sub_7100E786F0(mASName_s);
    } else {
        playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    }
    if (auto* controller = mActor->getCharacterController()) {
        const sead::Vector3f down = -sead::Vector3f::ey;
        sub_7100737C0C(controller, 0.0f, down);
    }
    sub_710072BB28(mActor);
    if (auto* unit = mActor->get548())
        unit->_18._50 = 1;
}

void DeleteInGround::leave_() {
    if (auto* mgr = mActor->getDamageMgr())
        mgr->mField_34 = 0;
    if (auto* unit = mActor->get548())
        unit->_18._50 = 0;
    sub_71007A3800(mActor);
    mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
}

void DeleteInGround::loadParams_() {
    getStaticParam(&mASName_s, "ASName");
}

void DeleteInGround::calc_() {
    if (isFinished() || isFailed())
        return;
    auto* actor = mActor;
    const sead::Vector3f gravity = getGravity(actor) * (1.0f / 900.0f);
    sub_7100738488(actor, 0.0f, gravity);
    sub_7100738AA8(actor, 0.0f);
    if (isFinishedAS(0, 0)) {
        mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        setFinished();
    }
}

}  // namespace uking::action
