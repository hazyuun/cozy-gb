#include <ROM.h>

ROM_header::ROM_header(unsigned char *raw, size_t size) {
  for (size_t pos = 0; pos < 0x150; pos++) {
    *(m_header + pos) = *(raw + pos);
  }
}
std::string ROM_header::getTitle() {
  std::string title;
  for (size_t i = 0x134; i < 0x143; i++) {
    title += m_header[i];
  }
  return title;
}

uint8_t ROM_header::getType() { return m_header[0x147]; }

Cartridge::~Cartridge() {}

MBC1_Cartridge::MBC1_Cartridge(unsigned char *raw, size_t size) {
  for (size_t pos = 0; pos < size; pos++) {
    *(m_rom + pos) = *(raw + pos);
  }
}
MBC1_Cartridge::~MBC1_Cartridge() {}
