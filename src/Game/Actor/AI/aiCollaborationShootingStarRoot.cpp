#include "Game/Actor/AI/aiCollaborationShootingStarRoot.h"
#include <codec/seadHashCRC32.h>
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/StageInfo.h"

namespace uking::ai {

CollaborationShootingStarRoot::CollaborationShootingStarRoot(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

// The original keeps this class's vtable store, which a defaulted destructor drops. Written like
// upstream's GameDataFlagSelector::~GameDataFlagSelector() { ; } (commit 96101229).
CollaborationShootingStarRoot::~CollaborationShootingStarRoot() {
    ;
}

bool CollaborationShootingStarRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void CollaborationShootingStarRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* anchor = ksys::world::ShootingStarMgrEx::sub_71010D0464(mIdentifier);
    const bool started = anchor && anchor->sub_71010D0734();
    changeChild(started ? "光の柱を出す" : "飛んでいく");
    ksys::act::acc::PlayerBase player;
    if (!started && player.getPlayerFromPlayerInfo()) {
        const bool state = player.sub_7100D0FF48() && player.m188();
        const bool other_state = player.m186();
        if (state || other_state) {
            if (anchor)
                anchor->sub_71010D1394();
            mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
            setFinished();
        }
    }
}

// NON_MATCHING: the original calls ShootingStarMgrEx::sub_71010D05F8 before getCurrentMapType (C++14 operand order of
// the member operator!=); only the registers of the two results differ.
void CollaborationShootingStarRoot::calc_() {
    if (isFinished() || isFailed())
        return;

    auto* anchor = ksys::world::ShootingStarMgrEx::sub_71010D0464(mIdentifier);
    if (ksys::StageInfo::getCurrentMapType() != ksys::world::ShootingStarMgrEx::sub_71010D05F8()) {
        if (anchor)
            anchor->sub_71010D1394();
        mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        setFinished();
        return;
    }

    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    if (pos.x < -4000.0f || pos.x > 4000.0f || pos.z < -4000.0f || pos.z > 4000.0f) {
        if (anchor)
            anchor->sub_71010D1394();
        mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        setFinished();
    }

    if (anchor && isCurrentChild("光の柱を出す")) {
        if (!anchor->sub_71010D0F64(2)) {
            anchor->sub_71010D1394();
            mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
            setFinished();
        }
        if (!anchor->_88) {
            anchor->sub_71010D1394();
            mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
            setFinished();
        }
    }

    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        return;

    if (isCurrentChild("飛んでいく")) {
        if (child->isFinished()) {
            sead::Matrix34f mtx = sead::Matrix34f::ident;
            mtx.setTranslation(pos);
            xlinkSearchAndEmit(mActor, "BrightTower_00", 2, &_58);
            _58.sub_7101241A44(mtx);
            changeChild("光の柱を出す");
            return;
        }
        if (anchor)
            anchor->sub_71010D1394();
    } else if (!isCurrentChild("光の柱を出す")) {
        return;
    }
    mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    setFinished();
}

void CollaborationShootingStarRoot::leave_() {
    _58.fadeXLink();
}

void CollaborationShootingStarRoot::loadParams_() {
    getAITreeVariable(&mCollaboShootingStarId_a, "CollaboShootingStarId");
    const sead::SafeString id = mCollaboShootingStarId_a->cstr();
    mIdentifier.name = id;
    mIdentifier.hash = sead::HashCRC32::calcStringHash(id.cstr());
}

}  // namespace uking::ai
