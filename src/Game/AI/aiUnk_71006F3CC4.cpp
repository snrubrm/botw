#include "Game/AI/aiUnk_71006F3CC4.h"
#include "KingSystem/ActorSystem/actAiActionBase.h"

Unk_7102450038::Unk_7102450038(ksys::act::ai::ActionBase* owner) : mOwner(owner) {}

Unk_7102450038::~Unk_7102450038() {}

void Unk_7102450038::sub_71006F3DE8() {
    _18 = 0;
    _1c = -100.0f;
}

void Unk_7102450038::sub_71006F3DF4() {}

void Unk_7102450038::sub_71006F3DF8() {
    mOwner->getStaticParam(&_8, "FlyHeightMin");
}
