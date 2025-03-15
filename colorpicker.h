#ifndef COLORPICKER_H
#define COLORPICKER_H

#include <QWidget>
#include <QColorDialog>

class colorPicker : public QColorDialog
{
    Q_OBJECT
public:
    explicit colorPicker(QColorDialog  *parent = nullptr);

signals:

};

#endif // COLORPICKER_H
