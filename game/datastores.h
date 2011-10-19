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

#ifndef _DATASTORES_H
#define _DATASTORES_H

#include "common.h"
#include <string>
#include <cstring>
#include <cassert>

enum
{
    FT_FLOAT  = 'f',                                        // float
    FT_INT    = 'i',                                        // uint32
    FT_IND    = 'n'                                         // the same, but parsed to data
};

void LoadDataStores(const std::string&);

class DataFileLoader
{
    public:
        DataFileLoader();
        ~DataFileLoader();

        bool Load(char const* fileName, char const* fmt);

        class Record
        {
            public:
                float getFloat(size_t field) const
                {
                    assert(field < file.fieldCount);
                    float val = *reinterpret_cast<float*>(offset + file.GetOffset(field));
                    return val;
                }
                uint32 getUInt(size_t field) const
                {
                    assert(field < file.fieldCount);
                    uint32 val = *reinterpret_cast<uint32*>(offset + file.GetOffset(field));
                    return val;
                }

            private:
                Record(DataFileLoader& file_, unsigned char* offset_): offset(offset_), file(file_) {}
                unsigned char* offset;
                DataFileLoader& file;

                friend class DataFileLoader;

        };

        // Get record by id
        Record getRecord(size_t id);
        /// Get begin iterator over records

        uint32 GetNumRows() const { return recordCount; }
        uint32 GetRowSize() const { return recordSize; }
        uint32 GetCols() const { return fieldCount; }
        uint32 GetOffset(size_t id) const { return (fieldsOffset != NULL && id < fieldCount) ? fieldsOffset[id] : 0; }
        bool IsLoaded() const { return data != NULL; }
        char* AutoProduceData(char const* fmt, uint32& count, char**& indexTable);
        static uint32 GetFormatRecordSize(char const* format, int32* index_pos = NULL);
    private:

        uint32 recordSize;
        uint32 recordCount;
        uint32 fieldCount;
        uint32* fieldsOffset;
        unsigned char* data;
};

template<class T>
class DataStorage
{
    public:
        explicit DataStorage(const char *f) :
            fmt(f), nCount(0), fieldCount(0), dataTable(NULL)
        {
            indexTable.asT = NULL;
        }
        ~DataStorage() { Clear(); }

        T const* LookupEntry(uint32 id) const
        {
            return (id >= nCount) ? NULL : indexTable.asT[id];
        }
        uint32  GetNumRows() const { return nCount; }
        char const* GetFormat() const { return fmt; }
        uint32 GetFieldCount() const { return fieldCount; }

        bool Load(char const* fn)
        {
            DataFileLoader data;
            // Check if load was sucessful, only then continue
            if (!data.Load(fn, fmt))
                return false;

            fieldCount = data.GetCols();
            dataTable = (T*)data.AutoProduceData(fmt, nCount, indexTable.asChar);

            return indexTable.asT != NULL;
        }

        void Clear()
        {
            if (!indexTable.asT)
                return;

            delete[] ((char*)indexTable.asT);
            indexTable.asT = NULL;
            delete[] ((char*)dataTable);
            dataTable = NULL;

            nCount = 0;
        }

    private:
        char const* fmt;
        uint32 nCount;
        uint32 fieldCount;

        union
        {
            T** asT;
            char** asChar;
        } indexTable;

        T* dataTable;
};

extern DataStorage<SpellEntry> sSpellStore;

char const SpellEntryfmt[] = "niiifffiii";

#endif
