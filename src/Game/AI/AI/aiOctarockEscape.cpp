#include "Game/AI/AI/aiOctarockEscape.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

OctarockEscape::OctarockEscape(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

OctarockEscape::~OctarockEscape() = default;

bool OctarockEscape::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void OctarockEscape::enter_(ksys::act::ai::InlineParamPack* params) {
    _50 = ksys::Timer(30.0f, 30.0f);
    sub_71004EC9BC();
    changeChild("隠れる", params);
}

void OctarockEscape::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("隠れる")) {
            m35();
        } else if (isCurrentChild("移動")) {
            sub_71004EC6F0();
            mActor->setModelDrawEnabled(false);
            if (auto* controller = mActor->getCharacterController())
                controller->sub_7100F60604();
            changeChild("飛び出す");
        } else {
            auto* calc_child =
                sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcChild());
            if (calc_child && calc_child->isCalc())
                setFinished();
            else if (!_40.hasProc() || _50.value <= sead::Mathf::epsilon())
                setFailed();
            else
                _50.update();
        }
    } else {
        child->isChangeable();
    }

    if (!isCurrentChild("隠れる"))
        sub_71004EC6F0();

    if (isCurrentChild("飛び出す"))
        sub_71004EC7A0();

    if (isCurrentChild("移動"))
        getCurrentChild()->setDynamicParam(*m34(), "TargetPos");
}

void OctarockEscape::leave_() {
    if (_40.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_40, &accessor);
        if (accessor.isStateSleep()) {
            accessor.setThisActorAsChild(mActor, false);
            accessor.wakeUp(ksys::act::BaseProc::SleepWakeReason::_0);
        }
    }
    _40.reset();
}

void OctarockEscape::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

sead::Vector3f* OctarockEscape::m34() {
    return mTargetPos_d;
}

void OctarockEscape::m35() {
    sub_71004ECB04();
    ksys::act::ai::InlineParamPack params;
    params.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("移動", &params);
}

void OctarockEscape::sub_71004EC6F0() {
    auto* actor = mActor;
    if (!actor->getConnectedCalcChild() && _40.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_40, &accessor);
        if (accessor.isStateSleep()) {
            sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x8000001), actor);
            accessor.setThisActorAsChild(mActor, false);
        }
    }
}

void OctarockEscape::sub_71004EC9BC() {
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    controller->enableContactLayer(ksys::phys::ContactLayer::EntityNPC);
    controller->enableContactLayer(ksys::phys::ContactLayer::EntityNPC_NoHitPlayer);
    controller->enableContactLayer(ksys::phys::ContactLayer::EntityObject);
    controller->enableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
    controller->enableContactLayer(ksys::phys::ContactLayer::EntityRagdoll);
    controller->enableContactLayer(ksys::phys::ContactLayer::EntityRope);
}

void OctarockEscape::sub_71004ECB04() {
    auto* calc_child = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcChild());
    if (calc_child) {
        _40.acquire(calc_child, false);
        calc_child->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    }
    mActor->setModelDrawEnabled(true);
}

}  // namespace uking::ai
