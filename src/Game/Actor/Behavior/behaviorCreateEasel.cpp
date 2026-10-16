#include "Game/Actor/Behavior/behaviorCreateEasel.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

CreateEasel::CreateEasel(const InitArg& arg) : Unk_7102435118(arg) {}

CreateEasel::~CreateEasel() = default;

bool CreateEasel::init_(sead::Heap* heap) {
    return Unk_7102435118::init_(heap);
}

void CreateEasel::calc() {
    Unk_7102435118::calc();
}

void CreateEasel::enter() {
    Unk_7102435118::enter();
}

void CreateEasel::leave() {
    Unk_7102435118::leave();
}

void CreateEasel::loadParams() {
    Unk_7102435118::loadParams();
}

bool CreateEasel::m15() {
    return mActor->getASList()->x(70, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true);
}

}  // namespace uking::behavior
