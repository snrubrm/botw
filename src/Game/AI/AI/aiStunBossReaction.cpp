#include "Game/AI/AI/aiStunBossReaction.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

StunBossReaction::StunBossReaction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StunBossReaction::~StunBossReaction() = default;

bool StunBossReaction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StunBossReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    const s32* life = mActor->getLife();
    if (life && *life <= 0) {
        sub_710072BB28(mActor);
        changeChild("死亡", params);
        return;
    }

    auto* mgr = sub_710072BA90(mActor);
    if (!mgr) {
        changeChild("ダメージ", params);
        return;
    }
    if (mgr->checkDamageFlags(1)) {
        changeChild("特効", params);
        return;
    }
    switch (mgr->getField54()) {
    case 5:
    case 15:
    case 17:
        changeChild("ダメージ", params);
        break;
    case 11:
    case 12:
    case 13:
        changeChild("ガード", params);
        break;
    default:
        changeChild("スタン", params);
        break;
    }
}

// NON_MATCHING: the original tests case 17 before case 15
void StunBossReaction::calc_() {
    if (!isCurrentChild("死亡")) {
        const s32* life = mActor->getLife();
        if (life && *life <= 0) {
            sub_710072BB28(mActor);
            changeChild("死亡");
            return;
        }
    }

    if (isCurrentChild("ガード") || isCurrentChild("ダメージ")) {
        if (auto* mgr = sub_710072BA90(mActor)) {
            if (mgr->checkDamageFlags(1)) {
                changeChild("特効");
            } else {
                switch (mgr->getField54()) {
                case 21:
                case 22:
                    changeChild("スタン");
                    return;
                case 15:
                case 17:
                    if (isCurrentChild("ガード")) {
                        changeChild("ダメージ");
                        return;
                    }
                    if (isCurrentChild("ダメージ") && sub_71007368A4(mgr->getAttacker())) {
                        changeChild("ダメージ");
                        return;
                    }
                    break;
                default:
                    break;
                }
            }
        }
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (!isCurrentChild("死亡"))
            setFinished();
    } else if (child->isChangeable()) {
        // discarded call (in the original)
        isCurrentChild("死亡");
    }
}

void StunBossReaction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void StunBossReaction::loadParams_() {}

}  // namespace uking::ai
