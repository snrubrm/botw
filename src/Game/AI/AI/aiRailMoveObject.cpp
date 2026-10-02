#include "Game/AI/AI/aiRailMoveObject.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71024f15c0.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/Map/mapRail.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"

namespace uking::ai {

RailMoveObject::RailMoveObject(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RailMoveObject::~RailMoveObject() = default;

bool RailMoveObject::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RailMoveObject::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    _60 = m34();
    if (_60) {
        _74 = 0;
        _68 = _60->getNumPoints();
    }
    m35();
    _6c = 0;

    if (!_60 || (!actor->checkBasicSig() && actor->hasPlacementLinkForBasicSig())) {
        if (auto* as_list = actor->getASList(); as_list && as_list->sub_710115AA68(mASKeyName_Off_s))
            changeAS(mASKeyName_Off_s.cstr(), true, 0, 0);
        m37();
        return;
    }

    if (auto* as_list = actor->getASList(); as_list && as_list->sub_710115AA68(mASKeyName_On_s))
        changeAS(mASKeyName_On_s.cstr(), true, 0, 0);
    _70 = _6c + 1.0f;
    m38();
}

void RailMoveObject::calc_() {
    m36();
    auto* actor = mActor;
    auto* child = getCurrentChild();
    if (!_60)
        return;

    if (actor->hasPlacementLinkForBasicSig()) {
        if (!actor->checkBasicSig()) {
            if (auto* as_list = actor->getASList();
                as_list && as_list->sub_710115AA68(mASKeyName_Off_s)) {
                changeAS(mASKeyName_Off_s.cstr(), true, 0, 0);
            }
            if (isCurrentChild("移動")) {
                sub_7100533DB0();
                m37();
            }
            return;
        }
        if (auto* as_list = actor->getASList(); as_list && as_list->sub_710115AA68(mASKeyName_On_s))
            changeAS(mASKeyName_On_s.cstr(), true, 0, 0);
    }

    if (isCurrentChild("停止") && child->isChangeable()) {
        sub_7100533C58();
        m38();
    } else if (child->isFinished()) {
        _6c = _70;
        m37();
    }
}

// NON_MATCHING: the int conversion of _6c is scheduled before `_68 - 1`, and the `_70 = 0` store of
// the closed-rail branch is merged with the other branch's store
void RailMoveObject::sub_7100533C58() {
    if (sead::Mathf::abs(_6c - s32(_6c)) <= 0.0f) {
        _6c = _70;
        switch (_74) {
        case 0:
            _70 = _6c + 1.0f;
            break;
        case 1:
            _70 = _6c - 1.0f;
            break;
        }
        const f32 last = _68 - 1;
        _6c = sead::Mathf::clamp(_6c, 0.0f, last);
        _70 = sead::Mathf::clamp(_70, 0.0f, last);
    }

    const s32 idx = _6c;
    if (idx == _68 - 1 && sead::Mathf::abs(_6c - idx) <= 0.0f && _60) {
        if (_60->isClosed()) {
            _74 = 0;
            _70 = 0;
        } else {
            _74 = 1;
            _70 = _6c - 1.0f;
        }
    } else if (idx == 0 && sead::Mathf::abs(_6c - idx) <= 0.0f && _74 == 1) {
        _74 = 0;
        _6c = 0;
        _70 = 1.0f;
    }
}

void RailMoveObject::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RailMoveObject::loadParams_() {
    getStaticParam(&mASKeyName_On_s, "ASKeyName_On");
    getStaticParam(&mASKeyName_Off_s, "ASKeyName_Off");
    getMapUnitParam(&mRailMoveSpeed_m, "RailMoveSpeed");
}

void RailMoveObject::m9() {
    _60 = m34();
    if (_60) {
        _74 = 0;
        _68 = _60->getNumPoints();
    }
}

bool RailMoveObject::reenter_(ksys::act::ai::ActionBase* other, bool x) {
    if (!ksys::act::ai::ActionBase::reenter_(other, true))
        return false;

    auto* other_ = sead::DynamicCast<RailMoveObject>(other);
    if (!other_)
        return false;

    _60 = other_->_60;
    _68 = other_->_68;
    _6c = other_->_6c;
    _70 = other_->_70;
    _74 = other_->_74;
    return true;
}

ksys::map::Rail* RailMoveObject::m34() {
    return sub_7100EEF264(mActor, 0);
}

void RailMoveObject::m35() {
    auto* actor = mActor;
    auto* body = actor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkBody");
    if (!body)
        return;
    if (!body->isAddedToWorld())
        body->setTransform(actor->getMtx());
    getActorAttackSensor(actor)->activateAttackSensor(
        1, 12, actor->getParam()->getRes().mGParamList->getAttack()->mPower.ref(),
        actor->getParam()->getRes().mGParamList->getAttack()->mImpulse.ref(), 0.0f, 0, 1, -1,
        false, 1, -1);
    sub_71007A2B64(body, nullptr);
}

void RailMoveObject::m36() {
    auto* actor = mActor;
    auto* body = actor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkBody");
    if (!body)
        return;
    if (body->isAddedToWorld())
        body->changePositionAndRotation(actor->getMtx());
    else
        body->setTransform(actor->getMtx());
}

void RailMoveObject::m37() {
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    f32 stop_time;
    if (_60) {
        _60->calcTranslate(&pos, _6c);
        stop_time = sub_7100EEF078(_60, _6c);
    } else {
        stop_time = 0;
    }
    pack.addFloat(stop_time, "DynStopTime", -1);
    pack.addVec3(pos, "DynStopPos", -1);
    changeChild("停止", &pack);
}

void RailMoveObject::m38() {
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f start = sead::Vector3f::zero;
    sead::Vector3f end = sead::Vector3f::zero;
    if (_60) {
        start = _60->calcTranslate(_6c);
        end = _60->calcTranslate(_70);
    }
    pack.addVec3(start, "DynStartPos", -1);
    pack.addVec3(end, "DynTargetPos", -1);
    changeChild("移動", &pack);
}

}  // namespace uking::ai
