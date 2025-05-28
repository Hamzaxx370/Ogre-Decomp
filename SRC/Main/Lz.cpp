#include"Lz.h"

int OGRE_LZDecode(CAVLZChunk** arg0) {
    int Size;
    CAVLZChunk* temp_a0;
    void* temp_v0;

    temp_a0 = *arg0;
    if ((temp_a0->Identifier[0] == 0x41) && (temp_a0->Identifier[1] == 0x56) && (temp_a0->Identifier[2] == 0x4C) && (temp_a0->Identifier[3] == 0x5A)) {
        Size = temp_a0->Size1;
    } else {
        Size = 0;
    }
    if (Size != 0) {
        temp_v0 = D_15356C(Size + 8);
        LZDecode(temp_v0, *arg0);
        (void*)*arg0 = temp_v0;
    }
    return Size;
}
