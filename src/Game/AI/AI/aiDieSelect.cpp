#include "Game/AI/AI/aiDieSelect.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

DieSelect::DieSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DieSelect::~DieSelect() = default;

bool DieSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: only the order of the two `-1` copies on the null-manager path (declaring a3 before a2 matches)
void DieSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
    actor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_2000000);
    s32 a2 = -1;
    s32 a3 = -1;
    bool a4 = false;
    bool a5 = false;
    if (auto* manager = sub_710072BA90(actor)) {
        a3 = manager->getField54();
        a2 = manager->getField50();
        a4 = manager->checkDamageFlags(1);
        a5 = manager->checkDamageFlags(10);
    }
    m34(a2, a3, a4, a5);
}

bool DieSelect::isChangeable() const {
    return false;
}

void DieSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DieSelect::loadParams_() {}

void DieSelect::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        m35();
        callDeleteAndCreateDropAndEmit(mActor, 0);
        setFinished();
    }
}

// NON_MATCHING: the original computes the switch flag before the final getLife() call (with a
// range check + bit test); ours sinks it after the call
void DieSelect::m34(s32 a2, s32 a3, bool a4, bool a5) {
    if (a3 == 34) {
        changeChild("消滅");
        return;
    }
    if (a5) {
        *mActor->getLife() = 0;
        changeChild("被暗殺");
        return;
    }
    if (a4) {
        *mActor->getLife() = 0;
        changeChild("被特効");
        return;
    }
    if (a3 == 32) {
        changeChild("溺死");
        return;
    }
    if (sub_7100736BD8(a3)) {
        *mActor->getLife() = 0;
        changeChild("落下死");
        return;
    }
    if (a2 == 22 && a3 == 29) {
        changeChild("濡死");
        return;
    }

    bool x;
    switch (a3) {
    case 1:
    case 4:
    case 5:
    case 6:
    case 11:
    case 14:
    case 15:
    case 17:
    case 18:
    case 21:
    case 25:
    case 26:
    case 27:
    case 28:
    case 29:
    case 30:
    case 31:
        x = true;
        break;
    default:
        x = false;
        break;
    }
    *mActor->getLife() = 0;
    if (a3 == 23 || x)
        changeChild("死亡");
    else
        changeChild("自然死");
}

}  // namespace uking::ai
