#include "Game/AI/Action/actionHorseKickBackAction.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

HorseKickBackAction::HorseKickBackAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HorseKickBackAction::~HorseKickBackAction() = default;

bool HorseKickBackAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HorseKickBackAction::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* rideable = mActor->m132();
    if (!rideable) {
        setFailed();
        return;
    }
    mActor->getASList()->x_6(1, 0, 0.0f);
    mActor->getASList()->x_6(2, 0, 1.0f);
    _38 |= 1 << int(Bit(Bit::_0));
    const sead::SafeString& name = mASName_s;
    const bool succeeded = rideable->_18.sub_7100E76E74(name, false);
    const int mask = 1 << int(Bit(Bit::_1));
    if (succeeded)
        _38 |= mask;
    else
        _38 &= ~mask;
}

void HorseKickBackAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void HorseKickBackAction::loadParams_() {
    getStaticParam(&mSucceedGear_s, "SucceedGear");
    getStaticParam(&mASName_s, "ASName");
}

void HorseKickBackAction::calc_() {
    auto* as_list = mActor->getASList();
    auto* rideable = mActor->m132();
    if ((_38 & 3) != 3) {
        if (as_list->x_4(0, 0)) {
            if (rideable && *mSucceedGear_s >= 0) {
                rideable->sub_7100E63224(0, u32(*mSucceedGear_s));
                as_list->x_6(10, 0, f32(*mSucceedGear_s));
            }
            as_list->sub_710115B01C(0, 0, true);
            setFinished();
        }
    }
    if (as_list->x(0x47, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true))
        setFinished();
    if (auto* controller = mActor->getCharacterController())
        act::sub_7100E7F698(rideable, as_list, controller);
    _38 &= ~(1 << int(Bit(Bit::_0)));
}

}  // namespace uking::action
