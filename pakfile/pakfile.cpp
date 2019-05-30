#include "pakfile.h"
#include <iostream>
#include <zlib.h>
#include <string>
#include <QDebug>
#include <QProcess>
#include <QStringList>
#include <string>

// using namespace std;

pakfile::pakfile(/* args */)
{
}

pakfile::~pakfile()
{
}

QByteArray pakfile::arjCompress(const QByteArray &data, std::string password)
{
  throw std::runtime_error(std::string(__PRETTY_FUNCTION__) + std::string("unimplemented"));
}

QByteArray pakfile::arjUncompress(std::string filename, std::string password)
{
  // QByteArray result;

  QProcess arjProcess;
  QString exec = "/usr/bin/arj";
  QStringList params;
  params  << "p" 
          << "-y" 
          << QString::fromStdString(std::string("-g"+password))
          << QString::fromStdString(filename);
    
  arjProcess.start(exec, params);
  arjProcess.waitForFinished(); // sets current thread to sleep and waits for pingProcess end
  QString    error(arjProcess.readAllStandardError());
  QByteArray result(arjProcess.readAllStandardOutput());

  // qInfo() << error;
  
  return result;
}

QByteArray pakfile::zlibCompress(const QByteArray &data)
{
  throw std::runtime_error(std::string(__PRETTY_FUNCTION__) + std::string("unimplemented"));
}

QByteArray pakfile::zlibUncompress(const QByteArray &data)
{
  if (data.size() <= 4)
  {
    qWarning("gUncompress: Input data is truncated");
    return QByteArray();
  }

  QByteArray result;

  int ret;
  z_stream strm;
  static const int CHUNK_SIZE = 1024;
  char out[CHUNK_SIZE];

  /* allocate inflate state */
  strm.zalloc = Z_NULL;
  strm.zfree = Z_NULL;
  strm.opaque = Z_NULL;
  strm.avail_in = data.size();
  strm.next_in = (Bytef *)(data.data());

  ret = inflateInit2(&strm, 15 + 32); // gzip decoding
  if (ret != Z_OK) {
    zErr(ret);
    return QByteArray();
  }

  // run inflate()
  do
  {
    strm.avail_out = CHUNK_SIZE;
    strm.next_out = (Bytef *)(out);

    ret = inflate(&strm, Z_NO_FLUSH);
    Q_ASSERT(ret != Z_STREAM_ERROR); // state not clobbered

    switch (ret)
    {
    case Z_NEED_DICT:
      ret = Z_DATA_ERROR; // and fall through
    case Z_DATA_ERROR:
    case Z_MEM_ERROR:
      (void)inflateEnd(&strm);
      zErr(ret);
      return QByteArray();
    }

    result.append(out, CHUNK_SIZE - strm.avail_out);
  } while (strm.avail_out == 0);

  // clean up and return
  inflateEnd(&strm);
  return result;
}

/* report a zlib or i/o error */
void pakfile::zErr(int ret)
{
    std::string errorText;

    switch (ret) {
    case Z_ERRNO:
        if (ferror(stdin))
            errorText = "error reading stdin";
        if (ferror(stdout))
            errorText = "error writing stdout";
        break;
    case Z_STREAM_ERROR:
        errorText = "invalid compression level";
        break;
    case Z_DATA_ERROR:
        errorText = "invalid or incomplete deflate data";
        break;
    case Z_MEM_ERROR:
        errorText ="out of memory";
        break;
    case Z_VERSION_ERROR:
        errorText = "zlib version mismatch!";
    }
    qCritical() << "zpipe: " << QString::fromStdString(errorText);
    throw std::runtime_error( std::string( "zlib: " ) + errorText );
}