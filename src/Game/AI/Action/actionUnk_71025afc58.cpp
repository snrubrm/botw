#include "Game/AI/Action/actionUnk_71025afc58.h"

bool Unk_71025afc58::getStaticParam(sead::SafeString* value, const sead::SafeString& key) const {
    return mOwner->getStaticParam(value, key);
}

bool Unk_71025afc58::getStaticParam(const int** value, const sead::SafeString& key) const {
    return mOwner->getStaticParam(value, key);
}

bool Unk_71025afc58::getStaticParam(const float** value, const sead::SafeString& key) const {
    return mOwner->getStaticParam(value, key);
}

bool Unk_71025afc58::getStaticParam(const sead::Vector3f** value,
                                    const sead::SafeString& key) const {
    return mOwner->getStaticParam(value, key);
}

bool Unk_71025afc58::getStaticParam(const bool** value, const sead::SafeString& key) const {
    return mOwner->getStaticParam(value, key);
}

bool Unk_71025afc58::getDynamicParam(int** value, const sead::SafeString& key) const {
    return mOwner->getDynamicParam_2(value, key);
}

bool Unk_71025afc58::getDynamicParam(sead::Vector3f** value, const sead::SafeString& key) const {
    return mOwner->getDynamicParam(value, key);
}

bool Unk_71025afc58::getDynamicParam(ksys::act::BaseProcHandle*** value,
                                     const sead::SafeString& key) const {
    return mOwner->getDynamicParam(value, key);
}
