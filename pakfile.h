#ifndef _PAKFILE_H
#define _PAKFILE_H

#include <QByteArray>
#include <string>

class pakfile
{
private:
  /* data */
  QByteArray dataCompressed;
  QByteArray dataUncompressed;

public:
  static QByteArray zUncompress(const QByteArray &data);
  static QByteArray zCompress(const QByteArray &data);

public:
  pakfile(/* args */);
  ~pakfile();
};

#endif // _PAKFILE_H