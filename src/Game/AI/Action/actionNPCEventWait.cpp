#include "Game/AI/Action/actionNPCEventWait.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

// 0x7100712ad8 (declared only; unnamed free function, 472 B): bool test on the actor used by NPCEventWait::calc_.
bool sub_7100712AD8(ksys::act::Actor* actor);

namespace uking::action {

NPCEventWait::NPCEventWait(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCEventWait::~NPCEventWait() = default;

bool NPCEventWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCEventWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCEventWait::leave_() {
    resetRootAiFlag(ksys::act::ai::RootAiFlag::_5);
    mActor->getASList()->goLimpFromHeadShotMaybe(0x37, _20, 1);
}

void NPCEventWait::loadParams_() {}

void NPCEventWait::calc_() {
    bool play;
    if (mActor->getASList()->x_1(0, 0) == "Move_End") {
        play = mActor->getASList()->x_4(0, 0);
    } else {
        play = sub_7100712AD8(mActor) &&
               !mActor->getASList()->x(0x16, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true);
    }
    if (play)
        playAS("Wait", false, 0, 0, -1.0f);
    if (auto* controller = mActor->getCharacterController())
        act::sub_7100E7F318(mActor->getASList(), controller, 1.0f);
    if (_1c >= 3.0f && !ksys::evt::Manager::instance()->_1d2b8)
        setFailed();
    _1c += 1.0f;
}

}  // namespace uking::action
