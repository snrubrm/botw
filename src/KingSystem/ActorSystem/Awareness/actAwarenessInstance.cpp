#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/Awareness/actAwareness.h"
#include <gsys/gsysModel.h>
#include <cmath>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessRequest.h"

namespace ksys::act {

void Unk_71024dc900::sub_7100D77EAC(Actor* actor) {}

void Unk_71024dc900::m6(Actor* actor) {
    Unk_71024dca28::m6(actor);
}

Unk_71024dc978* Unk_71024dc900::m8() {
    return &_18;
}

void AwarenessInstance::disable() {
    if (auto* awareness = Awareness::instance()) {
        awareness->mInstances.deregisterInstance(this);
        _337 = false;
    }

    for (s32 i = 0; i < 4; ++i) {
        if (auto* sensor = _260[i]) {
            sensor->_8.clear();
            sensor->_3c = 0;
            _260[i]->_50 = false;
        }
    }
}

bool AwarenessInstance::enable() {
    if (!((_260[0] && _260[0]->_50) || (_260[1] && _260[1]->_50) || (_260[2] && _260[2]->_50) ||
          (_260[3] && _260[3]->_50) || _337)) {
        auto* awareness = Awareness::instance();
        if (!awareness)
            return false;
        if (!awareness->mInstances.registerInstance(this))
            return false;
        _337 = true;
    }

    for (auto* sensor : _260) {
        if (sensor)
            sensor->_50 = true;
    }
    return true;
}

void AwarenessInstance::sleep() {
    disable();
}

// NON_MATCHING: store grouping of the request object (see actAwarenessRequest.h)
bool AwarenessInstance::sub_7100D7E74C(f32 level) {
    if (!_260[0])
        return false;
    Unk_71023e26d8 request;
    if (!_260[0]->m4(&request))
        return false;
    request._c = level;
    return _260[0]->m6(&request);
}

bool AwarenessInstance::sub_7100D7E7E8() {
    bool result = true;
    if (_260(0))
        result = _260(0)->m11();
    if (_260(1))
        result &= _260(1)->m11();
    if (_260(2))
        result &= _260(2)->m11();
    if (_260(3))
        result &= _260(3)->m11();
    if (_337)
        disable();
    return result;
}

bool AwarenessInstance::sub_7100D7E6F4(Unk_71023e2708* request, int idx) {
    if (auto* sensor = _260[idx]) {
        if (!sensor->m6(request))
            return false;
        sub_7100D7C494();
        return true;
    }
    return false;
}

void AwarenessInstance::sub_7100D7EBE0(f32 value) {
    for (auto* sensor : _260) {
        if (sensor)
            sensor->_4c = value;
    }
    sub_7100D7C494();
}

void AwarenessInstance::sub_7100D7EC14(int idx, f32 value) {
    if (auto* sensor = _260[idx])
        sensor->_4c = value;
    sub_7100D7C494();
}

f32 AwarenessInstance::sub_7100D7EC34(int idx) const {
    if (auto* sensor = _260[idx])
        return sensor->_4c;
    return 0.0f;
}

// NON_MATCHING: register allocation in the search loop; the filter's _18 is addressed differently
void AwarenessInstance::sub_7100D7EA7C(Unk_71024dccf8* filter) {
    if (!_2e8)
        return;

    if (_2e8 == filter) {
        _2e8 = filter->_18;
        if (_2e8)
            _2e8->_10 = nullptr;
    } else {
        Unk_71024dccf8* prev = nullptr;
        Unk_71024dccf8* it = _2e8;
        while (it != filter) {
            prev = it;
            it = it->_18;
            if (!it)
                return;
        }
        if (prev)
            prev->_18 = filter->_18;
        if (filter->_18)
            filter->_18->_10 = prev;
    }
    filter->_18 = nullptr;
    filter->_20 = nullptr;
    filter->_10 = nullptr;
}

Unk_7100d78e50* sub_7100D7EEE8(sead::ObjArray<Unk_7100d78e50>* array, Unk_71024dccf8* filter) {
    s32 i = filter->_8;
    const s32 num = array->size();
    while (++i < num) {
        auto* entry = sub_7100D78E30(array, i);
        filter->_8 = i;
        if (filter->m2(&entry->_0))
            return sub_7100D78E30(array, i);
    }
    return nullptr;
}

bool AwarenessInstance::sub_7100D7E964() const {
    for (auto* s : _260) {
        if (s && s->_50)
            return true;
    }
    return _337;
}

bool AwarenessInstance::sub_7100D7E9BC(int idx) {
    auto* sensor = _260[idx];
    if (!sensor)
        return false;

    bool any_active = false;
    for (auto* s : _260) {
        if (s && s->_50) {
            any_active = true;
            break;
        }
    }

    if (!any_active && !_337) {
        auto* awareness = Awareness::instance();
        if (!awareness)
            return false;
        if (!awareness->mInstances.registerInstance(this))
            return false;
        _337 = true;
        sensor = _260[idx];
    }
    sensor->_50 = true;
    return true;
}

void AwarenessInstance::calcForEvent() {
    _300 = 0;
    _304 = -1;
    _8.clear();
    if (!sAwarenessDisabledSensorsMaybe.isOnBit(0)) {
        if (auto* sensor = _260[0]) {
            sensor->_8.clear();
            sensor->_3c = 0;
        }
    }
    if (!sAwarenessDisabledSensorsMaybe.isOnBit(1)) {
        if (auto* sensor = _260[1]) {
            sensor->_8.clear();
            sensor->_3c = 0;
        }
    }
    if (!sAwarenessDisabledSensorsMaybe.isOnBit(2)) {
        if (auto* sensor = _260[2]) {
            sensor->_8.clear();
            sensor->_3c = 0;
        }
    }
    if (!sAwarenessDisabledSensorsMaybe.isOnBit(3)) {
        if (auto* sensor = _260[3]) {
            sensor->_8.clear();
            sensor->_3c = 0;
        }
    }
}

void AwarenessInstance::sub_7100D7C494() {
    f32 level = 0.0f;
    if (!sAwarenessDisabledSensorsMaybe.isOnBit(0)) {
        if (auto* sensor = _260[0])
            level = sead::Mathf::max(sensor->m14() * sensor->_4c, 0.0f);
    }
    if (!sAwarenessDisabledSensorsMaybe.isOnBit(1)) {
        if (auto* sensor = _260[1])
            level = sead::Mathf::max(sensor->m14() * sensor->_4c, level);
    }
    if (!sAwarenessDisabledSensorsMaybe.isOnBit(2)) {
        if (auto* sensor = _260[2])
            level = sead::Mathf::max(sensor->m14() * sensor->_4c, level);
    }
    if (!sAwarenessDisabledSensorsMaybe.isOnBit(3)) {
        if (auto* sensor = _260[3])
            level = sead::Mathf::max(sensor->m14() * sensor->_4c, level);
    }
    _2f8 = sead::Mathf::clampMin(level, _2f4);
}

void AwarenessInstance::sub_7100D7EAE4(int idx) {
    auto* sensor = _260[idx];
    if (!sensor)
        return;
    sensor->_8.clear();
    sensor->_3c = 0;
    _260[idx]->_50 = false;

    for (auto* s : _260) {
        if (s && s->_50)
            return;
    }
    if (_337)
        return;
    auto* awareness = Awareness::instance();
    if (!awareness)
        return;
    awareness->mInstances.deregisterInstance(this);
    _337 = false;
}

}  // namespace ksys::act

