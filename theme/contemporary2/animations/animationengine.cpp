#include "animationengine.h"

#include "pushbuttonanimation.h"
#include "viewitemanimation.h"
#include "menuitemanimation.h"
#include "radiobuttonanimation.h"
#include "checkboxanimation.h"

#include <QRadioButton>
#include <QCheckBox>
#include <QAbstractButton>
#include <QAbstractItemView>
#include <QMenu>
#include <QDebug>

AnimationPair::AnimationPair() {

}

AnimationEngine::AnimationEngine(QObject* parent) : QObject(parent) {

}

void AnimationEngine::registerWidget(QWidget* widget) {
    Animation* anim = nullptr;
    if (qobject_cast<QRadioButton*>(widget)) {
        anim = new RadioButtonAnimation(widget);
    } else if (qobject_cast<QCheckBox*>(widget)) {
        anim = new CheckboxAnimation(widget);
    } else if (qobject_cast<QAbstractButton*>(widget)) {
        anim = new PushButtonAnimation(widget);
    } else if (qobject_cast<QAbstractItemView*>(widget)) {
        anim = new ViewItemAnimation(widget);
    } else if (qobject_cast<QMenu*>(widget)) {
        anim = new MenuItemAnimation(widget);
    }

    if (anim) {
        AnimationPair pair;
        pair.widget = widget;
        pair.anim = anim;

        connect(widget, &QWidget::destroyed, this, [ = ] {
            this->deregisterWidget(widget);
        });

        animations.append(pair);
    }
}

void AnimationEngine::deregisterWidget(QWidget* widget) {
    for (AnimationPair a : qAsConst(animations)) {
        if (a.widget == widget) {
            a.anim->deleteLater();
            animations.removeOne(a);
            return;
        }
    }
}

Animation* AnimationEngine::a(const QWidget* widget) {
    for (AnimationPair a : qAsConst(animations)) {
        if (a.widget == widget) return a.anim;
    }
    return nullptr;
}
