#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order;
};

// Fill out this structure
struct HashType
{
	struct RecordType data;
	struct HashType* next;
};

// Compute the hash function
int hash(int x)
{
	return x % 33;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType **pHashArray, int hashSz)
{
	int i;

	for (i=0;i<hashSz;++i)
	{
		printf("index %d -> ", i);
		if(pHashArray[i] != NULL)
        {
            struct HashType* current = pHashArray[i];
            while(current != NULL)
            {
                printf("%d, %c, %d -> ", current->data.id, current->data.name, current->data.order);
                current = current->next;
            }
        }
        printf("NULL\n");
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	struct HashType** hashArr = ((struct HashType**) malloc(sizeof(struct HashType*)  * 33));

	for (int i = 0; i < 33; i++)
    {
        hashArr[i] = NULL;
    }


    for (int i = 0; i < recordSz; i++)
    {
        int index = hash(pRecords[i].id);

        struct HashType* current = (struct HashType*) malloc(sizeof(struct HashType));
        current->next = NULL;
        current->data = pRecords[i];

        if(hashArr[index] = NULL)
        {
            hashArr[index] = current;
        }

        else
        {
            struct HashType* prev = hashArr[index];
            current->next = prev;
            hashArr[index] = current;
        }
    }
    displayRecordsInHash(hashArr, 33);

}
