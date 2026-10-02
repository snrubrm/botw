#include "Game/AI/AI/aiStalEnemyDoShootPartSelect.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_7100724C64.h"

namespace uking::ai {

StalEnemyDoShootPartSelect::StalEnemyDoShootPartSelect(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

StalEnemyDoShootPartSelect::~StalEnemyDoShootPartSelect() = default;

bool StalEnemyDoShootPartSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StalEnemyDoShootPartSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (s32(sead::GlobalRandom::instance()->getU32() & 0x7fffffff) % 100 < *mShootRate_s &&
        sub_7100728640(mActor)) {
        changeChild("パーツ投げ", params);
    } else {
        changeChild("通常", params);
    }
}

void StalEnemyDoShootPartSelect::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished()) {
        if (child->isFinished())
            setFinished();
        if (child->isFailed())
            setFailed();
    } else if (child->isFailed()) {
        if (child->isFinished())
            setFinished();
        if (child->isFailed())
            setFailed();
    } else {
        child->isChangeable();
    }
}

void StalEnemyDoShootPartSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void StalEnemyDoShootPartSelect::loadParams_() {
    getStaticParam(&mShootRate_s, "ShootRate");
}

}  // namespace uking::ai
