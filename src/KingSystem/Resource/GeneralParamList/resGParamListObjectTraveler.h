#pragma once

#include <utility/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectTraveler : public GParamListObject {
public:
    struct RoutePoint {
        RoutePoint();

        template <s32 I>
        KSYS_VISIBILITY_HIDDEN void initParameters_(agl::utl::ParameterObj* obj);

        struct DirectionInfo {
            template <s32 From, s32 To>
            KSYS_VISIBILITY_HIDDEN void initParameters_(agl::utl::ParameterObj* obj);

            agl::utl::Parameter<sead::SafeString> mEntryPoint;
            agl::utl::Parameter<f32> mWaitFrame;
            agl::utl::Parameter<sead::SafeString> mSchedule;
            agl::utl::Parameter<sead::SafeString> mMoveAS;
            agl::utl::Parameter<sead::SafeString> mWaitAS;
        };

        agl::utl::Parameter<sead::SafeString> mName;
        // i to i+1
        DirectionInfo mForward;
        // i+1 to i
        DirectionInfo mBackward;
    };
    static constexpr size_t NumRoutePoints = 29;

    GParamListObjectTraveler();
    const char* getName() const override { return "Traveler"; }

    // 0x7100ef0314..0x7100ef0578 (placeholder names): the forward / backward entry-point string
    // of each route point. The Traveler rail code calls them through the member function pointer
    // tables at 0x71024f2290 / 0x71024f23c0. The getters return the SafeString inside the
    // Parameter, at mRoutePoints + 0x158 / 0x218 (+ i * 0x1a8); mRoutePoints itself is at 0x118.
    const sead::SafeString& getRoutePoint0ForwardEntryPoint() const;
    const sead::SafeString& getRoutePoint1ForwardEntryPoint() const;
    const sead::SafeString& getRoutePoint2ForwardEntryPoint() const;
    const sead::SafeString& getRoutePoint3ForwardEntryPoint() const;
    const sead::SafeString& getRoutePoint4ForwardEntryPoint() const;
    const sead::SafeString& getRoutePoint5ForwardEntryPoint() const;
    const sead::SafeString& getRoutePoint6ForwardEntryPoint() const;
    const sead::SafeString& getRoutePoint7ForwardEntryPoint() const;
    const sead::SafeString& getRoutePoint8ForwardEntryPoint() const;
    const sead::SafeString& getRoutePoint9ForwardEntryPoint() const;
    const sead::SafeString& getRoutePoint10ForwardEntryPoint() const;
    const sead::SafeString& getRoutePoint11ForwardEntryPoint() const;
    const sead::SafeString& getRoutePoint12ForwardEntryPoint() const;
    const sead::SafeString& getRoutePoint13ForwardEntryPoint() const;
    const sead::SafeString& getRoutePoint14ForwardEntryPoint() const;
    const sead::SafeString& getRoutePoint15ForwardEntryPoint() const;
    const sead::SafeString& getRoutePoint16ForwardEntryPoint() const;
    const sead::SafeString& getRoutePoint17ForwardEntryPoint() const;
    const sead::SafeString& getRoutePoint18ForwardEntryPoint() const;
    const sead::SafeString& getRoutePoint19ForwardEntryPoint() const;
    const sead::SafeString& getRoutePoint20ForwardEntryPoint() const;
    const sead::SafeString& getRoutePoint21ForwardEntryPoint() const;
    const sead::SafeString& getRoutePoint22ForwardEntryPoint() const;
    const sead::SafeString& getRoutePoint23ForwardEntryPoint() const;
    const sead::SafeString& getRoutePoint24ForwardEntryPoint() const;
    const sead::SafeString& getRoutePoint25ForwardEntryPoint() const;
    const sead::SafeString& getRoutePoint26ForwardEntryPoint() const;
    const sead::SafeString& getRoutePoint27ForwardEntryPoint() const;
    const sead::SafeString& getRoutePoint28ForwardEntryPoint() const;
    const sead::SafeString& getRoutePoint0BackwardEntryPoint() const;
    const sead::SafeString& getRoutePoint1BackwardEntryPoint() const;
    const sead::SafeString& getRoutePoint2BackwardEntryPoint() const;
    const sead::SafeString& getRoutePoint3BackwardEntryPoint() const;
    const sead::SafeString& getRoutePoint4BackwardEntryPoint() const;
    const sead::SafeString& getRoutePoint5BackwardEntryPoint() const;
    const sead::SafeString& getRoutePoint6BackwardEntryPoint() const;
    const sead::SafeString& getRoutePoint7BackwardEntryPoint() const;
    const sead::SafeString& getRoutePoint8BackwardEntryPoint() const;
    const sead::SafeString& getRoutePoint9BackwardEntryPoint() const;
    const sead::SafeString& getRoutePoint10BackwardEntryPoint() const;
    const sead::SafeString& getRoutePoint11BackwardEntryPoint() const;
    const sead::SafeString& getRoutePoint12BackwardEntryPoint() const;
    const sead::SafeString& getRoutePoint13BackwardEntryPoint() const;
    const sead::SafeString& getRoutePoint14BackwardEntryPoint() const;
    const sead::SafeString& getRoutePoint15BackwardEntryPoint() const;
    const sead::SafeString& getRoutePoint16BackwardEntryPoint() const;
    const sead::SafeString& getRoutePoint17BackwardEntryPoint() const;
    const sead::SafeString& getRoutePoint18BackwardEntryPoint() const;
    const sead::SafeString& getRoutePoint19BackwardEntryPoint() const;
    const sead::SafeString& getRoutePoint20BackwardEntryPoint() const;
    const sead::SafeString& getRoutePoint21BackwardEntryPoint() const;
    const sead::SafeString& getRoutePoint22BackwardEntryPoint() const;
    const sead::SafeString& getRoutePoint23BackwardEntryPoint() const;
    const sead::SafeString& getRoutePoint24BackwardEntryPoint() const;
    const sead::SafeString& getRoutePoint25BackwardEntryPoint() const;
    const sead::SafeString& getRoutePoint26BackwardEntryPoint() const;
    const sead::SafeString& getRoutePoint27BackwardEntryPoint() const;
    const sead::SafeString& getRoutePoint28BackwardEntryPoint() const;

    agl::utl::Parameter<sead::SafeString> mAppearGameDataName;
    agl::utl::Parameter<sead::SafeString> mDeleteGameDataName;
    agl::utl::Parameter<sead::SafeString> mRouteType;
    agl::utl::Parameter<sead::SafeString> mRideHorseName;
    agl::utl::Parameter<bool> mIsLeadHorse;
    agl::utl::Parameter<s32> mHorseGearLevel;

    struct RoutePoints {
        RoutePoints();
        auto& operator[](s32 i) { return reinterpret_cast<RoutePoint&>(mStorage[i]); }
        auto& operator[](s32 i) const { return reinterpret_cast<const RoutePoint&>(mStorage[i]); }
        auto data() { return reinterpret_cast<RoutePoint*>(&mStorage[0]); }

    private:
        std::aligned_storage_t<sizeof(RoutePoint), alignof(RoutePoint)> mStorage[NumRoutePoints];
    };
    RoutePoints mRoutePoints;
    agl::utl::Parameter<sead::SafeString> mRoutePoint29Name;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectTraveler, 0x3148);

}  // namespace ksys::res
