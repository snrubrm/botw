#include "Game/Actor/Action/actionAdvanceTime.h"
#include "Game/gameResetter.h"
#include "KingSystem/Sound/sndBgmMgr.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/World/worldTimeMgr.h"

namespace uking::action {

AdvanceTime::AdvanceTime(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AdvanceTime::~AdvanceTime() = default;

bool AdvanceTime::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the original re-reads DestTime after setting a direct time and shares the final failure checks;
// branch layout differs.
void AdvanceTime::enter_(ksys::act::ai::InlineParamPack* params) {
    _40 = false;
    auto* wm = ksys::world::Manager::instance();
    ksys::world::TimeMgr* time_mgr;
    if (!wm || !(time_mgr = wm->getTimeMgr())) {
        setFailed();
        return;
    }

    ksys::snd::sub_7100FFEE10();

    if (*mDestTime_d == -1) {
        if (*mDirectTime_d != -1) {
            time_mgr->setTime(*mDirectTime_d * 15.0f);
            if (*mDestTime_d != -1 || *mPassTime_d != -1)
                setFailed();
            return;
        }
    } else {
        f32 time;
        switch (*mDestTime_d) {
        case 0:
            time = 75.0f;
            break;
        case 1:
            time = 180.0f;
            break;
        case 2:
            time = 315.0f;
            break;
        case 3:
            time = 90.0f;
            break;
        case 4:
            time = 240.0f;
            break;
        case 5:
            time = 300.0f;
            break;
        case 6:
            time = 45.0f;
            break;
        case 7:
            time = 60.0f;
            break;
        case 8:
            time = 105.0f;
            break;
        case 9:
            time = 150.0f;
            break;
        case 10:
            time = 195.0f;
            break;
        case 11:
            time = 255.0f;
            break;
        case 12:
            time = 285.0f;
            break;
        case 13:
            time = 315.0f;
            break;
        case 14:
            time = 360.0f;
            break;
        default:
            setFailed();
            return;
        }
        time_mgr->setTime(time);
        if (*mDirectTime_d != -1 || *mPassTime_d != -1) {
            setFailed();
            return;
        }
    }

    if (*mPassTime_d == -1)
        return;

    f32 new_time = *mPassTime_d * 15.0f + time_mgr->getTime();
    if (new_time >= 360.0f)
        new_time += -360.0f;
    time_mgr->setTime(new_time);
    if (*mDestTime_d != -1 || *mDirectTime_d != -1)
        setFailed();
}

void AdvanceTime::leave_() {
    ksys::act::ai::Action::leave_();
}

void AdvanceTime::loadParams_() {
    getDynamicParam(&mDestTime_d, "DestTime");
    getDynamicParam(&mDirectTime_d, "DirectTime");
    getDynamicParam(&mPassTime_d, "PassTime");
    getDynamicParam(&mActReset_d, "ActReset");
}

void AdvanceTime::calc_() {
    if (isFinished() || isFailed())
        return;

    if (*mActReset_d) {
        auto* resetter = Resetter::instance();
        if (_40) {
            if (!resetter->finishedReset())
                return;
        } else {
            if (resetter->startReset(ResetType{1}, ResetOption{0}, sead::SafeString::cEmptyString, false, false))
                _40 = true;
            return;
        }
    }
    setFinished();
}

}  // namespace uking::action
