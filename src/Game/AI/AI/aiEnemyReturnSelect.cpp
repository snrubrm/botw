#include "Game/AI/AI/aiEnemyReturnSelect.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

bool sub_710072C9FC(ksys::act::Actor* actor, f32 distance);

namespace uking::ai {

EnemyReturnSelect::EnemyReturnSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyReturnSelect::~EnemyReturnSelect() = default;

bool EnemyReturnSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: branch layout and parameter-pack cleanup address scheduling differ.
void EnemyReturnSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mCentralPos_d, "CentralPos", -1);
    bool return_home;
    if (sub_71005D9F04(mActor)) {
        return_home = isRootAiParamINot5() || sub_710072C9FC(mActor, 2.0f);
    } else {
        sead::Vector3f home;
        mActor->getHomePos(&home);
        return_home = !((home - *mCentralPos_d).length() > *mNotReturnDist_s);
    }
    changeChild(return_home ? "帰還" : "未帰還", &pack);
}

void EnemyReturnSelect::calc_() {}

bool EnemyReturnSelect::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool EnemyReturnSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

void EnemyReturnSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyReturnSelect::loadParams_() {
    getStaticParam(&mNotReturnDist_s, "NotReturnDist");
    getDynamicParam(&mCentralPos_d, "CentralPos");
}

}  // namespace uking::ai
