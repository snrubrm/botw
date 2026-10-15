#include "Game/Actor/Behavior/behaviorOnTrgGuardOffTargetXLinkCreate.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::behavior {

OnTrgGuardOffTargetXLinkCreate::OnTrgGuardOffTargetXLinkCreate(const InitArg& arg)
    : OnTrgGuardOffTargetXLinkCreateBase(arg) {}

OnTrgGuardOffTargetXLinkCreate::~OnTrgGuardOffTargetXLinkCreate() = default;

bool OnTrgGuardOffTargetXLinkCreate::m6(sead::Heap* heap) {
    return OnTrgGuardOffTargetXLinkCreateBase::m6(heap);
}

void OnTrgGuardOffTargetXLinkCreate::m7() {
    OnTrgGuardOffTargetXLinkCreateBase::m7();
}

void OnTrgGuardOffTargetXLinkCreate::m8() {
    OnTrgGuardOffTargetXLinkCreateBase::m8();
}

void OnTrgGuardOffTargetXLinkCreate::m9() {
    OnTrgGuardOffTargetXLinkCreateBase::m9();
}

// NON_MATCHING: the three vector/matrix locals occupy different stack slots.
void OnTrgGuardOffTargetXLinkCreate::m14(Unk_71012419b4* handle) {
    sead::Vector3f position;
    mActor->getMtx().getTranslation(position);
    sead::Vector3f direction = sub_71005D9330(mActor);
    direction -= position;
    direction.y = 0.0f;
    direction.normalize();
    sead::Matrix34f matrix;
    ksys::util::sub_71011F00EC(&matrix, direction, sead::Vector3f::ey, position, false);
    handle->mELink.setMatrix(matrix);
}

void OnTrgGuardOffTargetXLinkCreate::loadParams() {
    OnTrgGuardOffTargetXLinkCreateBase::loadParams();
}

}  // namespace uking::behavior
