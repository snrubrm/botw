#pragma once

#include <container/seadOffsetList.h>
#include <heap/seadHeap.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Utils/Types.h"
#include "KingSystem/Resource/resUnk_71024F9D48.h"
#include "KingSystem/Resource/resBfRes.h"

namespace ksys::res {

// TODO: very incomplete (vtable 0x71251aad8; the size is unknown)
class TextureHandleList {
public:
    // 0x71012bd610 (CSV TextureHandleList::ctor)
    explicit TextureHandleList(sead::Heap* heap);
    virtual ~TextureHandleList();

    // Vtable 0x710251aa90; the list node is at +0xa0.
    class Entry {
    public:
        Entry();
        virtual ~Entry();

        static constexpr size_t getListNodeOffset() { return 0xa0; }

        // 0x71012bd52c whether the list node is linked.
        bool isLinked() const;
        bool sub_71012BD330() const;
        void sub_71012BD338();
        void* sub_71012BD4D8() const;
        // 0x71012bd4e0 releases the entry (if flag byte +8 is set).
        void sub_71012BD4E0();

        class Unk18 {
        public:
            // Slot 0 is called by sub_71012BD4E0 with this entry.
            virtual void m0(Entry* entry) = 0;
        };

        // Native ctor 12BD24C constructs this callback at +20 and stores the owner at +38.
        class Callback : public Unk_71024f9d68 {
        public:
            explicit Callback(Entry* owner) : mOwner(owner) {}
            ~Callback() override = default;
            void m2(const void* arg) override;
            void m3(const void* arg) override;
            void m4(const void* arg) override;
            Entry* mOwner;
        };

        bool _8;
        u8 _9[7];
        void* _10;
        Unk18* _18;
        Callback _20{this};
        Unk_71024F9D48 _40;
        sead::ListNode mListNode;
    };

    // 0x71012bd69c (CSV unnamed): sets the list node offset and registers the list as the instance.
    bool init();
    // 0x71012bd73c / 0x71012bd790: add / remove an entry under the lock.
    void add(Entry* entry);
    void remove(Entry* entry);
    // 0x71012bd6bc: releases and unlinks every entry under the lock.
    void sub_71012BD6BC();

    // 0x71012bd5dc stores the instance pointer.
    static void setInstance(TextureHandleList* list);
    static TextureHandleList* sInstance;

private:
    sead::CriticalSection mCS;
    sead::OffsetList<Entry> mList;
};

KSYS_CHECK_SIZE_NX150(TextureHandleList::Entry, 0xb0);

}  // namespace ksys::res
