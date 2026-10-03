#include <math/seadMathCalcCommon.h>
#include "Game/UI/uiManager.h"

// UI wrapper functions around uking::ui::Manager (the 0x7100a94000 TU).
namespace uking::ui {

void sub_7100945320(f32, f32);
void sub_7100945344(f32, f32);

// 0x7100a94158
bool uiManagerInitialised() {
    return Manager::instance() != nullptr;
}

// 0x7100a94170
void setPauseStateMaybe(bool paused) {
    if (auto* manager = Manager::instance())
        manager->_38 = paused;
}

// 0x7100a9418c
bool sub_7100A9418C() {
    if (auto* manager = Manager::instance())
        return manager->_38 != 0;
    return false;
}

// 0x7100a941b4
void sub_7100A941B4() {
    if (auto* manager = Manager::instance())
        manager->sub_7100A76424();
}

// 0x7100a941cc
void sub_7100A941CC() {
    Manager::instance()->sub_7100A79968();
}

// 0x7100a941dc
void sub_7100A941DC() {
    Manager::instance()->sub_7100A79ED4();
}

// 0x7100a94460
void sub_7100A94460() {
    auto* manager = Manager::instance();
    if (manager && manager->_38)
        manager->sub_7100A76420();
}

// 0x7100a94480
void sub_7100A94480() {
    Manager::instance()->sub_7100A7A4C0();
}

// 0x7100a94490
void sub_7100A94490() {
    Manager::instance()->_64c30 |= 0x20;
}

// 0x7100a944b4
void sub_7100A944B4() {
    Manager::instance()->_64c30 &= ~0x20ull;
}

// 0x7100a94788
void sub_7100A94788() {
    Manager::instance()->_64c30 &= ~0x40ull;
}

// 0x7100a94a50
void sub_7100A94A50(bool set) {
    auto* manager = Manager::instance();
    manager->_64c30 = set ? (manager->_64c30 | 0x80) : (manager->_64c30 & ~0x80ull);
}

// 0x7100a94aa8
void sub_7100A94AA8(bool value) {
    Manager::instance()->set64c68(value);
}

// 0x7100a9b2ac
void sub_7100A9B2AC() {
    if (auto* manager = Manager::instance())
        manager->_64c4d = true;
}

// 0x7100a9b2d0
void sub_7100A9B2D0() {
    if (auto* manager = Manager::instance())
        manager->_64c4d = false;
}

// 0x7100a9b468
void updateLifeAndMaxLife(s32 life, s32 max_life) {
    if (auto* manager = Manager::instance()) {
        manager->_48 = sead::Mathi::clamp(life, 0, 120);
        manager->_4c = sead::Mathi::clamp(max_life, 0, 120);
    }
}

// 0x7100a9b4a4
void updateStaminaAndMax(f32 stamina, f32 max_stamina) {
    if (Manager::instance())
        sub_7100945320(sead::Mathf::clampMin(stamina, 0.0f), sead::Mathf::clampMin(max_stamina, 0.0f));
}

// 0x7100a9b4c8
void sub_7100A9B4C8(f32 a0, f32 a1) {
    if (Manager::instance())
        sub_7100945344(sead::Mathf::clampMin(a0, 0.0f), sead::Mathf::clampMin(a1, 0.0f));
}

// 0x7100a9b4ec
void sub_7100A9B4EC(f32 a0, f32 a1) {
    if (auto* manager = Manager::instance()) {
        manager->_74 = true;
        manager->_68 = a0;
        manager->_6c = a1;
    }
}

// 0x7100a9b510
void sub_7100A9B510(s32 a0, s32 a1) {
    if (auto* manager = Manager::instance()) {
        manager->_78 = a0;
        manager->_7c = a1;
    }
}

// 0x7100a9b528
void sub_7100A9B528(f32 a0) {
    if (auto* manager = Manager::instance())
        manager->_70 = a0;
}

// 0x7100a9b540
void sub_7100A9B540(const sead::Vector3f* a0, const sead::Vector3f* a1) {
    if (auto* manager = Manager::instance()) {
        manager->_80 = *a0;
        manager->_8c = *a1;
    }
}

// 0x7100a9b654
void sub_7100A9B654(const sead::Vector2f* a0) {
    if (auto* manager = Manager::instance())
        manager->_98 = *a0;
}

// 0x7100a9b678
void sub_7100A9B678(f32 a0) {
    if (auto* manager = Manager::instance())
        manager->_a0 = a0;
}

// 0x7100a9b690
s32 sub_7100A9B690() {
    if (auto* manager = Manager::instance())
        return manager->_48;
    return 0;
}

// 0x7100a9b6b0
s32 sub_7100A9B6B0() {
    if (auto* manager = Manager::instance())
        return manager->_4c;
    return 0;
}

// 0x7100a9b6d0
f32 sub_7100A9B6D0() {
    if (auto* manager = Manager::instance())
        return manager->_50;
    return 0;
}

// 0x7100a9b6f0
f32 sub_7100A9B6F0() {
    if (auto* manager = Manager::instance())
        return manager->_54;
    return 0;
}

// 0x7100a9b710
f32 sub_7100A9B710() {
    if (auto* manager = Manager::instance())
        return manager->_5c;
    return 0;
}

// 0x7100a9b730
bool sub_7100A9B730(f32* a0, f32* a1) {
    if (auto* manager = Manager::instance()) {
        if (manager->_74) {
            *a0 = manager->_68;
            *a1 = manager->_6c;
            return true;
        }
    }
    return false;
}

// 0x7100a9b770
void sub_7100A9B770(s32* a0, s32* a1) {
    if (auto* manager = Manager::instance()) {
        if (a0)
            *a0 = manager->_78;
        if (a1)
            *a1 = manager->_7c;
    }
}

// 0x7100a9b79c
f32 sub_7100A9B79C() {
    if (auto* manager = Manager::instance())
        return manager->_70;
    return 0;
}

// 0x7100a9b800
void sub_7100A9B800(sead::Vector3f* out) {
    if (out) {
        if (auto* manager = Manager::instance())
            *out = manager->_80;
    }
}

// 0x7100a9b94c
f32 sub_7100A9B94C() {
    if (auto* manager = Manager::instance())
        return manager->_a0;
    return 0;
}

// 0x7100a9b9f8
void sub_7100A9B9F8(s32 bit) {
    if (auto* manager = Manager::instance())
        manager->_649ec.setBit(bit);
}

// 0x7100a9ba28
void sub_7100A9BA28() {
    if (auto* manager = Manager::instance())
        manager->_649ec.makeAllZero();
}

// 0x7100a9ba48
bool sub_7100A9BA48() {
    if (auto* manager = Manager::instance())
        return !manager->_649ec.isZero();
    return false;
}

// 0x7100a9ba78
bool sub_7100A9BA78(s32 bit) {
    if (auto* manager = Manager::instance())
        return manager->_649ec.isOnBit(bit);
    return false;
}

// 0x7100a9bab4
void sub_7100A9BAB4(s32 idx, s32 value) {
    Manager::instance()->_b0[idx] = value;
}

// 0x7100a9bad8
void sub_7100A9BAD8(s32 value) {
    Manager::instance()->_c4 = value;
}

// 0x7100a9bca4
void sub_7100A9BCA4(const u64* value) {
    Manager::instance()->setD8(value);
}

// 0x7100a9bcbc
void sub_7100A9BCBC(const u64* value) {
    Manager::instance()->setE0(value);
}

// 0x7100a9c0fc
void sub_7100A9C0FC(s32 value) {
    Manager::instance()->_cc = value;
}

// 0x7100a9c110
bool sub_7100A9C110(s32 value) {
    return Manager::instance()->_d0 == value;
}

// 0x7100a9c12c
bool sub_7100A9C12C(s32 value) {
    auto* manager = Manager::instance();
    if (manager->_d0 != value)
        return false;
    return manager->_d4 != value;
}

// 0x7100a9e200
void loadSaveForStageUnload() {
    if (auto* manager = Manager::instance())
        manager->sub_7100A76180();
}

// 0x7100a9e218
void sub_7100A9E218() {
    Manager::instance()->sub_7100A7F81C();
}

// 0x7100a9e228
s32 sub_7100A9E228() {
    return Manager::instance()->_650f0;
}

// 0x7100a9e244
u64 sub_7100A9E244() {
    return Manager::instance()->_65160;
}

// 0x7100a9e260
s32 getSomeUiManagerField() {
    return Manager::instance()->_65168;
}

// 0x7100a9e2c4
void uiManagerUpdateIsDungeon() {
    Manager::instance()->sub_7100A7FBA4();
}

// 0x7100a9e5e0
void sub_7100A9E5E0() {
    if (auto* manager = Manager::instance())
        manager->sub_7100A7C8D4();
}

// 0x7100aa8f10
bool sub_7100AA8F10() {
    return (Manager::instance()->_64c30_bytes[1] >> 4) & 1;
}

// 0x7100a9f5e4
bool checkSomeFlagImpl() {
    if (auto* manager = Manager::instance())
        return (manager->_64c30_bytes[5] >> 3) & 1;
    return false;
}

// 0x7100a9f950
void return0_2() {
    Manager::instance()->sub_7100A7FDAC();
}

}  // namespace uking::ui
