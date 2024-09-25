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
int MySort(lineStartLen* featureLine, int countLine);
int RevCompare(lineStartLen line_1, lineStartLen line_2);
int AddrLine(lineStartLen* featureLine, char* buffer, int sizeFile);
size_t SizeFile(FILE* fp);
int CountLine(char* buffer, size_t sizeFile);


int main()
    {
    FILE* fp = fopen("onegin.txt", "rb");

    if (!fp)
        {
        printf("OPENING_ERROR");
        return OPENING_ERROR;
        }

    size_t sizeFile = SizeFile(fp);

    char* buffer = (char*)calloc(sizeFile + 1, sizeof(char));
    if (buffer == NULL)
        {
        printf("MEMORY_ALLOCATION_ERROR");
        return MEMORY_ALLOCATION_ERROR;
        }

    size_t result = fread(buffer, sizeof(char), sizeFile, fp);

    if (sizeFile != result)
        {
        printf("READING_FILE_ERROR");
        return READING_ERROR;
        }

    fclose(fp);

    int countLine = CountLine(buffer, sizeFile);

    printf("%d\n\n", countLine);

    lineStartLen* featureLine = (lineStartLen*)calloc(countLine, sizeof(lineStartLen));

    if (featureLine == nullptr)
        {
        printf("ADDRESSES_DECLARATION_ERROR\n");
        return ADDR_DECLARATION_ERROR;
        }

    AddrLine(featureLine, buffer, sizeFile);

    MySort(featureLine, countLine);

    for (int i = 0; i < countLine; i++)    // make as func
        {
        printf("%s\n", featureLine[i].startStr);
        }

    // print default, then reverse and then original

    free(buffer);
    free(featureLine);
    printf("hskjhsfjsfhskjfhsd");
    }

int MySort(lineStartLen* featureLine, int countLine) // pass comparator as argument
    {
    assert(featureLine != nullptr);

    for (int i = 0; i < countLine - 1; i++)
        {
        for (int j = 0; j < countLine - i - 1; j++)
            {
            if (Compare(featureLine[j], featureLine[j+1]) == SWAP)
                {
                lineStartLen flam = featureLine[j];
                featureLine[j] = featureLine[j+1];
                featureLine[j+1] = flam;
                }
            }
        }

    return 0;
    }
////////////////////////////////////////////////





int Compare(lineStartLen line_1, lineStartLen line_2)
    {
    //assert(line_1 != nullptr);
    //assert(line_2 != nullptr);
    printf("sdgsd");
    int index_1 = 0;
    char* addr_1 = line_1.startStr;

    int index_2 = 0;
    char* addr_2 = line_2.startStr;


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

    //assert(addr_1 != nullptr);
    //assert(addr_2 != nullptr);    как избавиться от этого дерьма.................(

    while (index_1 != -1 && index_2 != -1)
        {
        while ((isalpha(addr_1[index_1]) == 0) && (index_1 >= 0))
            index_1--;  // TODO: make as func

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
    fseek(fp, 0, SEEK_END);
    size_t sizeFile = ftell(fp);
    rewind(fp);

    return sizeFile;
    }

int CountLine(char* buffer, size_t sizeFile)
    {
    int countLine = 0;
    for (size_t i = 0; i < sizeFile; i++)
        {
        if (buffer[i] == '\r')
            buffer[i] = '\0';
        if (buffer[i] == '\n')
            {
            ++countLine;
            buffer[i] = '\0';
            }
        }
    buffer[sizeFile] = '\0';

    return countLine;
    }


int AddrLine(lineStartLen* featureLine, char* buffer, int sizeFile)
    {
    char* start_line = buffer;
    int number_line = 0;

    for (int i = 0; i < sizeFile - 1; i++)
        {
        int len = 0;

        while (buffer[i] != '\0')  // why while here?
            {
            len++;                                                       // как убрать нулевые одреса когда несколько \n
            i++;                                                         //ломается на большом количестве \n
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

    return 0;
    }
