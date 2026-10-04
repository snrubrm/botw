#include "KingSystem/ActorSystem/Attention/actAttClient.h"
#include <gfx/seadCamera.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Resource/Actor/resResourceAttCheck.h"
#include "KingSystem/System/CameraMgr.h"

namespace ksys::act {

const sead::SafeString& AttClient::getName() const {
    return mClient->name.ref();
}

s32 AttClient::sub_7100D72534() const {
    return int(mClient->client->getAttType());
}

void AttClient::sub_7100D724FC(u32 flags) {
    _54 |= flags;
}

void AttClient::sub_7100D7250C(u32 flags) {
    _54 &= ~flags;
}

void AttClient::resetEnabled() {
    if (mClient)
        mEnabled = mClient->is_valid.ref();
}

void AttClient::enable() {
    mEnabled = true;
}

void AttClient::disable() {
    mEnabled = false;
}

void AttClient::setEnabled(bool enabled) {
    mEnabled = enabled;
}

bool AttClient::isEnabled() const {
    switch (mMode) {
    case 1:
        return true;
    case 0:
        return mEnabled;
    default:
        return false;
    }
}

void AttClient::setCallback(void* callback) {
    mCallback = callback;
}

bool AttClient::sub_7100D72554(BaseProc* proc, const res::AttCheck_Unk1* arg, bool a3) const {
    switch (mClient->client->getAttType()) {
    case AttType::NameBalloon:
        return false;
    case AttType::Appeal: {
        auto* mgr = CameraMgr::instance();
        if (!mgr)
            return false;
        const auto* camera = mgr->getLookAtCamera();
        if (!camera || !mActor)
            return false;
        const sead::Vector3f diff = camera->getPos() - mActor->getMtx().getTranslation();
        return diff.squaredLength() < 900.0f;
    }
    default: {
        ActorConstDataAccess accessor{proc};
        return mClient->client->check(mActor, accessor, _38, _48, arg, a3, false) == -1;
    }
    }
}

}  // namespace ksys::act
