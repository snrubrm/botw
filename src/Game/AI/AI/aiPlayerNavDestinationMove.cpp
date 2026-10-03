#include "Game/AI/AI/aiPlayerNavDestinationMove.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

PlayerNavDestinationMove::PlayerNavDestinationMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
PlayerNavDestinationMove::~PlayerNavDestinationMove() {
    ;
}

bool PlayerNavDestinationMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PlayerNavDestinationMove::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (sub_710072E154(actor, {*mDestPosX_d, *mDestPosY_d, *mDestPosZ_d}, nullptr, -1)) {
        sub_710082DF0C();
        return;
    }
    auto* nav = actor->m45();
    if (!nav) {
        sub_710082DF0C();
        return;
    }
    if (!nav->_18)
        ksys::phys::HavokAI::instance()->sub_7100F82BCC(nav);
    nav->sub_7100F76790();
    _58._0 = nav;
    {
        auto lock = sead::makeScopedLock(nav->_68);
        nav->_60 = nullptr;
    }
    if (_58._0)
        _58._0->sub_7100F7604C(0.1f);
    _58.sub_7100710F04();
    const sead::Vector3f dest{*mDestPosX_d, *mDestPosY_d, *mDestPosZ_d};
    if (_58._0) {
        _58._0->sub_7100F75F8C(dest);
        _58._8 = 0;
    }
    sub_710082E048();
}

// NON_MATCHING: block layout only; the original probes the second state switch as 2, 3 and places the state-2
// block (`sub_710082E048`, destination) after the function's return
void PlayerNavDestinationMove::calc_() {
    _58.sub_7100710F28();
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (child->isFinished())
            setFinished();
        else
            setFailed();
        return;
    }
    if (isCurrentChild("適当移動")) {
        switch (_58._8) {
        case 1:
            sub_710082E38C();
            break;
        case 2: {
            const sead::Vector3f dest{*mDestPosX_d, *mDestPosY_d, *mDestPosZ_d};
            if (_58._0) {
                _58._0->sub_7100F75F8C(dest);
                _58._8 = 0;
            }
        }
            [[fallthrough]];
        case 3:
            setFinished();
            break;
        }
    } else if (isCurrentChild("移動")) {
        switch (_58._8) {
        case 2: {
            sub_710082E048();
            const sead::Vector3f dest{*mDestPosX_d, *mDestPosY_d, *mDestPosZ_d};
            if (_58._0) {
                _58._0->sub_7100F75F8C(dest);
                _58._8 = 0;
            }
            break;
        }
        case 3:
            setFinished();
            break;
        }
    }
    const sead::Vector3f dest{*mDestPosX_d, *mDestPosY_d, *mDestPosZ_d};
    if (sub_710072E154(mActor, dest, nullptr, -1)) {
        if (!isCurrentChild("直進"))
            sub_710082DF0C();
    }
}

void PlayerNavDestinationMove::leave_() {
    if (auto* nav = mActor->m45()) {
        nav->sub_7100F76778();
        _58.sub_7100710F08();
        _58._0 = nullptr;
    }
}

void PlayerNavDestinationMove::sub_710082DF0C() {
    ksys::act::ai::InlineParamPack pack;
    pack.addFloat(*mDestPosX_d, "DestPosX", -1);
    pack.addFloat(*mDestPosY_d, "DestPosY", -1);
    pack.addFloat(*mDestPosZ_d, "DestPosZ", -1);
    pack.addFloat(*mStickValue_d, "StickValue", -1);
    changeChild("直進", &pack);
}

void PlayerNavDestinationMove::sub_710082E048() {
    ksys::act::ai::InlineParamPack pack;
    pack.addFloat(*mDestPosX_d, "DestPosX", -1);
    pack.addFloat(*mDestPosY_d, "DestPosY", -1);
    pack.addFloat(*mDestPosZ_d, "DestPosZ", -1);
    pack.addFloat(*mStickValue_d, "StickValue", -1);
    changeChild("適当移動", &pack);
}

void PlayerNavDestinationMove::sub_710082E38C() {
    ksys::act::ai::InlineParamPack pack;
    pack.addFloat(*mDestPosX_d, "DestPosX", -1);
    pack.addFloat(*mDestPosY_d, "DestPosY", -1);
    pack.addFloat(*mDestPosZ_d, "DestPosZ", -1);
    pack.addFloat(*mStickValue_d, "StickValue", -1);
    changeChild("移動", &pack);
}

void PlayerNavDestinationMove::loadParams_() {
    getDynamicParam(&mDestPosX_d, "DestPosX");
    getDynamicParam(&mDestPosY_d, "DestPosY");
    getDynamicParam(&mDestPosZ_d, "DestPosZ");
    getDynamicParam(&mStickValue_d, "StickValue");
}

}  // namespace uking::ai