namespace ksys::act {

// NON_MATCHING: null-check scheduling and sensor-kind branch ordering differ.
void AwarenessInstance::sub_7100D7DEC4(s32 kind, const sead::Vector3f& position,
                                     Unk_71024dc858* target,
                                     const sead::Matrix34f& target_matrix, bool flag) {
    if (_334 & 0x20)
        return;
    auto* sensor = _260[kind];
    if (!sensor || !target || !sensor->_50)
        return;
    if (kind == 2) {
        if (!(target->_3c & _318))
            return;
    } else {
        if (kind == 0 && _2e8) {
            auto* filter = _2e8;
            do {
                if (filter->m2(target))
                    break;
                // The callback can change the registered head; the original reloads it here.
                filter = _2e8->_18;
                if (!filter)
                    return;
            } while (true);
        }
        if (kind == 0 && !flag)
            flag = !(_328 & target->_40);
    }
    const f32 level = target->m4(kind);
    const auto& transform = _38[kind];
    const auto& matrix = transform._68 ? transform._0 : _230;
    _260[kind]->sub_7100D7F8E4(level, target, position, matrix, target_matrix, _2c8, flag);
}

}  // namespace ksys::act

namespace ksys::act {

// NON_MATCHING: matrix/vector copies and temporary storage differ.
void AwarenessInstance::sub_7100D7CF20() {
    for (s32 i = 0; i < 4; ++i) {
        auto& transform = _38[i];
        if (!transform._68)
            continue;
        sead::Vector3f position;
        if (_334 & 0x10)
            position = transform._0.getTranslation();
        sead::Matrix34f bone_matrix;
        _2e0->getModel()->getBoneWorldMatrix(transform._30.getKey(), &bone_matrix);
        transform._0 = _2e0->getMtx();
        if (!(_334 & 0x10)) {
            position.setRotated(_2e0->getMtx(), sead::Vector3f::zero);
            position += bone_matrix.getTranslation();
            if (i == 0)
                _2c8 = position;
        }
        transform._0.setTranslation(position);
    }
}

}  // namespace ksys::act

