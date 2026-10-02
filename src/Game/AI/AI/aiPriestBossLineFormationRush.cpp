#include "Game/AI/AI/aiPriestBossLineFormationRush.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

PriestBossLineFormationRush::PriestBossLineFormationRush(const InitArg& arg)
    : PriestBossFormation(arg) {}

PriestBossLineFormationRush::~PriestBossLineFormationRush() = default;

bool PriestBossLineFormationRush::init_(sead::Heap* heap) {
    return PriestBossFormation::init_(heap);
}

void PriestBossLineFormationRush::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossFormation::enter_(params);
    if (auto* controller = mActor->getCharacterController())
        controller->enableContactLayer(ksys::phys::ContactLayer::EntityNPC);
    m43();
}

void PriestBossLineFormationRush::leave_() {
    PriestBossFormation::leave_();
}

void PriestBossLineFormationRush::loadParams_() {
    PriestBossFormation::loadParams_();
}

void PriestBossLineFormationRush::calc_() {
    PriestBossFormation::calc_();
    if (isCurrentChild("攻撃")) {
        sub_71005183C0(false);
        getCurrentChild()->setDynamicParam(sub_71005D93CC(mActor), "TargetPos");
    }
}

void PriestBossLineFormationRush::m42() {
    sead::FixedSafeString<16> name;
    name.format("%d", sub_7100518B50());
    mActor->getASList()->goLimpFromHeadShotMaybe(0x2f, name, 0);
    changeChild("攻撃前");
}

}  // namespace uking::ai
