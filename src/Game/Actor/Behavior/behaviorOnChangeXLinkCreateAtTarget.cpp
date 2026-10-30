#include "Game/Actor/Behavior/behaviorOnChangeXLinkCreateAtTarget.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "Game/gameMapStaticLoadMgr.h"
#include <resource/seadResource.h>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Byaml/Byaml.h"

namespace uking::behavior {

OnChangeXLinkCreateAtTarget::OnChangeXLinkCreateAtTarget(const InitArg& arg)
    : OnChangeXLinkCreate(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
OnChangeXLinkCreateAtTarget::~OnChangeXLinkCreateAtTarget() {
    ;
}

bool OnChangeXLinkCreateAtTarget::init_(sead::Heap* heap) {
    if (!OnChangeXLinkCreate::init_(heap))
        return false;
    sub_7100630570();
    return true;
}

void OnChangeXLinkCreateAtTarget::calc() {
    OnChangeXLinkCreate::calc();
}

void OnChangeXLinkCreateAtTarget::enter() {
    OnChangeXLinkCreate::enter();
}

void OnChangeXLinkCreateAtTarget::leave() {
    OnChangeXLinkCreate::leave();
}

void OnChangeXLinkCreateAtTarget::m14() {
    Unk_71012419b4 handle{};
    xlinkSearchAndEmit(mActor, mKey_s.cstr(), 2, &handle);
    handle.sub_7101241A44(sead::Matrix34f::ident);
    handle.sub_71012419B4(_50);
}

// NON_MATCHING: the final vector copy uses three component stores instead of a paired store.
bool OnChangeXLinkCreateAtTarget::sub_7100630570() {
    auto* handle = getMapStaticMubin("MainField");
    if (!handle || !handle->requestedLoad() || !handle->isSuccess())
        return false;
    auto* resource = sead::DynamicCast<sead::DirectResource>(handle->getResource());
    if (!resource)
        return false;
    al::ByamlIter root(resource->getRawData());
    if (!root.isValid())
        return false;
    al::ByamlIter markers;
    root.tryGetIterByKey(&markers, "TargetPosMarker");
    if (!markers.isValid())
        return false;
    const s32 count = markers.getSize();
    al::ByamlIter marker;
    const char* name = nullptr;
    sead::Vector3f translate = sead::Vector3f::zero;
    const sead::SafeString target("VolcanoEruptionField");
    for (s32 i = 0; i < count; ++i) {
        markers.tryGetIterByIndex(&marker, i);
        if (!marker.isValid() || !marker.tryGetStringByKey(&name, "UniqueName"))
            continue;
        if (target == sead::SafeString(name) && al::tryGetByamlV3f(&translate, marker, "Translate")) {
            _50 = translate;
            return true;
        }
    }
    return false;
}

void OnChangeXLinkCreateAtTarget::loadParams() {
    OnChangeXLinkCreate::loadParams();
    getStaticParam(&mTargetUniqueName_s, "TargetUniqueName");
}

}  // namespace uking::behavior
