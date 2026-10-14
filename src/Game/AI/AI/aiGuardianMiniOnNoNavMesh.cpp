#include "Game/AI/AI/aiGuardianMiniOnNoNavMesh.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/AI/aiGuardianMiniRoot.h"
#include "KingSystem/ActorSystem/actPhysicsUserTag.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

GuardianMiniOnNoNavMesh::GuardianMiniOnNoNavMesh(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GuardianMiniOnNoNavMesh::~GuardianMiniOnNoNavMesh() = default;

void GuardianMiniOnNoNavMesh::enter_(ksys::act::ai::InlineParamPack* params) {
    _40.reset();
    _5c = 0;
    if (sub_710041DBE0())
        _50.reset(*mChangeToIceTimer_s);
    changeChild("ナビメッシュなし", params);
}

void GuardianMiniOnNoNavMesh::leave_() {
    _40.reset();
}

void GuardianMiniOnNoNavMesh::loadParams_() {
    getStaticParam(&mChangeToIceTimer_s, "ChangeToIceTimer");
}

void GuardianMiniOnNoNavMesh::changeToOnIceMaker() {
    _5c |= 1;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("アイスメーカー上", &pack);
}

// NON_MATCHING: vector temporaries and loop register allocation differ.
bool GuardianMiniOnNoNavMesh::sub_710041DBE0() {
    auto* actor = mActor;
    if (!actor || !sub_71004282EC(actor))
        return false;
    for (s32 i = 0; i < 5; ++i) {
        sead::Vector3f offset = sead::Vector3f::zero;
        switch (i) {
        case 1:
            offset.setRotated(actor->getMtx(), sead::Vector3f::ez);
            break;
        case 2:
            offset.setRotated(actor->getMtx(), -sead::Vector3f::ez);
            break;
        case 3:
            offset.setRotated(actor->getMtx(), sead::Vector3f::ex);
            break;
        case 4:
            offset.setRotated(actor->getMtx(), -sead::Vector3f::ex);
            break;
        }
        const auto position = offset + actor->getMtx().getTranslation();
        const sead::Vector3f start{position.x, position.y + 1.0f, position.z};
        const sead::Vector3f end{position.x, position.y - 5.0f, position.z};
        ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
        query.setStartAndEnd(start, end);
        query.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
        if (query.worldRayCast(ksys::phys::ContactLayerType::Entity)) {
            if (auto* body = query.getHitRigidBody()) {
                if (auto* tag = sead::DynamicCast<ksys::act::PhysicsUserTag>(body->getUserTag())) {
                    ksys::act::ActorLinkConstDataAccess accessor;
                    tag->acquireActor(&accessor);
                    if (accessor.hasTag(ksys::act::tags::IsIceMakerBlock)) {
                        accessor.linkAcquire(&_40);
                        break;
                    }
                }
            }
        }
    }
    return _40.hasProc();
}

void GuardianMiniOnNoNavMesh::sub_710041E15C() {
    if (_5c & 1) {
        if (!isBgGroundHit(mActor, false))
            _5c = (_5c & 0xfffc) | 2;
    } else if (_5c & 2) {
        if (isBgGroundHit(mActor, false)) {
            _5c = (_5c & 0xfff9) | 4;
            if (_40.hasProc()) {
                ksys::act::ActorLinkConstDataAccess accessor;
                ksys::act::acquireActor(&_40, &accessor);
                sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x8000004), nullptr);
                _40.reset();
            }
        }
    }
}

void GuardianMiniOnNoNavMesh::calc_() {
    if (!(_50.value <= sead::Mathf::epsilon()))
        _50.update();
    if (isCurrentChild("ナビメッシュなし") && getCurrentChild()->isChangeable() &&
        _50.value <= sead::Mathf::epsilon() && _40.hasProc()) {
        changeToOnIceMaker();
    } else {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed()) {
            if (isCurrentChild("アイスメーカー上") && _40.hasProc()) {
                ksys::act::ActorLinkConstDataAccess accessor;
                ksys::act::acquireActor(&_40, &accessor);
                sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x8000004), nullptr);
                _40.reset();
            }
            if (getCurrentChild()->isFinished())
                setFinished();
            else
                setFailed();
            return;
        }
    }
    if (isCurrentChild("アイスメーカー上"))
        sub_710041E15C();
}

}  // namespace uking::ai
