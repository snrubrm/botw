#pragma once

#include <container/seadSafeArray.h>
#include <math/seadVector.h>
#include "KingSystem/Utils/Types.h"
#include "KingSystem/World/worldDefines.h"
#include "KingSystem/World/worldJob.h"

namespace ksys::world {

constexpr u32 NumWeatherCycles = 3;

// Current and previous weather type; the constructor clears both bytes at once.
struct WeatherState {
    u8 type;
    s8 prevType;
};

// This may be incorrect
struct ClimateWeathers {
    s32 weather[NumWeatherCycles];
};

// Weather interpolation state at 0x2c4; the constructor value-initialises it.
// Field names keep the WeatherMgr offsets so the code below can stay readable.
struct WeatherTransition {
    u8 _2c4[0xc];
    f32 _2d0;
    u8 _2d4[4];
    f32 _2d8;
    f32 _2dc;
    u8 _2e0[4];
    f32 _2e4;
    f32 _2e8;
    f32 _2ec;
    f32 _2f0;
    f32 _2f4;
    f32 _2f8;
    f32 _2fc;
    u8 _300[0xc];
};
KSYS_CHECK_SIZE_NX150(WeatherTransition, 0x48);

// TODO
class WeatherMgr : public Job {
    SEAD_RTTI_OVERRIDE(WeatherMgr, Job)
public:
    WeatherMgr();
    ~WeatherMgr() override;

    JobType getType() const override { return JobType::Weather; }

    void reset();
    void onUnload();
    void rerollClimateWindPowers();

    static bool isExposureZero();
    // 0x71010eb5e8 (CSV name): picks one wind direction type for every climate.
    static void climateStuff();
    void loadInfo();
    WeatherType rollNewWeather(Climate climate);
    // 0x71010eab84: packs the nibbles of the climate weather table into the three GDT arrays.
    void x_0();
    // 0x71010eb4bc (CSV wm::WeatherMgr::calcNewWeathers): shifts every climate's weather table by one cycle and
    // rolls the six new entries (not in the test stage).
    void calcNewWeathers();
    WeatherType getWeather() const;

    // UI weather setup/frame callbacks pass the WeatherMgr receiver and use a float result.
    float getTime() const;
    u8 x_6(int idx) const;
    bool x_8() const;
    static bool x_7();
    // 0x71010edccc: emits Far_Lightning on the reaction actor 2000 units in front of the camera (random yaw
    // offset in [-0.65, 0.65]), at the camera height.
    static void x_10();
    void setWeatherEffect(int effect);
    void x_16();
    void x_17();
    WeatherType x_1(int climate) const;
    WeatherType x_2(int climate) const;
    WeatherType x_3(int climate) const;
    WeatherType x_4(int climate) const;
    WeatherType x_5(int climate) const;
    WeatherType x_18(int climate) const;
    // 10ED7B8 receives the lightning position; D9C0CC passes a Vector3f temporary.
    void x_12(const sead::Vector3f& position);
    void x_11(const sead::Vector3f& position);
    void x_13();
    void x_14();
    void sub_71010EDEBC(int value);
    f32 sub_71010ED5B4(const sead::Vector3f& position);
    int x() const;
    bool isRaining();
    bool isSnowing();

protected:
    void init_(sead::Heap* heap) override;
    void calcType2_() override;

public:

    u8 _20;
    float _24;
    WeatherState mWeather;  // 0x28
    sead::SafeArray<sead::SafeArray<WeatherType, NumWeatherCycles * 6>, NumClimates> _2a;
    u8 _193;
    // Three arrays of packed 6-nibble weather values (0x71010eab84 / loadInfo 0x71010ea34c).
    sead::SafeArray<sead::SafeArray<s32, NumClimates>, 3> mClimateWeathers;  // 0x194
    sead::SafeArray<u8, 6> _284;
    u8 _28a[2];
    // Zeroed by the constructor; no other function in the binary reads it yet.
    s32 _28c;
    s32 _290;
    s32 _294;
    s32 _298;
    s32 _29c;
    s32 _2a0;
    s32 _2a4;
    s32 _2a8;
    // Constructor sets (0, 1, 0); x_12 and x_9 write the camera-facing direction.
    sead::Vector3f _2ac;
    u8 _2b8[0xc];
    // Value-initialised by the constructor.
    WeatherTransition mTransition;  // 0x2c4
    f32 _30c;
    f32 _310;
    int _314;
    float mTimeBlock;  // 0x318
    u32 mWeekDay;      // 0x31c
    int _320;
    int _324;
    int _328;
    u32 _32c;  // zeroed by the constructor
    u32 _330;
    int _334;
    int _338;
    int _33c;
    int _340;
    int _344;
    int _348;
    int _34c;
    int _350;
    s32 _354;
    s32 _358;
    u32 _35c;  // zeroed by the constructor
    u32 _360;
    u32 _364;
    u32 _368;
    int _36c;
    int _370;
    int _374;
    s32 _378;
    s32 _37c;
    int _380;
    s32 _384;
    s32 _388;
    s32 _38c;
    bool _390;
    bool _391;
    u8 _392;
    u8 _393;
    u16 _394;
    u8 _396[2];
};
KSYS_CHECK_SIZE_NX150(WeatherMgr, 0x398);
static_assert(offsetof(WeatherMgr, mTransition) == 0x2c4);
static_assert(offsetof(WeatherTransition, _2e4) == 0x20);
static_assert(offsetof(WeatherTransition, _2fc) == 0x38);

// 0x71010eb430 (CSV wm::isGetPlayerStole2): the TimeMgr's "plateau done" flag. The manager argument
// is unused (the body reads TimeMgr through Manager::instance()); the caller passes the WeatherMgr.
bool isGetPlayerStole2(WeatherMgr* weather_mgr);

}  // namespace ksys::world

namespace wm {
ksys::world::WeatherMgr* getWeatherMgr();
}
