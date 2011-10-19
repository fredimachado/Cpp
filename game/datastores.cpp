/**
 * Studying C++
 * Simple Turn Based Battle Game
 * 
 * Based on TrinityCore's code
 * https://github.com/TrinityCore/TrinityCore
 *
 * Fredi Machado
 * http://github.com/fredi
 */

#include "datastores.h"

DataStorage<SpellEntry> sSpellStore(SpellEntryfmt);

uint32 DataFileCount = 0;

template<class T>
inline void LoadData(DataStorage<T>& storage, std::string const& dataPath, std::string const& filename)
{
    ++DataFileCount;
    std::string dataFilename = dataPath + filename;

    if (!storage.Load(dataFilename.c_str()))
    {
        // sort problematic dbc to (1) non compatible and (2) non-existed
        if (FILE* f = fopen(dataFilename.c_str(), "rb"))
        {
            printf("%s has invalid data.\n", dataFilename.c_str());
            fclose(f);
        }
        else
            printf("Data store %s doesn't exist.\n", dataFilename.c_str());
    }
}

void LoadDataStores(const std::string& dataPath)
{
    LoadData(sSpellStore, dataPath, "spells.dat");

    printf("Loaded %d data stores.\n", DataFileCount);
}

DataFileLoader::DataFileLoader()
{
    data = NULL;
    fieldsOffset = NULL;
}

bool DataFileLoader::Load(const char* fileName, char const* fmt)
{
    uint32 header;
    if (data)
    {
        delete[] data;
        data = NULL;
    }

    FILE* f = fopen(fileName, "rb");
    if (!f)
        return false;

    if (fread(&header, 4, 1, f) != 1)
    {
        fclose(f);
        return false;
    }

    if (header != 0x454D4147)                                // 'GAME'
    {
        fclose(f);
        return false;
    }

    if (fread(&recordCount, 4, 1, f) != 1)                   // Number of records
    {
        fclose(f);
        return false;
    }

    if (fread(&fieldCount, 4, 1, f) != 1)                    // Number of fields
    {
        fclose(f);
        return false;
    }

    if (fread(&recordSize, 4, 1, f) != 1)                    // Size of a record
    {
        fclose(f);
        return false;
    }

    fieldsOffset = new uint32[fieldCount];
    fieldsOffset[0] = 0;
    for (uint32 i = 1; i < fieldCount; ++i)
    {
        fieldsOffset[i] = fieldsOffset[i - 1];
        fieldsOffset[i] += sizeof(uint32);                   // 4 byte fields (int32/float)
    }

    data = new unsigned char[recordSize * recordCount];

    if (fread(data, recordSize * recordCount, 1, f) != 1)
    {
        fclose(f);
        return false;
    }

    fclose(f);

    return true;
}

DataFileLoader::~DataFileLoader()
{
    if (data)
        delete[] data;

    if (fieldsOffset)
        delete[] fieldsOffset;
}

DataFileLoader::Record DataFileLoader::getRecord(size_t id)
{
    assert(data);
    return Record(*this, data + id * recordSize);
}

uint32 DataFileLoader::GetFormatRecordSize(const char* format, int32* index_pos)
{
    uint32 recordsize = 0;
    int32 i = -1;
    for (uint32 x = 0; format[x]; ++x)
    {
        switch (format[x])
        {
            case FT_FLOAT:
                recordsize += sizeof(float);
                break;
            case FT_INT:
                recordsize += sizeof(uint32);
                break;
            case FT_IND:
                i = x;
                recordsize += sizeof(uint32);
                break;
            default:
                assert(false && "Unknown field format character in fmt");
                break;
        }
    }

    if (index_pos)
        *index_pos = i;

    return recordsize;
}

char* DataFileLoader::AutoProduceData(char const* format, uint32& records, char**& indexTable)
{
    typedef char* ptr;
    if (strlen(format) != fieldCount)
        return NULL;

    //get struct size and index pos
    int32 i;
    uint32 recordsize = GetFormatRecordSize(format, &i);

    if (i >= 0)
    {
        uint32 maxi = 0;
        //find max index
        for (uint32 y = 0; y < recordCount; ++y)
        {
            uint32 ind = getRecord(y).getUInt(i);
            if (ind > maxi)
                maxi = ind;
        }

        ++maxi;
        records = maxi;
        indexTable = new ptr[maxi];
        memset(indexTable, 0, maxi * sizeof(ptr));
    }
    else
    {
        records = recordCount;
        indexTable = new ptr[recordCount];
    }

    char* dataTable = new char[(recordCount) * recordsize];

    uint32 offset = 0;

    for (uint32 y = 0; y < recordCount; ++y)
    {
        if (i >= 0)
            indexTable[getRecord(y).getUInt(i)] = &dataTable[offset];
        else
            indexTable[y] = &dataTable[offset];

        for (uint32 x=0; x < fieldCount; ++x)
        {
            switch (format[x])
            {
                case FT_FLOAT:
                    *((float*)(&dataTable[offset])) = getRecord(y).getFloat(x);
                    offset += sizeof(float);
                    break;
                case FT_IND:
                case FT_INT:
                    *((uint32*)(&dataTable[offset])) = getRecord(y).getUInt(x);
                    offset += sizeof(uint32);
                    break;
                default:
                    assert(false && "Unknown field format character in fmt");
                    break;
            }
        }
    }

    return dataTable;
}
