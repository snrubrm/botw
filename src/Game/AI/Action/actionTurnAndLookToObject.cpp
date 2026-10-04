#include "Game/AI/Action/actionTurnAndLookToObject.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "Game/Actor/actNPC.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

TurnAndLookToObject::TurnAndLookToObject(const InitArg& arg) : LookAtObject(arg) {}

TurnAndLookToObject::~TurnAndLookToObject() = default;

bool TurnAndLookToObject::init_(sead::Heap* heap) {
    return LookAtObject::init_(heap);
}

void TurnAndLookToObject::enter_(ksys::act::ai::InlineParamPack* params) {
    m33();
    ksys::act::BaseProcLink link;
    sead::Vector3f pos;
    pos = sead::Vector3f::zero;
    switch (_30) {
    case 0:
        if (!m34(&link, &pos, _48, _58)) {
            _d0 = true;
            _34 = 0;
        }
        break;
    case 4:
        if (!m35(&link, &pos, _48, _58)) {
            _d0 = true;
            _34 = 0;
        }
        break;
    }

    if (link.hasProc())
        m36(&link, sead::Vector3f::zero);
    else
        m36(nullptr, pos);

    if (auto* npc = sead::DynamicCast<uking::act::NPC>(mActor)) {
        switch (_34) {
        case 0:
            npc->sub_7100022E3C(_45);
            break;
        case 1:
            npc->sub_7100022D44(_45, 0, sead::Vector3f::zero, nullptr, sead::Vector3f::zero);
            break;
        }
    } else {
        setFailed();
    }
    m40();
}

void TurnAndLookToObject::leave_() {
    if (auto* cc = mActor->getCharacterController())
        cc->sub_7100F5FB24(sead::Vector3f::zero);
}

void TurnAndLookToObject::loadParams_() {
    LookAtObject::loadParams_();
    getDynamicParam(&mIsConfront_d, "IsConfront");
}

void TurnAndLookToObject::calc_() {
    LookAtObject::calc_();
    sub_7100738488(mActor, 0.0f, -sead::Vector3f::ey);
    auto* controller = mActor->getCharacterController();
    if (isFinished())
        playAS("Wait", true, 0, 0, -1.0f);
    if (isFinished() || isFailed()) {
        sub_7100738AA8(mActor, 0.0f);
        return;
    }
    if (controller)
        m41(controller);
}

}  // namespace uking::action
