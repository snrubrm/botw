#include "Game/AI/AI/aiChuchuNavMoveTarget.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

ChuchuNavMoveTarget::ChuchuNavMoveTarget(const InitArg& arg) : NavMoveTarget(arg) {}

ChuchuNavMoveTarget::~ChuchuNavMoveTarget() = default;

bool ChuchuNavMoveTarget::init_(sead::Heap* heap) {
    return NavMoveTarget::init_(heap);
}

void ChuchuNavMoveTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    NavMoveTarget::enter_(params);
    const f32 half_time = *mWallHitTime_s * 0.5f;
    if (half_time > 0)
        _388._84 = half_time;
    if (*mWallHitTime_s > 0)
        _388._88 = *mWallHitTime_s;
    _388._78 = _388._88;
    _388._7c = 0;
    _388._80 = 0;
    _388._90.setUndef();
    _388._8c = false;
}

// NON_MATCHING: position copy store order and register allocation of the move direction (same operations).
void ChuchuNavMoveTarget::calc_() {
    NavMoveTarget::calc_();

    if (isCurrentChild("直進")) {
        const sead::Vector3f pos = mActor->getMtx().getTranslation();
        sead::Vector3f target;
        m35(&target);
        sead::Vector3f dir(target.x - pos.x, 0.0f, target.z - pos.z);
        dir.normalize();
        sead::Vector3f front;
        sub_71000891C8(&front, mActor);
        if (dir.dot(front) >= 0.9396926f)
            _388.sub_7100716408(pos);
        else
            _388.reset();
        if (getCurrentChild()->isChangeable() && _388._78 <= 0.0f) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(target, "TargetPos", -1);
            changeChild("ジャンプ", &pack);
        }
    } else if (isCurrentChild("移動")) {
        const sead::Vector3f pos = mActor->getMtx().getTranslation();
        sead::Vector3f target;
        m35(&target);
        sead::Vector3f dir;
        if (auto* nav = mActor->m45()) {
            {
                auto lock = sead::makeScopedLock(nav->_1e0);
                dir.set(nav->_23c.x, 0.0f, nav->_23c.z);
            }
            if (dir.x == 0.0f && dir.z == 0.0f) {
                auto lock = sead::makeScopedLock(nav->_1e0);
                dir = nav->_248;
            }
        } else {
            dir.set(target.x - pos.x, 0.0f, target.z - pos.z);
        }
        const f32 len = dir.normalize();
        sead::Vector3f front;
        sub_71000891C8(&front, mActor);
        if (dir.dot(front) >= 0.9396926f)
            _388.sub_7100716408(pos);
        else
            _388.reset();
        if (getCurrentChild()->isChangeable() && _388._78 <= 0.0f) {
            sead::Vector3f jump_target = target;
            if (mActor->m45())
                jump_target = pos + dir * (len * 5.0f);
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(jump_target, "TargetPos", -1);
            changeChild("ジャンプ", &pack);
        }
    } else {
        _388.reset();
    }
}

void ChuchuNavMoveTarget::leave_() {
    NavMoveTarget::leave_();
}

void ChuchuNavMoveTarget::loadParams_() {
    NavMoveTarget::loadParams_();
    getStaticParam(&mWallHitTime_s, "WallHitTime");
}

}  // namespace uking::ai
