#include "Game/Actor/Action/actionWarpPlayerToAnchorGimmickReset.h"
#include "Game/Scene/gameStageInfo.h"
#include "Game/gameResetter.h"
#include <resource/seadResource.h>
#include "Game/Scene/gameScene.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Byaml/Byaml.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/World/worldWeatherMgr.h"
#include "Game/Actor/Player/actPlayerBase.h"

// Declaration only (CSV getMapStaticMubin 0x7100e8dca8).
ksys::res::Handle* getMapStaticMubin(const sead::SafeString& name);

namespace uking::action {

WarpPlayerToAnchorGimmickReset::WarpPlayerToAnchorGimmickReset(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

WarpPlayerToAnchorGimmickReset::~WarpPlayerToAnchorGimmickReset() = default;

bool WarpPlayerToAnchorGimmickReset::init_(sead::Heap* heap) {
    ksys::act::acc::PlayerBase player;
    player.getPlayerFromPlayerInfo();
    if (player.hasProc())
        _48.set(player.getField418());
    else
        _48.set(1.0f, 1.0f, 1.0f);
    _54 = false;
    _58 = 0.0f;
    return true;
}

void WarpPlayerToAnchorGimmickReset::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!Resetter::instance()) {
        setFailed();
        return;
    }
    auto* handle = getMapStaticMubin(uking::StageInfo::getCurrentMapType());
    if (!handle || !handle->isSuccess()) {
        setFailed();
        return;
    }
    auto* resource = sead::DynamicCast<sead::DirectResource>(handle->getResource());
    if (!resource) {
        setFailed();
        return;
    }

    al::ByamlIter root(resource->getRawData());
    if (!root.isValid()) {
        setFailed();
        return;
    }
    al::ByamlIter objects;
    if (!root.tryGetIterByKey(&objects, mAnchorName_m.cstr())) {
        setFailed();
        return;
    }

    sead::Vector3f translate = sead::Vector3f::zero;
    sead::Vector3f rotate = sead::Vector3f::zero;
    const s32 count = objects.getSize();
    for (s32 i = 0; i <= count; ++i) {
        if (i == count) {
            setFailed();
            return;
        }
        al::ByamlIter object;
        if (!objects.tryGetIterByIndex(&object, i))
            continue;
        const char* name = nullptr;
        if (!(object.tryGetStringByKey(&name, "UniqueName") && sead::SafeString(name) == mAnchorUniqueName_m)) {
            if (!object.tryGetStringByKey(&name, "PosName") || !(sead::SafeString(name) == mAnchorUniqueName_m))
                continue;
        }
        if (!al::tryGetByamlV3f(&translate, object, "Translate")) {
            setFailed();
            return;
        }
        if (!al::tryGetByamlV3f(&rotate, object, "Rotate"))
            rotate = {0, 0, 0};
        break;
    }

    if (!Resetter::instance()->sub_71007D25A4(nullptr, ResetOption{1}, &translate, &rotate, &_48,
                                             sead::SafeString(""), false)) {
        setFailed();
        return;
    }
    auto* placement = ksys::map::PlacementMgr::instance();
    placement->_288 = 1;
    placement->_27c = translate;
}

void WarpPlayerToAnchorGimmickReset::leave_() {
    ksys::act::ai::Action::leave_();
}

void WarpPlayerToAnchorGimmickReset::loadParams_() {
    getStaticParam(&mWaitFrameAfterReset_s, "WaitFrameAfterReset");
    getMapUnitParam(&mAnchorName_m, "AnchorName");
    getMapUnitParam(&mAnchorUniqueName_m, "AnchorUniqueName");
}

void WarpPlayerToAnchorGimmickReset::calc_() {
    if (isFinished() || isFailed())
        return;
    const f32 time = _58;
    if (time > 0) {
        f32 current = time;
        if (time > *mWaitFrameAfterReset_s) {
            setFinished();
            current = _58;
        }
        _58 = current + 1.0f;
    } else if (_54) {
        if (ksys::world::Manager::instance()->getWeatherMgrUnchecked()->_24 >= 1.0f)
            _58 = time + 1.0f;
    } else {
        auto* resetter = Resetter::instance();
        if (!resetter) {
            setFailed();
            return;
        }
        if (resetter->finishedReset())
            _54 = true;
    }
}

}  // namespace uking::action
