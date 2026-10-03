#include "Game/AI/AI/aiItemAmiiboRoot.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/UI/uiUtils.h"
#include "Game/gameAmiiboMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::ai {

ItemAmiiboRoot::ItemAmiiboRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ItemAmiiboRoot::~ItemAmiiboRoot() = default;

bool ItemAmiiboRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ItemAmiiboRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ItemAmiiboRoot::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("エポナ対応対象のリンク検出")) {
            if (!child->isFinished()) {
                changeChild("ドロップテーブルからアクタ生成");
                return;
            }
            ui::playSound("AmiiboHit", nullptr);
        }
        const bool finished = child->isFinished();
        auto* mgr = AmiiboMgr::instance();
        if (finished) {
            if (mgr->_2cc == 1)
                mgr->_2cc = 2;
        } else {
            if (mgr->_2cc == 1)
                mgr->_2cc = 3;
        }
        setFinished();
        mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }

    if (mActor->getMainBody())
        mActor->getMainBody()->setTransform(getPlayerPositionViaPlayerInfo(),
                                            ksys::phys::PropagateToLinkedMotions{true});
}

void ItemAmiiboRoot::leave_() {
    if (!isFinished() && !isFailed()) {
        auto* mgr = AmiiboMgr::instance();
        if (mgr->_2cc == 1)
            mgr->_2cc = 3;
    }
}

void ItemAmiiboRoot::loadParams_() {
    getMapUnitParam(&mAmiiboCharacterId_m, "AmiiboCharacterId");
    getMapUnitParam(&mAmiiboNumberingId_m, "AmiiboNumberingId");
}

}  // namespace uking::ai
