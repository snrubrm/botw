#include "KingSystem/Physics/physDefines.h"

namespace ksys::phys {

ContactLayerType getContactLayerType(ContactLayer layer) {
    if (layer > ContactLayer::EntityEnd)
        return ContactLayerType::Sensor;
    return ContactLayerType::Entity;
}

u32 makeContactLayerMask(ContactLayer layer) {
    if (layer < FirstSensor)
        return 1 << layer;
    return 1 << (layer - FirstSensor);
}

u32 getContactLayerBase(ContactLayerType type) {
    if (type == ContactLayerType::Entity)
        return FirstEntity;
    return FirstSensor;
}

int getContactLayerBaseRelativeValue(ContactLayer layer) {
    return layer - (layer < FirstSensor ? FirstEntity : FirstSensor);
}

const char* contactLayerToText(ContactLayer layer) {
    return layer.text();
}

ContactLayer contactLayerFromText(const sead::SafeString& text) {
    for (auto layer : ContactLayer()) {
        if (text == layer.text())
            return layer;
    }
    return 0;
}

const char* materialToText(Material material) {
    return material.text();
}

Material materialFromText(const sead::SafeString& text) {
    for (auto material : Material()) {
        if (text == material.text())
            return material;
    }
    return 0;
}

const char* groundHitToText(GroundHit hit) {
    return hit.text();
}

GroundHit groundHitFromText(const sead::SafeString& text) {
    for (auto hit : GroundHit()) {
        if (text == hit.text())
            return hit;
    }
    return GroundHit::HitAll;
}

const char* floorCodeToText(FloorCode code) {
    return code.text();
}

FloorCode floorCodeFromText(const sead::SafeString& text) {
    for (auto code : FloorCode()) {
        if (text == code.text())
            return code;
    }
    return 0;
}

const char* wallCodeToText(WallCode code) {
    return code.text();
}

WallCode wallCodeFromText(const sead::SafeString& text) {
    for (auto code : WallCode()) {
        if (text == code.text())
            return code;
    }
    return 0;
}

MotionType motionTypeFromText(const sead::SafeString& text) {
    static constexpr const char* texts[] = {
        "Dynamic",
        "Fixed",
        "Keyframed",
    };
    static_assert(int(MotionType::Dynamic) == 0);
    static_assert(int(MotionType::Fixed) == 1);
    static_assert(int(MotionType::Keyframed) == 2);

    int type = 0;
    for (const char* type_text : texts) {
        if (text == type_text)
            return static_cast<MotionType>(type);
        ++type;
    }
    return MotionType::Unknown;
}

// 0x7100e94740. Layer numbers match ContactLayer (2 = EntityGroundObject,
// 8/9/10 = EntityGround/Smooth/Rough, 12 = EntityTree).
bool xxx_2(int layer) {
    switch (layer) {
    case 2:
    case 8:
    case 9:
    case 10:
    case 12:
        return true;
    default:
        return false;
    }
}

// 0x7100e94768 (0 = EntityObject on top of xxx_2's set minus EntityGroundRough).
// NON_MATCHING (m): the original masks the table index in 64-bit
// (`and x8, x0, #0x1fff`); all tested source forms (int/u32/long param, casts,
// explicit range check, SEAD_ENUM) produce the 32-bit form. Structure identical.
bool xxx_3(int layer) {
    switch (layer) {
    case 0:
    case 2:
    case 8:
    case 9:
    case 12:
        return true;
    default:
        return false;
    }
}

}  // namespace ksys::phys
