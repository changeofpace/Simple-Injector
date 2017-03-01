#include "LazyLoadedComboBox.h"

LazyLoadedComboBox::LazyLoadedComboBox(QWidget *parent) : QComboBox(parent)
{
}

void LazyLoadedComboBox::mousePressEvent(QMouseEvent* event)
{
    emit clicked();
    QComboBox::mousePressEvent(event);
}
