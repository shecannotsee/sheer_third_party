#include <cstring>  // for memcpy
#include <iostream>
#include <sstream>
#include <string>

// Include zlib headers
#include <zlib.h>

// Function to compress data using zlib
std::string compress(const std::string& data) {
  z_stream zs;
  memset(&zs, 0, sizeof(zs));

  if (deflateInit(&zs, Z_BEST_COMPRESSION) != Z_OK) throw std::runtime_error("deflateInit failed while compressing.");

  zs.next_in  = (Bytef*)data.data();
  zs.avail_in = data.size();

  int ret;
  char outbuffer[32768];
  std::string outstring;

  // Retrieve the compressed bytes blockwise
  do {
    zs.next_out  = reinterpret_cast<Bytef*>(outbuffer);
    zs.avail_out = sizeof(outbuffer);

    ret = deflate(&zs, Z_FINISH);
    if (outstring.size() < zs.total_out) {
      // Append the block to the output string
      outstring.append(outbuffer, zs.total_out - outstring.size());
    }
  } while (ret == Z_OK);

  deflateEnd(&zs);

  if (ret != Z_STREAM_END) {  // an error occurred that was not EOF
    std::ostringstream errmsg;
    errmsg << "Exception during zlib compression: (" << ret << ") " << zs.msg;
    throw std::runtime_error(errmsg.str());
  }

  return outstring;
}

// Function to decompress data using zlib
std::string decompress(const std::string& compressed_data) {
  z_stream zs;
  memset(&zs, 0, sizeof(zs));

  if (inflateInit(&zs) != Z_OK) throw std::runtime_error("inflateInit failed while decompressing.");

  zs.next_in  = (Bytef*)compressed_data.data();
  zs.avail_in = compressed_data.size();

  int ret;
  char outbuffer[32768];
  std::string outstring;

  // Retrieve the decompressed bytes blockwise
  do {
    zs.next_out  = reinterpret_cast<Bytef*>(outbuffer);
    zs.avail_out = sizeof(outbuffer);

    ret = inflate(&zs, 0);

    if (outstring.size() < zs.total_out) {
      // Append the block to the output string
      outstring.append(outbuffer, zs.total_out - outstring.size());
    }

  } while (ret == Z_OK);

  inflateEnd(&zs);

  if (ret != Z_STREAM_END) {  // an error occurred that was not EOF
    std::ostringstream errmsg;
    errmsg << "Exception during zlib decompression: (" << ret << ") " << zs.msg;
    throw std::runtime_error(errmsg.str());
  }

  return outstring;
}

int main() {
  std::string original_data = "Hello, world! This is a test string for zlib compression.";

  // Compress the data
  std::string compressed_data = compress(original_data);
  std::cout << "Compressed data size: " << compressed_data.size() << " bytes" << std::endl;

  // Decompress the data
  std::string decompressed_data = decompress(compressed_data);
  std::cout << "Decompressed data: " << decompressed_data << std::endl;

  return 0;
}
