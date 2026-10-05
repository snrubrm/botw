#include "Game/AI/AI/aiTreasureBox.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"

bool sub_710072B8E8(ksys::act::Actor* actor);

namespace uking::ai {

TreasureBox::TreasureBox(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TreasureBox::~TreasureBox() {
    auto** unit = static_cast<Unk_71025afb58**>(mSharpWeaponAddParam_a);
    if (*unit)
        *unit = nullptr;
    if (_c0._10)
        delete _c0._10;
}

bool TreasureBox::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TreasureBox::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TreasureBox::leave_() {
    ksys::act::ai::Ai::leave_();
}

// NON_MATCHING: the contact checks and listener result join the return paths differently.
bool TreasureBox::handleMessage_(const ksys::Message* message) {
    if (!isCurrentChild("クローズ待機"))
        return false;
    auto* actor = mActor;
    if (sub_710072B8E8(actor))
        return true;
    auto* body = actor->getMainBody();
    if (body && body->getMotionType() == ksys::phys::MotionType::Dynamic) {
        auto* info = body->getContactPointInfo();
        if (body->isActive() && info &&
            (info->getNumContactPoints().load() == 0 || info->begin().isEnd())) {
            return true;
        }
    }
    return _80.m2(*message);
}

void TreasureBox::loadParams_() {
    getMapUnitParam(&mSharpWeaponJudgeType_m, "SharpWeaponJudgeType");
    getMapUnitParam(&mDropActor_m, "DropActor");
    getMapUnitParam(&mDropTable_m, "DropTable");
    getAITreeVariable(&mIsOpenTreasureBox_a, "IsOpenTreasureBox");
    getAITreeVariable(&mIsSetupDropActor_a, "IsSetupDropActor");
    getAITreeVariable(&mDropActorName_a, "DropActorName");
    getAITreeVariable(&mSharpWeaponAddParam_a, "SharpWeaponAddParam");
}

}  // namespace uking::ai
