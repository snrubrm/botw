#include "Game/AI/AI/aiBattleBgmRequestFinishTag.h"
#include "Game/AI/aiUnk_7100FFD79C.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

BattleBgmRequestFinishTag::BattleBgmRequestFinishTag(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BattleBgmRequestFinishTag::~BattleBgmRequestFinishTag() = default;

bool BattleBgmRequestFinishTag::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void BattleBgmRequestFinishTag::enter_(ksys::act::ai::InlineParamPack* params) {
    _38 = mActor->checkBasicSig();
    changeChild("待機");
}

void BattleBgmRequestFinishTag::calc_() {
    const bool signal = mActor->checkBasicSig();
    if (!_38 && signal) {
        if (auto* bgm = sub_7100FFD79C())
            bgm->m10();
    }
    _38 = signal;
}

void BattleBgmRequestFinishTag::leave_() {
    ksys::act::ai::Ai::leave_();
}

void BattleBgmRequestFinishTag::loadParams_() {}

}  // namespace uking::ai
