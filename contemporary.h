#ifndef CONTEMPORARY_H
#define CONTEMPORARY_H

#include "contemporary_global.h"
#include <QCommonStyle>
#include <QPainter>
#include <QStyleOption>
#include <QDebug>
#include <QTimer>
#include <QGraphicsColorizeEffect>
#include <QVariantAnimation>

//Include controls
#include <QPushButton>
#include <QMainWindow>
#include <QTextEdit>
#include <QCheckBox>
#include <QAbstractItemView>
#include <QComboBox>
#include <QToolButton>
#include <QRadioButton>

class CONTEMPORARYSHARED_EXPORT Style : public QCommonStyle
{

public:
    Style();
    ~Style();

    void drawControl(ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget *widget) const override;
    void drawComplexControl(ComplexControl control, const QStyleOptionComplex* option, QPainter* painter, const QWidget *widget) const override;
    void drawPrimitive(PrimitiveElement primitive, const QStyleOption *option, QPainter *painter, const QWidget *widget) const override;
    QSize sizeFromContents(ContentsType ct, const QStyleOption *opt, const QSize &contentsSize, const QWidget *widget) const override;

    void polish(QWidget* widget) override;

    int styleHint(StyleHint sh, const QStyleOption *opt, const QWidget *w, QStyleHintReturn *shret) const override;
    int layoutSpacing(QSizePolicy::ControlType control1, QSizePolicy::ControlType control2, Qt::Orientation orientation, const QStyleOption *option, const QWidget *widget) const override;
    SubControl hitTestComplexControl(ComplexControl cc, const QStyleOptionComplex *option, const QPoint &pt, const QWidget *w) const override;
    void tintImage(QImage &image, QColor tint) const;
private:
    const QColor transparent = QColor::fromRgba64(0, 0, 0, 0);
    QColor col(int r, int g, int b) const;
    void scheduleRepaint(const QWidget* widget, int after = 1000 / 60) const;

    uint indetermiateProgressSection = 0;

};

//const QWidget* Style::selectedMenu = NULL;

#endif // CONTEMPORARY_H
