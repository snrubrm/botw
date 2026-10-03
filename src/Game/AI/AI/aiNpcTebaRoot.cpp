#include "Game/AI/AI/aiNpcTebaRoot.h"
#include "KingSystem/ActorSystem/Attention/actActorAttention.h"
#include "KingSystem/ActorSystem/Attention/actAttClient.h"
#include <prim/seadSafeString.h>
#include <random/seadGlobalRandom.h>
#include "Game/UI/uiUI.h"
#include "Game/gameFlagUtils.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

NpcTebaRoot::NpcTebaRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NpcTebaRoot::~NpcTebaRoot() = default;

bool NpcTebaRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

inline void NpcTebaRoot::showMsg(const sead::SafeString& name, s32 n) {
    sead::FixedSafeString<64> label;
    const u32 idx = n == 0 ? sead::GlobalRandom::instance()->getU32(5) : n - 1;
    label.format("%s_%02d", name.cstr(), idx);
    _70.sub_7100721B1C(5.0f, label);
}

void NpcTebaRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* client = mActor->getAttention()->getClientByName("Talk"))
        client->disable();
    if (auto* client = mActor->getAttention()->getClientByName("LockOn"))
        client->disable();
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5EDD8(1.0f);
        controller->sub_7100F5EDBC(mActor->getMtx().getBase(2));
    }
    mActor->emitBasicSigOff();
    _54 = ksys::Timer(90.0f, 90.0f);
    _60 = ksys::Timer(-1.0f, -1.0f, 0.0f);
    _70.sub_7100721830(mActor, true);
    _70._c8 = false;
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    _51 = (pos - getPlayerPosition()).length() < *mShowMessageDoDist_s;
    showMsg("GoBattle", 0);
    changeChild("飛行", nullptr);
}

void NpcTebaRoot::leave_() {
    if (auto* client = mActor->getAttention()->getClientByName("Ride"))
        client->disable();
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
    }
}

// NON_MATCHING: the original loads `_51` before the distance's sqrt NaN check (see lane1 log s22)
void NpcTebaRoot::calc_() {
    _54.update();
    const sead::Vector3f& player = getPlayerPosition();
    if (isCurrentChild("飛行")) {
        if (player.y > *mApproachPlayerHeight_s)
            changeChild("プレイヤーに接近", nullptr);
    } else if (isCurrentChild("プレイヤーに接近")) {
        if (_54.value <= sead::Mathf::epsilon()) {
            auto* client = mActor->getAttention()->getClientByName("Ride");
            if (client && !client->isEnabled())
                client->enable();
        }
        if (player.y < *mApproachPlayerHeight_s * 0.99f) {
            if (auto* client = mActor->getAttention()->getClientByName("Ride"))
                client->disable();
            changeChild("飛行", nullptr);
        }
    }

    const float dist = (mActor->getMtx().getTranslation() - player).length();
    bool entered_range = false;
    if (_51) {
        if (dist > *mShowMessageDoDist_s * 1.5f)
            _51 = false;
    } else if (dist < *mShowMessageDoDist_s) {
        _51 = true;
        entered_range = true;
    }

    _60.update();
    if (_50) {
        _50 = false;
        if (!ui::UI::instance()->sub_71010A5B0C(mActor) &&
            _60.value <= sead::Mathf::epsilon()) {
            _60 = ksys::Timer(f32(*mShowMessageLockonMinInterval_s), f32(*mShowMessageLockonMinInterval_s));
            showMsg("LockOn", 0);
        }
    } else {
        s32 value;
        if (getFlagInt(&value, "Wind_Relic_BreakBattery") && value <= 3) {
            showMsg("BreakBattery", value);
        } else if (entered_range && isCurrentChild("プレイヤーに接近")) {
            showMsg("Do", 0);
        }
    }
    _70.sub_7100721C48();
}

bool NpcTebaRoot::handleMessage_(const ksys::Message* message) {
    if (message && message->getType() == 0x800000e) {
        _50 = true;
        return true;
    }
    return false;
}

void NpcTebaRoot::loadParams_() {
    getStaticParam(&mShowMessageLockonMinInterval_s, "ShowMessageLockonMinInterval");
    getStaticParam(&mApproachPlayerHeight_s, "ApproachPlayerHeight");
    getStaticParam(&mShowMessageDoDist_s, "ShowMessageDoDist");
}

}  // namespace uking::ai
