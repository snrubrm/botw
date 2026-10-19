#include "Game/Actor/Action/actionWarpToStaticAnchor.h"
#include "Game/Scene/gameStageInfo.h"
#include <math/seadMathCalcCommon.h>
#include <resource/seadResource.h>
#include "Game/Scene/gameScene.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Byaml/Byaml.h"

// Declaration only (CSV getMapStaticMubin 0x7100e8dca8).
ksys::res::Handle* getMapStaticMubin(const sead::SafeString& name);

namespace uking::action {

WarpToStaticAnchor::WarpToStaticAnchor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WarpToStaticAnchor::~WarpToStaticAnchor() = default;

bool WarpToStaticAnchor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool WarpToStaticAnchor::oneShot_() {
    auto* handle = getMapStaticMubin(uking::StageInfo::getCurrentMapType());
    if (!handle || !handle->isSuccess())
        return false;
    auto* resource = sead::DynamicCast<sead::DirectResource>(handle->getResource());
    if (!resource)
        return false;
    al::ByamlIter root(resource->getRawData());
    if (!root.isValid())
        return false;
    al::ByamlIter objects;
    if (!root.tryGetIterByKey(&objects, mAnchorName_d.cstr()))
        return false;

    const s32 count = objects.getSize();
    for (s32 i = 0; i < count; ++i) {
        al::ByamlIter object;
        if (!objects.tryGetIterByIndex(&object, i))
            continue;
        const char* name = nullptr;
        if (!(object.tryGetStringByKey(&name, "UniqueName") && sead::SafeString(name) == mUniqueName_d)) {
            if (!object.tryGetStringByKey(&name, "PosName") ||
                !(sead::SafeString(name) == mUniqueName_d))
                continue;
        }
        sead::Vector3f translate;
        if (!al::tryGetByamlV3f(&translate, object, "Translate"))
            return false;
        sead::Vector3f rotate;
        if (al::tryGetByamlV3f(&rotate, object, "Rotate"))
            rotate *= sead::Mathf::deg2rad(1);
        else
            rotate = {0, 0, 0};
        sead::Matrix34f mtx;
        mtx.makeRT(rotate, translate);
        mActor->setMtx(mtx, false, true);
        return true;
    }
    return false;
}

void WarpToStaticAnchor::loadParams_() {
    getDynamicParam(&mAnchorName_d, "AnchorName");
    getDynamicParam(&mUniqueName_d, "UniqueName");
}

}  // namespace uking::action
