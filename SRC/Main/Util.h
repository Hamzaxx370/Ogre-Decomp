class MTRandom
{
    public:
    MTRandom(unsigned int);
    virtual ~MTRandom();
    char DontKnowYet[0x9c4];
};

unsigned int _Random();

extern MTRandom* D_157454;