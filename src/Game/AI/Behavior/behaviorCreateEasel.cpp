#include "Game/AI/Behavior/behaviorCreateEasel.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

CreateEasel::CreateEasel(const InitArg& arg) : Unk_7102435118(arg) {}

CreateEasel::~CreateEasel() = default;

bool CreateEasel::m6(sead::Heap* heap) {
    return Unk_7102435118::m6(heap);
}

void CreateEasel::m7() {
    Unk_7102435118::m7();
}

void CreateEasel::m8() {
    Unk_7102435118::m8();
}

void CreateEasel::m9() {
    Unk_7102435118::m9();
}

void CreateEasel::loadParams() {
    Unk_7102435118::loadParams();
}

bool CreateEasel::m15() {
    return mActor->getASList()->x(70, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true);
}

}  // namespace uking::behavior
