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

struct lineStartEnd
    {
    char* startStr,
          endStr;
    };


int Compare(char* line_1, char* line_2);
int MySort(char** addr, int countLine);
int RevCompare(char* line_1, char* line_2);


int main()
    {
    FILE* fp = fopen("onegin.txt", "rb");

    if (!fp)
        {
        printf("OPENING_ERROR");
        return OPENING_ERROR;
        }

    fseek(fp , 0 , SEEK_END);
    long sizeFile = ftell(fp);
    rewind(fp);

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

    int countLine = 0;
    for (int i = 0; i < sizeFile; i++)
        {
        if (buffer[i] == '\r')
            buffer[i] = '\0';
        if (buffer[i] == '\n')
            {
            ++countLine;
            buffer[i] = '\0';
            }
        }
    buffer[sizeFile + 1] = '\0';


    char** addr = (char**)calloc(countLine, sizeof(char*));
    if (addr == NULL)
        {
        printf("ADDRESSES_DECLARATION_ERROR");
        return ADDR_DECLARATION_ERROR;
        }

    addr[0] = buffer;
    int countAddr = 1;
    for (int i = 1; i < sizeFile; i++)
        {

        if (buffer[i] != '\0' && buffer[i - 1] == '\0')
            {
            addr[countAddr] = buffer + i;
            ++countAddr;
            }
        }

    MySort(addr, countLine);

    for (int i = 0; i < countLine; i++)
        {
        printf("%s\n", addr[i]);
        }

    free(buffer);
    free(addr);

    }

int MySort(char** addr, int countLine)
    {
    assert(addr != nullptr);

    for (int i = 0; i < countLine - 2; i++)
        {
        for (int j = 0; j < countLine - i - 1; j++)
            {
            if (RevCompare(addr[j], addr[j+1]) == SWAP)
                {
                char* flam = addr[j];
                addr[j] = addr[j+1];
                addr[j+1] = flam;
                }
            }
        }
    }


int Compare(char* line_1, char* line_2)
    {
    assert(line_1 != nullptr);
    assert(line_2 != nullptr);

    int flag_l_1 = 0,
        flag_l_2 = 0;

    while (line_1[flag_l_1] != '\0' && line_2[flag_l_2] != '\0')
        {
        while (isalpha(line_1[flag_l_1]) == 0)
            flag_l_1++;

        while (isalpha(line_2[flag_l_2]) == 0)
            flag_l_2++;

        if (tolower(line_1[flag_l_1]) - tolower(line_2[flag_l_2]) > 0)
            return SWAP;

        if (tolower(line_1[flag_l_1]) - tolower(line_2[flag_l_2]) < 0)
            return GOOD_ORDER;
        flag_l_1++;
        flag_l_2++;
        }
    if (line_1[flag_l_1] == '\0' && line_2[flag_l_2] != '\0')
        return GOOD_ORDER;

    if (line_1[flag_l_1] != '\0' && line_2[flag_l_2] == '\0')
        return SWAP;

    if (line_1[flag_l_1] == '\0' && line_2[flag_l_2] == '\0')
        return EQUAL;
    }

int RevCompare(char* line_1, char* line_2)
    {
    assert(line_1 != nullptr);
    assert(line_2 != nullptr);

    int flag_l_1 = 0,
        flag_l_2 = 0;

    while (line_1[flag_l_1] != '\0')
        flag_l_1++;

    while (line_2[flag_l_2] != '\0')
        flag_l_2++;

    flag_l_1--;
    flag_l_2--;

    while (flag_l_1 != -1 && flag_l_2 != -1)
        {
        while ((isalpha(line_1[flag_l_1]) == 0) && (flag_l_1 >= 0))
            flag_l_1--;

        while ((isalpha(line_2[flag_l_2]) == 0) && (flag_l_2 >= 0))
            flag_l_2--;

        if (tolower(line_1[flag_l_1]) - tolower(line_2[flag_l_2]) > 0)
            return SWAP;

        if (tolower(line_1[flag_l_1]) - tolower(line_2[flag_l_2]) < 0)
            return GOOD_ORDER;

        if ((flag_l_1 == -1) && (flag_l_2 > -1))
            return GOOD_ORDER;

        if ((flag_l_2 == -1) && (flag_l_1 > -1))
            return SWAP;

        flag_l_1--;
        flag_l_2--;
        }
    }
