#include "Game/Actor/Action/actionHorseMoveToSafePos.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::action {

HorseMoveToSafePos::HorseMoveToSafePos(const InitArg& arg) : AnimalMoveGuidedBase(arg) {}

HorseMoveToSafePos::~HorseMoveToSafePos() = default;

bool HorseMoveToSafePos::init_(sead::Heap* heap) {
    return AnimalMoveGuidedBase::init_(heap);
}

void HorseMoveToSafePos::enter_(ksys::act::ai::InlineParamPack* params) {
    AnimalMoveGuidedBase::enter_(params);
}

void HorseMoveToSafePos::leave_() {
    AnimalMoveGuidedBase::leave_();
    if (_a8) {
        if (auto* nav = mActor->m45())
            nav->sub_7100F75AB8();
        _a8 = false;
    }
    if (_a0) {
        ksys::phys::HavokAI::instance()->destroyQuery(_a0);
        _a0 = nullptr;
    }
}

void HorseMoveToSafePos::loadParams_() {
    AnimalMoveGuidedBase::loadParams_();
    getStaticParam(&mSearchRadius_s, "SearchRadius");
    getStaticParam(&mAreaThreshold_s, "AreaThreshold");
    getStaticParam(&mResolvePenetrationRadiusScale_s, "ResolvePenetrationRadiusScale");
    getStaticParam(&mResolvePenetrationSearchRadius_s, "ResolvePenetrationSearchRadius");
    getStaticParam(&mSetEndIfCurrentFaceIsSafe_s, "SetEndIfCurrentFaceIsSafe");
}

void HorseMoveToSafePos::calc_() {
    auto* character = mActor->m45();
    if (isFinished() || isFailed() || !character || (character->_220 & 0x41000)) {
        AnimalMoveGuidedBase::calc_();
        return;
    }
    if (_a8) {
        if (!_a0 && !sub_71001A25D4(character))
            setFailed();
    } else {
        if (!_a0) {
            AnimalMoveGuidedBase::calc_();
            return;
        }
        if (_a0->_8 == 2) {
            character->sub_7100F75F8C(_a0->_c);
            ksys::phys::HavokAI::instance()->destroyQuery(_a0);
            _a0 = nullptr;
        }
    }
    mActor->getASList()->x_6(1, 0, 0.0f);
    mActor->getASList()->x_6(2, 0, 0.0f);
    mActor->getASList()->x_6(9, 0, 0.0f);
    auto* rideable = mActor->m132();
    auto* as_list = mActor->getASList();
    act::sub_7100E7F698(rideable, as_list, mActor->getCharacterController());
}

}  // namespace uking::action
