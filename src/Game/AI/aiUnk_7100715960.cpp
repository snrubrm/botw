#include "Game/AI/aiUnk_7100715960.h"
#include "KingSystem/ActorSystem/actActor.h"

Unk_7100715960::Unk_7100715960(ksys::act::Actor* actor) : mActor(actor) {}

Unk_7100715960::~Unk_7100715960() = default;

void Unk_7100715960::sub_7100715B3C() {
    mActor->sub_71011DA868(&_40);
}

void Unk_7100715960::sub_7100715A20(sead::Vector3f* target, const sead::SafeString& bone_name) {
    _40.setName(bone_name);
    _40._68.makeRT(sead::Vector3f::zero, sead::Vector3f::zero);
    mActor->boneHandleStuff(&_40, false);
}
