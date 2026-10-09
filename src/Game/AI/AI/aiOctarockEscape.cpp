#include "Game/AI/AI/aiOctarockEscape.h"
#include <math/seadMathCalcCommon.h>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelAccessKey.h>
#include <gsys/gsysModelUnit.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/Thread/Message.h"

// 0x7100edd258: existing actor default-bone-name API, declaration only.
const sead::SafeString& sub_7100EDD258(ksys::act::Actor* actor, int a2);

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

// 0x71004ec7a0
bool OctarockEscape::sub_71004EC7A0() {
    auto* actor = mActor;
    auto* child = sead::DynamicCast<ksys::act::Actor>(actor->getConnectedCalcChild());
    if (!child) {
        sub_71004EC6F0();
        return false;
    }
    if (_40.hasProcInCalcState()) {
        _40.reset();
        return true;
    }
    if (child->isSleep() && !sub_71005DC444(child) && sub_71004ECBB4()) {
        sendMessage(*child->getMesTransceiverId(), ksys::MessageType(0x8000001), actor);
        sub_71005DC208(actor, child, 0);
        sub_71005DC41C(child);
    }
    return false;
}

// 0x71004ecbb4
// NON_MATCHING: model receiver caching, vector-copy scheduling and stack placement differ.
bool OctarockEscape::sub_71004ECBB4() {
    auto* actor = mActor;
    const auto key = actor->getModel()->searchBone(sub_7100EDD258(actor, 0));
    if (!key.isValid())
        return false;
    sead::Matrix34f matrix;
    actor->getModel()->getUnits().unsafeAt(key.model_unit_index)->mModelUnit->getBoneWorldMatrix(
        &matrix, key.bone_index);
    const sead::Vector3f bone_pos = matrix.getTranslation();
    actor = mActor;
    sead::Vector3f position = actor->getMtx().getTranslation();
    position.y += 2.0f;
    return !sub_710072EB10(bone_pos, position, ksys::phys::RayCast::NormalCheckingMode::DoNotCheck,
                          actor, nullptr, nullptr, nullptr, 0.0f);
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
