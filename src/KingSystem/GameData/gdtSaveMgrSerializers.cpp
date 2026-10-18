#include "KingSystem/GameData/gdtSaveMgr.h"
#include <cstring>

namespace ksys {

bool SaveMgr::x_18(res::GameSaveData::Flag& entry, gdt::FlagT<s32>* flag, u32 size,
                        u32 is_array) {
    if (entry._8 == 0)
        entry._8 = _e14;
    for (u32 i = 0; i < size; i += 4) {
        if (_e14 + 4 >= (_e2c == 0 ? _e10 : _e38))
            return false;
        const u32 hash = flag->getHash();
        std::memcpy(_e14 + (_e2c == 0 ? _e08 : _e30), &hash, sizeof(hash));
        _e14 += 4;
        if (_e14 + 4 >= (_e2c == 0 ? _e10 : _e38))
            return false;
        const s32* values = &flag->getValueRef();
        std::memcpy(_e14 + (_e2c == 0 ? _e08 : _e30), &values[i], sizeof(values[i]));
        const u32 category = _1038;
        if (category == flag->getHash())
            _103c = _e14;
        _e14 += 4;
    }
    return true;
}

bool SaveMgr::sub_7100E0A57C(res::GameSaveData::Flag& entry, gdt::FlagT<f32>* flag, u32 size,
                        u32 is_array) {
    if (entry._8 == 0)
        entry._8 = _e14;
    for (u32 i = 0; i < size; i += 4) {
        if (_e14 + 4 >= (_e2c == 0 ? _e10 : _e38))
            return false;
        const u32 hash = flag->getHash();
        std::memcpy(_e14 + (_e2c == 0 ? _e08 : _e30), &hash, sizeof(hash));
        _e14 += 4;
        if (_e14 + 4 >= (_e2c == 0 ? _e10 : _e38))
            return false;
        const f32* values = &flag->getValueRef();
        std::memcpy(_e14 + (_e2c == 0 ? _e08 : _e30), &values[i], sizeof(values[i]));
        const u32 category = _1038;
        if (category == flag->getHash())
            _103c = _e14;
        _e14 += 4;
    }
    return true;
}

bool SaveMgr::sub_7100E0A6C8(res::GameSaveData::Flag& entry,
                        const gdt::FlagT<sead::FixedSafeString<32>>* flag, u32 size,
                        u32 is_array) {
    const u32 length = flag->getValueRef().calcLength();
    if (entry._8 == 0)
        entry._8 = _e14;
    for (u32 i = 0; i < size; i += 4) {
        if (_e14 + 4 >= (_e2c == 0 ? _e10 : _e38))
            return false;
        const u32 hash = flag->getHash();
        std::memcpy(_e14 + (_e2c == 0 ? _e08 : _e30), &hash, sizeof(hash));
        _e14 += 4;
        if (_e14 + 4 >= (_e2c == 0 ? _e10 : _e38))
            return false;
        if (length < i) {
            std::memset(_e14 + (_e2c == 0 ? _e08 : _e30), 0, sizeof(u32));
        } else if (length < i + 4) {
            std::memset(_e14 + (_e2c == 0 ? _e08 : _e30), 0, sizeof(u32));
            std::memcpy(_e14 + (_e2c == 0 ? _e08 : _e30), flag->getValueRef().cstr() + i,
                        length - i);
        } else {
            std::memcpy(_e14 + (_e2c == 0 ? _e08 : _e30), flag->getValueRef().cstr() + i,
                        sizeof(u32));
        }
        _e14 += 4;
    }
    return true;
}

bool SaveMgr::sub_7100E0A934(res::GameSaveData::Flag& entry,
                        const gdt::FlagT<sead::FixedSafeString<64>>* flag, u32 size,
                        u32 is_array) {
    const u32 length = flag->getValueRef().calcLength();
    if (entry._8 == 0)
        entry._8 = _e14;
    for (u32 i = 0; i < size; i += 4) {
        if (_e14 + 4 >= (_e2c == 0 ? _e10 : _e38))
            return false;
        const u32 hash = flag->getHash();
        std::memcpy(_e14 + (_e2c == 0 ? _e08 : _e30), &hash, sizeof(hash));
        _e14 += 4;
        if (_e14 + 4 >= (_e2c == 0 ? _e10 : _e38))
            return false;
        if (length < i) {
            std::memset(_e14 + (_e2c == 0 ? _e08 : _e30), 0, sizeof(u32));
        } else if (length < i + 4) {
            std::memset(_e14 + (_e2c == 0 ? _e08 : _e30), 0, sizeof(u32));
            std::memcpy(_e14 + (_e2c == 0 ? _e08 : _e30), flag->getValueRef().cstr() + i,
                        length - i);
        } else {
            std::memcpy(_e14 + (_e2c == 0 ? _e08 : _e30), flag->getValueRef().cstr() + i,
                        sizeof(u32));
        }
        _e14 += 4;
    }
    return true;
}

bool SaveMgr::sub_7100E0ABA0(res::GameSaveData::Flag& entry,
                        const gdt::FlagT<sead::FixedSafeString<256>>* flag, u32 size,
                        u32 is_array) {
    const u32 length = flag->getValueRef().calcLength();
    if (entry._8 == 0)
        entry._8 = _e14;
    for (u32 i = 0; i < size; i += 4) {
        if (_e14 + 4 >= (_e2c == 0 ? _e10 : _e38))
            return false;
        const u32 hash = flag->getHash();
        std::memcpy(_e14 + (_e2c == 0 ? _e08 : _e30), &hash, sizeof(hash));
        _e14 += 4;
        if (_e14 + 4 >= (_e2c == 0 ? _e10 : _e38))
            return false;
        if (length < i) {
            std::memset(_e14 + (_e2c == 0 ? _e08 : _e30), 0, sizeof(u32));
        } else if (length < i + 4) {
            std::memset(_e14 + (_e2c == 0 ? _e08 : _e30), 0, sizeof(u32));
            std::memcpy(_e14 + (_e2c == 0 ? _e08 : _e30), flag->getValueRef().cstr() + i,
                        length - i);
        } else {
            std::memcpy(_e14 + (_e2c == 0 ? _e08 : _e30), flag->getValueRef().cstr() + i,
                        sizeof(u32));
        }
        _e14 += 4;
    }
    return true;
}

}  // namespace ksys
