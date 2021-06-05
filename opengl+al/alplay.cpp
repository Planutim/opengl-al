#ifdef skiplol
#pragma once
#include <AL/al.h>
#include <AL/alext.h>
#include <cstdio>
#include <sndfile.h>
#include <climits>
#include <cinttypes>
#include <cstdlib>
#include <cassert>
#include <windows.h>
#include "sound.h"

int InitAL();
void CloseAL();
static ALuint LoadSound(const char* filename);
void al_nssleep(unsigned long nsec)
{
    Sleep(nsec / 1000000);
}

int main()
{
    ALuint source, buffer;
    ALfloat offset;
    ALenum state;

    if (InitAL() != 0)
        return 1;

    buffer = LoadSound("StarWars3.wav");
    if (!buffer)
    {
        CloseAL();
        return 1;
    }

    source = 0;
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, (ALint)buffer);
    assert(alGetError() == AL_NO_ERROR && "Failed to setup sound source");

    alSourcePlay(source);


    do {
        al_nssleep(100000000);
        alGetSourcei(source, AL_SOURCE_STATE, &state);

        alGetSourcef(source, AL_SEC_OFFSET, &offset);
        printf("\rOffset: %f ", offset);
        fflush(stdout);
    } while (alGetError() == AL_NO_ERROR && state == AL_PLAYING);

    printf("\n");

    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);

    CloseAL();

    return 0;
}
#endif
