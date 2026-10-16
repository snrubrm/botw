#include "KingSystem/ActorSystem/actChemicalElementHolder.h"
#include <cmath>
#include <prim/seadScopedLock.h>
#include "KingSystem/ActorSystem/actChemical.h"

namespace ksys::act {

namespace {

// The world parameters copied by sub_7100D9A384 (in .data).
WorldParams sWorldParams = {24.0f, 2.0f, -5.0f, 0.3f, 0.3f, 30.0f, 300.0f, 0.5f, 0.1f, 24.0f, 410000.0f, 0.5f, 0.05f, 0.5f, 1.0f, 10.0f, 0.1f, 90.0f, 90.0f, 1.0f, 25.0f};

}  // namespace

Unk_71024dd490::CreateArg::CreateArg()
    : _0(0x400), _4(0x400), worldName(sead::SafeString::cEmptyString), _18(nullptr) {}

Unk_71024dd490::Unk_71024dd490() = default;

Unk_71024dd490::~Unk_71024dd490() {
    mChemicals.freeBuffer();
    _e8.freeBuffer();
    _f8.freeBuffer();
    _108.freeBuffer();
    _118.buffer.freeBuffer();
    _130.buffer.freeBuffer();
    _148.buffer.freeBuffer();
}

// NON_MATCHING: the inlined constructor merges and orders its zero stores differently
Unk_71024dd490* sub_7100D9A1D0(const Unk_71024dd490::CreateArg& arg, sead::Heap* heap) {
    auto* holder = new (heap) Unk_71024dd490;
    holder->sub_7100D9A384(arg, heap);
    chm::Chemical::instance()->sub_7100D99738(holder);
    return holder;
}

void Unk_71024dd490::sub_7100D9A8F8(Unk_71024dd490* holder) {
    chm::Chemical::instance()->sub_7100D99760(holder);
    delete holder;
}

// NON_MATCHING: the two counter stores of each PtrBuffer::clear are merged into one 64-bit store
void Unk_71024dd490::sub_7100D9A384(const CreateArg& arg, sead::Heap* heap) {
    mWorld = &chm::SystemConfig::instance()->getWorld(arg.worldName);
    mChemicals.allocBuffer(arg._0, heap);
    mChemicals.clear();
    _e8.allocBuffer(arg._0, heap, 8);
    _e8.clear();
    _f8.allocBuffer(arg._4, heap, 8);
    _f8.clear();
    _108.allocBuffer(arg._4, heap, 8);
    _108.clear();
    _118.init(arg._0, heap);
    _130.init(arg._0, heap);
    _148.init(arg._0, heap);
    _168 = arg._18;

    sWorldParams.heatTransferSpeedRate = mWorld->heat_transfer_speed_rate.ref();
    sWorldParams.fireHeatTransferSpeedRate = mWorld->fire_heat_transfer_speed_rate.ref();
    sWorldParams.conductionSpeedRateLog = mWorld->conduction_speed_rate_log.ref();
    sWorldParams.evaporationSpeedRate = mWorld->evaporation_speed_rate.ref();
    sWorldParams.burnSpeedRate = mWorld->burn_speed_rate.ref();
    sWorldParams.fireExtraRadius = mWorld->fire_extra_radius.ref();
    sWorldParams.playerFireMargin = mWorld->player_fire_margin.ref();
    sWorldParams.electricityExtraRadiusRate = mWorld->electricity_extra_radius_rate.ref();
    sWorldParams.electricWaterExtraRadiusRate = mWorld->electric_water_extra_radius_rate.ref();
    sWorldParams.minIceSize = mWorld->min_ice_size.ref();
    sWorldParams.iceHeatCheatThreshold = mWorld->ice_heat_cheat_threshold.ref();
    sWorldParams.iceHeatCheatRate = mWorld->ice_heat_cheat_rate.ref();
    sWorldParams.iceMeltRatioEnvTemp = mWorld->ice_melt_ratio_env_temp.ref();
    sWorldParams.iceMeltRatioWarmAir = mWorld->ice_melt_ratio_warm_air.ref();
    sWorldParams.iceMeltRatioFire = mWorld->ice_melt_ratio_fire.ref();
    sWorldParams.iceMeltRatioFire2 = mWorld->ice_melt_ratio_fire2.ref();
    sWorldParams.windLiftRate = mWorld->wind_lift_rate.ref();
    sWorldParams.lightningDistance = mWorld->lightning_distance.ref();
    sWorldParams.characterIgnitionCount = mWorld->character_ignition_count.ref();
    sWorldParams.objectIgnitionCount = mWorld->object_ignition_count.ref();
    sWorldParams.offensiveRigidRadius = mWorld->offensive_rigid_radius.ref();
}

void Unk_71024dd490::sub_7100D9AA84() {
    _c8 &= ~0x1f8;
    const auto lock = sead::makeScopedLock(_48);
    for (auto& chemical : mChemicals)
        chemical.sub_7100D8F0FC();
}


f32 Unk_71024dd490::sub_7100D99FD0() const {
    return sWorldParams.heatTransferSpeedRate;
}

f32 Unk_71024dd490::sub_7100D99FDC() const {
    return sWorldParams.fireHeatTransferSpeedRate;
}

f32 Unk_71024dd490::sub_7100D99FF8() const {
    return std::pow(10.0f, sWorldParams.conductionSpeedRateLog);
}

f32 Unk_71024dd490::sub_7100D9A00C() const {
    return sWorldParams.fireExtraRadius;
}

f32 Unk_71024dd490::sub_7100D9A01C() const {
    return sWorldParams.playerFireMargin;
}

f32 Unk_71024dd490::sub_7100D9A038() const {
    return sWorldParams.electricityExtraRadiusRate;
}

f32 Unk_71024dd490::sub_7100D9A048() const {
    return sWorldParams.electricWaterExtraRadiusRate;
}

f32 Unk_71024dd490::sub_7100D9A058() const {
    return sWorldParams.minIceSize;
}

f32 Unk_71024dd490::sub_7100D9A080() const {
    return sWorldParams.burnSpeedRate;
}

f32 Unk_71024dd490::sub_7100D9A090() const {
    return sWorldParams.evaporationSpeedRate;
}

f32 Unk_71024dd490::sub_7100D9A0AC() const {
    return sWorldParams.iceHeatCheatThreshold;
}

f32 Unk_71024dd490::sub_7100D9A0BC() const {
    return sWorldParams.iceHeatCheatRate;
}

f32 Unk_71024dd490::sub_7100D9A0CC() const {
    return sWorldParams.iceMeltRatioEnvTemp;
}

f32 Unk_71024dd490::sub_7100D9A0DC() const {
    return sWorldParams.iceMeltRatioWarmAir;
}

f32 Unk_71024dd490::sub_7100D9A0EC() const {
    return sWorldParams.iceMeltRatioFire;
}

f32 Unk_71024dd490::sub_7100D9A0FC() const {
    return sWorldParams.iceMeltRatioFire2;
}

f32 Unk_71024dd490::sub_7100D9A118() const {
    return sWorldParams.windLiftRate;
}

f32 Unk_71024dd490::sub_7100D9A17C() const {
    return sWorldParams.characterIgnitionCount;
}

f32 Unk_71024dd490::sub_7100D9A18C() const {
    return sWorldParams.objectIgnitionCount;
}

f32 Unk_71024dd490::sub_7100D9A19C() const {
    return sWorldParams.offensiveRigidRadius;
}

}  // namespace ksys::act
