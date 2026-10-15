#include "Game/Actor/AI/aiFishSafeReturn.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include <gfx/seadCamera.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/Camera/CameraMgr.h"

namespace uking::ai {

FishSafeReturn::FishSafeReturn(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

FishSafeReturn::~FishSafeReturn() = default;

bool FishSafeReturn::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void FishSafeReturn::enter_(ksys::act::ai::InlineParamPack* params) {
    _60.set(*mTargetPos_d);
    changeToMove();
}

// NON_MATCHING: the camera look vector subtractions are scheduled differently; the rest matches.
void FishSafeReturn::calc_() {
    if (isFinished() || isFailed())
        return;

    auto* child = getCurrentChild();
    if (!child) {
        setFailed();
        return;
    }

    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("移動")) {
            setFinished();
            return;
        }
        if (isCurrentChild("逃走")) {
            child->setDynamicParam(getPlayerPosition(), "MoveAwayFromPos");
            if (!*mIsEscape_d) {
                changeChild("待機");
                return;
            }
            const auto& mtx = mActor->getMtx();
            const f32 x = mtx(0, 3);
            const f32 z = mtx(2, 3);
            if (auto* camera = ksys::CameraMgr::instance()->getLookAtCamera()) {
                const auto& cam_pos = camera->getPos();
                const auto& cam_at = camera->getAt();
                const sead::Vector3f to_actor(x - cam_pos.x, 0.0f, z - cam_pos.z);
                const sead::Vector3f look(cam_at.x - cam_pos.x, 0.0f, cam_at.z - cam_pos.z);
                if (to_actor.dot(look) > 0.0f) {
                    sub_71003CFB58();
                    return;
                }
            }
            changeChild("フェードアウト");
            return;
        }
        if (isCurrentChild("待機")) {
            if (*mIsEscape_d) {
                sub_71003CFB58();
                return;
            }
            if (!((_60 - getPlayerPosition()).squaredLength() <=
                  *mAllowReturnThreatDist_s * *mAllowReturnThreatDist_s)) {
                changeToMove();
                return;
            }
            changeChild("待機");
            return;
        }
        if (isCurrentChild("フェードアウト")) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(_60, "TargetPos", -1);
            pack.addVec3(sead::Vector3f::ez, "TargetFoward", -1);
            changeChild("ワープ", &pack);
            return;
        }
        if (isCurrentChild("ワープ")) {
            getPlayerPosition();
            if (*mIsEscape_d || !((_60 - getPlayerPosition()).squaredLength() <=
                                  *mAllowReturnThreatDist_s * *mAllowReturnThreatDist_s)) {
                ksys::act::disableAllAttClients(mActor);
                ksys::act::disableAttClient(mActor, "NoticeDo");
                return;
            }
            changeChild("フェードイン");
            return;
        }
        if (isCurrentChild("フェードイン")) {
            setFinished();
            return;
        }
    }

    if (isCurrentChild("移動") || isCurrentChild("待機")) {
        if (*mIsEscape_d)
            sub_71003CFB58();
        return;
    }
    if (!isCurrentChild("逃走"))
        ksys::act::disableAllAttClients(mActor);
}

void FishSafeReturn::leave_() {
    ksys::act::ai::Ai::leave_();
}

void FishSafeReturn::loadParams_() {
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mDivePercent_s, "DivePercent");
    getStaticParam(&mAllowReturnThreatDist_s, "AllowReturnThreatDist");
    getDynamicParam(&mIsEscape_d, "IsEscape");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void FishSafeReturn::changeToMove() {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_60, "TargetPos", -1);
    pack.addVec3(_60, "MoveAwayFromPos", -1);
    changeChild("移動", &pack);
}

// NON_MATCHING: camera vector subtraction and normalization scheduling differ.
void FishSafeReturn::sub_71003CFB58() {
    if (isCurrentChild("逃走"))
        return;
    sead::Vector3f pos = mActor->getMtx().getTranslation();
    // The original calls this getter before acquiring the player and discards its result.
    getPlayerPosition();
    ksys::act::ActorLinkConstDataAccess accessor;
    sead::Vector3f dir;
    if (ksys::act::acquireActor(&act::PlayerInfo::getSomeProcLink(), &accessor) &&
        accessor.sub_7100D0FF48()) {
        dir = getPlayerPosition();
        dir -= pos;
        dir.y = 0.0f;
        dir.normalize();
        dir.y = *mDivePercent_s;
        dir = -dir;
        dir.normalize();
    } else {
        auto* camera = ksys::CameraMgr::instance()->getLookAtCamera();
        if (!camera) {
            setFailed();
            return;
        }
        dir = camera->getAt() - camera->getPos();
        dir.y = -*mDivePercent_s;
        dir.normalize();
    }
    pos += dir * 10.0f;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    pack.addVec3(getPlayerPosition(), "MoveAwayFromPos", -1);
    changeChild("逃走", &pack);
}

bool FishSafeReturn::isChangeable() const {
    return isCurrentChild("移動") || isCurrentChild("逃走");
}

}  // namespace uking::ai
