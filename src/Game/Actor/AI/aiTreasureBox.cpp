#include "Game/Actor/AI/aiTreasureBox.h"
#include "KingSystem/Physics/Constraint/physUnk_7102519e58.h"
#include <basis/seadNew.h>
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

// NON_MATCHING: name-search temporaries and hinge initialization are scheduled differently.
bool TreasureBox::init_(sead::Heap* heap) {
    *mIsOpenTreasureBox_a = false;
    *mIsSetupDropActor_a = false;
    auto* actor = mActor;
    const auto& name = actor->getName();
    if (name.findIndex("Iron") != -1 || name.findIndex("Wood") != -1 ||
        name.findIndex("Sandworm") != -1) {
        _c0._10 = new (heap) Unk_71024f7180;
        if (_c0._10) {
            const Unk_71024f7180::InitArg arg{actor->getPhysics(), "Body", sead::Vector3f::ex,
                                            sead::Vector3f::ez, "Cover"};
            if (!_c0._10->init(arg, heap)) {
                delete _c0._10;
                _c0._10 = nullptr;
            }
        }
    }
    return true;
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
