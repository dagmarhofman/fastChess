#ifndef FENMOVES_H
#define FENMOVES_H

#include <QObject>

class fenMoves
{
public:
    fenMoves();
    void readAllMoves();
private

    QVector<QString> fenPositions;
};

#endif // FENMOVES_H
