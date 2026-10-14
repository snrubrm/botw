#include "Game/Actor/AI/aiSandwormBlownOff.h"
#include "Game/Actor/actSandworm.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

SandwormBlownOff::SandwormBlownOff(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SandwormBlownOff::~SandwormBlownOff() = default;

bool SandwormBlownOff::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SandwormBlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("先行動");
}

void SandwormBlownOff::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("先行動")) {
            if (auto* worm = sead::DynamicCast<act::Sandworm>(mActor))
                worm->sub_71002CDAE4(true);
            changeChild("ぴより開始");
        } else if (isCurrentChild("ぴより開始")) {
            _40.reset(*mBlownOffTimer_s);
            changeChild("ぴより中");
        } else if (isCurrentChild("ぴより中")) {
            changeChild("ぴより終了");
        } else if (isCurrentChild("ぴより終了")) {
            if (auto* worm = sead::DynamicCast<act::Sandworm>(mActor))
                worm->sub_71002CDAE4(false);
            changeChild("後攻撃");
        } else if (isCurrentChild("後攻撃")) {
            setFinished();
        }
    } else if (isCurrentChild("ぴより中")) {
        _40.update();
        if (_40.value <= sead::Mathf::epsilon())
            changeChild("ぴより終了");
    }
}

void SandwormBlownOff::leave_() {
    if (auto* worm = sead::DynamicCast<act::Sandworm>(mActor))
        worm->sub_71002CDAE4(false);
}

void SandwormBlownOff::loadParams_() {
    getStaticParam(&mBlownOffTimer_s, "BlownOffTimer");
}

bool SandwormBlownOff::isFinished() const {
    return ksys::act::ai::Ai::isFinished() ||
           (isCurrentChild("後攻撃") && getCurrentChild()->isFinished());
}

}  // namespace uking::ai
