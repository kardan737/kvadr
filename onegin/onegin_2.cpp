#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>


enum CompareAction
    {
    SWAP       = 0,
    GOOD_ORDER = 1,
    EQUAL      = 2,
    };

enum ErrorType
    {
    OPENING_ERROR           = 1,
    MEMORY_ALLOCATION_ERROR = 2,
    READING_ERROR           = 3,
    ADDR_DECLARATION_ERROR  = 4,
    };

struct lineStartLen
    {
    char* startStr;
    size_t   lenStr;
    };



int Compare(lineStartLen line_1, lineStartLen line_2);
int MySort(lineStartLen* featureLine, int countLine, int (*Comparee)(lineStartLen line_1, lineStartLen line_2));
int RevCompare(lineStartLen line_1, lineStartLen line_2);
lineStartLen* AddrLine(char* buffer, int sizeFile, int countLine);
size_t SizeFile(FILE* fp);
int CountLine(char* buffer, size_t sizeFile);
void Record(FILE* sorted, int countLine, lineStartLen* featureLine);
char* buffering(int sizeFile, FILE* fp);
lineStartLen* RememberAddr(lineStartLen* featureLine, int countLine);



int main()
    {
    FILE* fp = fopen("onegin.txt", "rb");
    FILE* sorted = fopen("onegin_sorted.txt", "w+");

    if (!fp)
        {
        printf("OPENING_ERROR");
        return OPENING_ERROR;
        }

    size_t sizeFile = SizeFile(fp);

    char* buffer = buffering(sizeFile, fp);

    fclose(fp);

    int countLine = CountLine(buffer, sizeFile);

    lineStartLen* featureLine = AddrLine(buffer, sizeFile, countLine);

    lineStartLen* originalAddr = RememberAddr(featureLine, countLine);

    MySort(featureLine, countLine, &Compare);
    Record(sorted, countLine, featureLine);

    MySort(featureLine, countLine, &RevCompare);
    Record(sorted, countLine, featureLine);

    Record(sorted, countLine, originalAddr);

    free(buffer);
    free(featureLine);
    free(originalAddr);
    }


int MySort(lineStartLen* featureLine, int countLine, int (*Comparee)(lineStartLen line_1, lineStartLen line_2))
    {
    assert(featureLine != nullptr);
    assert(Comparee != nullptr);

    for (int i = 0; i < countLine - 1; i++)
        {
        for (int j = 0; j < countLine - i - 1; j++)
            {
            if (Comparee(featureLine[j], featureLine[j+1]) == SWAP)
                {
                lineStartLen flam = featureLine[j];
                featureLine[j] = featureLine[j+1];
                featureLine[j+1] = flam;
                }
            }
        }

    return 0;
    }


int Compare(lineStartLen line_1, lineStartLen line_2)
    {

    int index_1 = 0;
    char* addr_1 = line_1.startStr;

    int index_2 = 0;
    char* addr_2 = line_2.startStr;

    assert(addr_1 != nullptr);
    assert(addr_2 != nullptr);

    while (addr_1[index_1] != '\0' && addr_2[index_2] != '\0')
        {
        while (isalpha(addr_1[index_1]) == 0)
            index_1++;

        while (isalpha(addr_2[index_2]) == 0)
            index_2++;

        if (tolower(addr_1[index_1]) - tolower(addr_2[index_2]) > 0)
            return SWAP;

        if (tolower(addr_1[index_1]) - tolower(addr_2[index_2]) < 0)
            return GOOD_ORDER;
        index_1++;
        index_2++;
        }

    if (addr_1[index_1] == '\0' && addr_2[index_2] != '\0')
        return GOOD_ORDER;

    if (addr_1[index_1] != '\0' && addr_2[index_2] == '\0')
        return SWAP;

    if (addr_1[index_1] == '\0' && addr_2[index_2] == '\0')
        return EQUAL;

    return 0;
    }


