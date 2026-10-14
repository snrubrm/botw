#include "Game/Actor/AI/aiWarpActivateTerminal.h"
#include <cmath>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"
#include "KingSystem/System/StageInfo.h"
#include "Game/UI/uiUtils.h"

namespace uking::ai {

WarpActivateTerminal::WarpActivateTerminal(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WarpActivateTerminal::~WarpActivateTerminal() = default;

bool WarpActivateTerminal::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WarpActivateTerminal::enter_(ksys::act::ai::InlineParamPack* params) {
    if (mActor->isWaitRevivalForUsed()) {
        ksys::act::disableAllAttClients(mActor);
        _68.x();
        changeChild("起動後待機");
    } else {
        _68.x();
        changeChild("待機");
    }
    _a8 = false;
}

// NON_MATCHING: the original copies the home position into the info as 8 + 4 bytes (a memcpy-style copy) and
// schedules the stores differently
void WarpActivateTerminal::calc_() {
    auto* actor = mActor;
    auto* child = getCurrentChild();

    {
        TerminalInfo info;
        const sead::Vector3f home_mtx_pos = actor->getHomeMtxRaw().getTranslation();
        sead::Vector3f home_pos;
        actor->getHomePos(&home_pos);
        info.type = *mRemainsTerminalType_m;
        info.home_pos = home_pos;
        info.home_mtx_pos = home_mtx_pos;
        info.is_used = actor->isWaitRevivalForUsed();
        info.actor = actor;
        ui::sub_7100A9D0D4(&info);
    }

    if (!child->isChangeable() && !child->isFinished() && !child->isFailed())
        return;

    if (isCurrentChild("待機")) {
        bool out_of_range = false;
        if (*mIsCheckLimit_s) {
            const sead::Vector3f up = sead::Vector3f::ey;
            sead::Matrix34f home;
            mActor->getHomeMtx(&home);
            const f32 angle =
                std::acos(up.x * home(0, 1) + up.y * home(1, 1) + up.z * home(2, 1));
            out_of_range = angle >= *mDoLimitAngle_s;
        }
        if (out_of_range)
            ksys::act::disableAllAttClients(actor);
        else
            ksys::act::enableAllAttClients(actor);

        if (_68._30 || _a8) {
            _a8 = false;
            ksys::act::disableAllAttClients(mActor);
            _68.x();
            changeChild("起動");
            return;
        }
    }

    if (isCurrentChild("起動")) {
        const bool can_reboot = *mIsAbleToReboot_s;
        const bool used = actor->isWaitRevivalForUsed();
        if (can_reboot) {
            if (!used) {
                ksys::act::enableAllAttClients(mActor);
                _68.x();
                changeChild("再起動準備");
                return;
            }
            ksys::act::disableAllAttClients(mActor);
            _68.x();
            changeChild("起動後待機");
            return;
        }
        if (used) {
            ksys::act::disableAllAttClients(mActor);
            _68.x();
            changeChild("起動後待機");
            return;
        }
    }

    if (isCurrentChild("再起動準備")) {
        _68.x();
        changeChild("待機");
    }
}

void WarpActivateTerminal::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WarpActivateTerminal::loadParams_() {
    getStaticParam(&mDoLimitAngle_s, "DoLimitAngle");
    getStaticParam(&mIsAbleToReboot_s, "IsAbleToReboot");
    getStaticParam(&mIsCheckLimit_s, "IsCheckLimit");
    getStaticParam(&mIsRejectMsgForRemains_s, "IsRejectMsgForRemains");
    getMapUnitParam(&mRemainsTerminalType_m, "RemainsTerminalType");
    getMapUnitParam(&mRemainsTerminalIndex_m, "RemainsTerminalIndex");
}

bool WarpActivateTerminal::sub_71005EABF4() {
    if (!*mIsRejectMsgForRemains_s)
        return false;
    auto* actor = mActor;
    if (!actor->hasForbidAttentionLink_0())
        return false;
    if (actor->checkForbidAttentionSignal())
        return true;
    if (!ksys::StageInfo::sIsRemainsElectric) {
        if (ksys::gdt::getBoolByKey("RemainsElectric_Drum2Rotate0", false))
            return true;
    } else if (!ksys::StageInfo::sIsRemainsFire) {
        if (ksys::gdt::getBoolByKey("RemainsFire_Rotate0", false))
            return true;
    } else if (!ksys::StageInfo::sIsRemainsWind) {
        if (ksys::gdt::getBoolByKey("RemainsWind_RotHorizontal", false))
            return true;
    }
    return false;
}

// NON_MATCHING: the original turns the listener result into a branch (tbz/orr/mov) instead of `and #1`
bool WarpActivateTerminal::handleMessage_(const ksys::Message* message) {
    if (*mIsRejectMsgForRemains_s && sub_71005EABF4())
        return true;

    if (*mIsCheckLimit_s) {
        const sead::Vector3f up = sead::Vector3f::ey;
        sead::Matrix34f mtx;
        mActor->getHomeMtx(&mtx);
        sead::Vector3f actor_up;
        mtx.getBase(actor_up, 1);
        if (std::acos(up.dot(actor_up)) >= *mDoLimitAngle_s)
            return false;
    }

    return _68.sub_710070A674(*message);
}

}  // namespace uking::ai
