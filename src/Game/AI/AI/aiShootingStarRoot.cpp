#include "Game/AI/AI/aiShootingStarRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/World/worldManager.h"

namespace uking::ai {

ShootingStarRoot::ShootingStarRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ShootingStarRoot::~ShootingStarRoot() = default;

bool ShootingStarRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ShootingStarRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* wm = ksys::world::Manager::instance();
    if (!wm)
        return;
    auto* mgr = wm->getShootingStarMgr();
    if (!mgr)
        return;

    if (mgr->isStarPositionValid()) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(-sead::Vector3f::ey, "HitGroundAngle", -1);
        changeChild("光の柱を出す", &pack);
    } else {
        changeChild("飛んでいく");
    }
}

void ShootingStarRoot::calc_() {
    if (isFinished() || isFailed())
        return;

    const auto& pos = mActor->getMtx().getTranslation();
    if (pos.x < -4000.0f || pos.x > 4000.0f || pos.z < -3000.0f || pos.z > 3000.0f) {
        mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        setFailed();
    }

    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed()) {
        child->isChangeable();
        return;
    }

    if (isCurrentChild("飛んでいく")) {
        if (child->isFinished()) {
            ksys::act::ai::InlineParamPack pack;
            const sead::Vector3f angle =
                mActor->getVelocity().x == 0 && mActor->getVelocity().y == 0 &&
                        mActor->getVelocity().z == 0 ?
                    -sead::Vector3f::ey :
                    mActor->getVelocity();
            pack.addVec3(angle, "HitGroundAngle", -1);
            changeChild("光の柱を出す", &pack);
            return;
        }
    } else if (!isCurrentChild("光の柱を出す")) {
        return;
    }
    mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    setFinished();
}

void ShootingStarRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ShootingStarRoot::loadParams_() {}

}  // namespace uking::ai
