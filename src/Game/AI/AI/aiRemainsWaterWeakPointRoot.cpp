#include "Game/AI/AI/aiRemainsWaterWeakPointRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::ai {

RemainsWaterWeakPointRoot::RemainsWaterWeakPointRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RemainsWaterWeakPointRoot::~RemainsWaterWeakPointRoot() = default;

bool RemainsWaterWeakPointRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RemainsWaterWeakPointRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71007A458C(mActor, true);
    if (ksys::gdt::getFlag_Water_Relic_Step4()) {
        changeChild("戦闘終了");
    } else if (mActor->checkLinkBasicSig()) {
        changeChild("機能停止");
    } else {
        const bool battle_time = ksys::gdt::getFlag_Water_Relic_BattleTime();
        mActor->emitBasicSigOff();
        if (battle_time)
            changeChild("起動中");
        else
            changeChild("待機");
    }
}

void RemainsWaterWeakPointRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RemainsWaterWeakPointRoot::loadParams_() {}

}  // namespace uking::ai
