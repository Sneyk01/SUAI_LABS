//
// Created by prgle on 30.06.2022.
//

#ifndef LAB16_WAV_H
#define LAB16_WAV_H

#include <iostream>
#include <windows.h>
#include <cstdio>
#include <cstdlib>


typedef struct {
    WORD wFormatTag;
    WORD nChannels;
    DWORD nSamplesPerSec;
    DWORD nAvgBytesPerSec;
    WORD nBlockAlign;
} waveFormat;


typedef struct {
    WORD nBitsPerSample;
    //WORD cbSize;
} fmtSpecific;


typedef struct {
    BYTE riff[4];
    DWORD riffSize;

    BYTE wave[4];
    BYTE fmt[4];
    DWORD fmtSize;

    waveFormat waveForm;
    fmtSpecific fmtSpec;
} fmtChunk;


typedef struct {
    BYTE ckId[4];
    DWORD datSize;
    SHORT* data;    // word => unsigned!
} dataChunk;


void readFmtChunk(fmtChunk& fmtCk, FILE* src);
void readDataChunk(dataChunk& dataCk, fmtChunk& fmtCk, FILE* src);
void createNewWav(dataChunk& dataCk, fmtChunk& fmtCk, int percent, FILE* path);

#endif //LAB16_WAV_H
