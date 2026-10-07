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

}  // namespace uking
