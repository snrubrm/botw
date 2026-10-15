#include "Game/Actor/Action/actionSandwormTackleMove.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actPhysicsUserTag.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/Physics/System/physCollisionInfo.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

const sead::SafeString& sub_71002CCC20(s32 idx);

// Adjacent target-list helper family used by the two Sandworm tackle actions.
namespace uking::action {

// Vtable 24510F8. Inline construction in 71F8B0 owns position/radius and the m2 result flag.
class Unk_71024510f8 : public ksys::act::Unk_71024dccf8 {
public:
    Unk_71024510f8(const sead::Vector3f& position, f32 radius)
        : mPosition(position), mRadius(radius) {}
    ~Unk_71024510f8() override = default;
    bool m2(ksys::act::Unk_71024dc978* entry) override;

    sead::Vector3f mPosition;
    bool _34 = false;
    f32 mRadius;
};
KSYS_CHECK_SIZE_NX150(Unk_71024510f8, 0x40);

bool Unk_71024510f8::m2(ksys::act::Unk_71024dc978* entry) {
    _34 = false;
    auto* target = sead::DynamicCast<ksys::act::Unk_71024dc858>(entry);
    if (!target)
        return false;
    if (ksys::act::hasTag(&target->mLink, ksys::act::tags::EatItem)) {
        ksys::act::ActorLinkConstDataAccess actor;
        if (ksys::act::acquireActor(&target->mLink, &actor) && actor.isStateCalc() &&
            (mPosition - actor.getActorMtx().getTranslation()).length() < mRadius)
            return true;
    }
    if (ksys::act::hasTag(&target->mLink, ksys::act::tags::ExplosivesEnemyAI)) {
        ksys::act::ActorLinkConstDataAccess actor;
        if (ksys::act::acquireActor(&target->mLink, &actor) && actor.isStateCalc() &&
            actor.getName().findIndex("RemoteBomb") != -1 &&
            (mPosition - actor.getActorMtx().getTranslation()).length() < mRadius) {
            _34 = true;
            return true;
        }
    }
    return false;
}

// NON_MATCHING: available-target scan and awareness iteration scheduling.
bool Unk_SandwormTackleMoveList::sub_710071F8B0(const sead::Vector3f& position, f32 radius) {
    auto* awareness = mActor->getAwareness();
    if (!awareness)
        return false;
    Unk_SandwormTackleTarget* target = nullptr;
    for (s32 i = 0, n = mTargets.size(); i < n; ++i) {
        if (mTargets.at(i)->sub_710073E4C4()) {
            target = mTargets.at(i);
            break;
        }
    }
    Unk_71024510f8 filter(position, radius);
    bool found = false;
    while (auto* entry = ksys::act::sub_7100D7EEE8(&awareness->_8, &filter)) {
        if (!filter._34) {
            ksys::act::ActorLinkConstDataAccess actor;
            if (ksys::act::acquireActor(&entry->_0.mLink, &actor))
                actor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        } else if (target) {
            target->sub_710073E580(&entry->_0.mLink);
            found = true;
            target = nullptr;
            for (s32 i = 0, n = mTargets.size(); i < n; ++i) {
                if (mTargets.at(i)->sub_710073E4C4()) {
                    target = mTargets.at(i);
                    break;
                }
            }
        }
    }
    return found;
}

// NON_MATCHING: contact iteration and accessor distance scheduling.
void Unk_SandwormTackleMoveList::sub_710071FAEC(ksys::act::Actor* actor,
                                              const sead::Vector3f& center, f32 radius) {
    auto* set = actor->getRigidBodyByName(sub_71007A24BC()->cstr());
    if (!set || set->getRigidBodies().size() < 1)
        return;
    auto* contacts = set->getRigidBody(0)->getContactPointInfo();
    if (contacts && contacts->getNumContactPoints() != 0 && !contacts->begin().isEnd()) {
        for (const auto* point : *contacts) {
            auto* body = point->body_b;
            if (!body)
                continue;
            sead::Vector3f position;
            body->getPosition(&position);
            if ((position - center).squaredLength() < radius * radius) {
                if (auto* tag = sead::DynamicCast<ksys::act::PhysicsUserTag>(body->getUserTag())) {
                    ksys::act::ActorLinkConstDataAccess accessor;
                    tag->acquireActor(&accessor);
                    if (accessor.hasProc() && accessor.isStateCalc() &&
                        accessor.hasTag(ksys::act::tags::CookMaterial))
                        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
                }
            }
        }
    }
    auto* info = set->getRigidBody(0)->getCollisionInfo();
    if (!info || info->getCollidingBodies().size() == 0)
        return;
    auto* collision = info->getCollidingBodies().front();
    info->lock();
    for (; collision; collision = info->getCollidingBodies().next(collision)) {
        auto* body = collision->bodies[1];
        if (!body)
            continue;
        sead::Vector3f position;
        body->getPosition(&position);
        if ((position - center).squaredLength() < radius * radius) {
            if (auto* tag = sead::DynamicCast<ksys::act::PhysicsUserTag>(body->getUserTag())) {
                ksys::act::ActorLinkConstDataAccess accessor;
                tag->acquireActor(&accessor);
                if (accessor.hasProc() && accessor.isStateCalc() &&
                    accessor.hasTag(ksys::act::tags::CookMaterial))
                    accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
            }
        }
    }
    info->unlock();
}

bool Unk_SandwormTackleMoveList::sub_71F6DC(sead::Heap* heap) {
    auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor);
    if (!enemy)
        return false;

    auto* target = new (heap, 8) Unk_SandwormTackleTarget(enemy);
    if (!target)
        return false;
    mTargets.pushBack(target);
    target->_48 = sub_71002CCC20(0);
    if (!target->sub_710073E45C(heap, sead::SafeString::cEmptyString))
        return false;

    auto* target2 = new (heap, 8) Unk_SandwormTackleTarget(enemy);
    if (!target2)
        return false;
    mTargets.pushBack(target2);
    target2->_48 = sub_71002CCC20(1);
    return target2->sub_710073E45C(heap, sead::SafeString::cEmptyString);
}

// Deletes all targets (called from the owners' destructors).
void Unk_SandwormTackleMoveList::sub_71F858() {
    while (mTargets.size() > 0) {
        if (auto* target = mTargets.popBack())
            delete target;
    }
}

void Unk_SandwormTackleMoveList::sub_71FEFC() {
    for (s32 i = 0, n = mTargets.size(); i < n; ++i) {
        auto* target = mTargets.at(i);
        target->_38.reset();
        target->_58 = 0;
    }
}

bool Unk_SandwormTackleMoveList::sub_71FF70(const ksys::MessageAck* ack) {
    for (s32 i = 0, n = mTargets.size(); i < n; ++i) {
        if (mTargets.at(i)->sub_710073E5E0(ack)) {
            if (mTargets(i)->_58 == 2)
                xlinkSearchAndEmit(mActor, "BombEatAngry", 2, nullptr);
            return true;
        }
    }
    return false;
}

bool Unk_SandwormTackleMoveList::sub_71FEB4() const {
    for (s32 i = 0, n = mTargets.size(); i < n; ++i) {
        if (mTargets(i)->_58 == 1)
            return true;
    }
    return false;
}

}  // namespace uking::action
