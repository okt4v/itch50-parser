#include <cstdint>
#include <cstdio>
#include <fstream>
#include <map>
#include <vector>

int main(int argc, char **argv) {
  if (argc != 2) {
    std::fprintf(stderr, "usage: %s <itch_file>\n", argv[0]);
    return 1;
  }

  std::ifstream file(argv[1], std::ios::binary);
  if (!file) {
    std::fprintf(stderr, "cannot open %s\n", argv[1]);
    return 1;
  }

  std::map<char, uint64_t> counts;
  uint64_t total = 0;
  std::vector<char> payload;

  while (true) {
    unsigned char len_bytes[2];
    file.read(reinterpret_cast<char *>(len_bytes), 2);
    if (file.gcount() != 2)
      break;

    uint16_t len = (uint16_t(len_bytes[0]) << 8) | len_bytes[1];

    payload.resize(len);
    file.read(payload.data(), len);
    if (file.gcount() != len) {
      std::fprintf(stderr, "truncated message at count %llu\n",
                   (unsigned long long)total);
      return 1;
    }

    ++counts[payload[0]];
    ++total;
  }

  std::printf("total messages: %llu\n", (unsigned long long)total);
  for (auto [type, n] : counts)
    std::printf("  %c : %llu\n", type, (unsigned long long)n);
  return 0;
}
