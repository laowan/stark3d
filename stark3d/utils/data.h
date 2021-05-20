#pragma once

#include "global.h"

#include <string>

SK_BEGIN_NAMESPACE

class Data
{
    friend class Properties;

public:
    /**
     * This parameter is defined for convenient reference if a null Data object is needed.
     */
    static const Data Null;

    /**
     * Constructor of Data.
     */
    Data();

    /**
     * Copy constructor of Data.
     */
    Data(const Data& other);

    /**
     * Copy constructor of Data.
     */
    Data(Data&& other);

    /**
     * Destructor of Data.
     */
    ~Data();

    /**
     * Overloads of operator=.
     */
    Data& operator= (const Data& other);

    /**
     * Overloads of operator=.
     */
    Data& operator= (Data&& other);

    /**
     * Gets internal bytes of Data. It will return the pointer directly used in Data, so don't delete it.
     *
     * @return Pointer of bytes used internal in Data.
     */
    unsigned char* getBytes() const;

    /**
     * Gets the size of the bytes.
     *
     * @return The size of bytes of Data.
     */
    uint64 getSize() const;

    /** Copies the buffer pointer and its size.
     *  @note This method will copy the whole buffer.
     *        Developer should free the pointer after invoking this method.
     *  @see Data::fastSet
     */
    void copy(const unsigned char* bytes, const uint64 size);

    /** Fast set the buffer pointer and its size. Please use it carefully.
     *  @param bytes The buffer pointer, note that it have to be allocated by 'malloc' or 'calloc',
     *         since in the destructor of Data, the buffer will be deleted by 'free'.
     *  @note 1. This method will move the ownship of 'bytes'pointer to Data,
     *        2. The pointer should not be used outside after it was passed to this method.
     *  @see Data::copy
     */
    void fastSet(unsigned char* bytes, const uint64 size);

    /**
     * Clears data, free buffer and reset data size.
     */
    void clear();

    /**
     * Check whether the data is null.
     *
     * @return True if the Data is null, false if not.
     */
    bool isNull() const;

    /**
     * Get the internal buffer of data and set data to empty state.
     *
     * The ownership of the buffer removed from the data object.
     * That is the user have to free the returned buffer.
     * The data object is set to empty state, that is internal buffer is set to nullptr
     * and size is set to zero.
     * Usage:
     * @code
     *  Data d;
     *  // ...
     *  OFUInt64 size;
     *  unsigned char* buffer = d.takeBuffer(&size);
     *  // use buffer and size
     *  free(buffer);
     * @endcode
     *
     * @param size Will fill with the data buffer size in bytes, if you do not care buffer size, pass nullptr.
     * @return the internal data buffer, free it after use.
     */
    unsigned char* takeBuffer(uint64* size);

    // ---- stream operator ----

    bool eof() const;
    bool good() const;
    uint64 gcount() const;
    uint64 tellg() const;
    // dir same as std::stream::beg/cur/end
    bool seekg(uint64 pos, int dir = 0);

    //template<typename T>
    //void read(T& t)
    //{
    //    if (eof())
    //    {
    //        //OF_LOGE("Data::read failed, Premature end of array!");
    //        throw std::runtime_error("Data::read failed, Premature end of array!");
    //    }

    //    if ((_index + sizeof(T)) > _size)
    //        throw std::runtime_error("Premature end of array!");

    //    memcpy((void*)(&t), &_bytes[_index], sizeof(T));

    //    //old::swap(t, m_same_type);

    //    _index += sizeof(T);
    //    _gcnt = sizeof(T);
    //}
    //void read(typename std::vector<char>& vec);
    void read(char* p, size_t size);
    void read(std::string& str, const unsigned int size);
    // same as fgets: get line end with '\n'(without '\' in str, fill '\0' to last char)
    void readLine(char* str, size_t maxSize);

private:
    void move(Data& other);

private:
    unsigned char* _bytes;
    uint64 _size;
    size_t _index;
    size_t _gcnt;
};

SK_END_NAMESPACE