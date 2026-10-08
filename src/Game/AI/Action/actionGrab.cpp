#include "Game/AI/Action/actionGrab.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Attention/actAttClient.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Resource/Actor/resResourceAttCheck.h"

namespace uking::action {

Grab::Grab(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

bool Grab::init_(sead::Heap* heap) {
    return ActionWithPosAngReduce::init_(heap);
}

void Grab::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
    m32();
}

void Grab::leave_() {
    ActionWithPosAngReduce::leave_();
}

void Grab::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mGrabIdx_s, "GrabIdx");
    getStaticParam(&mCheckRadius_s, "CheckRadius");
    getStaticParam(&mCheckSpeed_s, "CheckSpeed");
    getStaticParam(&mAttOffset_s, "AttOffset");
}

void Grab::calc_() {
    ActionWithPosAngReduce::calc_();
    if (m33()) {
        auto* child = mActor->getConnectedCalcChild();
        if (auto* actor = sead::DynamicCast<ksys::act::Actor>(child)) {
            if (m34())
                sub_71005DC208(mActor, actor, *mGrabIdx_s);
            else
                mActor->resetConnectedCalcChild(false);
        } else {
            mActor->resetConnectedCalcChild(false);
        }
    }
    if (isFinishedAS(0, 0)) {
        if (!mActor->getConnectedCalcChild()) {
            setFailed();
        } else {
            auto* child = mActor->getConnectedCalcChild();
            if (auto* actor = sead::DynamicCast<ksys::act::Actor>(child))
                sub_71005DC41C(actor);
            setFinished();
        }
    }
}

void Grab::m32() {
    playAS("Grab", false, 0, 0, -1.0f);
}

bool Grab::m33() {
    return mActor->getASList()->x(0x45, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true);
}

// NON_MATCHING: scheduling only — ours emits the _34/_35 strh before the rotation dots
// and reloads mActor for the sub_71005DF024 call early; the original does both late
// (strh between the translation loads and the translation adds). All calls, branches,
// constants and the setRotated + translation-add structure match.
bool Grab::m34() {
    auto* child = mActor->getConnectedCalcChild();
    auto* actor = sead::DynamicCast<ksys::act::Actor>(child);
    if (!actor)
        return false;
    if (sub_71005DF024(*mCheckRadius_s * 3.0f, *mCheckSpeed_s, sead::Mathf::pi(), actor, mActor))
        return false;
    auto* client = ksys::act::sub_7100EE3E2C(actor, "Grab");
    const auto& mtx = mActor->getMtx();
    ksys::res::AttCheck_Unk1 check;
    check._0 = mtx;
    const auto& scale = mActor->getScale();
    sead::Vector3f offset = *mAttOffset_s;
    offset.x *= scale.x;
    offset.y *= scale.y;
    offset.z *= scale.z;
    sead::Vector3f pos;
    pos.setRotated(check._0, offset);
    check._34 = true;
    check._35 = true;
    pos += mtx.getTranslation();
    check._0.setTranslation(pos);
    check._30 = *mCheckRadius_s;
    if (!client)
        return false;
    return client->sub_7100D72554(mActor, &check, true);
}

}  // namespace uking::action
