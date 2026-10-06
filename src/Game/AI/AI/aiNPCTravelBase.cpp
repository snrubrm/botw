#include "Game/AI/AI/aiNPCTravelBase.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actSchedule.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

NPCTravelBase::NPCTravelBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCTravelBase::~NPCTravelBase() = default;

bool NPCTravelBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NPCTravelBase::enter_(ksys::act::ai::InlineParamPack* params) {
    _68 = ksys::Timer(16, 16);
}

void NPCTravelBase::calc_() {
    if (_68.value <= sead::Mathf::epsilon())
        return;
    _68.update();
}

void NPCTravelBase::leave_() {
    if (_68.value <= sead::Mathf::epsilon())
        mActor->setFlag(ksys::act::Actor::ActorFlag::_34, false);
}

void NPCTravelBase::loadParams_() {}

// 0x71004dfa0c
void NPCTravelBase::sub_71004DFA0C(bool crouching) {
    const sead::SafeString name = crouching ? "Crouching" : "Standing";
    auto* cc = mActor->getCharacterController();
    auto* physics = mActor->getPhysics();
    if (cc && physics) {
        const s32 idx = physics->sub_7100FBE7F0(name);
        if (idx >= 0)
            cc->sub_7100F5F270(idx);
    }
}

// 0x71004df78c
void NPCTravelBase::sub_71004DF78C() {
    if (auto* schedule = mActor->getSchedule()) {
        mActor->getASList()->goLimpFromHeadShotMaybe(0x37, schedule->_248, 0);
        mActor->getASList()->goLimpFromHeadShotMaybe(0x38, schedule->_248, 0);
    }
}

}  // namespace uking::ai
