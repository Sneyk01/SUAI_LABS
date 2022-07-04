//
// Created by prgle on 30.06.2022.
//

#include "WAV.h"

void readFmtChunk(fmtChunk& fmtCk, FILE* src) {
    fread(fmtCk.riff, 4, 1, src);
    fread(&fmtCk.riffSize, 4, 1, src);

    fread(&fmtCk.wave, 4, 1, src);
    fread(&fmtCk.fmt, 4, 1, src);
    fread(&fmtCk.fmtSize, 4, 1, src);

    fread(&fmtCk.waveForm.wFormatTag, 2, 1, src);
    fread(&fmtCk.waveForm.nChannels, 2, 1, src);
    fread(&fmtCk.waveForm.nSamplesPerSec, 4, 1, src);
    fread(&fmtCk.waveForm.nAvgBytesPerSec, 4, 1, src);
    fread(&fmtCk.waveForm.nBlockAlign, 2, 1, src);

    fread(&fmtCk.fmtSpec.nBitsPerSample, 2, 1, src);
}


void readDataChunk (dataChunk& dataCk, fmtChunk& fmtCk, FILE* src) {
    fread(&dataCk.ckId, 4, 1, src);
    fread(&dataCk.datSize, 4, 1, src);

    if (memcmp(&dataCk.ckId, "data", 4) != 0) {              // SKIP LIST
        fseek(src, (int32_t)dataCk.datSize, SEEK_CUR);
        fread(&dataCk.ckId, 4, 1, src);
        fread(&dataCk.datSize, 4, 1, src);
    }

    SHORT* samples = new SHORT[dataCk.datSize / (fmtCk.fmtSpec.nBitsPerSample / 8)];

    for (int i = 0; i < (dataCk.datSize) / (fmtCk.fmtSpec.nBitsPerSample / 8); i++)
        fread(&(samples[i]), (fmtCk.fmtSpec.nBitsPerSample / 8), 1, src);

    dataCk.data = samples;
}


void writeFmtChunk(fmtChunk& fmtCk, FILE* src) {
    fwrite(fmtCk.riff, 4, 1, src);
    fwrite(&fmtCk.riffSize, 4, 1, src);

    fwrite(&fmtCk.wave, 4, 1, src);
    fwrite(&fmtCk.fmt, 4, 1, src);
    fwrite(&fmtCk.fmtSize, 4, 1, src);

    fwrite(&fmtCk.waveForm.wFormatTag, 2, 1, src);
    fwrite(&fmtCk.waveForm.nChannels, 2, 1, src);
    fwrite(&fmtCk.waveForm.nSamplesPerSec, 4, 1, src);
    fwrite(&fmtCk.waveForm.nAvgBytesPerSec, 4, 1, src);
    fwrite(&fmtCk.waveForm.nBlockAlign, 2, 1, src);

    fwrite(&fmtCk.fmtSpec.nBitsPerSample, 2, 1, src);
}

void createNewWav(dataChunk& dataCk, fmtChunk& fmtCk, int percent, FILE* dst) {
    writeFmtChunk(fmtCk, dst);

    fwrite(&dataCk.ckId, 4, 1, dst);
    fwrite(&dataCk.datSize, 4, 1, dst);

    SHORT temp;
    for (int i = 0; i < dataCk.datSize / (fmtCk.fmtSpec.nBitsPerSample / 8); i++) {
        temp = (SHORT)(dataCk.data[i] * (1. - ((double)percent / 100)));

        if (fmtCk.fmtSpec.nBitsPerSample == 8)      // 8 bit sound
            temp = (uint8_t)((uint8_t)temp - (127 * ((double)percent / 100)));   // in 8 bits sound 0 == 128; 1 == 129; -1 == 127

        fwrite(&temp, (fmtCk.fmtSpec.nBitsPerSample / 8), 1, dst);
    }
}

