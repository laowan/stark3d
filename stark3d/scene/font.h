#ifndef SK_FONT_H
#define SK_FONT_H

#include "global.h"
#include <string>
#include <unordered_map>

SK_BEGIN_NAMESPACE

struct TTFConfig
{
    std::string fontFilePath;
    float fontSize;
    int outlineSize;
    bool bold;
    bool distanceFieldEnabled;
    TTFConfig() : fontSize(0.0f), outlineSize(0), bold(false), distanceFieldEnabled(false) {}
};

class Font;
class FontAtlas
{
public:
    FontAtlas(Font* font) {}
    ~FontAtlas() {}
private:
    Font* _font;
};

class FontAtlasCache
{
public:
    FontAtlasCache() {}
    ~FontAtlasCache() {}

    FontAtlas* getFontAltas(const TTFConfig& config) { return nullptr; }

private:
    std::unordered_map<std::string, FontAtlas*> _atlasMap;
};

class Font
{
public:
    virtual FontAtlas* createFontAtlas() = 0;
};

class FontCharMap : public Font
{
public:
    virtual FontAtlas* createFontAtlas() override;
};

class FontFreeType : public Font
{
public:
    FontFreeType();
    ~FontFreeType();
    virtual FontAtlas* createFontAtlas() override;
private:
    FontAtlas* _fontAtlas;
};

SK_END_NAMESPACE
#endif