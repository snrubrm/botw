#include "Game/AI/AI/aiRemainsFireRoot.h"
#include "Game/Actor/actRemains.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::ai {

RemainsFireRoot::RemainsFireRoot(const InitArg& arg) : RemainsRoot(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
RemainsFireRoot::~RemainsFireRoot() {
    ;
}

bool RemainsFireRoot::init_(sead::Heap* heap) {
    return RemainsRoot::init_(heap);
}

// NON_MATCHING: register allocation / scheduling of the final grid-cell snap only (the control flow, the
// map-object-or-actor position select and the constants match); the x / z cell centre is
// `sign * (floor(|v| / 1000) * 1000 + 500)`
void RemainsFireRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    RemainsRoot::enter_(params);

    auto* as_list = mActor->getASList();
    if (!as_list) {
        setFailed();
        return;
    }
    if (!mTargetBoneName_s.isEmpty()) {
        as_list->sub_710115BAF8(mTargetBoneName_s);
        if (!as_list->_14.isValid()) {
            setFailed();
            return;
        }
    }

    const bool add_to_world = !_49 && !isCurrentChild("待機");
    if (auto* body_set = mActor->getPhysics()->findBodyByName(*sub_71007A2534())) {
        if (add_to_world)
            body_set->addToWorld();
        else
            body_set->removeFromWorld();
    }

    f32 x = 0;
    f32 z = 0;
    if (auto* actor = mActor) {
        if (auto* object = actor->getMapObject()) {
            z = object->getTranslate().z;
            x = object->getTranslate().x;
        } else {
            z = actor->getMtx().m[2][3];
            x = actor->getMtx().m[0][3];
        }
    }

    _60 = (x >= 0 ? 1.0f : -1.0f) *
          (f32(sead::Mathf::floor((x > 0 ? x : -x) / 1000.0f)) * 1000.0f + 500.0f);
    _64 = 0;
    _68 = (z >= 0 ? 1.0f : -1.0f) *
          (f32(sead::Mathf::floor((z > 0 ? z : -z) / 1000.0f)) * 1000.0f + 500.0f);
    _6c = 0;
}

bool RemainsFireRoot::reenter_(ksys::act::ai::ActionBase* other, bool x) {
    if (!RemainsRoot::reenter_(other, true))
        return false;

    auto* fire = sead::DynamicCast<RemainsFireRoot>(other);
    if (!fire)
        return false;

    _60 = fire->_60;
    _64 = fire->_64;
    _68 = fire->_68;
    _6c = 0;

    const bool add_to_world = !_49 && !isCurrentChild("待機");
    if (auto* body_set = mActor->getPhysics()->findBodyByName(*sub_71007A2534())) {
        if (add_to_world)
            body_set->addToWorld();
        else
            body_set->removeFromWorld();
    }
    return true;
}

// NON_MATCHING: the original peels the first iteration of the first SafeString == literal loop (first
// literal byte 0xe9 folded, no pointer-equality shortcut); ours emits both comparisons the same way
void RemainsFireRoot::handlePendingChildChange_() {
    const sead::SafeString name = mChildren[mPendingChildIdx]->getName();
    if (name == "遺物チャレンジ中") {
        if (auto* remains = sead::DynamicCast<act::Remains>(mActor))
            remains->_bb8 = true;
        sub_71007A3540(mActor);
        changeChild("遺物チャレンジ中");
    } else if (name == "通常行動") {
        m36();
    } else {
        if (auto* remains = sead::DynamicCast<act::Remains>(mActor))
            remains->_bb8 = false;
        sub_71007A36BC(mActor);
        changeChild("待機");
    }
}

void RemainsFireRoot::calc_() {
    RemainsRoot::calc_();

    if (!isCurrentChild("待機")) {
        ksys::act::acc::PlayerBase player;
        if (player.getPlayerFromPlayerInfo() && player.x_5()) {
            if (_6c++ >= 30) {
                mActor->sendMessage(*player.getMessageTransceiverId(), ksys::MessageType(0x3000007),
                                    nullptr, true);
                _6c = 0;
            }
        }
    }
}

void RemainsFireRoot::leave_() {
    RemainsRoot::leave_();
}

void RemainsFireRoot::loadParams_() {
    RemainsRoot::loadParams_();
    getStaticParam(&mTargetBoneName_s, "TargetBoneName");
}

void RemainsFireRoot::m34() {}

// NON_MATCHING (M): the control flow and calls match, but the original calls assureTerminationImpl_ + a
// virtual SafeString slot (0x18) after both name comparisons fail (not reproduced; it has no visible
// consumer) and lays out the "待機" tail differently
void RemainsFireRoot::m35(bool x) {
    if (x && handlePendingChildChange())
        return;

    auto* actor = mActor;
    if (_48) {
        if (const char* unique_name = actor->getUniqueName()) {
            const sead::SafeString name = unique_name;
            if (name == "RemainsFire_Battle") {
                if (auto* remains = sead::DynamicCast<act::Remains>(mActor))
                    remains->_bb8 = true;
                sub_71007A3540(mActor);
                changeChild("遺物チャレンジ中");
                return;
            }
            if (name == "RemainsFire_Round") {
                m36();
                return;
            }
            if (auto* remains = sead::DynamicCast<act::Remains>(mActor))
                remains->_bb8 = false;
            sub_71007A36BC(mActor);
            changeChild("待機");
            return;
        }
    }

    if (auto* remains = sead::DynamicCast<act::Remains>(actor))
        remains->_bb8 = false;
    sub_71007A36BC(mActor);
    changeChild("待機");
}

void RemainsFireRoot::m36() {
    if (auto* remains = sead::DynamicCast<act::Remains>(mActor))
        remains->_bb8 = true;
    sub_71007A36BC(mActor);
    RemainsRoot::m36();
}

}  // namespace uking::ai
