#include "KingSystem/Resource/GeneralParamList/resGParamListObjectTraveler.h"
#include "KingSystem/Utils/FixedString.h"

namespace ksys::res {

template <std::size_t N, std::size_t I = 0>
KSYS_ALWAYS_INLINE static void
initGParamListTravelerRoutePoints(GParamListObjectTraveler::RoutePoint* point,
                                  agl::utl::ParameterObj* obj) {
    if constexpr (I < N) {
        point->initParameters_<I>(obj);
        initGParamListTravelerRoutePoints<N, I + 1>(point + 1, obj);
    }
}

GParamListObjectTraveler::GParamListObjectTraveler() {
    auto* const obj = &mObj;

    mAppearGameDataName.init("", "AppearGameDataName", "", obj);
    mDeleteGameDataName.init("", "DeleteGameDataName", "", obj);
    mRouteType.init("", "RouteType", "", obj);
    mRideHorseName.init("", "RideHorseName", "", obj);
    mIsLeadHorse.init(false, "IsLeadHorse", "", obj);
    mHorseGearLevel.init(-1, "HorseGearLevel", "", obj);

    initGParamListTravelerRoutePoints<NumRoutePoints>(mRoutePoints.data(), obj);
    mRoutePoint29Name.init("", "RoutePoint29Name", "", obj);
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint0ForwardEntryPoint() const {
    return mRoutePoints[0].mForward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint1ForwardEntryPoint() const {
    return mRoutePoints[1].mForward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint2ForwardEntryPoint() const {
    return mRoutePoints[2].mForward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint3ForwardEntryPoint() const {
    return mRoutePoints[3].mForward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint4ForwardEntryPoint() const {
    return mRoutePoints[4].mForward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint5ForwardEntryPoint() const {
    return mRoutePoints[5].mForward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint6ForwardEntryPoint() const {
    return mRoutePoints[6].mForward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint7ForwardEntryPoint() const {
    return mRoutePoints[7].mForward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint8ForwardEntryPoint() const {
    return mRoutePoints[8].mForward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint9ForwardEntryPoint() const {
    return mRoutePoints[9].mForward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint10ForwardEntryPoint() const {
    return mRoutePoints[10].mForward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint11ForwardEntryPoint() const {
    return mRoutePoints[11].mForward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint12ForwardEntryPoint() const {
    return mRoutePoints[12].mForward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint13ForwardEntryPoint() const {
    return mRoutePoints[13].mForward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint14ForwardEntryPoint() const {
    return mRoutePoints[14].mForward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint15ForwardEntryPoint() const {
    return mRoutePoints[15].mForward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint16ForwardEntryPoint() const {
    return mRoutePoints[16].mForward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint17ForwardEntryPoint() const {
    return mRoutePoints[17].mForward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint18ForwardEntryPoint() const {
    return mRoutePoints[18].mForward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint19ForwardEntryPoint() const {
    return mRoutePoints[19].mForward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint20ForwardEntryPoint() const {
    return mRoutePoints[20].mForward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint21ForwardEntryPoint() const {
    return mRoutePoints[21].mForward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint22ForwardEntryPoint() const {
    return mRoutePoints[22].mForward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint23ForwardEntryPoint() const {
    return mRoutePoints[23].mForward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint24ForwardEntryPoint() const {
    return mRoutePoints[24].mForward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint25ForwardEntryPoint() const {
    return mRoutePoints[25].mForward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint26ForwardEntryPoint() const {
    return mRoutePoints[26].mForward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint27ForwardEntryPoint() const {
    return mRoutePoints[27].mForward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint28ForwardEntryPoint() const {
    return mRoutePoints[28].mForward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint0BackwardEntryPoint() const {
    return mRoutePoints[0].mBackward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint1BackwardEntryPoint() const {
    return mRoutePoints[1].mBackward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint2BackwardEntryPoint() const {
    return mRoutePoints[2].mBackward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint3BackwardEntryPoint() const {
    return mRoutePoints[3].mBackward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint4BackwardEntryPoint() const {
    return mRoutePoints[4].mBackward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint5BackwardEntryPoint() const {
    return mRoutePoints[5].mBackward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint6BackwardEntryPoint() const {
    return mRoutePoints[6].mBackward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint7BackwardEntryPoint() const {
    return mRoutePoints[7].mBackward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint8BackwardEntryPoint() const {
    return mRoutePoints[8].mBackward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint9BackwardEntryPoint() const {
    return mRoutePoints[9].mBackward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint10BackwardEntryPoint() const {
    return mRoutePoints[10].mBackward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint11BackwardEntryPoint() const {
    return mRoutePoints[11].mBackward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint12BackwardEntryPoint() const {
    return mRoutePoints[12].mBackward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint13BackwardEntryPoint() const {
    return mRoutePoints[13].mBackward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint14BackwardEntryPoint() const {
    return mRoutePoints[14].mBackward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint15BackwardEntryPoint() const {
    return mRoutePoints[15].mBackward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint16BackwardEntryPoint() const {
    return mRoutePoints[16].mBackward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint17BackwardEntryPoint() const {
    return mRoutePoints[17].mBackward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint18BackwardEntryPoint() const {
    return mRoutePoints[18].mBackward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint19BackwardEntryPoint() const {
    return mRoutePoints[19].mBackward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint20BackwardEntryPoint() const {
    return mRoutePoints[20].mBackward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint21BackwardEntryPoint() const {
    return mRoutePoints[21].mBackward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint22BackwardEntryPoint() const {
    return mRoutePoints[22].mBackward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint23BackwardEntryPoint() const {
    return mRoutePoints[23].mBackward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint24BackwardEntryPoint() const {
    return mRoutePoints[24].mBackward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint25BackwardEntryPoint() const {
    return mRoutePoints[25].mBackward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint26BackwardEntryPoint() const {
    return mRoutePoints[26].mBackward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint27BackwardEntryPoint() const {
    return mRoutePoints[27].mBackward.mEntryPoint.ref();
}

const sead::SafeString& GParamListObjectTraveler::getRoutePoint28BackwardEntryPoint() const {
    return mRoutePoints[28].mBackward.mEntryPoint.ref();
}

KSYS_ALWAYS_INLINE GParamListObjectTraveler::RoutePoints::RoutePoints() {
    // Nintendo seems to have duplicated the definitions for each of the 29 route points,
    // which is utterly disgusting and error prone. Manually writing out the loop and using
    // placement-new is necessary to prevent Clang from emitting a loop.
#pragma clang loop unroll(full)
    for (auto& storage : mStorage)
        new (&storage) RoutePoint;
}

KSYS_ALWAYS_INLINE GParamListObjectTraveler::RoutePoint::RoutePoint() = default;

template <s32 I>
KSYS_ALWAYS_INLINE void
GParamListObjectTraveler::RoutePoint::initParameters_(agl::utl::ParameterObj* obj) {
    mName.init("", KSYS_STR(Str("RoutePoint") + Str<I>() + Str("Name")), "", obj);
    mForward.initParameters_<I, I + 1>(obj);
    mBackward.initParameters_<I + 1, I>(obj);
}

template <s32 From, s32 To>
KSYS_ALWAYS_INLINE void
GParamListObjectTraveler::RoutePoint::DirectionInfo::initParameters_(agl::utl::ParameterObj* obj) {
    static constexpr auto prefix = [] {
        using ksys::util::Str;
        return Str("RoutePoint") + Str<From>() + Str("to") + Str<To>();
    }();

    mEntryPoint.init("", KSYS_STR(prefix + Str("EntryPoint")), "", obj);
    mWaitFrame.init(0.0, KSYS_STR(prefix + Str("WaitFrame")), "", obj);
    mSchedule.init("", KSYS_STR(prefix + Str("Schedule")), "", obj);
    mMoveAS.init("", KSYS_STR(prefix + Str("MoveAS")), "", obj);
    mWaitAS.init("", KSYS_STR(prefix + Str("WaitAS")), "", obj);
}

}  // namespace ksys::res
