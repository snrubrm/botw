#include "Game/Actor/AI/aiStalEnemyGrabShootOwnPart.h"
#include "Game/Actor/aiUnk_7100724C64.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

StalEnemyGrabShootOwnPart::StalEnemyGrabShootOwnPart(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StalEnemyGrabShootOwnPart::~StalEnemyGrabShootOwnPart() = default;

bool StalEnemyGrabShootOwnPart::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StalEnemyGrabShootOwnPart::enter_(ksys::act::ai::InlineParamPack* params) {
    switch (sub_7100728870(mActor)) {
    case 1: {
        ksys::act::ai::InlineParamPack pack;
        pack.addInt(1, "PartIndex", -1);
        changeChild("左腕掴み", &pack);
        break;
    }
    case 2: {
        ksys::act::ai::InlineParamPack pack;
        pack.addInt(2, "PartIndex", -1);
        changeChild("アゴ掴み", &pack);
        break;
    }
    case 3: {
        ksys::act::ai::InlineParamPack pack;
        pack.addInt(3, "PartIndex", -1);
        changeChild("肋骨掴み", &pack);
        break;
    }
    case 4: {
        ksys::act::ai::InlineParamPack pack;
        pack.addInt(4, "PartIndex", -1);
        changeChild("肋骨掴み", &pack);
        break;
    }
    case 5: {
        ksys::act::ai::InlineParamPack pack;
        pack.addInt(5, "PartIndex", -1);
        changeChild("肋骨掴み", &pack);
        break;
    }
    case 6: {
        ksys::act::ai::InlineParamPack pack;
        pack.addInt(6, "PartIndex", -1);
        changeChild("肋骨掴み", &pack);
        break;
    }
    default:
        setFailed();
        break;
    }
}

void StalEnemyGrabShootOwnPart::calc_() {
    if (isFinished() || isFailed())
        return;

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("投げる")) {
            setFinished();
            return;
        }
        if (child->isFinished() && mActor->getConnectedCalcChild()) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("投げる", &pack);
        } else {
            setFailed();
        }
    } else if (isCurrentChild("投げる")) {
        child->setDynamicParam(*mTargetPos_d, "TargetPos");
    }
}

void StalEnemyGrabShootOwnPart::leave_() {
    mActor->resetConnectedCalcChild(false);
}

void StalEnemyGrabShootOwnPart::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
