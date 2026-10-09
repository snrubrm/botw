#pragma once

class Unk_710245bee0;

namespace uking {

// Vtable 0x710245bf10 has only the two destructor slots, with no RTTI interface.
// The constructor at 0x71007cbe90 writes that vptr; remaining layout is unrecovered.
class StageFactory {
public:
    StageFactory();
    virtual ~StageFactory();

    // 0x71007cbeac, declared only: fills the stage output in the polymorphic binder request.
    void create(Unk_710245bee0* request);
};

}  // namespace uking
