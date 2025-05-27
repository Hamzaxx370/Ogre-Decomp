#include"..\..\Libs\Player\LibPlayer.cpp"
void ModuleInit_Game()
{
    LibInit_Player(void)
    LibInit_Stalker(void)
    EnemyInterfaceInit(void)
    WandererInterfaceInit(void)
    return;
}