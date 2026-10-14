#include "Game/Actor/AI/aiEnemyMoveBattle.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"

// Declaration only (same function as in aiSimpleEscapeFromTarget.cpp).
bool sub_710072F99C(ksys::act::Actor* actor, const sead::Vector3f& from, const sead::Vector3f& to,
                    sead::Vector3f* out_pos, s32 a5, f32 a6, f32 a7);

namespace uking::ai {

EnemyMoveBattle::EnemyMoveBattle(const InitArg& arg) : EnemyBattle(arg) {}

EnemyMoveBattle::~EnemyMoveBattle() = default;

void EnemyMoveBattle::sub_7100399BC8(sead::Vector3f* out, const sead::Vector3f& dir) {
    sead::Vector3f side;
    side.setCross(dir, sead::Vector3f::ey);
    side.y = 0.0f;
    side.normalize();
    sead::Vector3f front;
    mActor->getMtx().getBase(front, 2);
    if (side.dot(front) < 0.0f)
        side = -side;
    sead::Vector3f position;
    mActor->getMtx().getTranslation(position);
    *out = position;
    *out += side * *mMoveDist_s;
    *out -= dir * 0.5f;
    sub_710072F99C(mActor, position, *out, out, -1, -1.0f, -1.0f);
}

// NON_MATCHING: register allocation of the flattened direction and one store order.
bool EnemyMoveBattle::sub_710039997C(sead::Vector3f* normal) {
    auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor);
    if (!actor)
        return false;
    if (!normal)
        return !sub_710072E1B4(actor, false);

    sead::Vector3f start = actor->getMtx().getTranslation();
    start.y = actor->getAwareness()->_2c8.y;
    const sead::Vector3f front = actor->getMtx().getBase(2);
    const sead::Vector3f target = sub_71005D960C(actor);
    sead::Vector3f dir(target.x - start.x, 0.0f, target.z - start.z);
    dir.normalize();
    if (front.dot(dir) <= -0.50000006f)
        return true;

    ksys::phys::RayCastBodyQuery query(sub_710072E804(mActor, 0), ksys::phys::GroundHit::HitAll);
    query.enableLayer(ksys::phys::ContactLayer::EntityGround);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundRough);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
    query.enableLayer(ksys::phys::ContactLayer::EntityObject);
    query.enableLayer(ksys::phys::ContactLayer::EntityTree);
    query.setStartAndEnd(start, target);
    query.setNormalCheckingMode(ksys::phys::RayCast::NormalCheckingMode::_0);
    bool hit = false;
    if (query.worldRayCast(ksys::phys::ContactLayerType::Entity)) {
        query.getHitNormal(normal);
        hit = true;
    }
    return hit;
}

void EnemyMoveBattle::calc_() {
    // Whether the way to the target is clear (the actor is a DynamicActor and sub_710072E1B4 is false).
    const auto isClear = [this] {
        auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor);
        return actor && !sub_710072E1B4(actor, false);
    };

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("戦闘準備")) {
            if (getCurrentChild()->isFailed()) {
                setFailed();
                return;
            }
            const sead::Vector3f* target = mTargetPos_d;
            const s32 time = *mLimitMoveTime_s;
            _a8 = ksys::Timer(time, time);
            _b4 = ksys::Timer(10, 10);
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*target, "TargetPos", -1);
            changeChild("移動", &pack);
            return;
        }
        if (isCurrentChild("戦闘攻撃")) {
            if (getCurrentChild()->isFailed())
                setFailed();
            else
                setFinished();
            return;
        }
        if (isCurrentChild("移動")) {
            if (getCurrentChild()->isFailed()) {
                setFailed();
                return;
            }
            if (isClear()) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
                changeChild("回転", &pack);
                return;
            }
            m38();
            return;
        }
        if (isCurrentChild("回転")) {
            if (isClear())
                setFinished();
            else
                m38();
            return;
        }
    } else if (getCurrentChild()->isChangeable()) {
        if (isCurrentChild("戦闘準備")) {
            sead::Vector3f normal;
            const bool blocked = sub_710039997C(*mMoveDist_s <= 0.0f ? nullptr : &normal);
            sead::Vector3f target = *mTargetPos_d;
            if (blocked)
                sub_71005DB198(&target, mActor);
            else
                target = sub_71005D960C(mActor);
            sub_71005DB068(mActor, target);
            getCurrentChild()->setDynamicParam(sub_71005D9330(mActor), "TargetPos");
            if (m39()) {
                if (blocked && !(*mMoveDist_s <= 0.0f)) {
                    sead::Vector3f pos;
                    sub_7100399BC8(&pos, normal);
                    const s32 time = *mLimitMoveTime_s;
                    _a8 = ksys::Timer(time, time);
                    _b4 = ksys::Timer(10, 10);
                    ksys::act::ai::InlineParamPack pack;
                    pack.addVec3(pos, "TargetPos", -1);
                    changeChild("移動", &pack);
                    return;
                }
                m38();
                return;
            }
        } else if (isCurrentChild("移動")) {
            sead::Vector3f target = *mTargetPos_d;
            if (isClear()) {
                sub_71005DB198(&target, mActor);
                _b4 = ksys::Timer(10, 10);
            } else {
                _b4.update();
                target = sub_71005D960C(mActor);
            }
            sub_71005DB068(mActor, target);
            if (_b4.value <= sead::Mathf::epsilon()) {
                m38();
                return;
            }
            _a8.update();
            if (_a8.value <= sead::Mathf::epsilon()) {
                setFailed();
                return;
            }
        }
    }

    if (!isCurrentChild("戦闘攻撃"))
        return;
    sead::Vector3f target = sub_71005D960C(mActor);
    sub_71005DB068(mActor, target);
    getCurrentChild()->setDynamicParam(sub_71005D9330(mActor), "TargetPos");
}

void EnemyMoveBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBattle::enter_(params);
    m37();
}

bool EnemyMoveBattle::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void EnemyMoveBattle::leave_() {
    EnemyBattle::leave_();
    sub_71005DB3EC(mActor);
}

void EnemyMoveBattle::loadParams_() {
    EnemyBattle::loadParams_();
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mLimitMoveTime_s, "LimitMoveTime");
    getStaticParam(&mMoveDist_s, "MoveDist");
}

bool EnemyMoveBattle::isFinished() const {
    return ActionBase::isFinished() || (getCurrentChild()->isFinished() && isCurrentChild("戦闘攻撃"));
}

}  // namespace uking::ai
