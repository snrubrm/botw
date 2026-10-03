#include "Game/AI/AI/aiWolfLinkReaction.h"
#include <prim/seadSafeString.h>
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Actor/actWolfLink.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

WolfLinkReaction::WolfLinkReaction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WolfLinkReaction::~WolfLinkReaction() = default;

bool WolfLinkReaction::init_(sead::Heap* heap) {
    _40 = sead::DynamicCast<act::WolfLink>(mActor);
    return true;
}

void WolfLinkReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    m34();
    _38 = true;
}

void WolfLinkReaction::leave_() {}

void WolfLinkReaction::loadParams_() {}

void WolfLinkReaction::m34() {
    if (m35())
        return;

    if (auto* manager = sub_710072BA90(mActor)) {
        manager->getField50();
        manager->getField54();
    }

    sead::FixedSafeString<128> message;
    message.format("%s：分岐条件が設定されていないリアクションです。", mActor->getName().cstr());
    setFailed();
    changeChild("小ダメージ");
}

bool WolfLinkReaction::isFinished() const {
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        return false;
    return true;
}

}  // namespace uking::ai
