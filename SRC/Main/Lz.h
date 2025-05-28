#include "..\Context.cpp"
class CAVLZChunk
{
    public:
    char Identifier[4];
    int Size1;
    int Size2;
};

int OGRE_LZDecode(CAVLZChunk **arg0);
void LZDecode(void*,void*);

