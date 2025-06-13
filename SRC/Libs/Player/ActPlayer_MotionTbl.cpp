class CPlayerCommand
{
    int Type;
    //ushort Unk;
    int Input;
    int AnimationEntry;
    int FollowUpIndex;
};
extern CPlayerCommand* D_006BA350[];
class CPlayerMotionProperty
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
CPlayerMotionProperty* Properties[] = {
};