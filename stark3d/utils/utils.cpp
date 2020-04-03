#include "utils.h"
#include "external/edtaa3func/edtaa3func.h"
#include "stdlib.h"

unsigned char* makeDistanceMap(unsigned char *img, int width, int height, int distanceMapSpread)
{
    long pixelAmount = (width + 2 * distanceMapSpread) * (height + 2 * distanceMapSpread);

    short * xdist = (short *)malloc(pixelAmount * sizeof(short));
    short * ydist = (short *)malloc(pixelAmount * sizeof(short));
    double * gx = (double *)calloc(pixelAmount, sizeof(double));
    double * gy = (double *)calloc(pixelAmount, sizeof(double));
    double * data = (double *)calloc(pixelAmount, sizeof(double));
    double * outside = (double *)calloc(pixelAmount, sizeof(double));
    double * inside = (double *)calloc(pixelAmount, sizeof(double));
    long i, j;

    // Convert img into double (data) rescale image levels between 0 and 1
    long outWidth = width + 2 * distanceMapSpread;
    for (i = 0; i < width; ++i)
    {
        for (j = 0; j < height; ++j)
        {
            data[j * outWidth + distanceMapSpread + i] = img[j * width + i] / 255.0;
        }
    }

    width += 2 * distanceMapSpread;
    height += 2 * distanceMapSpread;

    // Transform background (outside contour, in areas of 0's)   
    computegradient(data, width, height, gx, gy);
    edtaa3(data, gx, gy, width, height, xdist, ydist, outside);
    for (i = 0; i< pixelAmount; i++)
        if (outside[i] < 0.0)
            outside[i] = 0.0;

    // Transform foreground (inside contour, in areas of 1's)   
    for (i = 0; i< pixelAmount; i++)
        data[i] = 1 - data[i];
    computegradient(data, width, height, gx, gy);
    edtaa3(data, gx, gy, width, height, xdist, ydist, inside);
    for (i = 0; i< pixelAmount; i++)
        if (inside[i] < 0.0)
            inside[i] = 0.0;

    // The bipolar distance field is now outside-inside
    double dist;
    /* Single channel 8-bit output (bad precision and range, but simple) */
    unsigned char *out = (unsigned char *)malloc(pixelAmount * sizeof(unsigned char));
    for (i = 0; i < pixelAmount; i++)
    {
        dist = outside[i] - inside[i];
        dist = 128.0 - dist * 16;
        if (dist < 0) dist = 0;
        if (dist > 255) dist = 255;
        out[i] = (unsigned char)dist;
    }
    /* Dual channel 16-bit output (more complicated, but good precision and range) */
    /*unsigned char *out = (unsigned char *) malloc( pixelAmount * 3 * sizeof(unsigned char) );
    for( i=0; i< pixelAmount; i++)
    {
    dist = outside[i] - inside[i];
    dist = 128.0 - dist*16;
    if( dist < 0.0 ) dist = 0.0;
    if( dist >= 256.0 ) dist = 255.999;
    // R channel is a copy of the original grayscale image
    out[3*i] = img[i];
    // G channel is fraction
    out[3*i + 1] = (unsigned char) ( 256 - (dist - floor(dist)* 256.0 ));
    // B channel is truncated integer part
    out[3*i + 2] = (unsigned char)dist;
    }*/

    free(xdist);
    free(ydist);
    free(gx);
    free(gy);
    free(data);
    free(outside);
    free(inside);

    return out;
}

#if defined(_WIN32) || defined(WIN32)
#include <Windows.h>

std::string GbkToUtf8(const std::string& strGbk)
{
    int len = MultiByteToWideChar(CP_ACP, 0, strGbk.c_str(), -1, NULL, 0);
    wchar_t *strUnicode = new wchar_t[len];
    wmemset(strUnicode, 0, len);
    MultiByteToWideChar(CP_ACP, 0, strGbk.c_str(), -1, strUnicode, len);

    len = WideCharToMultiByte(CP_UTF8, 0, strUnicode, -1, NULL, 0, NULL, NULL);
    char * strUtf8 = new char[len];
    WideCharToMultiByte(CP_UTF8, 0, strUnicode, -1, strUtf8, len, NULL, NULL);

    std::string strTemp(strUtf8);
    delete[]strUnicode;
    delete[]strUtf8;
    strUnicode = NULL;
    strUtf8 = NULL;
    return strTemp;
}

