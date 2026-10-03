#pragma once

#include <container/seadListImpl.h>
#include <prim/seadBitUtil.h>
#include <prim/seadSafeString.h>

namespace gsys {

class Model;

// sic: this should be called IModelAccessHandle
class IModelAccesssHandle {
public:
    IModelAccesssHandle();
    virtual ~IModelAccesssHandle();

    bool search(const Model* p_model, const sead::SafeString& name);
    bool search();
    void remove();

    static constexpr size_t getListNodeOffset() { return offsetof(IModelAccesssHandle, mListNode); }

protected:
    virtual bool searchImpl_() = 0;
    virtual void removeImpl_() = 0;

    sead::SafeString mName = sead::SafeString::cEmptyString;
    const Model* mModel{};
    sead::ListNode mListNode;
};

struct BoneAccessKey {
    BoneAccessKey() { reset(); }

    void reset() {
        bone_index = -1;
        model_unit_index = -1;
    }

    bool isValid() const { return model_unit_index != -1 && bone_index != -1; }

    friend bool operator==(const BoneAccessKey& lhs, const BoneAccessKey& rhs) {
        static_assert(sizeof(BoneAccessKey) == sizeof(u32));
        return sead::BitUtil::bitCastPtr<u32>(&lhs) == sead::BitUtil::bitCastPtr<u32>(&rhs);
    }

    friend bool operator!=(const BoneAccessKey& lhs, const BoneAccessKey& rhs) {
        return !operator==(lhs, rhs);
    }

    s16 model_unit_index{};
    s16 bone_index{};
};

struct MaterialAccessKey {
    MaterialAccessKey() { reset(); }

    void reset() {
        material_index = -1;
        model_unit_index = -1;
    }

    bool isValid() const { return model_unit_index != -1 && material_index != -1; }

    s16 model_unit_index{};
    s16 material_index{};
};

class BoneAccessKeyEx : public IModelAccesssHandle {
public:
    BoneAccessKeyEx();
    ~BoneAccessKeyEx() override;

    using IModelAccesssHandle::search;
    bool search(const Model* p_model, const BoneAccessKey& key);

    bool isValid() const { return mKey.isValid(); }

    BoneAccessKey& getKey() { return mKey; }
    const BoneAccessKey& getKey() const { return mKey; }

protected:
    bool searchImpl_() override;
    void removeImpl_() override;

    BoneAccessKey mKey;
};

class MaterialAccessKeyEx : public IModelAccesssHandle {
public:
    MaterialAccessKeyEx();
    ~MaterialAccessKeyEx() override;

    bool isValid() const { return mKey.isValid(); }

    MaterialAccessKey& getKey() { return mKey; }
    const MaterialAccessKey& getKey() const { return mKey; }

protected:
    bool searchImpl_() override;
    void removeImpl_() override;

    MaterialAccessKey mKey;
};

}  // namespace gsys
