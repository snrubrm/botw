#include "Game/AI/AI/aiWolfLinkFollowWait.h"
#include <cmath>
#include "Game/Actor/actWolfLink.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::ai {

WolfLinkFollowWait::WolfLinkFollowWait(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WolfLinkFollowWait::~WolfLinkFollowWait() = default;

bool WolfLinkFollowWait::init_(sead::Heap* heap) {
    _48 = sead::DynamicCast<act::WolfLink>(mActor);
    return _48 != nullptr;
}

void WolfLinkFollowWait::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("待機");
}

// NON_MATCHING: regalloc (pos.x/pos.z registers swapped), dot product scheduled after the cross product
void WolfLinkFollowWait::calc_() {
    if (isFailed())
        return;

    if (isCurrentChild("待機")) {
        ksys::act::ActorConstDataAccess accessor;
        if (!ksys::act::acquireActor(&ksys::act::PlayerInfo::getSomeProcLink(), &accessor)) {
            setFailed();
            return;
        }

        if (!(_48->_1698 & 0x10))
            return;

        const auto& mtx = mActor->getMtx();
        sead::Vector3f front;
        mtx.getBase(front, 2);
        sead::Vector3f pos;
        mtx.getTranslation(pos);
        sead::Vector3f target_pos;
        accessor.getActorMtx().getTranslation(target_pos);
        const sead::Vector3f diff = target_pos - pos;
        sead::Vector3f dir = diff;
        dir.normalize();
        if (diff.z * diff.z + diff.x * diff.x >= 3.0f * 3.0f) {
            const f32 angle = std::atan2(front.cross(dir).length(), front.dot(dir));
            if (angle > *mLockonTurnThreshold_s) {
                target_pos += accessor.getVelocity() * 15.0f;
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(target_pos, "TargetPos", -1);
                changeChild("回転", &pack);
                return;
            }
        }
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed())
        changeChild("待機");
}

void WolfLinkFollowWait::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WolfLinkFollowWait::loadParams_() {
    getStaticParam(&mTurnThreshold_s, "TurnThreshold");
    getStaticParam(&mLockonTurnThreshold_s, "LockonTurnThreshold");
}

}  // namespace uking::ai
