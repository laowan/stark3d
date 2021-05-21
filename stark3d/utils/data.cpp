#include "utils/data.h"
#include <stdexcept>

SK_BEGIN_NAMESPACE

const Data Data::Null;

Data::Data() :
    _bytes(nullptr),
    _size(0),
    _index(0),
    _gcnt(0)
{
    printf("In the empty constructor of Data.");
}

Data::Data(Data&& other) :
    _bytes(nullptr),
    _size(0),
    _index(0),
    _gcnt(0)
{
    printf("In the move constructor of Data.");
    move(other);
}

Data::Data(const Data& other) :
    _bytes(nullptr),
    _size(0),
    _index(0),
    _gcnt(0)
{
    printf("In the copy constructor of Data.");
    copy(other._bytes, other._size);
}

Data::~Data()
{
    printf("deallocing Data: %p", this);
    clear();
}

Data& Data::operator= (const Data& other)
{
    printf("In the copy assignment of Data.");
    copy(other._bytes, other._size);
    return *this;
}

Data& Data::operator= (Data&& other)
{
    printf("In the move assignment of Data.");
    move(other);
    return *this;
}

void Data::move(Data& other)
{
    clear();

    _bytes = other._bytes;
    _size = other._size;

    other._bytes = nullptr;
    other._size = 0;
    other._index = 0;
    other._gcnt = 0;
}

bool Data::isNull() const
{
    return (_bytes == nullptr || _size == 0);
}

unsigned char* Data::getBytes() const
{
    return _bytes;
}

uint64 Data::getSize() const
{
    return _size;
}

void Data::copy(const unsigned char* bytes, const uint64 size)
{
    clear();

    if (size > 0)
    {
        _size = size;
        _bytes = (unsigned char*)malloc(sizeof(unsigned char) * _size);
        memcpy(_bytes, bytes, _size);
        _index = 0;
        _gcnt = 0;
    }
}

void Data::fastSet(unsigned char* bytes, const uint64 size)
{
    _bytes = bytes;
    _size = size;
    _index = 0;
    _gcnt = 0;
}

void Data::clear()
{
    if (_bytes)
    {
        free(_bytes);
        _bytes = nullptr;
    }
    _size = 0;
    _index = 0;
    _gcnt = 0;
}

unsigned char* Data::takeBuffer(uint64* size)
{
    auto buffer = getBytes();
    if (size)
        *size = getSize();
    fastSet(nullptr, 0);
    return buffer;
}

bool Data::eof() const
{
    return _index >= _size;
}

bool Data::good() const
{
    return !eof();
}

uint64 Data::gcount() const
{
    return _gcnt;
}

uint64 Data::tellg() const
{
    return _index;
}
bool Data::seekg(uint64 pos, int dir)
{
    uint64 tIdx = 0;
    if (dir == 0)
    {
        tIdx = pos;
    }
    else if (dir == 1)
    {
        tIdx = _index + pos;
    }
    else if (dir == 2)
    {
        tIdx = _size + pos;
    }

    /*if (tIdx >= _size)
        return false;*/

    _index = tIdx;
    return true;
}

//template<typename T>
//void Data::read(T& t)
//{
//    if (eof())
//    {
//        printf("Data::read failed, Premature end of array!");
//        throw std::runtime_error("Data::read failed, Premature end of array!");
//    }
//
//    if ((_index + sizeof(T)) > _size)
//        throw std::runtime_error("Premature end of array!");
//
//    memcpy(reinterpret_cast<void*>(&t), &_bytes[_index], sizeof(T));
//
//    //old::swap(t, m_same_type);
//
//    _index += sizeof(T);
//}

/*void Data::read(typename std::vector<char>& vec)
{
if (eof())
throw std::runtime_error("Premature end of array!");

if ((_index + vec.size()) > m_vec.size())
throw std::runtime_error("Premature end of array!");

memcpy(reinterpret_cast<void*>(&vec[0]), &m_vec[_index], vec.size());

_index += vec.size();
}*/

void Data::read(char* p, size_t size)
{
    if (eof())
    {
        printf("Data::read failed, Premature end of array!");
        throw std::runtime_error("Data::read failed, Premature end of array!");
    }

    if ((_index + size) > _size)
    {
        printf("Data::read failed, Premature end of array!");
        throw std::runtime_error("Data::read failed, Premature end of array!");
    }

    memcpy(reinterpret_cast<void*>(p), &_bytes[_index], size);

    _index += size;
    _gcnt = size;
}

void Data::read(std::string& str, const unsigned int size)
{
    if (eof())
    {
        printf("Data::read failed, Premature end of array!");
        throw std::runtime_error("Data::read failed, Premature end of array!");
    }

    if ((_index + size) > _size)
    {
        printf("Data::read failed, Premature end of array!");
        throw std::runtime_error("Data::read failed, Premature end of array!");
    }

    str.assign(_bytes[_index], size);

    _index += str.size();
    _gcnt = str.size();
}

void Data::readLine(char* str, size_t maxSize)
{
    if (eof())
    {
        printf("Data::readLine failed, Premature end of array!");
        throw std::runtime_error("Data::readLine failed, Premature end of array!");
    }

    int tIdx = _index;
    while (tIdx < _size && tIdx - _index < maxSize - 1 && _bytes[tIdx] != '\n')
    {
        tIdx += 1;
    }

    memcpy(reinterpret_cast<void*>(str), &_bytes[_index], tIdx - _index);
    str[tIdx - _index + 1] = '\0';

    _index += tIdx - _index;
    _gcnt = tIdx - _index;

    if (!eof() && _bytes[_index] == '\n')
    {
        _index += 1;
    }
}

SK_END_NAMESPACE