namespace ksys::act {

// NON_MATCHING: parameter load grouping and scheduling around cosine calls differ.
void AwarenessInstance::sub_7100D7C160(const SetupArg& arg) {
    if (auto* sensor = sead::DynamicCast<Unk_71024dcea8>(_260[0])) {
        sensor->sub_7100D7FDDC(arg.sight_delay_time_max);
        sensor->_8c = arg.sight_radius;
        sensor->_90 = arg.sight_angle;
        sensor->_94 = arg.sight_height_max;
        sensor->_98 = arg.sight_height_min;
        sensor->_9c = arg.sight_height_near_max;
        sensor->_a0 = arg.sight_height_near_min;
        sensor->_a4 = std::cos(arg.sight_angle);
        sensor->_a8 = arg.sight_alert_radius;
        sensor->_ac = arg.sight_alert_angle;
        sensor->_b0 = arg.sight_alert_height_max;
        sensor->_b4 = arg.sight_alert_height_min;
        sensor->_b8 = arg.sight_alert_height_near_max;
        sensor->_bc = arg.sight_alert_height_near_min;
        sensor->_c0 = std::cos(arg.sight_alert_angle);
        sensor->_c4 = arg.sight_ignore_grass_radius;
        sensor->_c8 = arg.sight_ray_check_range_max;
        sensor->_cc = arg.sight_far_use;
        sensor->_d0 = arg.sight_radius_far;
        sensor->_d4 = arg.sight_angle_far;
        sensor->_d8 = std::cos(arg.sight_angle_far);
        sensor->_70 = _2e0;
        sensor->_4c = 1.0f;
        if (arg.invalidate_weather_ratio)
            sensor->_51 = true;
    }
    if (auto* sensor = sead::DynamicCast<Unk_71024dcd68>(_260[1])) {
        sensor->sub_7100D7FDDC(arg.hearing_delay_time_max);
        sensor->_54 = arg.hearing_radius;
        sensor->_58._0 = arg.hearing_blind_angle;
        sensor->_58._4 = arg.hearing_blind_margin_angle;
        sensor->_58._8 = arg.hearing_reduce_ratio;
        sensor->_58.warnRatio = arg.hearing_alert_level;
        sensor->_58.noticeRatio = arg.hearing_notice_level;
        sensor->_4c = 1.0f;
        if (arg.invalidate_weather_ratio)
            sensor->_51 = true;
    }
    if (auto* sensor = sead::DynamicCast<Unk_71024dcfd0>(_260[2])) {
        sensor->sub_7100D7FDDC(arg.sense_delay_time_max);
        sensor->_54 = arg.sense_radius;
        sensor->_58 = arg.sense_angle;
        sensor->_5c = std::cos(arg.sense_angle);
        sensor->_4c = 1.0f;
        if (arg.invalidate_weather_ratio)
            sensor->_51 = true;
    }
    if (auto* sensor = sead::DynamicCast<Unk_71024dd070>(_260[3])) {
        sensor->sub_7100D7FDDC(arg.worry_delay_time_max);
        sensor->_54 = arg.worry_radius;
        sensor->_4c = 1.0f;
        if (arg.invalidate_weather_ratio)
            sensor->_51 = true;
    }
}

}  // namespace ksys::act
