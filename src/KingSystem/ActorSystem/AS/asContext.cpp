#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/AS/asElement.h"
#include "KingSystem/Resource/Actor/resResourceAS.h"

namespace ksys::as {

res::ASResource* Context::sub_7101258CC0() {
    if (res::AS* as = _d0->mAS)
        return as->getFirstResource();
    return nullptr;
}

act::Actor* Context::sub_7101258ABC() {
    return mList->_d8;
}

u8 Context::sub_7101258D1C(int index) {
    if (_921 & 2)
        return 0;
    return _d0->mIndexMap[index];
}

Context::Record* Context::sub_7101258CD4(int index) {
    Frame* frame = _d0;
    u8 record_index = 0;
    if (!(_921 & 2))
        record_index = frame->mIndexMap[index];
    return &frame->mRecords[record_index];
}

void Context::sub_7101258C1C() {
    _f4 = _f5;
    _d0 = _d8 ? _d8 : &mFrames[_f4];
}

// NON_MATCHING: the original decrements with a 32-bit `sub` and masks the stored byte afterwards (ours narrows to `add 0xff`)
void Context::sub_7101258C48() {
    _f4 = _f4 == 0 ? 2 : _f4 - 1;
    _d0 = &mFrames[_f4];
}

void Context::sub_7101258C80() {
    _f5 = _f5 + 1 == 3 ? 0 : _f5 + 1;
    _f4 = _f5;
    _d0 = _d8 ? _d8 : &mFrames[_f4];
}

int Context::sub_7101258E08() {
    return _d0->mRecords.size();
}

int Context::sub_7101258E14() {
    return _d0->mIndexMap.size();
}

int Context::sub_7101258E20() {
    return _d0->_10;
}

gsys::Model* Context::sub_7101258E2C() {
    return mList->_8;
}

void Context::sub_710125923C() {
    mUnk18 = sead::SafeString::cEmptyString;
    mUnk8 = sead::SafeString::cEmptyString;
}

}  // namespace ksys::as
