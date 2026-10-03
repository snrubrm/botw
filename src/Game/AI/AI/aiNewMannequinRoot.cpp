#include "Game/AI/AI/aiNewMannequinRoot.h"
#include "Game/AI/aiUnk_71005E0420.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

NewMannequinRoot::NewMannequinRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NewMannequinRoot::~NewMannequinRoot() = default;

bool NewMannequinRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NewMannequinRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    _48.sub_710070AE18(actor);
    if (actor->isWaitRevivalForUsed()) {
        ksys::act::disableAllAttClients(mActor);
        _48.x();
        changeChild("装備なし");
    } else {
        auto* mannequin = mActor;
        mannequin->emitBasicSigOff();
        ksys::act::enableAllAttClients(mannequin);
        _48.x();
        changeChild("装備あり");
    }
}

void NewMannequinRoot::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed())
        return;
    child->isChangeable();
}

bool NewMannequinRoot::handleMessage_(const ksys::Message* message) {
    if (isCurrentChild("装備あり"))
        return handleItemPickedMessageMaybe(*message, &_48, mActor, nullptr);
    return false;
}

void NewMannequinRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NewMannequinRoot::loadParams_() {
    getMapUnitParam(&mArmorDyeColor_m, "ArmorDyeColor");
    getMapUnitParam(&mShopSellType_m, "ShopSellType");
}

}  // namespace uking::ai
