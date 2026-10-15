#include "Game/Actor/Action/actionAnimalEatAction.h"
#include "Game/Actor/actHorseStrings.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"

namespace uking::action {

AnimalEatAction::AnimalEatAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AnimalEatAction::~AnimalEatAction() = default;

bool AnimalEatAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AnimalEatAction::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* rideable = mActor->m132();
    auto* as_list = mActor->getASList();
    if (!rideable || !as_list) {
        setFailed();
        return;
    }
    rideable->_130 = 0;
    rideable->_134 = 0;
    mActor->getASList()->x_6(1, 0, 0.0f);
    mActor->getASList()->x_6(2, 0, 0.0f);
    rideable->_18.sub_7100E76E74(act::sUnk_71026032d0, false);
    _30.setDirect(sead::BitFlag8::makeMask(Bit(Bit::_0)));
    const f32 frames = *mMinFramesPlayWaitAS_s;
    _34.value = frames;
    _34.previous_value = frames;
}

void AnimalEatAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void AnimalEatAction::loadParams_() {
    getStaticParam(&mMinFramesPlayWaitAS_s, "MinFramesPlayWaitAS");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

// NON_MATCHING: enum conversion temporaries occupy separate stack slots.
void AnimalEatAction::calc_() {
    if (isFinished() || isFailed())
        return;
    auto* as_list = mActor->getASList();
    auto* rideable = mActor->m132();
    if (!as_list || !rideable) {
        setFailed();
        return;
    }
    ksys::act::ActorLinkConstDataAccess accessor;
    const bool has_target = ksys::act::acquireActor(mTargetActor_d, &accessor);
    const bool eat = as_list->x(56, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true);
    if (has_target && eat) {
        _30.set(sead::BitFlag8::makeMask(Bit(Bit::_1)));
        if (!m32())
            setFailed();
        accessor.sub_7100D0EAA4(11);
    }
    if (!has_target && !_30.isOn(sead::BitFlag8::makeMask(Bit(Bit::_2))) && !_30.isOn(sead::BitFlag8::makeMask(Bit(Bit::_1)))) {
        _30.set(sead::BitFlag8::makeMask(Bit(Bit::_2)));
        rideable->_18.sub_7100E786F0(act::sUnk_7102603110);
    }
    if (_30.isOn(sead::BitFlag8::makeMask(Bit(Bit::_2)))) {
        if (!(_34.value <= sead::Mathf::epsilon())) {
            _34.update();
        } else if (_30.isOn(sead::BitFlag8::makeMask(Bit(Bit::_1)))) {
            setFinished();
        } else {
            setFailed();
        }
    } else if (!_30.isOn(sead::BitFlag8::makeMask(Bit(Bit::_0))) && as_list->x_4(0, 0)) {
        _30.set(sead::BitFlag8::makeMask(Bit(Bit::_2)));
        rideable->_18.sub_7100E786F0(act::sUnk_7102603110);
    }
    if (auto* controller = mActor->getCharacterController())
        act::sub_7100E7F698(rideable, as_list, controller);
    as_list->x_6(1, 0, 0.0f);
    as_list->x_6(2, 0, 0.0f);
    _30.reset(sead::BitFlag8::makeMask(Bit(Bit::_0)));
}

bool AnimalEatAction::m32() {
    return 1;
}

}  // namespace uking::action
