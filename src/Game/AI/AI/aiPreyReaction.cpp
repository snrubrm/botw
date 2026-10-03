#include "Game/AI/AI/aiPreyReaction.h"
#include <prim/seadSafeString.h>
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

PreyReaction::PreyReaction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PreyReaction::~PreyReaction() = default;

bool PreyReaction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PreyReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    m34();
    _38 = true;
}

void PreyReaction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PreyReaction::loadParams_() {}

void PreyReaction::m34() {
    if (m35())
        return;

    if (auto* manager = sub_710072BA90(mActor)) {
        manager->getField50();
        manager->getField54();
    }

    sead::FixedSafeString<128> message;
    message.format("%s：分岐条件が設定されていないリアクションです。", mActor->getName().cstr());
    setFailed();
    changeChild("ダメージ");
}

bool PreyReaction::isFinished() const {
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        return false;
    return true;
}

}  // namespace uking::ai
