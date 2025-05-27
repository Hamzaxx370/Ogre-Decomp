class PlayerCommand
{
    int Type;
    //ushort Unk;
    int Input;
    int AnimationEntry;
    int FollowUpIndex;
};
extern PlayerCommand* D_006BA350[];
class AnimProp
{
    int Unknown1;
    int Unknown2;
    float Unknown3;
    int AnimID;
    float Speed;
    int LoopFlag;
    int Flags[2];
    char Unknown[8];
    short Damage;
    short HitReaction;
};
AnimProp* Properties[] = {
};