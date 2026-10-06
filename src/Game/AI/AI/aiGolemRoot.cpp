#include "Game/AI/AI/aiGolemRoot.h"
#include "Game/Actor/actUnk_7100d3cd74.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actUnk_71024ef4e8.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerLink.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"

namespace uking::ai {

// NON_MATCHING: the original keeps the bounds check of the outer rigid body set lookup (and reloads the
// set table pointer in the loop); the compiler folds it away
// 0x71003ffd3c
bool Unk_71003ffbf0::sub_71003FFD3C() {
    auto* actor = _0;
    auto* link = sub_71005D9050(actor);
    if (link && ksys::act::isPlayerProfile(link)) {
        auto* info = ksys::act::ActorSystem::instance()->getPlayerLink()->getAttachedTargetActor2()
                         ->mAttachInfo;
        if (info->_48 & 2) {
            auto* body = info->_c0;
            if (body) {
                if (auto* physics = actor->getPhysics()) {
                    const s32 count = physics->getNumRigidBodySets();
                    for (s32 i = 0; i < count; ++i) {
                        auto* set = physics->getRigidBodySet(i);
                        const s32 body_count = set->getRigidBodies().size();
                        for (s32 j = 0; j < body_count; ++j) {
                            if (set->getRigidBody(j) == body)
                                return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

void Unk_71023f5460::call(s32* a1, s32* a2, u32* a3, u32* a4, s32* a5, u64 a6) {
    if (*a4 != 4 || *a5 == -1)
        return;

    auto* actor = mDamageManager->mActor;
    const auto* body_set = actor->getRigidBodyByName(sub_71007A24D0()->cstr());
    if (!body_set)
        return;
    auto* body = body_set->getRigidBody(0);
    if (!body)
        return;

    const s32 num = sub_71007A26AC(actor);
    bool found = false;
    for (s32 i = 0; i < num; ++i) {
        const auto* info = sub_71007A255C(actor, i);
        if (info && info->_50 == 0x10) {
            if (info->_c0 != body)
                return;
            found = true;
        }
    }
    if (found) {
        *a5 = -1;
        *a4 = -1;
    }
}

bool GolemRoot::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x3000003 || message->getType() == 0x3000004) {
        if (auto* parts = mActor->m101()) {
            auto& link = parts->getActorPartsActor("WeakPoint");
            if (link.hasProc()) {
                ksys::act::ActorConstDataAccess accessor;
                ksys::act::acquireActor(&link, &accessor);
                mActor->sendMessageOnProcessingThread(*accessor.getMessageTransceiverId(),
                                                      message->getType(), nullptr, true);
            }
        }
    }
    return GolemRootBase::handleMessage_(message);
}

GolemRoot::GolemRoot(const InitArg& arg) : GolemRootBase(arg) {}

void GolemRoot::sub_710040007C() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy)
        return;

    auto& link = enemy->getActorPartsActor("WeakPoint");
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&link, &accessor);
    accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    enemy->sub_7100D3CFEC("WeakPoint");
}

GolemRoot::~GolemRoot() {
    sub_710040007C();
}

bool GolemRoot::init_(sead::Heap* heap) {
    return GolemRootBase::init_(heap);
}

void GolemRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    GolemRootBase::enter_(params);
}

void GolemRoot::leave_() {
    GolemRootBase::leave_();
    sub_71005DA114(mActor, &_3b0);
}

void GolemRoot::loadParams_() {
    GolemRootBase::loadParams_();
    getStaticParam(&mClimbFinishTime_s, "ClimbFinishTime");
    getStaticParam(&mStandContactHeight_s, "StandContactHeight");
    getStaticParam(&mIsBreakContactTree_s, "IsBreakContactTree");
    getMapUnitParam(&mGolemWeakPointLocation_m, "GolemWeakPointLocation");
    getMapUnitParam(&mGolemSleepType_m, "GolemSleepType");
    getMapUnitParam(&mGolemWeakPointActor_m, "GolemWeakPointActor");
    getAITreeVariable(&mGolemClimbedTime_a, "GolemClimbedTime");
}

}  // namespace uking::ai
