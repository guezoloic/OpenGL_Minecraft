#include "texture.hpp"

#include <filesystem>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace fs = std::filesystem;

Texture::Texture(const std::string& filename)
{
  fs::path path = fs::absolute(fs::current_path() / "res" / filename);

  int maxTextureSize;
  glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);

  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  int imgW, imgH, numColCh;
  stbi_set_flip_vertically_on_load(true);
  unsigned char* data =
      stbi_load(path.string().c_str(), &imgW, &imgH, &numColCh, 0);

  if (!data)
  {
    std::cerr << "Error loading image: " << path << std::endl;
    return;
  }

  int loadedTextureSize = imgW * imgH;

  if (loadedTextureSize >= maxTextureSize)
  {
    std::cerr << "Error: max texture size is " << maxTextureSize
              << " pixels, but image size = " << loadedTextureSize << std::endl;
    stbi_image_free(data);
    return;
  }

  GLenum format = (numColCh == 4) ? GL_RGBA : GL_RGB;

  glTexImage2D(GL_TEXTURE_2D, 0, format, imgW, imgH, 0, format,
               GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);
}

Texture::~Texture() { glDeleteTextures(1, &id); }

void Texture::bind(GLenum textureUnit) const
{
  glActiveTexture(textureUnit);
  glBindTexture(GL_TEXTURE_2D, id);
}

unsigned int Texture::getID() const { return id; }