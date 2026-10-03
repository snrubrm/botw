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
    if (*mIsDirectTime_m) {
        if (*mStartTime_m == *mEndTime_m)
            mActor->getMapObjIter().tryGetParamStringByKey(&id, "Id");
        if (*mIsMorningA_m | *mIsMorningB_m | *mIsNoonA_m | *mIsNoonB_m | *mIsEveningA_m |
            *mIsEveningB_m | *mIsNightA_m | *mIsNightB_m) {
            mActor->getMapObjIter().tryGetParamStringByKey(&id, "Id");
        }
    } else {
        if (*mStartTime_m != *mEndTime_m)
            mActor->getMapObjIter().tryGetParamStringByKey(&id, "Id");
        if (!(*mIsMorningA_m | *mIsMorningB_m | *mIsNoonA_m | *mIsNoonB_m | *mIsEveningA_m |
              *mIsEveningB_m | *mIsNightA_m | *mIsNightB_m)) {
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

    if (*mIsDirectTime_m) {
        const int start = *mStartTime_m;
        const int end = *mEndTime_m;
        const int hour = tm->getHour();
        if (start < end) {
            if (hour < start || hour > end)
                return false;
        } else if (hour > end && hour < start) {
            return false;
        }

        const int minute = tm->getMinute();
        const int end_minute = *mEndTimeMinute_m;
        int ok = true;
        if (hour == start)
            ok = minute >= *mStartTimeMinute_m;
        if (end == hour)
            ok = minute < end_minute;
        return ok;
    }

    bool ret = false;
    if (*mIsMorningA_m)
        ret |= tm->getTimeDivision() == ksys::world::TimeDivision::Morning_A;
    if (*mIsMorningB_m)
        ret |= tm->getTimeDivision() == ksys::world::TimeDivision::Morning_B;
    if (*mIsNoonA_m)
        ret |= tm->getTimeDivision() == ksys::world::TimeDivision::Noon_A;
    if (*mIsNoonB_m)
        ret |= tm->getTimeDivision() == ksys::world::TimeDivision::Noon_B;
    if (*mIsEveningA_m)
        ret |= tm->getTimeDivision() == ksys::world::TimeDivision::Evening_A;
    if (*mIsEveningB_m)
        ret |= tm->getTimeDivision() == ksys::world::TimeDivision::Evening_B;
    if (*mIsNightA_m)
        ret |= tm->getTimeDivision() == ksys::world::TimeDivision::Night_A;
    if (*mIsNightB_m)
        ret |= tm->getTimeDivision() == ksys::world::TimeDivision::Night_B;
    return ret;
}

void TimeControlTagRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TimeControlTagRoot::loadParams_() {
    getMapUnitParam(&mStartTime_m, "StartTime");
    getMapUnitParam(&mEndTime_m, "EndTime");
    getMapUnitParam(&mStartTimeMinute_m, "StartTimeMinute");
    getMapUnitParam(&mEndTimeMinute_m, "EndTimeMinute");
    getMapUnitParam(&mIsDirectTime_m, "IsDirectTime");
    getMapUnitParam(&mIsMorningA_m, "IsMorningA");
    getMapUnitParam(&mIsMorningB_m, "IsMorningB");
    getMapUnitParam(&mIsNoonA_m, "IsNoonA");
    getMapUnitParam(&mIsNoonB_m, "IsNoonB");
    getMapUnitParam(&mIsEveningA_m, "IsEveningA");
    getMapUnitParam(&mIsEveningB_m, "IsEveningB");
    getMapUnitParam(&mIsNightA_m, "IsNightA");
    getMapUnitParam(&mIsNightB_m, "IsNightB");
}

}  // namespace uking::ai
