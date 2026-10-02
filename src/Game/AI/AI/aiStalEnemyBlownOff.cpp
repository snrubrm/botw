#include "Game/AI/AI/aiStalEnemyBlownOff.h"
#include "Game/AI/AI/aiStalEnemyRoot.h"
#include "Game/AI/aiUnk_7100724C64.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"

namespace uking::ai {

StalEnemyBlownOff::StalEnemyBlownOff(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StalEnemyBlownOff::~StalEnemyBlownOff() = default;

bool StalEnemyBlownOff::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StalEnemyBlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    auto* unit = sub_7100726FF4(actor);
    if (unit && unit->_8.isOff(0xe)) {
        auto* damage_mgr = sub_710072BA90(actor);
        if (damage_mgr && damage_mgr->getField50() == 3 && damage_mgr->checkDamageFlags(0) &&
            sub_7100726620(actor)) {
            changeChild("ヘッドショット");
            return;
        }
    }
    changeChild("ふっとび");
}

void StalEnemyBlownOff::calc_() {
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        return;

    if (getCurrentChild()->isFinished())
        setFinished();
    else if (getCurrentChild()->isFailed())
        setFailed();
}

bool StalEnemyBlownOff::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool StalEnemyBlownOff::isFinished() const {
    return ksys::act::ai::Ai::isFinished() || getCurrentChild()->isFinished();
}

void StalEnemyBlownOff::leave_() {
    ksys::act::ai::Ai::leave_();
}

void StalEnemyBlownOff::loadParams_() {
    getStaticParam(&mDrownDepth_s, "DrownDepth");
}

}  // namespace uking::ai
