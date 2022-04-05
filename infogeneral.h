#ifndef INFOGENERAL_H
#define INFOGENERAL_H

#include <QWidget>

class InfoGeneral : public QWidget
{
    Q_OBJECT

public:
    InfoGeneral(QWidget *parent = nullptr);
    ~InfoGeneral();

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // INFOGENERAL_H
