#include "Game/AI/AI/aiGanonDemoMoveSeqTwoAction.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::ai {

GanonDemoMoveSeqTwoAction::GanonDemoMoveSeqTwoAction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonDemoMoveSeqTwoAction::~GanonDemoMoveSeqTwoAction() = default;

bool GanonDemoMoveSeqTwoAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonDemoMoveSeqTwoAction::enter_(ksys::act::ai::InlineParamPack* params) {
    sead::Vector3f target_pos;
    if (auto* actor = mActor) {
        auto* link = sub_71005D9050(actor);
        if (link != nullptr && link->hasProc() && ksys::act::isPlayerProfile(link))
            target_pos = sub_71005D9330(actor);
        else
            target_pos = getPlayerPosition();
    }
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target_pos, "TargetPos", -1);
    changeChild("後行動", &pack);
}

void GanonDemoMoveSeqTwoAction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GanonDemoMoveSeqTwoAction::loadParams_() {}

void GanonDemoMoveSeqTwoAction::calc_() {
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        return;

    if (isCurrentChild("先行動")) {
        sead::Vector3f target_pos;
        if (auto* actor = mActor) {
            auto* link = sub_71005D9050(actor);
            if (link != nullptr && link->hasProc() && ksys::act::isPlayerProfile(link))
                target_pos = sub_71005D9330(actor);
            else
                target_pos = getPlayerPosition();
        }
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(target_pos, "TargetPos", -1);
        changeChild("後行動", &pack);
    } else if (child->isFinished()) {
        setFinished();
    } else {
        setFailed();
    }
}

}  // namespace uking::ai