//UTF-8 to gbk
std::string Utf8ToGbk(const std::string& strUtf8)
{
    int len = MultiByteToWideChar(CP_UTF8, 0, strUtf8.c_str(), -1, NULL, 0);
    wchar_t * strUnicode = new wchar_t[len];
    wmemset(strUnicode, 0, len);
    MultiByteToWideChar(CP_UTF8, 0, strUtf8.c_str(), -1, strUnicode, len);

    len = WideCharToMultiByte(CP_ACP, 0, strUnicode, -1, NULL, 0, NULL, NULL);
    char *strGbk = new char[len];
    memset(strGbk, 0, len);
    WideCharToMultiByte(CP_ACP, 0, strUnicode, -1, strGbk, len, NULL, NULL);

    std::string strTemp(strGbk);
    delete[]strUnicode;
    delete[]strGbk;
    strUnicode = NULL;
    strGbk = NULL;
    return strTemp;
}

//gbk to unicode
std::wstring GbkToUnicode(const std::string& strGbk)
{
    int len = MultiByteToWideChar(CP_ACP, 0, strGbk.c_str(), -1, NULL, 0);
    wchar_t *strUnicode = new wchar_t[len];
    wmemset(strUnicode, 0, len);
    MultiByteToWideChar(CP_ACP, 0, strGbk.c_str(), -1, strUnicode, len);

    std::wstring strTemp(strUnicode);
    delete[]strUnicode;
    strUnicode = NULL;
    return strTemp;
}

// Unicode to gbk
std::string UnicodeToGbk(const std::wstring& strUnicode)
{
    int len = WideCharToMultiByte(CP_ACP, 0, strUnicode.c_str(), -1, NULL, 0, NULL, NULL);
    char *strGbk = new char[len];
    memset(strGbk, 0, len);
    WideCharToMultiByte(CP_ACP, 0, strUnicode.c_str(), -1, strGbk, len, NULL, NULL);

    std::string strTemp(strGbk);
    delete[]strGbk;
    strGbk = NULL;
    return strTemp;
}

int gettimeofday(struct timeval * tp, struct timezone * tzp)
{
    //
    // Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
    // This magic number is the number of 100 nanosecond intervals since January 1, 1601 (UTC)
    // until 00:00:00 January 1, 1970 
    //
    static const SKUInt64 EPOCH = ((SKUInt64)116444736000000000ULL);

    SYSTEMTIME  system_time;
    FILETIME    file_time;
    SKUInt64    time;

    GetSystemTime(&system_time);
    SystemTimeToFileTime(&system_time, &file_time);
    time = ((SKUInt64)file_time.dwLowDateTime);
    time += ((SKUInt64)file_time.dwHighDateTime) << 32;

    tp->tv_sec = (long)((time - EPOCH) / 10000000L);
    tp->tv_usec = (long)(system_time.wMilliseconds * 1000);
    return 0;
}
#endif

SKUInt64 CurrentTime()
{
    struct timeval tv;
    gettimeofday(&tv, 0);
    return (SKUInt64)tv.tv_sec * 1000ULL + tv.tv_usec / 1000;
}

#ifdef TEST
void Test()
    //1、ANSI/GBK编码
    std::string strGbk = "我";
    int num = strGbk.size();//获取两个字符数，也是我字所占的字节数

    unsigned char* p = (unsigned char*)strGbk.c_str();
    for (int i = 0; i < num; i++)
    {
        printf("%0x", *p);
        p++;
    }  //输出ced2 所以我的GBK编码是0xced2
    printf("\n");

    char gbk[] = { 0xce, 0xd2, 0x00 }; //加上0x00字符串结束符,不会输出乱码
    cout << gbk << endl;//输出汉字我


    //2、unicodde编码

    //方法一
    //wchar_t str = 0x6211;  
    //wcout.imbue(locale("chs")); 
    //wcout << str << endl;//输出汉字我

    //wchar_t c=L'我';
    //cout << hex << (short)c << endl<<endl;//输出unicodde编码 6211

    //方法二:
    wstring strUnicode = L"我";//转成unicode编码
    num = strUnicode.size() * 2;//乘以2，才是我所占的字节数
    p = (unsigned char*)strUnicode.c_str();
    for (int i = 0; i < num; i++)
    {
        printf("%0x", *p);
        p++;
    }  //输出1162 因为默认是小端模式，所以我的unicode编码是0x6211
    printf("\n");

    wchar_t s[2] = { 0x6211, 0x00 }; //加上0x00字符串结束符,不会输出乱码
    wstring str = (wchar_t*)s;
    cout << UnicodeToGbk(str) << endl;//需要先将unicode字符串转成gbk之后才能用cout输出


    //3、UTF-8编码
    string strUtf8 = GbkToUtf8("我");//转成utf8编码
    num = strUtf8.size();//num=3
    p = (unsigned char*)strUtf8.c_str();
    for (int i = 0; i < num; i++)
    {
        printf("%0x", *p);
        p++;
    }  //输出e68891
    printf("\n");

    char utf8[] = { 0xe6, 0x88, 0x91,0x00 }; //加上0x00字符串结束符,不会输出乱码
    cout << Utf8ToGbk(utf8) << endl;//需要先将utf8字符串转成gbk之后才能用cout输出
}
#endif