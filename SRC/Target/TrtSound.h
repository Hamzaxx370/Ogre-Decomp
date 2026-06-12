/*
    SaveData.h
*/

#ifndef TRTSOUND_H
#define TRTSOUND_H

#include "defines.h"

enum eSND_OUTPUT {
    SND_OUTPUT_0,
    SND_OUTPUT_1,
    SND_OUTPUT_2
};

enum eSND_PORT {
};

enum eSND_ICS_PORT {
};

/* no place for this yet */ 
typedef struct tag_VERTEX VERTEX;

class CTrtSound {
public:
    virtual void BeginScene() = 0;
    virtual void EndScene() = 0;
    virtual void Update() = 0;
    virtual void IsPlay(unsigned long) = 0;
    virtual void Play(unsigned long, unsigned long) = 0;
    virtual void PlayAuto(VERTEX *, unsigned long, unsigned long) = 0;
    virtual void Stop(unsigned long, unsigned long) = 0;
    virtual void StopAllForce() = 0;
    virtual void SetVol(unsigned long, long) = 0;
    virtual void SetPan(unsigned long, long) = 0;
    virtual void SetPitch(unsigned long, long) = 0;
    virtual void ResetPos(unsigned long, VERTEX *) = 0;
    virtual void CalcVol(VERTEX *, VERTEX *) = 0;
    virtual void CalcPan(VERTEX *) = 0;
    virtual void PackSet(unsigned long, eSND_PORT, void *, int) = 0;
    virtual void PackAutoSet(unsigned long, void *, int) = 0;
    virtual void PackReloadSet(unsigned long, void *, unsigned long, long *) = 0;
    virtual void PackFree(unsigned long, long) = 0;
    virtual void IsFinishPackSet() = 0;
    virtual void BoolChangeOK() = 0;
    virtual void SetFX(unsigned long, unsigned long) = 0;
    virtual void PortReset() = 0;
    virtual void FindPort(unsigned long) = 0;
    virtual void FindPack(unsigned long) = 0;
    virtual void SetTotalVol(long, unsigned long) = 0;
    virtual void EnemyRandomPlay(VERTEX *, unsigned long, unsigned char) = 0;
    virtual void YActRandomPlay(VERTEX *, unsigned long, unsigned long) = 0;
    virtual void StageSEPlay(unsigned long, long) = 0;
    virtual void StageSEPlayAuto(unsigned long, VERTEX *, long) = 0;
    virtual void AmbientPlay(unsigned long) = 0;
    virtual void AmbientVolume(float) = 0;
    virtual void AmbientStop() = 0;
    virtual void AmbientFadeout() = 0;
    virtual void SetSESetID(unsigned long) = 0;
    virtual void GetSESetID() = 0;
    virtual void SetFlag(unsigned long, int) = 0;
    virtual void SetICS(eSND_ICS_PORT, unsigned long) = 0;
    virtual void SetICSStop() = 0;
    virtual void SetICSControl(eSND_ICS_PORT, unsigned long) = 0;
    virtual void SoundRange() = 0;
    virtual void AmbientFileRequest() = 0;
    virtual void AmbientUpdate() = 0;
    virtual void IsAmbientFileOK() = 0;
    virtual void GetSequenceID(unsigned char * *) = 0;
    virtual void SndfIcsControl(long, long, short) = 0;
    virtual void SetOutput(eSND_OUTPUT) = 0;
    virtual void StopPcmTrans() = 0;
    
    static CTrtSound* m_pInstance;
};

#endif