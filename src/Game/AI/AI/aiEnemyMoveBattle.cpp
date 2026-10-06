#include "Game/AI/AI/aiEnemyMoveBattle.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"

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
