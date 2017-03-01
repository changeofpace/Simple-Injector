#ifndef LAZYLOADEDCOMBOBOX_H
#define LAZYLOADEDCOMBOBOX_H

#include <QComboBox>

class LazyLoadedComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit LazyLoadedComboBox(QWidget *parent = 0);

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // LAZYLOADEDCOMBOBOX_H
