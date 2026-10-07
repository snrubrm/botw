#include "Game/AI/AI/aiPauseMenuPlayerRoot.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "Game/Actor/actPauseMenuPlayer.h"
#include "Game/UI/uiOnUiActorMgr.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

PauseMenuPlayerRoot::PauseMenuPlayerRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PauseMenuPlayerRoot::~PauseMenuPlayerRoot() = default;

bool PauseMenuPlayerRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PauseMenuPlayerRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _38 = false;
    _39 = false;
    mActor->getASList()->goLimpFromHeadShotMaybe(0x3e, "EatFood", 0);
    if (ui::OnUiActorMgr::instance()) {
        mActor->getASList()->x_2(66, 5, ui::OnUiActorMgr::instance()->_1f4.isOnBit(3), false);
        ui::OnUiActorMgr::instance()->sub_7100907A30();
    }
    const f32 value = mActor->getChemicalStuff() ? mActor->getChemicalStuff()->sub_7100D91958() : 0.0f;
    mActor->getASList()->x_6(24, 0, value);
    auto* actor = sead::DynamicCast<uking::act::PauseMenuPlayer>(mActor);
    if (actor)
        actor->getASList()->x_2(66, 33, actor->_c35, false);
    if (!isCurrentChild("通常待機"))
        changeChild("通常待機", nullptr);
}

void PauseMenuPlayerRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PauseMenuPlayerRoot::loadParams_() {}

// 0x71004f5624
void PauseMenuPlayerRoot::calc_() {
    if (_38) {
        changeChild("抱え持ち増加", nullptr);
        _38 = false;
    } else if (_39) {
        changeChild("アイテム使用", nullptr);
        _39 = false;
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("抱え持ち増加") || isCurrentChild("アイテム使用")) {
            if (!isCurrentChild("通常待機"))
                changeChild("通常待機", nullptr);
            return;
        }
    }
    if (!isCurrentChild("抱え持ち増加"))
        return;
    auto* actor = sead::DynamicCast<uking::act::PauseMenuPlayer>(mActor);
    if (!actor || actor->getFlagC34())
        return;
    if (!isCurrentChild("通常待機"))
        changeChild("通常待機", nullptr);
}

// 0x71004f57f8
bool PauseMenuPlayerRoot::handleMessage_(const ksys::Message* message) {
    const auto type = message->getType();
    if (type == 0x8000091) {
        _38 = true;
    } else if (type >= 0x8000092 && type <= 0x8000098) {
        switch (type) {
        case 0x8000093:
            mActor->getASList()->goLimpFromHeadShotMaybe(0x3e, "EatCookingDish", 0);
            break;
        case 0x8000094:
            mActor->getASList()->goLimpFromHeadShotMaybe(0x3e, "EatCookingSkewer", 0);
            break;
        case 0x8000095:
            mActor->getASList()->goLimpFromHeadShotMaybe(0x3e, "EatBizarre", 0);
            break;
        case 0x8000096:
            mActor->getASList()->goLimpFromHeadShotMaybe(0x3e, "EatTooHard", 0);
            break;
        case 0x8000097:
            mActor->getASList()->goLimpFromHeadShotMaybe(0x3e, "Drink", 0);
            break;
        case 0x8000098:
            mActor->getASList()->goLimpFromHeadShotMaybe(0x3e, "UseFairy", 0);
            break;
        default:
            mActor->getASList()->goLimpFromHeadShotMaybe(0x3e, "EatFood", 0);
            break;
        }
        _39 = true;
    } else if (type == 0x8000099) {
        if (auto* unk = mActor->getASList()->_b0)
            unk->_21 = false;
    } else if (type == 0x800009a) {
        if (!isCurrentChild("通常待機"))
            changeChild("通常待機", nullptr);
    } else {
        return false;
    }
    return true;
}

}  // namespace uking::ai
