#include "ImageFactory.hpp"

string GetPureFilename(string filename){
    size_t pos = filename.find_last_of("/");
    if(pos==filename.npos)
        return filename;
    return filename.substr(pos+1);
}

string Num2Str(int num){
    string ret = "";
    char sign = num>0?0:'-';
    if(num<0)
        num = -num;
    while(num!=0){
        ret = static_cast<char>(num%10+'0')+ret;
        num /= 10;
    }
    ret = sign+ret;
    return ret;
}

TextureSheet ReadImageFromImageSheet(string filename, int col, int row){
    TextureSheet ts(filename, col, row);
    return ts;
}

Texture ReadImage(string filename){
    return Texture(filename);
}

map<string, Texture> ImageFactory::images;
map<string, TextureSheet> ImageFactory::sheets;

Texture ImageFactory::ReadImage(string filename){
    Texture tex(filename);
    if(!tex.Valid())
        return Texture::NullTexture;
    images[GetPureFilename(filename)] = tex;
    return tex;
}

TextureSheet ImageFactory::ReadSheet(string filename, int col, int row){
    TextureSheet ts(filename, col, row);
    sheets[GetPureFilename(filename)] = ts;
    return ts;
}

Texture ImageFactory::GetTexture(string name){
    auto it = images.find(name);
    if(it==images.end()){
        cerr<<"no image "<<name<<endl;
        return Texture::NullTexture;
    }
    return it->second;
}

TextureSheet ImageFactory::GetSheet(string name){
    auto it = sheets.find(name);
    if(it==sheets.end()){
        cerr<<"no image "<<name<<endl;
        return TextureSheet::NullSheet;
    }
    return it->second;
}

void ImageFactory::DeleteTexture(string name){
    for(auto it=images.begin();it!=images.end();it++)
        if(it->first==name){
            images.erase(it);
            break;
        }
}

void ImageFactory::DeleteSheet(string name){
    for(auto it=sheets.begin();it!=sheets.end();it++)
        if(it->first==name){
            sheets.erase(it);
            break;
        }
}

void ImageFactory::ClearSheet(){
    sheets.clear();
}

void ImageFactory::ClearTexture(){
    images.clear();
}

size_t ImageFactory::Size(){
    return images.size();
}
