#include "WAV.h"

int main(int args, char** argv) {

    char* error;
    int percent = strtol(argv[3], &error, 10);

    FILE* src = fopen(argv[1], "rb");

    fmtChunk fmtCk;
    readFmtChunk(fmtCk, src);

    dataChunk dataCk;
    readDataChunk(dataCk, fmtCk, src);

    FILE* dst = fopen(argv[2], "wb");
    createNewWav(dataCk, fmtCk, percent, dst);

    fclose(src);
    fclose(dst);

    std::cout << "All done! \n";
    return 0;
}
