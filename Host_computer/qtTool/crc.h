#ifndef CRC_H
#define CRC_H

#include <QMainWindow>

quint16 getCrc16WithTail(quint8 * puchMsg, quint32 usDataLen);
quint16 getCrc16ExcludeTail(quint8 * puchMsg, quint32 usDataLen);
bool checkCrc16WithTail(quint8 *  puchMsg,quint32 usDataLen);
void appendCrc16WithTail(quint8 *puchMsg, quint32 usDataLen);



#endif // CRC_H
