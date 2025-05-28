#include"..\..\Libs\Player\LibPlayer.cpp"
#include"..\..\Libs\Stalker\LibStalker.cpp"
void ModuleInit_Game()
{
    LibInit_Player();
    LibInit_Stalker();
    EnemyInterfaceInit();
    WandererInterfaceInit();
    return;
}