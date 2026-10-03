#include "Game/AI/AI/aiTimeControlTagRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/World/worldManager.h"

namespace uking::ai {

TimeControlTagRoot::TimeControlTagRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TimeControlTagRoot::~TimeControlTagRoot() = default;

bool TimeControlTagRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the original converts the OR of the first seven time-division flags to bool
// before OR-ing IsNightB (tst/cset); ours ORs all eight then masks
void TimeControlTagRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    const char* id;
    if (*mParams.mIsDirectTime_m) {
        if (*mParams.mStartTime_m == *mParams.mEndTime_m)
            mActor->getMapObjIter().tryGetParamStringByKey(&id, "Id");
        if (*mParams.mIsMorningA_m | *mParams.mIsMorningB_m | *mParams.mIsNoonA_m | *mParams.mIsNoonB_m | *mParams.mIsEveningA_m |
            *mParams.mIsEveningB_m | *mParams.mIsNightA_m | *mParams.mIsNightB_m) {
            mActor->getMapObjIter().tryGetParamStringByKey(&id, "Id");
        }
    } else {
        if (*mParams.mStartTime_m != *mParams.mEndTime_m)
            mActor->getMapObjIter().tryGetParamStringByKey(&id, "Id");
        if (!(*mParams.mIsMorningA_m | *mParams.mIsMorningB_m | *mParams.mIsNoonA_m | *mParams.mIsNoonB_m | *mParams.mIsEveningA_m |
              *mParams.mIsEveningB_m | *mParams.mIsNightA_m | *mParams.mIsNightB_m)) {
            mActor->getMapObjIter().tryGetParamStringByKey(&id, "Id");
        }
    }

    if (sub_71005C9290())
        changeChild("On");
    else
        changeChild("Off");
}

void TimeControlTagRoot::calc_() {
    mActor->m107();
    if (sub_71005C9290()) {
        if (isCurrentChild("Off"))
            changeChild("On");
    } else {
        if (isCurrentChild("On"))
            changeChild("Off");
    }
}

bool TimeControlTagRoot::sub_71005C9290() {
    auto* tm = ksys::world::Manager::instance()->getTimeMgr();

    if (*mParams.mIsDirectTime_m) {
        const int start = *mParams.mStartTime_m;
        const int end = *mParams.mEndTime_m;
        const int hour = tm->getHour();
        if (start < end) {
            if (hour < start || hour > end)
                return false;
        } else if (hour > end && hour < start) {
            return false;
        }

        const int minute = tm->getMinute();
        const int end_minute = *mParams.mEndTimeMinute_m;
        int ok = true;
        if (hour == start)
            ok = minute >= *mParams.mStartTimeMinute_m;
        if (end == hour)
            ok = minute < end_minute;
        return ok;
    }

    bool ret = false;
    if (*mParams.mIsMorningA_m)
        ret |= tm->getTimeDivision() == ksys::world::TimeDivision::Morning_A;
    if (*mParams.mIsMorningB_m)
        ret |= tm->getTimeDivision() == ksys::world::TimeDivision::Morning_B;
    if (*mParams.mIsNoonA_m)
        ret |= tm->getTimeDivision() == ksys::world::TimeDivision::Noon_A;
    if (*mParams.mIsNoonB_m)
        ret |= tm->getTimeDivision() == ksys::world::TimeDivision::Noon_B;
    if (*mParams.mIsEveningA_m)
        ret |= tm->getTimeDivision() == ksys::world::TimeDivision::Evening_A;
    if (*mParams.mIsEveningB_m)
        ret |= tm->getTimeDivision() == ksys::world::TimeDivision::Evening_B;
    if (*mParams.mIsNightA_m)
        ret |= tm->getTimeDivision() == ksys::world::TimeDivision::Night_A;
    if (*mParams.mIsNightB_m)
        ret |= tm->getTimeDivision() == ksys::world::TimeDivision::Night_B;
    return ret;
}

void TimeControlTagRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TimeControlTagRoot::loadParams_() {
    getMapUnitParam(&mParams.mStartTime_m, "StartTime");
    getMapUnitParam(&mParams.mEndTime_m, "EndTime");
    getMapUnitParam(&mParams.mStartTimeMinute_m, "StartTimeMinute");
    getMapUnitParam(&mParams.mEndTimeMinute_m, "EndTimeMinute");
    getMapUnitParam(&mParams.mIsDirectTime_m, "IsDirectTime");
    getMapUnitParam(&mParams.mIsMorningA_m, "IsMorningA");
    getMapUnitParam(&mParams.mIsMorningB_m, "IsMorningB");
    getMapUnitParam(&mParams.mIsNoonA_m, "IsNoonA");
    getMapUnitParam(&mParams.mIsNoonB_m, "IsNoonB");
    getMapUnitParam(&mParams.mIsEveningA_m, "IsEveningA");
    getMapUnitParam(&mParams.mIsEveningB_m, "IsEveningB");
    getMapUnitParam(&mParams.mIsNightA_m, "IsNightA");
    getMapUnitParam(&mParams.mIsNightB_m, "IsNightB");
}

}  // namespace uking::ai
