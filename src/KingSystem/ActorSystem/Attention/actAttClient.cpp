#include "KingSystem/ActorSystem/Attention/actAttClient.h"
#include <gfx/seadCamera.h>
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/Attention/actAttentionSingleton.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Resource/Actor/resResourceAttCheck.h"
#include "KingSystem/System/CameraMgr.h"

namespace ksys::act {

// NON_MATCHING: the order of the member stores and the register assignment of the delay computation differ
AttClient::AttClient() {
    if (auto* attention = Attention::instance()) {
        const f32 width = sead::Mathf::clampMin(attention->_d8c, 0.0f);
        const f32 center = attention->_d88;
        const f32 min = sead::Mathf::clampMin(center - width * 0.5f, 0.0f);
        const f32 max = sead::Mathf::clampMin(center + width * 0.5f, 0.0f);
        if (min == max)
            _20 = min;
        else
            _20 = sead::GlobalRandom::instance()->getF32Range(min, max);
    } else {
        _20 = 30.0f;
    }
}

AttClient::~AttClient() {
    _38.freeBuffer();
}

const sead::SafeString& AttClient::getName() const {
    return mClient->name.ref();
}

s32 AttClient::sub_7100D72534() const {
    return int(mClient->client->getAttType());
}

void AttClient::sub_7100D72320() {
    if (auto* attention = Attention::instance()) {
        attention->sub_7100D74D78(this);
        _61 = true;
    }
}

bool AttClient::sub_7100D72144() const {
    return mActor && mClient;
}

void AttClient::sub_7100D7235C(void* value) {
    _30 = value;
}

bool AttClient::sub_7100D72364() const {
    return _30 != nullptr;
}

void AttClient::sub_7100D723DC(s32 mode) {
    if (u32(mode) <= 2)
        mMode = mode;
}

u32 AttClient::sub_7100D724F4() const {
    return _58;
}

bool AttClient::sub_7100D7251C(u32 mask) const {
    return _58 & mask;
}

Actor* AttClient::getActor() const {
    return mActor;
}

u32 AttClient::sub_7100D72544() const {
    return int(mClient->client->getActionCode());
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
