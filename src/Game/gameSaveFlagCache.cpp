#include "Game/gameSaveSystem.h"

namespace uking {

void sub_71008FCF34(sead::Buffer<SaveFlagCache::Entry0>* buffer);
void sub_71008FD050(sead::Buffer<SaveFlagCache::Entry1>* buffer);
void sub_71008FD16C(sead::Buffer<SaveFlagCache::Entry2>* buffer);
void sub_71008FD414(sead::Buffer<SaveFlagCache::Entry3>* buffer);
void sub_71008FD634(sead::Buffer<SaveFlagCache::Entry4>* buffer);

void SaveFlagCache::sub_710090CDA8() {
    _0 = true;
    sub_71008FCF34(&_8);
    sub_71008FD050(&_18);
    sub_71008FD16C(&_28);
    sub_71008FD414(&_38);
    sub_71008FD634(&_48);
}

void SaveFlagCache::sub_710090CDF4() {
    if (!_0)
        return;
    auto* manager = ksys::gdt::Manager::instance();
    if (!manager)
        return;
    for (const auto& entry : _8)
        manager->setBool(entry.value, entry.handle);
    for (const auto& entry : _18)
        manager->setS32(entry.value, entry.handle);
    for (const auto& entry : _28)
        for (const auto& value : entry.values)
            manager->setS32(value.value, entry.handle, value.index);
    for (const auto& entry : _38)
        for (const auto& value : entry.values)
            manager->setStr64(value.value.cstr(), entry.handle, value.index);
    for (const auto& entry : _48)
        for (const auto& value : entry.values)
            manager->setStr256(value.value.cstr(), entry.handle, value.index);
}

}  // namespace uking