int RevCompare(lineStartLen line_1, lineStartLen line_2)
    {

    int index_1 = line_1.lenStr - 1;
    char* addr_1 = line_1.startStr;

    int index_2 = line_2.lenStr - 1;
    char* addr_2 = line_2.startStr;

    assert(addr_1 != nullptr);
    assert(addr_2 != nullptr);

    while (index_1 != -1 && index_2 != -1)
        {
        while ((isalpha(addr_1[index_1]) == 0) && (index_1 >= 0))
            index_1--;                                          // TODO: make as func

        while ((isalpha(addr_2[index_2]) == 0) && (index_2 >= 0))
            index_2--;

        if ((tolower(addr_1[index_1]) - tolower(addr_2[index_2]) > 0) ||
            ((index_2 == -1) && (index_1 > -1)))

            return SWAP;

        if ((tolower(addr_1[index_1]) - tolower(addr_2[index_2]) < 0) ||
            ((index_1 == -1) && (index_2 > -1)))

            return GOOD_ORDER;

        index_1--;
        index_2--;
        }

    return 0;
    }


size_t SizeFile(FILE* fp)
    {
    assert(fp != nullptr);

    fseek(fp, 0, SEEK_END);
    size_t sizeFile = ftell(fp);
    rewind(fp);

    return sizeFile;
    }


int CountLine(char* buffer, size_t sizeFile)
    {
    assert(buffer != nullptr);

    int countLine = 0;
    bool notEmptyStr = false;
    for (size_t i = 0; i < sizeFile; i++)
        {
        if (isalpha(buffer[i]) != false)
            notEmptyStr = true;

        if (buffer[i] == '\r')
            buffer[i] = '\0';

        if (buffer[i] == '\n')
            {
            if (notEmptyStr == true)
                {
                ++countLine;
                notEmptyStr = false;
                }
            buffer[i] = '\0';
            }
        }
    buffer[sizeFile] = '\0';

    return countLine;
    }


lineStartLen* AddrLine(char* buffer, int sizeFile, int countLine)
    {
    assert(buffer != nullptr);

    lineStartLen* featureLine = (lineStartLen*)calloc(countLine, sizeof(lineStartLen));

    if (featureLine == nullptr)
        {
        printf("ADDRESSES_DECLARATION_ERROR\n");

        }

    char* start_line = buffer;
    int number_line = 0;

    for (int i = 0; i < sizeFile - 1; i++)
        {
        int len = 0;

        while (buffer[i] != '\0')
            {
            len++;
            i++;
            }

        if (len > 0)
            {
            featureLine[number_line] = {start_line, len};
            number_line++;
            len = 0;
            }

        if (buffer[i] == '\0' && buffer[i+1] != '\0')
            start_line = buffer + i + 1;
        }

    return featureLine;
    }

void Record(FILE* sorted, int countLine, lineStartLen* featureLine)
    {
    assert(sorted != nullptr);

    fprintf(sorted, "//////////////////////////////////////////\n");

    for (int i = 0; i < countLine; i++)
        fprintf(sorted, "%s\n", featureLine[i].startStr);

    fprintf(sorted, "//////////////////////////////////////////\n");
    }

char* buffering(int sizeFile, FILE* fp)
    {
    assert(fp != nullptr);

    char* buffer = (char*)calloc(sizeFile + 1, sizeof(char));
    if (buffer == NULL)
        {
        printf("MEMORY_ALLOCATION_ERROR");
        exit(EXIT_FAILURE);
        }

    size_t result = fread(buffer, sizeof(char), sizeFile, fp);

    if (sizeFile != result)
        {
        printf("READING_FILE_ERROR");
        exit(EXIT_FAILURE);
        }

    return buffer;
    }

lineStartLen* RememberAddr(lineStartLen* featureLine, int countLine)
    {
    assert(featureLine != nullptr);

    lineStartLen* originalAddr = (lineStartLen*)calloc(countLine, sizeof(lineStartLen));

    if (originalAddr == nullptr)
        {
        printf("ADDRESSES_DECLARATION_ERROR\n");
        exit(EXIT_FAILURE);
        }

    for (int i = 0; i < countLine; i++)
        {
        originalAddr[i].startStr = featureLine[i].startStr;
        }

    return originalAddr;
    }
