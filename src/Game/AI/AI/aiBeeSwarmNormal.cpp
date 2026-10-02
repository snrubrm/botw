#include "Game/AI/AI/aiBeeSwarmNormal.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

BeeSwarmNormal::BeeSwarmNormal(const InitArg& arg) : EnemyNormal(arg) {}

BeeSwarmNormal::~BeeSwarmNormal() = default;

bool BeeSwarmNormal::init_(sead::Heap* heap) {
    return EnemyNormal::init_(heap);
}

void BeeSwarmNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNormal::enter_(params);
}

void BeeSwarmNormal::leave_() {
    if (auto* awareness = mActor->getAwareness())
        awareness->enable();
    EnemyNormal::leave_();
}

void BeeSwarmNormal::loadParams_() {
    EnemyNormal::loadParams_();
}

bool BeeSwarmNormal::handleMessage_(const ksys::Message& message) {
    const bool had_message = _3d8._30;
    if (_3d8.m2(message)) {
        _450 = _3d8._38._2c;
        if (!had_message)
            sub_71005D8DE8(mActor, _3d8._38._0, nullptr, nullptr);
        return true;
    }
    return EnemyNormal::handleMessage_(message);
}

void BeeSwarmNormal::calc_() {
    if (isCurrentChild("死亡")) {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed())
            mActor->deleteEx(ksys::act::Actor::DeleteType::_1, ksys::act::BaseProc::DeleteReason::_0);
        return;
    }

    if (_3d8._30 && isCurrentChild("諦め")) {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed()) {
            auto* actor = mActor;
            sub_710072BB28(actor);
            actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
            actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_2000000);
            actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::Alive);
            changeChild("死亡");
            return;
        }
    }

    EnemyNormal::calc_();
    if (_3d8._30 && isCurrentChild("待機")) {
        auto* actor = mActor;
        sub_710072BB28(actor);
        actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
        actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_2000000);
        actor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::Alive);
        changeChild("死亡");
    }
}

s32 BeeSwarmNormal::m52(s32 idx) {
    static const s32 sTable[] = {1, 0, 2, 3, 4, 5, 6, 7, 8};
    return sTable[idx];
}

void BeeSwarmNormal::m37() {
    if (auto* awareness = mActor->getAwareness())
        awareness->enable();
    EnemyNormal::m37();
}

void BeeSwarmNormal::m38() {
    EnemyNormal::m38();
    if (auto* awareness = mActor->getAwareness())
        awareness->disable();
}

void BeeSwarmNormal::m48(sead::Vector3f* pos) {
    *pos = _450;
}

void BeeSwarmNormal::m50(Unk1* out, s32 idx) {
    if (isCurrentChild("見失い") || isCurrentChild("諦め") || isCurrentChild("怒り")) {
        out->_0 = -1;
        return;
    }
    EnemyNormal::m50(out, idx);
}

// NON_MATCHING: the original stores _0 = 1 / _4 = 2 as a 32-bit pair (stp) after the flag update;
// ours merges them into one 64-bit constant store
void BeeSwarmNormal::m49(Unk1* out, s32 idx) {
    if (isCurrentChild("見失い") || isCurrentChild("諦め") || isCurrentChild("怒り")) {
        out->_0 = -1;
        return;
    }
    const s32 type = m52(idx);
    if (type == 5) {
        out->_0 = -1;
        return;
    }

    if (isCurrentChild("プレイヤー発見")) {
        if (ksys::act::isPlayerProfile(&sub_71005D94AC(mActor)) && type == 1) {
            out->_8 |= 0x284;
            out->_0 = 1;
            out->_4 = 2;
            return;
        }
        out->_0 = -1;
        return;
    }

    if (type == 1) {
        if (!_3d8._30) {
            out->_0 = -1;
            return;
        }
        out->_0 = 1;
        out->_8 |= 2;
        return;
    }
    EnemyNormal::m49(out, idx);
}

ksys::act::Unk_71024dc858* BeeSwarmNormal::m47(ksys::act::AwarenessInstance* awareness,
                                               ksys::act::Unk_71024dccf8* filter, s32 a3) {
    while (awareness->_260[3]) {
        auto* entry = ksys::act::sub_7100D7EEE8(&awareness->_260[3]->_8, filter);
        if (!entry)
            return nullptr;
        if (entry->_a0 == 2 && sub_71005E116C(&entry->mLink))
            return entry;
    }
    return nullptr;
}

}  // namespace uking::ai
