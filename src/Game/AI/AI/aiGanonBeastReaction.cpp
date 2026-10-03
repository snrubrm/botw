#include "Game/AI/AI/aiGanonBeastReaction.h"
#include "Game/AI/aiUnk_710070284C.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::ai {

GanonBeastReaction::GanonBeastReaction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonBeastReaction::~GanonBeastReaction() = default;

bool GanonBeastReaction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonBeastReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_80000000);
    if (sub_71007028CC(mActor)) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&ksys::act::PlayerInfo::getSomeProcLink(), &accessor);
        mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x80000c1),
                            nullptr, false);
        changeChild("死亡");
        return;
    }
    if (sub_7100703BC8(mActor))
        changeChild("形態変化ダメージ");
    else
        changeChild("弱点ヒット");
}

void GanonBeastReaction::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        setFinished();
    } else if (child->isChangeable()) {
        auto* actor = mActor;
        if (!isCurrentChild("死亡") && sub_71007028CC(actor)) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&ksys::act::PlayerInfo::getSomeProcLink(), &accessor);
            mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x80000c1),
                                nullptr, false);
            changeChild("死亡");
            return;
        }
    }

    if (isCurrentChild("弱点ヒット")) {
        if (auto* damage_mgr = sub_710072BA90(mActor)) {
            const s32 damage = damage_mgr->getDamage();
            if (damage > 0) {
                if (sub_7100703BC8(mActor))
                    changeChild("形態変化ダメージ");
                else
                    changeChild("弱点ヒット");
            }
        }
    }
}

void GanonBeastReaction::leave_() {
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_80000000);
}

void GanonBeastReaction::loadParams_() {
    getStaticParam(&mASSlot_s, "ASSlot");
    getAITreeVariable(&mWeakPointAliveFlag_a, "WeakPointAliveFlag");
    getAITreeVariable(&mWeakPointActiveFlag_a, "WeakPointActiveFlag");
    getAITreeVariable(&mIsWeakPointAppearMode_a, "IsWeakPointAppearMode");
}

}  // namespace uking::ai
