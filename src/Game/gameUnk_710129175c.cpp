#include "Game/gameGraphics.h"

// Graphics' render-record TUs (0x71012915bc .. 0x71012955xx). Unk_710129175c and Unk_710129421c
// are constructed by gameGraphics.cpp's initializer but their methods live here.

Unk_710129175c::Unk_710129175c() : _8(0), mRecords(), mPage(), _260() {}
Unk_710129175c::~Unk_710129175c() = default;

void Unk_710129175c::sub_71012920C4(s32 index) {
    mRecords[index]._1ff4 = 1;
}

// NON_MATCHING: the original stores the four bounds floats directly; sead::BoundBox2::set (our only
// public way in) also normalises min / max, which costs four fcmp/fcsel.
void Unk_710129175c::sub_710129276C(s32 index, Result* result) {
    const Record& record = mRecords[index];
    result->_0 = record._1f98;
    result->bounds.set(record._1fa0, record._1fa4, record._1fa8, record._1fac);
    result->_18 = record._1fc8;
    result->_1c._0.x = record._1fd0;
    result->_1c._0.y = record._1fd4;
    result->_1c._0.z = record._1fd8;
    result->_1c._c = record._1fdc;
    result->_2c = record._1fcc;
}

void Unk_710129421c::sub_71012955AC(f32 value, s32 index) {
    mEntries[index]._7e4 = value;
}

