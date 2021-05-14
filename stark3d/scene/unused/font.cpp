#include "font.h"

SK_BEGIN_NAMESPACE

FontAtlas::FontAtlas(Font* font) : _font(font)
{

}

FontAtlas::~FontAtlas()
{
    SK_SAFE_DELETE(_font);
}

FontAtlasCache::~FontAtlasCache()
{
    for (auto&& atlas : _atlasMap)
    {
        SK_SAFE_DELETE(atlas.second);
    }
    _atlasMap.clear();
}

FontAtlas* FontAtlasCache::getFontAltas(const TTFConfig& config)
{
    bool useDistanceField = config.distanceFieldEnabled;
    char tmp[255];
    if (useDistanceField)
        snprintf(tmp, 255, "df_%.2f_%d_%s", config.fontSize, config.outlineSize, config.fontFilePath.c_str());
    else
        snprintf(tmp, 255, "%.2f_%d_%s", config.fontSize, config.outlineSize, config.fontFilePath.c_str());

    std::string atlasName = tmp;
    auto it = _atlasMap.find(atlasName);
    if (it == _atlasMap.end())
    {
        auto font = new FontFreeType;
        _atlasMap[atlasName] = font->createFontAtlas();
    }
    else
    {
        return it->second;
    }
}

FontAtlas* FontCharMap::createFontAtlas()
{
    return nullptr;
}

FontFreeType::FontFreeType()
{

}

FontFreeType::~FontFreeType()
{

}

FontAtlas* FontFreeType::createFontAtlas()
{
    _fontAtlas = new FontAtlas(this);
    return _fontAtlas;
}

SK_END_NAMESPACE