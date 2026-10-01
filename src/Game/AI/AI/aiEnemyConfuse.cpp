#include "Game/AI/AI/aiEnemyConfuse.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

EnemyConfuse::EnemyConfuse(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyConfuse::~EnemyConfuse() = default;

bool EnemyConfuse::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyConfuse::enter_(ksys::act::ai::InlineParamPack* params) {
    _40 = *mConfuseTime_s;
    sead::Vector3f pos;
    mActor->getHomePos(&pos);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "CentralPos", -1);
    changeChild("行動", &pack);
}

void EnemyConfuse::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyConfuse::loadParams_() {
    getStaticParam(&mConfuseTime_s, "ConfuseTime");
}

// NON_MATCHING: the original hoists the child vtable loads above the isFinished/isFailed branches
void EnemyConfuse::calc_() {
    if (_40 > 0.0f)
        ksys::Timer::update(&_40, -1.0f);

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (child->isFinished())
            setFinished();
        else
            setFailed();
    } else if (child->isChangeable() && _40 <= 0.0f) {
        setFinished();
    }
}

}  // namespace uking::ai
