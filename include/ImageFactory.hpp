#ifndef IMAGEFACTORY_HPP
#define IMAGEFACTORY_HPP
#include "Texture.hpp"
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

string GetPureFilename(string filename);
string Num2Str(int num);

TextureSheet ReadImageFromImageSheet(string filename, int col, int row);
Texture ReadImage(string filename);

/**
 * @brief 图像仓库，用于保管所有的图像。需要长期使用的图像应当从这里面获得
 */
class ImageFactory{
public:
    static TextureSheet ReadSheet(string filename, int col, int row);
    static Texture ReadImage(string filename);
    static Texture GetTexture(string name);
    static TextureSheet GetSheet(string name);
    static void DeleteTexture(string name);
    static void DeleteSheet(string name);
    static void ClearTexture();
    static void ClearSheet();
    static size_t Size();
private:
    static map<string, Texture> images;
    static map<string, TextureSheet> sheets;
};

#endif
